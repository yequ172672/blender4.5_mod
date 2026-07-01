/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spfile
 *
 * HTTP client and JSON utilities for the FModel HeadlessHost-backed file browser.
 * Uses raw sockets (Winsock on Windows) for localhost HTTP/1.1 communication.
 */

#pragma once

#include <cstddef>

#include "BLI_vector.hh"

struct FileList;

/** Entry parsed from the FModel /tree JSON response. */
struct FmodelEntry {
  char name[256];
  char asset_id[1024];
  char type[32];  /* Host type string ("StaticMesh", "Texture", "Folder", etc.) */
  bool is_folder;
};

/**
 * Check dir callback - always returns true for FModel (paths are virtual UE paths).
 */
bool filelist_checkdir_fmodel(const FileList *filelist,
                              char dirpath[/*FILE_MAX_LIBEXTRA*/ 1090],
                              const bool check_lib);

/**
 * Set the FModel HTTP host/port configuration.
 */
void FMODEL_filebrowser_set_host(const char *host, int port);

/**
 * HTTP GET /tree?path=<dir> from the FModel HeadlessHost.
 * Returns malloc'd (MEM_mallocN) string or nullptr on failure.
 * Caller must free with MEM_freeN.
 */
char *FMODEL_filebrowser_http_tree(const char *dirpath);

/**
 * Parse the JSON /tree response into a vector of FmodelEntry structs.
 * \param json: NUL-terminated JSON string.
 * \returns Vector of parsed entries (empty on error).
 */
blender::Vector<FmodelEntry> FMODEL_filebrowser_parse_tree_response(const char *json);

/**
 * Returns true if the FModel HeadlessHost is reachable.
 */
bool FMODEL_filebrowser_is_host_available(void);
