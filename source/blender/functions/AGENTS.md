<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# functions - Function System for Lazy Evaluation

Function framework providing lazy evaluation, multi-functions, and field evaluation. Core infrastructure for Geometry Nodes execution. Public API uses the `FN_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Internal implementation |
| `tests/` | Unit tests |

## Key Files

| File | Description |
|------|-------------|
| `FN_field.hh` | Field system - lazy attribute evaluation (e.g., position, normal) |
| `FN_lazy_function.hh` | Lazy function base classes and infrastructure |
| `FN_lazy_function_execute.hh` | Lazy function execution engine |
| `FN_lazy_function_graph.hh` | Graph representation of lazy function networks |
| `FN_lazy_function_graph_executor.hh` | Graph-based lazy function execution |
| `FN_multi_function.hh` | Multi-function - vectorized function evaluation |
| `FN_multi_function_builder.hh` | Builder pattern for constructing multi-functions |
| `FN_multi_function_context.hh` | Evaluation context for multi-functions |
| `FN_multi_function_data_type.hh` | Data type definitions for multi-function I/O |
| `FN_multi_function_param_type.hh` | Parameter type classification (input/output/mutable) |
| `FN_multi_function_params.hh` | Parameter layout and access for multi-functions |
| `FN_multi_function_procedure.hh` | Procedural multi-function representation |
| `FN_multi_function_procedure_builder.hh` | Builder for procedural multi-functions |
| `FN_multi_function_procedure_executor.hh` | Execute procedural multi-functions |
| `FN_multi_function_procedure_optimization.hh` | Optimization passes for procedures |
| `FN_multi_function_signature.hh` | Function signature definitions |
| `FN_user_data.hh` | User data threading through evaluation |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- **Fields**: Represent lazy attribute computations evaluated on-demand per element
- **Multi-Functions**: Vectorized functions operating on arrays of data (SIMD-friendly)
- **Lazy Functions**: Functions that defer computation until results are needed
- **Procedures**: Programmable multi-functions built from instruction sequences
- Builder patterns are used extensively for constructing function objects

## For AI Agents

- `FN_field.hh` is essential for understanding Geometry Nodes attribute evaluation
- `FN_multi_function.hh` and its builder are used to implement geometry node operations
- `FN_lazy_function_graph*.hh` handles the node graph execution model
- Fields propagate through the geometry node graph and are evaluated lazily at output
- This module has no Blender DNA dependencies - pure computational framework
