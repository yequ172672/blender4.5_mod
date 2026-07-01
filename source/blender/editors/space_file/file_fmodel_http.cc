/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spfile
 *
 * HTTP client and JSON utilities for the FModel HeadlessHost-backed file browser.
 * Uses raw sockets (Winsock on Windows) for localhost HTTP/1.1 communication.
 */

#include "file_fmodel_http.hh"

#include "BLI_listbase.h"
#include "BLI_string.h"
#include "BLI_vector.hh"

#include "DNA_space_enums.h"

#include "MEM_guardedalloc.h"

#include "filelist.hh"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <arpa/inet.h>
#  include <netdb.h>
#  include <netinet/in.h>
#  include <sys/socket.h>
#  include <unistd.h>
#  define SOCKET int
#  define INVALID_SOCKET -1
#  define closesocket close
#endif

/* -------------------------------------------------------------------- */
/** \name Host Configuration
 * \{ */

/** Host address and port, accessed via FMODEL_filebrowser_set_host(). */
static char fmodel_host[64] = "127.0.0.1";
static int fmodel_port = 6170;

static bool fmodel_http_header_contains(const char *headers,
                                        const char *name,
                                        const char *value)
{
  if (!headers || !name || !value) {
    return false;
  }

  const size_t name_len = strlen(name);
  const char *line = headers;
  while (line && *line) {
    const char *line_end = strstr(line, "\r\n");
    if (!line_end) {
      line_end = line + strlen(line);
    }
    if (BLI_strncasecmp(line, name, name_len) == 0 && line[name_len] == ':') {
      const char *header_value = line + name_len + 1;
      while (header_value < line_end && (*header_value == ' ' || *header_value == '\t')) {
        header_value++;
      }
      const size_t value_len = strlen(value);
      for (const char *p = header_value; p + value_len <= line_end; p++) {
        if (BLI_strncasecmp(p, value, value_len) == 0) {
          return true;
        }
      }
    }
    line = (*line_end == '\0') ? nullptr : line_end + 2;
  }

  return false;
}

static char *fmodel_http_decode_chunked_body(const char *body)
{
  if (!body) {
    return nullptr;
  }

  const char *p = body;
  size_t decoded_len = 0;
  char *decoded = static_cast<char *>(MEM_mallocN(1, "fmodel_http_chunked_body"));
  decoded[0] = '\0';

  while (*p) {
    char *end = nullptr;
    const long chunk_size = strtol(p, &end, 16);
    if (end == p || chunk_size < 0) {
      MEM_freeN(decoded);
      return nullptr;
    }

    const char *line_end = strstr(end, "\r\n");
    if (!line_end) {
      MEM_freeN(decoded);
      return nullptr;
    }
    p = line_end + 2;

    if (chunk_size == 0) {
      break;
    }

    decoded = static_cast<char *>(
        MEM_reallocN(decoded, decoded_len + size_t(chunk_size) + 1));
    memcpy(decoded + decoded_len, p, size_t(chunk_size));
    decoded_len += size_t(chunk_size);
    decoded[decoded_len] = '\0';

    p += chunk_size;
    if (p[0] == '\r' && p[1] == '\n') {
      p += 2;
    }
    else {
      MEM_freeN(decoded);
      return nullptr;
    }
  }

  return decoded;
}

/* Forward declare the set_host from bridge for the linker.
 * Alternatively, define set_host here and have bridge.cc call it via header. */
void FMODEL_filebrowser_set_host(const char *host, int port)
{
  if (host) {
    /* Security: only allow localhost to prevent SSRF. */
    if (strcmp(host, "127.0.0.1") != 0 && strcmp(host, "localhost") != 0 &&
        strcmp(host, "::1") != 0) {
      fprintf(stderr, "FModel: rejected non-localhost host '%s'\n", host);
      return;
    }
    SNPRINTF(fmodel_host, "%s", host);
  }
  if (port > 0 && port <= 65535) {
    fmodel_port = port;
  }
}

bool FMODEL_filebrowser_is_host_available(void)
{
#ifdef _WIN32
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
    return false;
  }
#endif

  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET) {
#ifdef _WIN32
    WSACleanup();
#endif
    return false;
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(fmodel_port);
  addr.sin_addr.s_addr = inet_addr(fmodel_host);
  if (addr.sin_addr.s_addr == INADDR_NONE) {
    struct hostent *he = gethostbyname(fmodel_host);
    if (!he) {
      closesocket(sock);
#ifdef _WIN32
      WSACleanup();
#endif
      return false;
    }
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
  }

  int result = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  closesocket(sock);
#ifdef _WIN32
  WSACleanup();
#endif
  return result == 0;
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name HTTP Client (Winsock)
 * \{ */

/**
 * Perform an HTTP GET request to the FModel HeadlessHost.
 * Returns malloc'd response body string, or nullptr on failure.
 * Caller must free with MEM_freeN.
 */
static char *http_get(const char *path)
{
#ifdef _WIN32
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
    return nullptr;
  }
#endif

  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET) {
#ifdef _WIN32
    WSACleanup();
#endif
    return nullptr;
  }

  /* Set receive / send timeout (cross-platform). */
#ifdef _WIN32
  int timeout = 5000;
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
  setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));
