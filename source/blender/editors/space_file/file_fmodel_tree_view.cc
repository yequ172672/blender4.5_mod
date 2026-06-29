/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spfile
 *
 * FModel folder tree panel for the TOOLS region of the file browser.
 * Displays path navigation buttons for UE asset paths.
 */

#include "file_fmodel_tree_view.hh"

#include "BLI_string.h"

#include "BKE_context.hh"

#include "BLT_translation.hh"

#include "DNA_space_types.h"

#include "ED_fileselect.hh"
#include "ED_screen.hh"

#include "RNA_access.hh"

#include "UI_interface.hh"
#include "UI_interface_icons.hh"

#include "WM_api.hh"
#include "WM_types.hh"

#include <cstring>

void file_fmodel_tree_view_draw(const bContext *C, uiLayout *layout)
{
  const SpaceFile *sfile = CTX_wm_space_file(C);
  if (!sfile || !sfile->params) {
    return;
  }

  const char *dir = sfile->params->dir;
  if (!dir || dir[0] == '\0') {
    return;
  }

  uiBlock *block = uiLayoutGetBlock(layout);
  int y = 0;

  /* Current path label. */
  uiDefBut(block,
           UI_BTYPE_LABEL,
           0,
           dir,
           0,
           y,
           UI_UNIT_X * 12,
           UI_UNIT_Y,
           nullptr,
           0.0f,
           0.0f,
           TIP_("Current FModel directory"));
  y -= UI_UNIT_Y + 2;

  /* Horizontal separator + spacing. */
  y -= UI_UNIT_Y / 2;

  /* "Go to /Game" button. */
  {
    uiBut *but = uiDefIconButO(block,
                               UI_BTYPE_BUT,
                               "FMODEL_OT_tree_nav",
                               WM_OP_INVOKE_DEFAULT,
                               ICON_HOME,
                               0,
                               y,
                               UI_UNIT_X * 4,
                               UI_UNIT_Y,
                               TIP_("Go to root /Game directory"));
    if (but) {
      PointerRNA *ptr = UI_but_operator_ptr_ensure(but);
      RNA_string_set(ptr, "directory", "/Game");
    }
  }

  /* Refresh button. */
  {
    uiDefIconButO(block,
                  UI_BTYPE_BUT,
                  "FMODEL_OT_refresh_fb",
                  WM_OP_INVOKE_DEFAULT,
                  ICON_FILE_REFRESH,
                  UI_UNIT_X * 4 + 4,
                  y,
                  UI_UNIT_X,
                  UI_UNIT_Y,
                  TIP_("Refresh file browser"));
  }

  y -= UI_UNIT_Y + 4;

  /* Draw path navigation. */
  {
    char dir_copy[FILE_MAX];
    STRNCPY(dir_copy, dir);

    const char *p = dir_copy;
    const char *seg_start = nullptr;
    char current_path[FILE_MAX] = "/";
    int path_len = 0;

    /* Process path segments. */
    if (*p == '/') {
      p++;
    }

    /* First segment label. */
    uiDefBut(block,
             UI_BTYPE_LABEL,
             0,
             "Folders:",
             0,
             y,
             UI_UNIT_X * 12,
             UI_UNIT_Y,
             nullptr,
             0.0f,
             0.0f,
             "");
    y -= UI_UNIT_Y + 1;

    /* Root "Game" button. */
    {
      uiBut *but = uiDefIconButO(block,
                                 UI_BTYPE_BUT,
                                 "FMODEL_OT_tree_nav",
                                 WM_OP_INVOKE_DEFAULT,
                                 ICON_FILE_FOLDER,
                                 0,
                                 y,
                                 UI_UNIT_X * 6,
                                 UI_UNIT_Y,
                                 TIP_("Navigate to /Game"));
      if (but) {
        PointerRNA *ptr = UI_but_operator_ptr_ensure(but);
        RNA_string_set(ptr, "directory", "/Game");
      }
    }
    y -= UI_UNIT_Y + 2;

    /* Follow the rest of the path. */
    while (*p) {
      seg_start = p;
      while (*p && *p != '/') {
        p++;
      }

      int seg_len = p - seg_start;
      if (seg_len > 0) {
        char seg[256];
        BLI_strncpy(seg, seg_start, std::min(seg_len + 1, 256));

        /* Append to current_path. */
        size_t cur_len = strlen(current_path);
        if (cur_len > 0 && current_path[cur_len - 1] != '/') {
          BLI_strncat(current_path, "/", FILE_MAX);
        }
        BLI_strncat(current_path, seg, FILE_MAX);

        /* Draw a navigation button for this segment. */
        uiBut *but = uiDefIconButO(block,
                                   UI_BTYPE_BUT,
                                   "FMODEL_OT_tree_nav",
                                   WM_OP_INVOKE_DEFAULT,
                                   ICON_FILE_FOLDER,
                                   0,
                                   y,
                                   UI_UNIT_X * 8,
                                   UI_UNIT_Y,
                                   TIP_("Navigate to this folder"));
        if (but) {
          PointerRNA *ptr = UI_but_operator_ptr_ensure(but);
          RNA_string_set(ptr, "directory", current_path);
          UI_but_drawflag_enable(but, UI_BUT_TEXT_LEFT);
        }

        y -= UI_UNIT_Y + 1;
      }

      if (*p == '/') {
        p++;
      }
    }
  }

  y -= UI_UNIT_Y;

  /* Info label. */
  uiDefBut(block,
           UI_BTYPE_LABEL,
           0,
           IFACE_("Click a folder to navigate"),
           0,
           y,
           UI_UNIT_X * 12,
           UI_UNIT_Y,
           nullptr,
           0.0f,
           0.0f,
           "");
}
