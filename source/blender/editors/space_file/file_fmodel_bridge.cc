/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spfile
 *
 * Python-C++ bridge API for FModel File Browser integration.
 * Host configuration, refresh and type icon management.
 */

#include "file_fmodel_bridge.hh"

#include "file_fmodel_http.hh"

#include "BKE_context.hh"
#include "BKE_screen.hh"

#include "DNA_screen_types.h"
#include "DNA_space_types.h"
#include "DNA_windowmanager_types.h"

#include "ED_fileselect.hh"
#include "ED_screen.hh"

#include "WM_api.hh"

#include "filelist.hh"

#include "IMB_imbuf.hh"
#include "IMB_imbuf_types.hh"

#include "BLI_listbase.h"
#include "BLI_map.hh"
#include "BLI_string.h"

#include <cstring>

/* -------------------------------------------------------------------- */
/** \name Type Icon Management
 * \{ */

static blender::Map<std::string, ImBuf *> g_type_icons;

void FMODEL_filebrowser_register_type_icon(const char *type_name, const char *png_path)
{
  if (!type_name || !png_path) {
    return;
  }

  ImBuf *ibuf = IMB_load_image_from_filepath(png_path, IB_byte_data);
  if (!ibuf) {
    return;
  }

  /* If re-registering, free old icon first. */
  if (ImBuf *const *old_ptr = g_type_icons.lookup_ptr(type_name)) {
    IMB_freeImBuf(*old_ptr);
  }

  g_type_icons.add(std::string(type_name), ibuf);
}

ImBuf *FMODEL_filebrowser_get_type_icon(const char *type_name)
{
  if (!type_name) {
    return nullptr;
  }
  if (const ImBuf *const *ptr = g_type_icons.lookup_ptr(type_name)) {
    return const_cast<ImBuf *>(*ptr);
  }
  return nullptr;
}

void FMODEL_filebrowser_clear_type_icons()
{
  for (auto item : g_type_icons.items()) {
    IMB_freeImBuf(item.value);
  }
  g_type_icons.clear();
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Refresh
 * \{ */

void FMODEL_filebrowser_refresh(bContext *C)
{
  wmWindowManager *wm = CTX_wm_manager(C);
  if (!wm) {
    return;
  }

  LISTBASE_FOREACH (wmWindow *, win, &wm->windows) {
    bScreen *screen = WM_window_get_active_screen(win);
    if (!screen) {
      continue;
    }
    LISTBASE_FOREACH (ScrArea *, area, &screen->areabase) {
      if (area->spacetype != SPACE_FILE) {
        continue;
      }
      SpaceFile *sfile = static_cast<SpaceFile *>(area->spacedata.first);
      if (!sfile || !sfile->params || sfile->params->type != FILE_FMODEL_HTTP) {
        continue;
      }
      if (sfile->files) {
        filelist_tag_force_reset(sfile->files);
      }
      ARegion *region = BKE_area_find_region_type(area, RGN_TYPE_WINDOW);
      if (region) {
        ED_region_tag_redraw(region);
      }
    }
  }
}

/** \} */
