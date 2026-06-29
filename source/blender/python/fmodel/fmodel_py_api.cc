/* SPDX-FileCopyrightText: 2024 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup fmodel_py
 *
 * Python C module wrapping the FModel C++ bridge API (_fmodel_filebrowser).
 * Exposes set_host, is_host_available, register_icon, clear_icons, and refresh
 * so that Python code can configure the FModel file browser without bpy.
 */

#include <Python.h>

#include "file_fmodel_bridge.hh"
#include "file_fmodel_http.hh"

#include "bpy_capi_utils.hh"

static PyObject *py_fmodel_set_host(PyObject * /*self*/, PyObject *args)
{
  const char *host;
  int port;
  if (!PyArg_ParseTuple(args, "si", &host, &port)) {
    return nullptr;
  }
  FMODEL_filebrowser_set_host(host, port);
  Py_RETURN_NONE;
}

static PyObject *py_fmodel_is_host_available(PyObject * /*self*/, PyObject * /*args*/)
{
  return PyBool_FromLong(FMODEL_filebrowser_is_host_available());
}

static PyObject *py_fmodel_register_icon(PyObject * /*self*/, PyObject *args)
{
  const char *type_name;
  const char *png_path;
  if (!PyArg_ParseTuple(args, "ss", &type_name, &png_path)) {
    return nullptr;
  }
  FMODEL_filebrowser_register_type_icon(type_name, png_path);
  Py_RETURN_NONE;
}

static PyObject *py_fmodel_clear_icons(PyObject * /*self*/, PyObject * /*args*/)
{
  FMODEL_filebrowser_clear_type_icons();
  Py_RETURN_NONE;
}

static PyObject *py_fmodel_refresh(PyObject * /*self*/, PyObject * /*args*/)
{
  bContext *C = BPY_context_get();
  if (C) {
    FMODEL_filebrowser_refresh(C);
  }
  Py_RETURN_NONE;
}

static PyMethodDef fmodel_methods[] = {
    {"set_host", py_fmodel_set_host, METH_VARARGS, "Set the FModel HeadlessHost address and port"},
    {"is_host_available",
     py_fmodel_is_host_available,
     METH_NOARGS,
     "Check if the FModel HeadlessHost is reachable"},
    {"register_icon",
     py_fmodel_register_icon,
     METH_VARARGS,
     "Register a type icon from a PNG file path"},
    {"clear_icons",
     py_fmodel_clear_icons,
     METH_NOARGS,
     "Clear all registered type icons"},
    {"refresh",
     py_fmodel_refresh,
     METH_NOARGS,
     "Refresh the FModel file browser (force reset + redraw all spaces)"},
    {nullptr, nullptr, 0, nullptr},
};

static struct PyModuleDef fmodel_module = {
    PyModuleDef_HEAD_INIT,
    "_fmodel_filebrowser",
    "FModel file browser bridge API",
    -1,
    fmodel_methods,
};

PyMODINIT_FUNC PyInit__fmodel_filebrowser(void)
{
  return PyModule_Create(&fmodel_module);
}
