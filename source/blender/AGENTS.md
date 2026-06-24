<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# blender

## Purpose
Core of Blender's C/C++ source code. Contains all major subsystems: data structures (DNA/RNA), kernel, editors, rendering, GPU abstraction, node systems, I/O, Python API, and the window manager. This is the largest and most architecturally significant directory in the Blender codebase.

## Key Files
| File | Purpose |
|------|---------|
| `CMakeLists.txt` | Top-level build definition for all `source/blender/` modules; enumerates DNA headers (SRC_DNA_INC) and wires subdirectory targets |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `animrig/` | Animation rigging system: keying, drivers, channels, NLA, and action library |
| `asset_system/` | Asset browser backend: asset catalogs, indexing, library management |
| `blendthumb/` | Standalone tool to generate `.blend` file thumbnail icons for OS file managers |
| `blenfont/` | Font loading, text shaping, and glyph rasterization (wraps FreeType/HarfBuzz) |
| `blenkernel/` | Core kernel: object creation, mesh operations, scene management, ID management, evaluation helpers |
| `blenlib/` | Low-level utility library (BLI_): math, data structures (lists, arrays, hash), memory, threading, path utils |
| `blenloader/` | `.blend` file read/write (versioning, undo, library linking) |
| `blenloader_core/` | Core file loading primitives shared between blenloader and runtime |
| `blentranslation/` | Internationalization: gettext wrappers, language catalogs, UI string translation |
| `bmesh/` | Mesh editing library: half-edge mesh structure, operators, selection, custom data |
| `compositor/` | Node-based compositor: image post-processing pipeline and node implementations |
| `cpucheck/` | CPU feature detection utility (SSE, AVX, etc.) for runtime capability checks |
| `datatoc/` | Build tool: converts data files (shaders, icons, fonts) into C source arrays for embedding |
| `depsgraph/` | Dependency graph: scene evaluation scheduling, relations, flush, and update tagging |
| `draw/` | Draw engine and management: orchestrates OpenGL/Vulkan rendering passes, overlays, engines (eevee, workbench, etc.) |
| `editors/` | All editor types and their space implementations (see editor list below) |
| `freestyle/` | Freestyle non-photorealistic line rendering: stroke graph, chaining, styling modules |
| `functions/` | Multi-function and lazy-function framework used by geometry nodes evaluation |
| `geometry/` | Geometry processing utilities: attribute handling, mesh operations, curve evaluation |
| `gpu/` | GPU abstraction layer: shader compilation, texture/framebuffer management, OpenGL/Vulkan backends |
| `ikplugin/` | Inverse kinematics solver plugins (iTaSC, standard bone IK) |
| `imbuf/` | Image buffer library: image I/O codecs (PNG, JPEG, OpenEXR, etc.), color management, thumbnails |
| `io/` | Import/export format modules: Alembic, USD, FBX, Collada, STL, PLY, OBJ, CSV, Grease Pencil |
| `makesdna/` | DNA system: C struct definitions that define Blender's data model; enables file forward/backward compatibility |
| `makesrna/` | RNA property system: exposes DNA structs as a dynamic property API with type info, UI hints, and accessors |
| `modifiers/` | Modifier stack implementations: subdivision, boolean, mirror, array, physics, geometry nodes, etc. |
| `nodes/` | Node system framework and implementations for shader, geometry, compositor, and texture nodes |
| `python/` | Python API (`bpy` module): RNA wrapping, BMesh Python API, mathutils, GPU module |
| `render/` | Render pipeline: internal renderer, render engine API, Hydra delegate, compositor integration |
| `sequencer/` | Video Sequence Editor (VSE) backend: strips, effects, proxy, audio mixing |
| `shader_fx/` | Shader effects for Grease Pencil: blur, pixelate, shadow, and other post-processing effects |
| `simulation/` | Simulation framework: node-based simulation data and evaluation |
| `windowmanager/` | Window manager: event loop, operators, keymaps, undo system, ghost platform abstraction, startup/exit |

### editors/ subdirectory summary
The `editors/` directory contains all Blender editor space types and editor-level operators:

