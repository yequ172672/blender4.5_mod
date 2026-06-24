<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# gpu

## Purpose
Blender's GPU abstraction layer. Wraps OpenGL, Vulkan, and Metal behind a unified API so that higher-level modules (draw, editors, Python gpu module) never call platform APIs directly. Provides shader compilation, texture/framebuffer management, vertex buffers, compute dispatch, and state management.

## Key Files
| File | Purpose |
|------|---------|
| `CMakeLists.txt` | Build definition; wires platform backends and shared GPU sources |
| `GPU_shader.hh` | Shader creation, uniform setting, bind/unbind API |
| `GPU_texture.hh` | Texture creation, sampling, image load/store (largest public header) |
| `GPU_framebuffer.hh` | Framebuffer creation, attachment management, read/draw target binding |
| `GPU_batch.hh` | Batch rendering: combines vertex buffer + index buffer + shader for draw calls |
| `GPU_vertex_buffer.hh` | Vertex buffer allocation and data upload |
| `GPU_index_buffer.hh` | Index buffer allocation and data upload |
| `GPU_uniform_buffer.hh` | Uniform buffer object (UBO) API |
| `GPU_storage_buffer.hh` | Shader storage buffer object (SSBO) API |
| `GPU_immediate.hh` | Immediate mode drawing (legacy compatibility, `imm*` functions) |
| `GPU_state.hh` | GPU state management: blend, depth, stencil, culling, viewport |
| `GPU_context.hh` | GPU context creation and management |
| `GPU_format.hh` | Texture/data format definitions and conversion utilities |
| `GPU_material.hh` | GPU material shader generation from node trees |
| `GPU_pass.hh` | Compiled shader pass cache for material shaders |
| `GPU_compute.hh` | Compute shader dispatch API |
| `GPU_platform.hh` | Platform/vendor detection and capability queries |
| `GPU_capabilities.hh` | Runtime GPU capability queries (max texture size, compute groups, etc.) |
| `GPU_debug.hh` | Debug labeling and profiling markers for GPU captures |
| `GPU_matrix.hh` | Matrix stack (legacy compatibility layer) |
| `GPU_select.hh` | GPU-based selection/occlusion query API |
| `GPU_viewport.hh` | Viewport management for render targets |
| `GPU_worker.hh` | GPU worker thread for async operations |
| `GPU_shader_create_info.hh` | Declarative shader creation system (replaces manual shader setup) |
| `GPU_shader_shared.hh` | Shared C/GLSL type definitions for push constants and SSBOs |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `intern/` | Shared implementation code: backend-agnostic logic, shader codegen, texture utilities |
| `opengl/` | OpenGL backend: implements all GPU_ interfaces using GL calls (`gl_*` files) |
| `vulkan/` | Vulkan backend: implements GPU_ interfaces using Vulkan API; includes render graph, descriptor management |
| `metal/` | Metal backend: implements GPU_ interfaces for macOS/iOS using Metal API (`.mm` Objective-C++ files) |
| `dummy/` | Dummy backend: stub implementations for headless/testing contexts without a real GPU |
| `shaders/` | Built-in GLSL shaders: 2D/3D drawing, widgets, image display, node links, area borders |
| `glsl_preprocess/` | GLSL preprocessor: handles `#pragma`, include resolution, and create info expansion |
| `tests/` | Unit tests for textures, framebuffers, shaders, buffers, compute, state |

## For AI Agents

### Working In This Directory
- All public APIs use the `GPU_` prefix. Headers are in the module root (e.g., `GPU_shader.hh`).
- Platform backends (`opengl/`, `vulkan/`, `metal/`) implement abstract base classes defined in `intern/gpu_backend.hh`. Each backend provides `GLBackend`, `VKBackend`, `MTLBackend`.
- Internal types use `gl_`, `vk_`, `mtl_` prefixes matching their backend directory.
- The shader create info system (`GPU_shader_create_info.hh`) is the preferred way to define shaders. Create info definitions are listed in `intern/gpu_shader_create_info_list.hh`.
- Shader codegen in `intern/gpu_codegen.cc` translates node graphs into GLSL for material shaders.

### Common Patterns
- **Resource lifecycle**: `GPU_*_create()` -> configure -> `GPU_*_update()` -> bind -> draw -> `GPU_*_free()`.
- **Shader creation**: Define a `GPUShaderCreateInfo` with `vertex_in()`, `fragment_out()`, `push_constant()`, `vertex_source()`, etc., then call `GPU_shader_create_from_info()`.
- **Texture creation**: Use `GPU_texture_create_*()` with a `eGPUTextureFormat` from `GPU_format.hh`. Wrap in RAII `Texture` from draw module when possible.
- **Backend selection**: `GPU_backend_get_type()` returns `GPU_BACKEND_OPENGL`, `GPU_BACKEND_VULKAN`, or `GPU_BACKEND_METAL`.
- **Vulkan specifics**: Uses a render graph (`vulkan/render_graph/`) for command scheduling and resource transitions. Descriptor sets are managed via `vk_descriptor_pools.cc`.

### Testing Requirements
- Tests in `tests/` use Google Test. Build with `WITH_GTESTS=ON`.
- Comprehensive coverage: texture formats, framebuffer operations, shader compilation, buffer uploads, compute dispatch, state management, specialization constants.
- Test helpers in `tests/gpu_testing.hh` provide context setup.

## Dependencies
- **External**: OpenGL (system), Vulkan SDK, Metal framework (macOS), shader compiler (GLSL -> SPIR-V for Vulkan)
- **Internal**: `blenlib/` (math, data structures), `windowmanager/` (context creation via GHOST), `makesdna/` (data types)