#else
  struct timeval tv;
  tv.tv_sec = 5;
  tv.tv_usec = 0;
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
  setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#endif

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(fmodel_port);
  addr.sin_addr.s_addr = inet_addr(fmodel_host);
  if (addr.sin_addr.s_addr == INADDR_NONE) {
    struct hostent *he = gethostbyname(fmodel_host);
    if (!he) {
      closesocket(sock);
#ifdef _WIN32
      WSACleanup();
#endif
      return nullptr;
    }
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
  }

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    closesocket(sock);
#ifdef _WIN32
    WSACleanup();
#endif
    return nullptr;
  }

  /* Build HTTP/1.1 GET request. */
  char request[2048];
  SNPRINTF(request,
           "GET %s HTTP/1.1\r\n"
           "Host: %s:%d\r\n"
           "Connection: close\r\n"
           "\r\n",
           path,
           fmodel_host,
           fmodel_port);

  if (send(sock, request, strlen(request), 0) < 0) {
    closesocket(sock);
#ifdef _WIN32
    WSACleanup();
#endif
    return nullptr;
  }

  /* Read response. */
  char buf[4096];
  char *response = (char *)MEM_mallocN(1, "fmodel_http_response");
  response[0] = '\0';
  int total_len = 0;
  int bytes_read;

  while ((bytes_read = recv(sock, buf, sizeof(buf) - 1, 0)) > 0) {
    buf[bytes_read] = '\0';
    total_len += bytes_read;
    response = (char *)MEM_reallocN(response, total_len + 1);
    memcpy(response + (total_len - bytes_read), buf, bytes_read);
    response[total_len] = '\0';
  }

  closesocket(sock);
#ifdef _WIN32
  WSACleanup();