| Editor Module | Purpose |
|---------------|---------|
| `space_view3d/` | 3D Viewport: navigation, snapping, gizmos, draw modes |
| `space_outliner/` | Outliner: scene hierarchy, data browsing |
| `space_node/` | Node Editor: visual node graph for shaders, compositing, geometry nodes |
| `space_image/` | Image/UV Editor: texture painting, UV editing |
| `space_sequencer/` | Video Sequence Editor: timeline, strip editing |
| `space_graph/` | Graph Editor: animation F-curve editing |
| `space_action/` | Action Editor: keyframe editing |
| `space_nla/` | NLA Editor: non-linear animation strip management |
| `space_text/` | Text Editor: script editing, running Python |
| `space_console/` | Python Console |
| `space_file/` | File Browser |
| `space_buttons/` | Properties Editor |
| `space_spreadsheet/` | Spreadsheet: inspect geometry attributes and instances |
| `space_userpref/` | Preferences Editor |
| `space_topbar/` | Top bar header |
| `space_statusbar/` | Status bar |
| `sculpt_paint/` | Sculpt and paint tools (brush, stroke, undo) |
| `transform/` | Transform system: translate, rotate, scale, snap, gizmo interaction |
| `mesh/` | Mesh editing operators (extrude, bevel, loop cut, etc.) |
| `curve/` | Curve editing operators |
| `curves/` | Curves (new hair/curves object) editing |
| `grease_pencil/` | Grease Pencil editing operators |
| `object/` | Object-level operators (join, apply, relations) |
| `armature/` | Armature/bone editing |
| `animation/` | Animation operators (keying, baking) |
| `physics/` | Physics simulation UI and operators |
| `asset/` | Asset browser operators |
| `geometry/` | Geometry editing utilities |

## For AI Agents

### Working In This Directory
- This is a large C/C++ codebase. Most modules follow the pattern: `module/intern/` (private implementation), `module/` (public headers), with a `CMakeLists.txt` at each level.
- DNA structs in `makesdna/` are the foundation -- changes here affect file compatibility and require versioning in `blenloader/`.
- RNA definitions in `makesrna/` expose DNA data to the UI and Python. Adding a new property requires both DNA and RNA changes.
- `blenkernel/` is the "glue" layer; it depends on nearly everything and is depended upon by nearly everything. Keep changes here minimal and well-tested.
- Node implementations in `nodes/` are split by domain: `shader/`, `geometry/`, `composite/`, `texture/`.

### Testing Requirements
- Unit tests live in `tests/` subdirectories within modules (e.g., `blenlib/tests/`, `bmesh/tests/`, `draw/tests/`).
- Geometry nodes have extensive regression tests in `nodes/geometry/tests/`.
- Build with CMake `WITH_GTESTS=ON` to enable Google Test targets.
- Python tests for the `bpy` API are in `tests/python/` (repo root level).

### Common Patterns
- **Header naming**: Public headers use `BKE_` (blenkernel), `BLI_` (blenlib), `DNA_` (makesdna), `RNA_` (makesrna), `ED_` (editors), `WM_` (windowmanager), `GPU_` (gpu), `DRW_` (draw) prefixes.
- **ID management**: All data-blocks derive from `ID`. Use `BKE_id_*` functions for creation, deletion, copying. Never allocate ID structs directly.
- **RNA property access**: Use `RNA_*_get/set` functions. Custom properties need RNA definitions in `makesrna/`.
- **Operator pattern**: Editors define operators via `WM_OT_*` structs with `exec`, `invoke`, `poll`, `modal` callbacks registered in `windowmanager/`.
- **Modifier pattern**: Each modifier in `modifiers/` implements a `ModifierTypeInfo` with `deform`, `modify_mesh`, `foreach_ID_link` callbacks.
- **Memory**: Use `MEM_mallocN` / `MEM_freeN` for heap allocations (tracks leaks). BLI provides `BLI_array_*`, `BLI_ghash_*`, etc.

## Dependencies
- **External**: OpenGL, Vulkan (via GPU module), Python, OpenEXR, OpenColorIO, Alembic, USD, FreeType, HarfBuzz, Embree, oneAPI/oneTBB
- **Internal (repo-level)**: `intern/` (Cycles, ghost, guardedalloc, mvbf, opensubdiv), `makesdna/` and `makesrna/` are built first as code-generation targets

<!-- MANUAL: -->
