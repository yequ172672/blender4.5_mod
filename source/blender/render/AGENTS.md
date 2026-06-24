<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# render

## Purpose
Blender's internal render pipeline and render engine integration layer. Provides the `RE_` prefix API for render result management, render baking, texture evaluation, and compositor integration. This is the orchestration layer -- not a renderer itself. It coordinates external render engines (Cycles, EEVEE) and manages the render pipeline from scene to final image.

## Key Files
| File | Purpose |
|------|---------|
| `CMakeLists.txt` | Build definition for render module |
| `RE_pipeline.h` | Main render pipeline API: render result creation, layer/pass management, display, job scheduling |
| `RE_engine.h` | Render engine API: base class and callbacks for render engines (external renderer integration point) |
| `RE_bake.h` | Bake API: texture baking for normals, AO, displacement, emission, etc. |
| `RE_compositor.hh` | Compositor integration: triggers node compositor evaluation on render results |
| `RE_texture.h` | Texture evaluation API: procedural and image texture sampling at render time |
| `RE_texture_margin.h` | Texture margin/UV dilation for bake edge artifacts |
| `RE_multires_bake.h` | Multiresolution baking: bake from sculpt subdivision levels |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `intern/` | Internal implementation: pipeline, engine, bake, render result, texture evaluation, z-buffer |
| `hydra/` | USD Hydra render delegate: allows Blender scenes to be rendered by Hydra-compatible renderers |

### intern/ key files
| File | Purpose |
|------|---------|
| `intern/pipeline.cc` | Core render pipeline: render loop, result accumulation, display callbacks |
| `intern/pipeline.hh` | Internal pipeline types and helpers |
| `intern/engine.cc` | Render engine base implementation and dispatch |
| `intern/render_result.cc` | RenderResult, RenderLayer, RenderPass data management |
| `intern/render_types.cc` | Internal render type definitions |
| `intern/bake.cc` | Bake implementation: UV-based texture baking workflow |
| `intern/compositor.cc` | Compositor invocation from render pipeline |
| `intern/texture_image.cc` | Image texture evaluation |
| `intern/texture_procedural.cc` | Procedural texture evaluation (noise, voronoi, etc.) |
| `intern/texture_pointdensity.cc` | Point density texture evaluation |
| `intern/texture_margin.cc` | UV margin/dilation algorithm |
| `intern/multires_bake.cc` | Multires baking implementation |
| `intern/zbuf.cc` | Z-buffer utilities for depth operations |
| `intern/tile_highlight.cc` | Render tile visualization for progress display |
| `intern/initrender.cc` | Render initialization helpers |

### hydra/ key files
| File | Purpose |
|------|---------|
| `hydra/engine.cc` | Hydra render engine integration in Blender |
| `hydra/final_engine.cc` | Final (offline) render via Hydra |
| `hydra/viewport_engine.cc` | Viewport (interactive) render via Hydra |
| `hydra/preview_engine.cc` | Material preview render via Hydra |
| `hydra/camera.cc` | Camera conversion from Blender to Hydra |
| `hydra/render_task_delegate.cc` | Hydra render task setup and delegation |
| `hydra/light_tasks_delegate.cc` | Hydra light task delegation |
| `hydra/python.cc` | Python bindings for Hydra engine selection |

## For AI Agents

### Working In This Directory
- All public APIs use the `RE_` prefix. Public headers are in the module root.
- Internal implementation lives in `intern/` with `render_` prefix for types and plain names for functions.
- The Hydra delegate in `hydra/` bridges Blender's scene to USD Hydra's render index, enabling third-party renderers that support the Hydra protocol.
- This module does NOT contain Cycles -- that lives in `intern/cycles/` at the repo root.

### Common Patterns
- **Render job lifecycle**: `RE_NewRender()` -> `RE_engine_begin()` -> render passes -> `RE_engine_end()` -> `RE_FreeRenderResult()`.
- **Render result structure**: `RenderResult` contains `RenderLayer` list, each with `RenderPass` list (Combined, Depth, Normal, etc.).
- **Engine integration**: External engines implement `RenderEngine` callbacks registered via RNA. The `RE_engine.h` API defines the contract.
- **Bake workflow**: `RE_bake_mask_pixels()` -> iterate UV islands -> sample shader at each texel -> write to image.
- **Compositor hook**: `RE_compositor.hh` provides `CompositorJob` that runs the node compositor on completed render results.

### Testing Requirements
- No dedicated test directory in this module. Render pipeline testing is done through integration tests at the application level.

## Dependencies
- **Internal**: `blenkernel/` (scene/object data), `compositor/` (post-processing), `draw/` (viewport rendering), `gpu/` (GPU resources), `imbuf/` (image buffer I/O), `makesdna/`/`makesrna/` (data/property system)
- **External**: USD (for Hydra delegate), OpenColorIO (color management)
