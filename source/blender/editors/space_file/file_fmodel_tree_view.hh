/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spfile
 *
 * FModel folder tree view for the TOOLS region of the file browser.
 * Shows the UE directory hierarchy and allows navigating the file browser.
 */

#pragma once

struct bContext;
struct uiLayout;

/**
 * Draw handler for the FModel folder tree panel in the TOOLS region.
 * Creates a folder tree interface from the current FModel directory listing.
 */
void file_fmodel_tree_view_draw(const bContext *C, uiLayout *layout);
