<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md — BMesh

BMesh is Blender's core mesh editing data structure. It supports n-gons, custom data layers, and topological operations. All public API uses the `BM_` prefix.

## Key Files

| File | Purpose |
|------|---------|
| `bmesh.hh` | Main public header — includes all BMesh sub-headers |
| `bmesh_class.hh` | Core data types: `BMesh`, `BMVert`, `BMEdge`, `BMFace`, `BMLoop` |
| `bmesh_tools.hh` | Public header for the `tools/` high-level operations |
| `CMakeLists.txt` | Build configuration |

## Subdirectories

| Directory | Purpose |
|-----------|---------|
| `intern/` | Core BMesh implementation — mesh construction, topology, iterators, queries, operators, normals, tessellation, logging |
| `operators/` | Low-level BMesh operators (BMO) — each file implements one operator (bevel, extrude, dissolve, subdivide, etc.) |
| `tools/` | High-level editing tools built on BMesh — bevel, boolean, decimate, triangulate, bisect, wireframe, path operations |
| `tests/` | Unit tests (`bmesh_core_test.cc`) |

## Architecture

### Core Internals (`intern/`)

- **Topology**: `bmesh_core.cc` — vertex/edge/face creation and deletion; `bmesh_structure.cc` — edge/loop rewiring
- **Queries**: `bmesh_query.cc` / `bmesh_query_inline.hh` — topology lookups (adjacent faces, edge sharing, manifold tests)
- **Iterators**: `bmesh_iterators.cc` — iteration over mesh elements with filtering
- **Walkers**: `bmesh_walkers.cc` / `bmesh_walkers_impl.cc` — graph traversal (flood fill, shells, islands, hoops)
- **Operators**: `bmesh_operators.cc` / `bmesh_operator_api.hh` — BMO execution engine and slot system
- **Mesh conversion**: `bmesh_mesh_convert.cc` — to/from `Mesh` and `MVert/MEdge/MPoly`
- **Normals**: `bmesh_mesh_normals.cc` — custom normals and auto-smooth
- **Tessellation**: `bmesh_mesh_tessellate.cc` — triangulation for rendering
- **Marking**: `bmesh_marking.cc` — selection and history management
- **Logging**: `bmesh_log.cc` — undo/redo logging for mesh edits

### Operators (`operators/`)

Each file is a self-contained BMO operator (prefixed `bmo_`). Key operators:
- `bmo_bevel.cc`, `bmo_extrude.cc`, `bmo_subdivide.cc`, `bmo_dissolve.cc`
- `bmo_hull.cc` (convex hull), `bmo_mirror.cc`, `bmo_triangulate.cc`
- `bmo_fill_grid.cc`, `bmo_fill_edgeloop.cc`, `bmo_bridge.cc`

### Tools (`tools/`)

Higher-level tools (prefixed `bmesh_`) that compose BMO operators and BMesh queries:
- `bmesh_bevel.cc`, `bmesh_boolean.cc`, `bmesh_decimate_*.cc`
- `bmesh_intersect.cc`, `bmesh_bisect_plane.cc`
- `bmesh_triangulate.cc`, `bmesh_wireframe.cc`
- `bmesh_path.cc` / `bmesh_path_uv.cc` — shortest-path selection

## Common Patterns

- Elements use a flag system (`BM_ELEM_SELECT`, `BM_ELEM_HIDDEN`, etc.)
- Custom data layers accessed via `CustomData` on verts/edges/faces/loops
- Operator slots use `BMO_OP_SLOT_*` macros for input/output
- Inline functions in `*_inline.hh` files for hot-path performance

## Dependencies

- `source/blender/blenlib/` — BLI utility types and math
- `source/blender/makesdna/` — DNA struct definitions (Mesh, MVert, etc.)
- `source/blender/blenkernel/` — BKE mesh operations
