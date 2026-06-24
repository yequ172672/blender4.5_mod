<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# compositor

## Purpose
Blender's node-based compositor for image post-processing. Evaluates compositor node trees to produce final images from render results. Supports both real-time viewport compositing and offline render compositing. All operations are GPU-accelerated via compute shaders.

## Key Files
| File | Purpose |
|------|---------|
| `CMakeLists.txt` | Build definition; enumerates compositor sources, shaders, and node implementations |
| `COM_compositor.hh` | Top-level compositor entry point: creates and runs a compositor evaluation |
| `COM_context.hh` | Evaluation context: holds node tree, render context, and resource references |
| `COM_evaluator.hh` | Evaluator: schedules and executes operations from the node graph |
| `COM_compile_state.hh` | Compilation state: converts node graph into an operation graph |
| `COM_operation.hh` | Base class for all compositor operations |
| `COM_pixel_operation.hh` | Per-pixel GPU operation base class |
| `COM_shader_operation.hh` | GPU shader-based operation: wraps compute shader dispatch |
| `COM_node_operation.hh` | Operation generated from a single compositor node |
| `COM_result.hh` | Result type: represents a texture or value flowing between operations |
| `COM_domain.hh` | Domain: describes the resolution, transform, and wrap mode of a result |
| `COM_scheduler.hh` | Scheduler: determines operation execution order |
| `COM_shader_node.hh` | Base class for GPU shader-backed node implementations |
| `COM_profiler.hh` | Performance profiling for compositor operations |
| `COM_render_context.hh` | Render context: manages GPU resources for compositor evaluation |
| `COM_static_cache_manager.hh` | Cache manager for reusable compositor resources (bokeh, blur weights, etc.) |
| `COM_utilities.hh` | Utility functions for compositor operations |
| `COM_meta_data.hh` | Metadata for compositor results (color space, etc.) |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `algorithms/` | Reusable compositor algorithms: blur variants, morphological ops, jump flooding, SMAA, parallel reduction |
| `cached_resources/` | Cached GPU resources: bokeh kernels, blur weights, fog glow, keying screen, SMAA textures, OCIO shaders |
| `derived_resources/` | Derived per-frame resources: denoised auxiliary passes |
| `intern/` | Implementation of core compositor classes (evaluator, context, operations, result, etc.) |
| `shaders/` | GLSL compute shaders for compositor node operations (~108 shaders: blur, filter, mask, convert, glare, etc.) |
| `utilities/` | Utility headers: diagonal patterns, GPU material helpers, OIDN integration |

### algorithms/ key files
| File | Purpose |
|------|---------|
| `COM_algorithm_recursive_gaussian_blur.hh` | Deriche/recursive Gaussian blur (single-pass, IIR) |
| `COM_algorithm_symmetric_separable_blur.hh` | Symmetric separable blur kernel |
| `COM_algorithm_morphological_blur.hh` | Morphological dilate/erode via blur |
| `COM_algorithm_morphological_distance.hh` | Morphological distance transform |
| `COM_algorithm_morphological_distance_feather.hh` | Feathered morphological distance |
| `COM_algorithm_jump_flooding.hh` | Jump flooding algorithm for Voronoi/distance fields |
| `COM_algorithm_smaa.hh` | Subpixel morphological anti-aliasing |
| `COM_algorithm_parallel_reduction.hh` | GPU parallel reduction (min/max/sum) |
| `COM_algorithm_summed_area_table.hh` | Summed area table for box blur |
| `COM_algorithm_compute_preview.hh` | Thumbnail preview generation |
| `COM_algorithm_extract_alpha.hh` | Alpha channel extraction |

## For AI Agents

### Working In This Directory
- All public headers use the `COM_` prefix and live in the module root.
- The compositor converts a node tree into an operation graph during compilation (`compile_state.cc`), then the evaluator (`evaluator.cc`) schedules and dispatches GPU compute shaders.
- Each compositor node maps to a `NodeOperation` subclass. GPU-backed nodes inherit from `PixelOperation` or `ShaderOperation`.
- Results (`COM_result.hh`) are GPU textures or single values that flow between operations. The domain system (`COM_domain.hh`) handles resolution mismatches and transforms.
- Shaders in `shaders/` follow the naming convention `compositor_<operation_name>.glsl`.

### Common Patterns
- **Adding a new node operation**: Create a class inheriting `PixelOperation` or `ShaderOperation`, implement `execute()`, register the GLSL shader in `shaders/`.
- **Shader dispatch**: `ShaderOperation` subclasses call `invoke()` with a shader name and domain. The framework handles texture binding and compute dispatch.
- **Domain resolution**: When inputs have different resolutions, the compositor auto-inserts `RealizeOnDomainOperation` to resample.
- **Cached resources**: Bokeh kernels, blur weights, and other expensive-to-compute textures are managed by `StaticCacheManager` and shared across frames.
- **Blur pattern**: Most blur nodes use the symmetric separable blur algorithm with precomputed weights from `cached_resources/COM_symmetric_separable_blur_weights.hh`.

### Testing Requirements
- No dedicated test directory in this module. Compositor testing is done through render regression tests and Python-based node tests in the main test suite.

## Dependencies
- **Internal**: `gpu/` (compute shader dispatch, textures, framebuffers), `blenkernel/` (node tree, scene data), `render/` (render result input), `nodes/` (node type definitions)
- **External**: OpenImageDenoise (for denoising integration via `utilities/COM_utilities_oidn.hh`)
