<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md — Dependency Graph (Depsgraph)

The dependency graph is Blender's evaluation engine. It determines the order in which objects, modifiers, constraints, and other data are evaluated. All public API uses the `DEG_` prefix. Internal types use `depsgraph::` namespace.

## Key Files

| File | Purpose |
|------|---------|
| `DEG_depsgraph.hh` | Main public API — tag for update, copy-on-write access, evaluation state |
| `DEG_depsgraph_build.hh` | Graph construction API — adding IDs, relations |
| `DEG_depsgraph_query.hh` | Query API — getting evaluated data, foreach iterators |
| `DEG_depsgraph_debug.hh` | Debug utilities — graphviz export, stats |
| `DEG_depsgraph_physics.hh` | Physics simulation integration |
| `DEG_depsgraph_light_linking.hh` | Light linking support |
| `DEG_depsgraph_writeback_sync.hh` | Writeback synchronization for evaluated data |
| `CMakeLists.txt` | Build configuration |

## Subdirectories

| Directory | Purpose |
|-----------|---------|
| `intern/` | Core depsgraph implementation |
| `intern/builder/` | Graph construction — builds nodes and relations from scene data |
| `intern/eval/` | Graph evaluation engine — topological sort, execution, copy-on-write |
| `intern/node/` | Node type definitions — ID nodes, component nodes, operation nodes |
| `intern/debug/` | Debug visualization — graphviz output, gnuplot stats |

## Architecture

### Core Internals (`intern/`)

- `depsgraph.cc` / `depsgraph.hh` — `Depsgraph` class definition
- `depsgraph_build.cc` — high-level graph construction API
- `depsgraph_eval.cc` — evaluation entry point
- `depsgraph_tag.cc` — tag-for-update logic (dirty propagation)
- `depsgraph_update.cc` — update flushing
- `depsgraph_relation.cc` — relation (edge) management
- `depsgraph_registry.cc` — global depsgraph registry
- `depsgraph_query.cc` / `depsgraph_query_foreach.cc` / `depsgraph_query_iter.cc` — query API implementation
- `depsgraph_debug.cc` — debug output
- `depsgraph_physics.cc` — physics time source management
- `depsgraph_light_linking.cc` — light linking evaluation
- `depsgraph_writeback_sync.cc` — writeback of evaluated data to original IDs

### Builder (`intern/builder/`)

Constructs the dependency graph from scene data:
- `deg_builder.cc` — base builder class
- `deg_builder_nodes.cc` — creates operation nodes from ID data blocks
- `deg_builder_nodes_rig.cc` — armature/bone-specific node building
- `deg_builder_nodes_scene.cc` — scene-level node building
- `deg_builder_nodes_view_layer.cc` — view layer node building
- `deg_builder_relations.cc` — creates edges (relations) between nodes
- `deg_builder_relations_rig.cc` — armature-specific relations
- `deg_builder_relations_drivers.cc` — driver dependency relations
- `deg_builder_rna.cc` — RNA path-based relation detection
- `deg_builder_cache.cc` — caching for incremental rebuilds
- `deg_builder_cycle.cc` — cycle detection and breaking
- `deg_builder_transitive.cc` — transitive reduction (remove redundant edges)
- `deg_builder_remove_noop.cc` — remove no-op nodes
- `deg_builder_stack.cc` — build stack management
- `deg_builder_key.cc` — node identification keys
- `deg_builder_map.cc` — ID/component/operation mapping
- `deg_builder_pchanmap.cc` — pose channel mapping
- `pipeline.cc` / `pipeline_*.cc` — high-level build pipelines (render, compositor, view layer, collection, all objects)

### Evaluation (`intern/eval/`)

Executes the dependency graph:
- `deg_eval.cc` — main evaluation loop (topological sort and execution)
- `deg_eval_copy_on_write.cc` — copy-on-write ID duplication
- `deg_eval_flush.cc` — dirty flag propagation
- `deg_eval_visibility.cc` — visibility-based evaluation filtering
- `deg_eval_stats.cc` — performance statistics collection
- `deg_eval_runtime_backup_*.cc` — runtime data backup/restore for copy-on-write (animation, modifiers, pose, scene, movie clip, sequencer, sound, volume)

### Node Types (`intern/node/`)

- `deg_node.cc` — base `TimeSourceNode`, `IDDepsNode`, `ComponentDepsNode`, `OperationDepsNode`
- `deg_node_component.cc` — component types (Transform, Geometry, Pose, etc.)
- `deg_node_id.cc` — ID datablock node
- `deg_node_operation.cc` — individual evaluation operations
- `deg_node_time.cc` — time source node
- `deg_node_factory.cc` — node creation factories

### Debug (`intern/debug/`)

- `deg_debug.cc` — debug name formatting
- `deg_debug_relations_graphviz.cc` — graphviz DOT export of the dependency graph
- `deg_debug_stats_gnuplot.cc` — gnuplot-compatible performance stats

## Common Patterns

- Evaluation uses copy-on-write: original IDs are duplicated before modification
- Relations have a type (`DepsRelationType`) indicating the kind of dependency
- Nodes have a component-operation hierarchy: ID -> Component -> Operation
- Tag functions (`DEG_graph_tag_*`) trigger selective re-evaluation
- Time sources propagate frame change information through the graph

## Dependencies

- `source/blender/blenkernel/` — BKE scene, object, modifier evaluation
- `source/blender/makesdna/` — DNA structs for IDs, scenes, objects
- `source/blender/blenlib/` — BLI task pool, utility functions
- `source/blender/animrig/` — animation evaluation
- `source/blender/render/` — render pipeline integration
