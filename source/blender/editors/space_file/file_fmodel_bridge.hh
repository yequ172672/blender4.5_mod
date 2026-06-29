/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spfile
 *
 * Python-C++ bridge API for FModel File Browser integration.
 * Host configuration and refresh.
 */

#pragma once

struct bContext;
struct ImBuf;

/**
 * Refresh the file browser after Host state changes.
 * Called from Python when Host starts or stops.
 */
void FMODEL_filebrowser_refresh(struct bContext *C);

/* Type icon registration (called from Python). */
void FMODEL_filebrowser_register_type_icon(const char *type_name, const char *png_path);
ImBuf *FMODEL_filebrowser_get_type_icon(const char *type_name);
void FMODEL_filebrowser_clear_type_icons();
