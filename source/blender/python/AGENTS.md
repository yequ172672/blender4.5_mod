<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# Python Module (`source/blender/python/`)

Python API implementation providing the `bpy` module and its sub-modules. Bridges C/C++ Blender internals to Python via RNA wrapping, and exposes mathutils, bmesh, gpu, and generic utility modules.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `bmesh/` | BMesh Python API (`bmesh` module) - mesh editing in Python |
| `generic/` | Generic Python utilities (bgl, blf, bl_math, idprop, imbuf) |
| `gpu/` | GPU Python API (`gpu` module) - shaders, batches, framebuffers |
| `intern/` | Core `bpy` module implementation (operators, RNA, drivers) |
| `mathutils/` | Math types (Vector, Matrix, Quaternion, Euler, Color) and geometry utilities |

## Key Files

| File | Description |
|------|-------------|
| `BPY_extern.hh` | External C API for Python integration |
| `BPY_extern_clog.hh` | Python logging integration |
| `BPY_extern_python.hh` | Python runtime extern declarations |
| `BPY_extern_run.hh` | Python script execution API |
| `CMakeLists.txt` | Build configuration |

## Key Internal Files (`intern/`)

| File | Description |
|------|-------------|
| `bpy.cc` / `bpy.hh` | Main `bpy` module definition and initialization |
| `bpy_interface.cc` | Python interpreter initialization/exit |
| `bpy_interface_run.cc` | Script execution (run string, run file) |
| `bpy_operator.cc` | `bpy.ops` operator calling from Python |
| `bpy_rna.cc` | RNA-to-Python type wrapping (the core of `bpy.types`/`bpy.props`) |
| `bpy_rna_driver.cc` | Python driver expression evaluation |
| `bpy_driver.cc` | Driver system Python integration |
| `bpy_props.cc` | `bpy.props` property definitions (IntProperty, StringProperty, etc.) |
| `bpy_app_handlers.cc` | `bpy.app.handlers` (load_pre, save_post, etc.) |
| `bpy_app_timers.cc` | `bpy.app.timers` API |
| `bpy_msgbus.cc` | Python message bus integration |
| `bpy_gizmo_wrap.cc` | Python gizmo wrapper |
| `bpy_path.cc` | Path utilities for Python |
| `bpy_library_load.cc` | Library linking/appending from Python |

## Key Sub-module Files

| Module | Key File | Description |
|--------|----------|-------------|
| `bmesh` | `bmesh_py_api.cc` | `bmesh` module init and top-level API |
| `bmesh` | `bmesh_py_types.cc` | BMVert, BMEdge, BMFace Python types |
| `bmesh` | `bmesh_py_ops.cc` | `bmesh.ops` operator calling |
| `mathutils` | `mathutils.cc` | `mathutils` module init |
| `mathutils` | `mathutils_Vector.cc` | `mathutils.Vector` type |
| `mathutils` | `mathutils_Matrix.cc` | `mathutils.Matrix` type |
| `mathutils` | `mathutils_geometry.cc` | `mathutils.geometry` utilities |
| `gpu` | `gpu_py_api.cc` | `gpu` module init and API |
| `gpu` | `gpu_py_shader.cc` | `gpu.types.GPUShader` |
| `gpu` | `gpu_py_batch.cc` | `gpu.types.GPUBatch` |
| `generic` | `idprop_py_api.cc` | ID property Python access |
| `generic` | `bl_math_py_api.cc` | `bl_math` utility module |
| `generic` | `blf_py_api.cc` | `blf` font drawing module |

## Common Patterns

- **BPY_ prefix**: Public C API functions for Python integration use `BPY_` prefix
- **RNA wrapping**: `bpy_rna.cc` dynamically creates Python types from RNA type definitions
- **Property system**: `bpy.props` defines RNA properties accessible from Python panels/operators
- **Operator wrapping**: `bpy_operator.cc` wraps `WM_OT_*` operators as `bpy.ops.*` callable functions
- **C/Python type bridges**: Each mathutils type has a C struct + Python typeobject + accessors
- **Module init**: Each sub-module uses `PyModule_AddObject()` during `bpy` initialization

## For AI Agents

- The `intern/` directory contains the core `bpy` module - most Python API changes happen here
- RNA wrapping is the backbone: `bpy.types.*` and `bpy.data` are generated from RNA type metadata
- To add a new Python-accessible property, use `bpy.props.*` in `bpy_props.cc`
- `bpy_rna.cc` is one of the largest files - it maps RNA structs/properties to Python type objects
- `bmesh/` provides a parallel Python API for edit-mode mesh operations, independent of `bpy.data`
- `mathutils/` types are reference-counted and support `__mul__`, `__add__`, etc. via Python slots
- `gpu/` module exposes Blender's GPU module to Python for custom drawing in 3D viewport
- Driver expressions are evaluated via `bpy_driver.cc` with restricted Python builtins for security
