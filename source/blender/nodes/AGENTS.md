<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md — Nodes

The node system implements Blender's shader nodes, geometry nodes, compositor nodes, function nodes, and texture nodes. Each node type is registered with the `NOD_` prefix. Public API headers use `NOD_` prefix (`.hh` / `.h`).

## Key Files

| File | Purpose |
|------|---------|
| `NOD_node_declaration.hh` | `NodeDeclaration` — declarative socket and panel definitions for nodes |
| `NOD_socket_declarations.hh` | Typed socket declaration classes (Float, Vector, Color, etc.) |
| `NOD_register.hh` | Node type registration API |
| `NOD_multi_function.hh` | Multi-function binding for node evaluation |
| `NOD_geometry_exec.hh` | Geometry nodes execution context and field evaluation |
| `NOD_geometry_nodes_lazy_function.hh` | Lazy function graph for geometry node evaluation |
| `NOD_geometry_nodes_execute.hh` | Geometry nodes modifier execution entry point |
| `NOD_geometry_nodes_log.hh` | Geometry nodes debug logging |
| `NOD_geometry_nodes_gizmos.hh` | Gizmo support for geometry nodes |
| `NOD_geometry_nodes_dependencies.hh` | Dependency analysis for geometry nodes |
| `NOD_math_functions.hh` | Math function definitions for function/math nodes |
| `NOD_value_elem.hh` / `NOD_value_elem_eval.hh` | Value element system for field propagation |
| `NOD_inverse_eval_*.hh` | Inverse evaluation for attribute propagation |
| `NOD_socket_items.hh` | Repeated socket item management (e.g., enum items, switch cases) |
| `NOD_socket_search_link.hh` | Link drag search functionality |
| `NOD_socket_usage_inference.hh` | Automatic socket usage inference for optimization |
| `NOD_rna_define.hh` | RNA property definition helpers for nodes |
| `NOD_common.hh` | Shared node utilities |
| `NOD_shader.h` / `NOD_texture.h` | C-only headers for shader/texture node registration |
| `CMakeLists.txt` | Build configuration |

## Subdirectories

| Directory | Purpose |
|-----------|---------|
| `shader/` | Shader node types (BSDFs, textures, input, output, color, vector, converter) |
| `geometry/` | Geometry node types (mesh operations, curve operations, instances, fields, simulation) |
| `composite/` | Compositor node types (blur, color, matte, filter, distortion, transform) |
| `function/` | Function/utility nodes (math, rotation, string, compare, combine/separate) |
| `texture/` | Legacy texture node types |
| `intern/` | Core node system implementation |

## Architecture

### Intern (`intern/`)

Core implementation files:
- `node_register.cc` — node type registry
- `node_declaration.cc` — declaration system implementation
- `node_socket.cc` / `node_socket_declarations.cc` — socket type system
- `node_multi_function.cc` — multi-function binding
- `node_rna_define.cc` — RNA integration
- `derived_node_tree.cc` — optimized derived node tree for evaluation
- `partial_eval.cc` — compile-time partial evaluation optimization
- `socket_search_link.cc` — link drag search
- `socket_usage_inference.cc` — unused socket detection
- `inverse_eval.cc` — inverse evaluation for attribute inference
- `value_elem.cc` — value element propagation
- `math_functions.cc` — built-in math function implementations
- Geometry nodes internals: `geometry_nodes_lazy_function.cc`, `geometry_nodes_execute.cc`, `geometry_nodes_log.cc`, `geometry_nodes_gizmos.cc`, `geometry_nodes_dependencies.cc`, `geometry_nodes_closure.cc`, `geometry_nodes_repeat_zone.cc`, `geometry_nodes_warning.cc`

### Per-Tree-Type Structure

Each tree type directory (`shader/`, `geometry/`, `composite/`, `function/`, `texture/`) follows the same pattern:
- `node_<type>_tree.cc` — tree type definition and callbacks
- `node_<type>_util.cc` / `.hh` — shared utilities for that tree type
- `node_<type>_register.cc` — registration of all node types (where applicable)
- `nodes/` subdirectory — one `.cc` file per node type (e.g., `node_shader_bsdf_principled.cc`, `node_geo_mesh_primitive_line.cc`)
- Some have `materialx/` subdirectories for MaterialX export support

### Geometry Nodes Specifics

- `geometry/nodes/` contains `node_geo_*.cc` files for each geometry node
- `geometry/include/` contains shared geometry node headers
- Nodes use `LazyFunction` for demand-driven evaluation
- Field evaluation system enables attribute propagation through node chains

## Common Patterns

- Each node type has a `node_register_*` function that populates `bNodeType`
- Socket declarations use the builder pattern: `builder.add_input<DeclFloat>(...).default_value(...)`
- Geometry nodes use `GeoNodeExecParams` for runtime parameter access
- Shader nodes use `bNodeExecContext` for execution
- Node poll functions check tree type compatibility

## Dependencies

- `source/blender/blenkernel/` — BKE node tree, node type management
- `source/blender/makesdna/` — DNA structs for nodes, node trees, sockets
- `source/blender/blenlib/` — BLI utility functions
- `source/blender/functions/` — FN_multi_function, FN_lazy_function
- `source/blender/io/` — MaterialX export integration (shader nodes)
