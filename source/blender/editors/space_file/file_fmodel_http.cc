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

/* Forward declare the set_host from bridge for the linker.
 * Alternatively, define set_host here and have bridge.cc call it via header. */
void FMODEL_filebrowser_set_host(const char *host, int port)
{
  if (host) {
    SNPRINTF(fmodel_host, "%s", host);
  }
  fmodel_port = port;
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

  /* Set timeout. */
#ifdef _WIN32
  int timeout = 5000;
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
  setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));
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

  /* Find body after "\r\n\r\n". */
  char *body = strstr(response, "\r\n\r\n");
  if (!body) {
    MEM_freeN(response);
    return nullptr;
  }
  body += 4;

  char *result = BLI_strdup(body);
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
  while (*p && *p != '"' && i < out_max - 1) {
    if (*p == '\\') {
      p++;
      if (*p) {
        out[i++] = *p;
        p++;
      }
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

int FMODEL_filebrowser_parse_tree_response(const char *json,
                                            FmodelEntry *entries_out,
                                            int max_entries)
{
  if (!json || !*json || !entries_out || max_entries <= 0) {
    return -1;
  }

  /* Find "children" array. */
  const char *p = strstr(json, "\"children\"");
  if (!p) {
    return -1;
  }

  /* Find '[' after "children": */
  p = strchr(p, '[');
  if (!p) {
    return -1;
  }
  p++;

  int count = 0;

  while (p && *p && count < max_entries) {
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
        entries_out[count++] = entry;
      }
    }
  }

  return count;
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

