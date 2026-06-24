<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md — Modifiers

The modifier stack implements Blender's non-destructive modifier system. Each modifier is registered via `ModifierTypeInfo` with the `MOD_` prefix. Modifiers are evaluated in order as a stack on meshes, volumes, curves, and grease pencil objects.

## Key Files

| File | Purpose |
|------|---------|
| `MOD_modifiertypes.hh` | `ModifierTypeInfo` struct and all modifier type declarations |
| `MOD_nodes.hh` | Geometry Nodes modifier integration API |
| `CMakeLists.txt` | Build configuration |

## Subdirectories

| Directory | Purpose |
|-----------|---------|
| `intern/` | All modifier implementations — one `.cc` file per modifier |
| `intern/lineart/` | Line Art modifier internals (CPU line art rendering) |

## Architecture

### Modifier Implementation Pattern

Each modifier in `intern/` follows a consistent pattern:
1. Define a `ModifierTypeInfo` struct with callbacks: `modify_mesh`, `modify_mesh_set`, `deform_verts`, `panel_register`, etc.
2. Register via `ModifierTypeTypeInfo_initData` or similar
3. Callbacks handle: initialization, copy, free, is_disabled, update_deps, panel UI registration

### Mesh Modifiers (`intern/MOD_*.cc`)

Deform modifiers (modify vertex positions):
- `MOD_armature.cc`, `MOD_hook.cc`, `MOD_lattice.cc`, `MOD_meshdeform.cc`
- `MOD_shrinkwrap.cc`, `MOD_simpledeform.cc`, `MOD_smooth.cc`, `MOD_correctivesmooth.cc`
- `MOD_laplaciansmooth.cc`, `MOD_laplaciandeform.cc`, `MOD_wave.cc`, `MOD_cast.cc`
- `MOD_surface.cc`, `MOD_surfacedeform.cc`, `MOD_warp.cc`

Generate modifiers (create/modify geometry):
- `MOD_subsurf.cc`, `MOD_multires.cc`, `MOD_bevel.cc`, `MOD_boolean.cc`
- `MOD_mirror.cc`, `MOD_array.cc`, `MOD_screw.cc`, `MOD_solidify.cc`
- `MOD_skin.cc`, `MOD_remesh.cc`, `MOD_weld.cc`, `MOD_triangulate.cc`
- `MOD_edgesplit.cc`, `MOD_mask.cc`, `MOD_build.cc`, `MOD_decimate.cc`
- `MOD_displace.cc`, `MOD_uvproject.cc`, `MOD_uvwarp.cc`, `MOD_datatransfer.cc`
- `MOD_normal_edit.cc`, `MOD_weighted_normal.cc`, `MOD_wireframe.cc`
- `MOD_shapekey.cc`, `MOD_meshcache.cc`, `MOD_meshsequencecache.cc`
- `MOD_ocean.cc`, `MOD_explosion.cc`, `MOD_particlesystem.cc`, `MOD_particleinstance.cc`
- `MOD_dynamicpaint.cc`, `MOD_fluid.cc`, `MOD_cloth.cc`, `MOD_collision.cc`, `MOD_softbody.cc`
- `MOD_lineart.cc`, `MOD_nodes.cc`

Solidify internals: `MOD_solidify_extrude.cc`, `MOD_solidify_nonmanifold.cc`

### Grease Pencil Modifiers (`intern/MOD_grease_pencil_*.cc`)

A full set of grease pencil modifiers:
- Transform: `MOD_grease_pencil_offset.cc`, `MOD_grease_pencil_mirror.cc`, `MOD_grease_pencil_noise.cc`
- Generate: `MOD_grease_pencil_array.cc`, `MOD_grease_pencil_build.cc`, `MOD_grease_pencil_subdiv.cc`, `MOD_grease_pencil_multiply.cc`, `MOD_grease_pencil_envelope.cc`
- Deform: `MOD_grease_pencil_hook.cc`, `MOD_grease_pencil_lattice.cc`, `MOD_grease_pencil_smooth.cc`, `MOD_grease_pencil_shrinkwrap.cc`, `MOD_grease_pencil_simplify.cc`
- Color/Style: `MOD_grease_pencil_color.cc`, `MOD_grease_pencil_tint.cc`, `MOD_grease_pencil_opacity.cc`, `MOD_grease_pencil_thickness.cc`, `MOD_grease_pencil_outline.cc`, `MOD_grease_pencil_dash.cc`, `MOD_grease_pencil_texture.cc`, `MOD_grease_pencil_length.cc`
- Weight: `MOD_grease_pencil_weight_proximity.cc`, `MOD_grease_pencil_weight_angle.cc`
- Armature: `MOD_grease_pencil_armature.cc`
- Time: `MOD_grease_pencil_time.cc`
- Shared utilities: `MOD_grease_pencil_util.cc` / `.hh`

### Volume Modifiers (`intern/MOD_volume_*.cc`)

- `MOD_volume_displace.cc` — volume displacement
- `MOD_volume_to_mesh.cc` — volume to mesh conversion
- `MOD_mesh_to_volume.cc` — mesh to volume conversion

### Line Art (`intern/lineart/`)

CPU-based line art rendering for the Line Art modifier:
- `lineart_cpu.cc` — main CPU line art algorithm
- `lineart_chain.cc` — line chain construction and chaining
- `lineart_shadow.cc` — shadow line generation
- `lineart_util.cc` — utility functions
- `lineart_intern.hh` / `MOD_lineart.hh` — internal headers

### Utilities (`intern/MOD_util.cc`, `MOD_ui_common.cc`)

- `MOD_util.cc` / `.hh` — shared modifier utilities (texture lookup, vgroup lookup, deform matrix)
- `MOD_ui_common.cc` / `.hh` — common UI panel registration helpers
- `MOD_weightvg_util.cc` / `.hh` — weight vertex group utilities (shared by weight modifiers)
- `MOD_none.cc` — placeholder for unknown/missing modifiers

## Common Patterns

- Each modifier fills a `ModifierTypeInfo` struct and calls `BKE_modifier_typeinfo_register`
- `modify_mesh` callback receives `Mesh *` and returns a new `Mesh *` (ownership transferred)
- `deform_verts` callback modifies `(*vertexCos)` array in-place for deform-only modifiers
- Panel registration uses `PanelType` with RNA-based UI layout
- `is_disabled` checks visibility flags and mode compatibility
- `update_deps` adds depsgraph relations for the modifier's dependencies
- Copy-on-write: modifier data is duplicated during depsgraph evaluation

## Dependencies

- `source/blender/blenkernel/` — BKE modifier system, mesh operations, texture lookup
- `source/blender/makesdna/` — DNA modifier structs
- `source/blender/bmesh/` — BMesh used by some modifiers (boolean, bevel, triangulate, etc.)
- `source/blender/nodes/` — Geometry Nodes modifier (`MOD_nodes.cc`)
- `source/blender/depsgraph/` — Depsgraph relation building
- `source/blender/blenlib/` — BLI math, utility functions
- `source/blender/draw/` — Line Art modifier rendering backend
