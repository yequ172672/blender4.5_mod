# SPDX-FileCopyrightText: 2024 Blender Authors
#
# SPDX-License-Identifier: GPL-2.0-or-later

set(INC
  .
  ../../editors/space_file
  ../../editors/include
  ..
  ../intern
)

set(INC_SYS
  ${PYTHON_INCLUDE_DIRS}
)

set(SRC
  fmodel_py_api.cc
)

set(LIB
  PRIVATE bf::blenkernel
  PRIVATE bf::blenlib
  PRIVATE bf::dna
  PRIVATE bf::imbuf
  PRIVATE bf::intern::guardedalloc
  bf_editor_space_api
  bf_editor_space_file
  PRIVATE bf::windowmanager

  ${PYTHON_LINKFLAGS}
  ${PYTHON_LIBRARIES}
)

blender_add_lib(bf_python_fmodel "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