#endif

  if (total_len == 0) {
    MEM_freeN(response);
    return nullptr;
  }

  /* Verify HTTP status line. Expect "HTTP/1.1 2xx" or "HTTP/1.0 2xx". */
  {
    /* Need at least "HTTP/1.1 200" (12 chars) before reading response+9. */
    if (total_len < 12) {
      MEM_freeN(response);
      return nullptr;
    }
    if (strncmp(response, "HTTP/", 5) != 0) {
      MEM_freeN(response);
      return nullptr;
    }
    /* Find first space, then parse status code (robust against HTTP version length). */
    const char *space = strchr(response, ' ');
    int status_code = space ? atoi(space + 1) : 0;
    if (status_code < 200 || status_code >= 300) {
      MEM_freeN(response);
      return nullptr;
    }
  }

  /* Find body after "\r\n\r\n". */
  char *body = strstr(response, "\r\n\r\n");
  if (!body) {
    MEM_freeN(response);
    return nullptr;
  }
  *body = '\0';
  body += 4;

  char *result = nullptr;
  if (fmodel_http_header_contains(response, "Transfer-Encoding", "chunked")) {
    result = fmodel_http_decode_chunked_body(body);
  }
  else {
    result = BLI_strdup(body);
  }
  MEM_freeN(response);
  return result;
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name HTTP Tree API
 * \{ */

/**
 * Percent-encode a path for use in a URL query parameter.
 * Encodes '/' as %2F, space as %20, etc.
 * \param src: Input string (UE path like "/Game/Characters/").
 * \param dst: Output buffer for encoded path.
 * \param dst_size: Size of dst buffer.
 * \returns Pointer to dst, or nullptr on buffer overflow.
 */
static char *fmodel_url_encode(const char *src, char *dst, int dst_size)
{
  if (!src || !dst || dst_size <= 0) {
    return nullptr;
  }

  int di = 0;
  for (int si = 0; src[si] && di < dst_size - 4; si++) {
    const char c = src[si];
    /* Unreserved characters per RFC 3986: A-Z a-z 0-9 - _ . ~ */
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~')
    {
      dst[di++] = c;
    }
    else {
      /* Percent-encode: %XX */
      BLI_snprintf(dst + di, 4, "%%%02X", (unsigned char)c);
      di += 3;
    }
  }
  dst[di] = '\0';
  return dst;
}

char *FMODEL_filebrowser_http_tree(const char *dirpath)
{
  char encoded[4096];
  if (!fmodel_url_encode(dirpath, encoded, sizeof(encoded))) {
    return nullptr;
  }

  char path[4096];
  SNPRINTF(path, "/tree?path=%s", encoded);
  return http_get(path);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name JSON Parser
 * \{ */

static const char *json_skip_ws(const char *p)
{
  while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')) {
    p++;
  }
  return p;
}

static const char *json_parse_string(const char *p, char *out, int out_max)
{
  p = json_skip_ws(p);
  if (*p != '"') {
    return nullptr;
  }
  p++;
  int i = 0;
  while (*p && i < out_max - 1) {
    if (*p == '\\') {
      p++;
      if (!*p) {
        break;
      }
      /* Handle standard JSON escape sequences. */
      switch (*p) {
        case '"':
        case '\\':
        case '/':
          out[i++] = *p;
          break;
        case 'n':
          out[i++] = '\n';
          break;
        case 't':
          out[i++] = '\t';
          break;
        case 'r':
          out[i++] = '\r';
          break;
        case 'b':
          out[i++] = '\b';
          break;
        case 'f':
          out[i++] = '\f';
          break;
        default:
          /* Unknown escape: keep literal character. */
          out[i++] = *p;
          break;
      }
      p++;
    }
    else if (*p == '"') {
      break;
    }
    else {
      out[i++] = *p;
      p++;
    }
  }
  out[i] = '\0';
  if (*p == '"') {
    p++;
  }
  return p;
}

static const char *json_skip_value(const char *p)
{
  p = json_skip_ws(p);
  if (!*p) {
    return nullptr;
  }
  if (*p == '"') {
    p++;
    while (*p) {
      if (*p == '\\' && *(p + 1)) {
        p += 2;  /* Skip escaped character */
        continue;
      }
      if (*p == '"') {
        p++;
        break;
      }
      p++;
    }
  }
  else if (*p == '{' || *p == '[') {
    char closer = (*p == '{') ? '}' : ']';
    int depth = 1;
    p++;
    while (*p && depth > 0) {
      if (*p == '"') {
        /* Skip string content to avoid counting braces inside strings. */
        p++;
        while (*p) {
          if (*p == '\\' && *(p + 1)) {
            p += 2;
            continue;
          }
          if (*p == '"') {
            p++;
            break;
          }
          p++;
        }
        if (!*p) {
          break;
        }
        continue;
      }
      if (*p == closer) {
        depth--;
      }
      else if (*p == '{' || *p == '[') {
        depth++;
      }
      p++;
    }
  }
  else {
    while (*p && *p != ',' && *p != ']' && *p != '}' && *p != ':' && *p != ' ') {
      p++;
    }
  }
  return p;
}

blender::Vector<FmodelEntry> FMODEL_filebrowser_parse_tree_response(const char *json)
{
  blender::Vector<FmodelEntry> entries;

  if (!json || !*json) {
    return entries;
  }

  /* Find "children" array. */
  const char *p = strstr(json, "\"children\"");
  if (!p) {
    return entries;
  }

  /* Find '[' after "children": */
  p = strchr(p, '[');
  if (!p) {
    return entries;
  }
  p++;

  while (p && *p) {
    p = json_skip_ws(p);
    if (*p == ']' || *p == '\0') {
      break;
    }
    if (*p == ',') {
      p++;
      continue;
    }
    if (*p == '{') {
      p++;

      FmodelEntry entry;
      memset(&entry, 0, sizeof(entry));
      entry.is_folder = false;

      while (*p && *p != '}') {
        p = json_skip_ws(p);
        if (*p == ',') {
          p++;
          continue;
        }

        char key[64] = "";
        p = json_parse_string(p, key, sizeof(key));
        if (!p) {
          break;
        }
        p = json_skip_ws(p);
        if (*p == ':') {
          p++;
        }

        if (STREQ(key, "name")) {
          p = json_parse_string(p, entry.name, sizeof(entry.name));
        }
        else if (STREQ(key, "id")) {
          p = json_parse_string(p, entry.asset_id, sizeof(entry.asset_id));
        }
        else if (STREQ(key, "type")) {
          char type[64] = "";
          p = json_parse_string(p, type, sizeof(type));
          entry.is_folder = STREQ(type, "Folder");
          BLI_strncpy(entry.type, type, sizeof(entry.type));
        }
        else {
          p = json_skip_value(p);
        }
        if (!p) {
          break;
        }
      }
      if (p && *p == '}') {
        p++;
      }

      if (!p) {
        break;
      }

      if (entry.name[0] != '\0') {
        entries.append(entry);
      }
    }
  }

  return entries;
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Directory Validation
 * \{ */

bool filelist_checkdir_fmodel(const FileList * /*filelist*/,
                              char /*dirpath*/[FILE_MAX_LIBEXTRA],
                              const bool /*check_lib*/)
{
  /* FModel paths are virtual UE paths - always accept them. */
  return true;
}

/** \} */
