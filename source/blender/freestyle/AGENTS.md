<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# freestyle - Non-Photorealistic Line Rendering

Freestyle module for non-photorealistic rendering (NPR) with programmable line styles. Provides edge detection, stroke generation, and stylized line rendering. Public API uses the `FRS_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Core Freestyle implementation |
| `intern/application/` | Application layer and integration |
| `intern/blender_interface/` | Interface between Freestyle and Blender |
| `intern/geometry/` | Geometric primitives and operations |
| `intern/image/` | Image processing for stroke rendering |
| `intern/python/` | Python scripting API for line styles |
| `intern/scene_graph/` | Scene graph representation |
| `intern/stroke/` | Stroke generation and rendering |
| `intern/system/` | System utilities |
| `intern/view_map/` | View map - edge/feature detection from camera view |
| `intern/winged_edge/` | Winged-edge mesh data structure |

## Key Files

| File | Description |
|------|-------------|
| `FRS_freestyle.h` | Main public API - enable/disable Freestyle, scene setup |
| `FRS_precomp.h` | Precompiled header |
| `CMakeLists.txt` | Build configuration (large - many source files) |

## Common Patterns

- Freestyle has its own internal class hierarchy (separate from Blender DNA)
- View map generation: 3D scene -> 2D edge detection -> stroke creation
- Line styles are programmable via Python scripting or UI-based configuration
- Integration with Blender render pipeline through `blender_interface/`
- Uses winged-edge data structure for mesh topology analysis

## For AI Agents

- `FRS_freestyle.h` is the thin public API - most logic is in `intern/`
- `intern/view_map/` handles the core edge/feature detection algorithms
- `intern/stroke/` manages stroke creation from detected edges
- `intern/python/` exposes Freestyle to Python for custom line style scripting
- The module is largely self-contained with its own geometry and scene graph systems
- Freestyle operates as a post-processing pass after the main render
