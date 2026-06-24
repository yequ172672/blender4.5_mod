<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# draw

## Purpose
Blender's draw engine and management module. Orchestrates the rendering pipeline for the 3D Viewport and other display contexts. Manages draw passes, cache extraction from mesh/curve/volume data, and delegates to specialized draw engines (EEVEE, Workbench, Overlay, etc.) for actual GPU submission.

## Key Files
| File | Purpose |
|------|---------|
| `CMakeLists.txt` | Build definition; enumerates all draw module sources, shaders, and engine targets |
| `DRW_engine.hh` | Public API for draw engine registration, initialization, and draw callbacks |
| `DRW_pbvh.hh` | PBVH (Parallel BVH) drawing interface for sculpt mode |
| `DRW_select_buffer.hh` | Selection buffer API for GPU-based object/element picking |
| `intern/draw_manager.hh` | Core draw manager: orchestrates passes, engines, and view setup per frame |
| `intern/draw_pass.hh` | Draw pass abstraction: groups draw commands for batched submission |
| `intern/draw_command.hh` | Draw command recording and sorting infrastructure |
| `intern/draw_cache.hh` | Mesh/object cache management for efficient GPU data upload |
| `intern/draw_cache_extract_mesh.cc` | Mesh attribute extraction (positions, normals, UVs, etc.) into GPU buffers |
| `intern/draw_shader.cc` | Shader loading and management for draw module built-in shaders |
| `intern/draw_view.cc` | View/projection matrix management and culling |
| `intern/draw_resource.cc` | Per-object resource management (transforms, object infos) |
| `intern/DRW_render.hh` | Internal rendering utilities shared across engines |
| `intern/DRW_gpu_wrapper.hh` | RAII GPU resource wrappers (textures, buffers, framebuffers) |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `engines/` | Draw engine implementations, each handling a specific rendering mode |
| `engines/eevee/` | EEVEE real-time PBR renderer: lighting, shadows, SSR, AO, volumetrics, DOF, film |
| `engines/workbench/` | Workbench solid/matcap renderer: fast viewport shading with cavity, outline, DOF effects |
| `engines/overlay/` | Overlay engine: gizmos, grid, armature, bounds, cursors, wireframes, annotations |
| `engines/compositor/` | Viewport compositor engine: real-time post-processing in the 3D viewport |
| `engines/gpencil/` | Grease Pencil draw engine for legacy grease pencil objects |
| `engines/image/` | Image draw engine for the Image/UV Editor display |
| `engines/select/` | Selection engine: GPU-based selection ID rendering pass |
| `engines/external/` | External render engine viewport integration bridge |
| `intern/` | Core draw infrastructure: manager, passes, cache, shaders, resource management |
| `intern/mesh_extractors/` | Mesh data extractors: convert BMesh/Mesh data into GPU vertex/index buffers |
| `intern/shaders/` | GLSL shaders for draw module: visibility, resource finalization, subdivision, color management |
| `tests/` | Unit tests for draw passes, EEVEE integration |

## For AI Agents

### Working In This Directory
- Public headers use the `DRW_` prefix. Internal headers in `intern/` use `draw_` prefix.
- Draw engines register themselves via `DRW_engine_register()` and implement callbacks for `init`, `draw`, `view_update`, `cache_init`.
- Mesh cache extraction uses a modular extractor pattern: each `intern/mesh_extractors/extract_mesh_vbo_*.cc` file handles one vertex attribute type.
- GPU resource wrappers in `intern/DRW_gpu_wrapper.hh` provide RAII `draw::Texture`, `draw::StorageBuffer`, etc. -- prefer these over raw GPU_ calls.
- Shaders use Blender's shader create info system (`GPU_shader_create_info`); GLSL files in `intern/shaders/` follow `draw_*_info.hh` naming for create info definitions.

### Common Patterns
- **Engine lifecycle**: `engine_init` -> `engine_cache_init` (populate draw groups) -> `engine_draw` (submit passes) -> `engine_free`.
- **Draw groups**: Objects are grouped into `DrawGroup` instances for batched rendering. Use `DRW_shgroup_*` API.
- **Pass submission**: Create passes with `drw_pass()`, add draw commands, submit via `DRW_draw_pass()`.
- **PBVH drawing**: Sculpt mode uses PBVH for efficient partial mesh updates; see `draw_pbvh.cc` and `draw_sculpt.cc`.

### Testing Requirements
- Tests in `tests/` use Google Test. Build with `WITH_GTESTS=ON`.
- `draw_pass_test.cc` tests pass creation and command recording.
- `eevee_test.cc` tests EEVEE engine integration.

## Dependencies
- **Internal**: `gpu/` (GPU abstraction), `blenkernel/` (mesh/object data), `bmesh/` (edit mesh), `makesdna/`/`makesrna/` (data types)
- **External**: OpenGL/Vulkan (via GPU module), shader compiler
