<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# geometry - Geometry Processing Algorithms

Core geometry processing library providing mesh, curve, point cloud, and volume operations. Public API uses the `GEO_` prefix. Heavily used by Geometry Nodes.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Internal implementation of all geometry algorithms |

## Key Files

| File | Description |
|------|-------------|
| `GEO_add_curves_on_mesh.hh` | Scatter curves on mesh surface |
| `GEO_curve_constraints.hh` | Curve constraint solving |
| `GEO_curves_remove_and_split.hh` | Curve deletion and splitting |
| `GEO_extend_curves.hh` | Extend curves at endpoints |
| `GEO_extract_elements.hh` | Extract mesh/curve elements by selection |
| `GEO_fillet_curves.hh` | Curve fillet (rounding) operations |
| `GEO_fit_curves.hh` | Fit curves to point data |
| `GEO_interpolate_curves.hh` | Interpolation along curves |
| `GEO_join_geometries.hh` | Join multiple geometry types |
| `GEO_merge_curves.hh` | Merge curve endpoints |
| `GEO_merge_layers.hh` | Merge geometry layers |
| `GEO_mesh_boolean.hh` | Boolean operations on meshes |
| `GEO_mesh_copy_selection.hh` | Copy selected mesh elements |
| `GEO_mesh_merge_by_distance.hh` | Merge vertices by distance threshold |
| `GEO_mesh_primitive_*.hh` | Mesh primitive generation (grid, sphere, cylinder, etc.) |
| `GEO_mesh_selection.hh` | Mesh selection utilities |
| `GEO_mesh_split_edges.hh` | Split mesh edges |
| `GEO_mesh_to_curve.hh` | Convert mesh edges to curves |
| `GEO_mesh_to_volume.hh` | Convert mesh to volume |
| `GEO_mesh_triangulate.hh` | Mesh triangulation |
| `GEO_mix_geometries.hh` | Mix/interpolate between geometries |
| `GEO_point_merge_by_distance.hh` | Merge points by distance |
| `GEO_points_to_volume.hh` | Convert points to volume |
| `GEO_randomize.hh` | Randomize element order |
| `GEO_realize_instances.hh` | Realize geometry instances to concrete geometry |
| `GEO_reorder.hh` | Reorder geometry elements |
| `GEO_resample_curves.hh` | Resample curves to new point counts |
| `GEO_reverse_uv_sampler.hh` | Reverse UV lookup (UV to 3D position) |
| `GEO_separate_geometry.hh` | Separate geometry by selection |
| `GEO_set_curve_type.hh` | Convert between curve types |
| `GEO_simplify_curves.hh` | Curve simplification/decimation |
| `GEO_smooth_curves.hh` | Curve smoothing algorithms |
| `GEO_subdivide_curves.hh` | Curve subdivision |
| `GEO_transform.hh` | Geometry transform operations |
| `GEO_trim_curves.hh` | Curve trimming by parameter |
| `GEO_uv_pack.hh` | UV island packing |
| `GEO_uv_parametrizer.hh` | UV parameterization (unwrapping) |
| `GEO_volume_grid_resample.hh` | Volume grid resampling |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- All public headers use `GEO_` prefix and `.hh` extension
- Implementations in `intern/` use C++ with Blender's `blender::` namespace
- Mesh boolean operations use manifold-based algorithms (`mesh_boolean_manifold.cc`)
- UV operations include packing (`uv_pack.cc`) and parameterization (`uv_parametrizer.cc`)

## For AI Agents

- This module is the backbone of Geometry Nodes - most geometry nodes delegate here
- Mesh operations: `mesh_boolean`, `mesh_merge_by_distance`, `mesh_triangulate`, `mesh_split_edges`
- Curve operations: `resample_curves`, `simplify_curves`, `fillet_curves`, `trim_curves`
- Conversion: `mesh_to_curve`, `mesh_to_volume`, `points_to_volume`, `realize_instances`
- `intern/transform.cc` and `intern/subdivide_curves.cc` handle spatial transformations
