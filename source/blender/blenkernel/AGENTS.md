<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md - Blender Kernel (BKE)

## Overview

Blender's core kernel library (`blenkernel`) is the central C/C++ library containing data management, object operations, mesh processing, material evaluation, scene management, and all fundamental data-block operations. This is the heart of Blender's data model.

- **Prefix**: `BKE_` (all public functions)
- **License**: GPL-2.0-or-later
- **Language**: C++ (`.cc`) with C-compatible headers (`.h` / `.hh`)

## Directory Structure

```
blenkernel/
├── BKE_*.h / BKE_*.hh    # Public API headers (224 files)
├── intern/                # Implementation files (316 .cc files)
│   ├── *.cc               # Core implementations
│   └── *_test.cc          # Unit tests (co-located)
└── CMakeLists.txt         # Build configuration
```

## Key Subsystems

### ID / Data-Block Management
- `BKE_lib_id.hh` - High-level ID operations (create, rename, delete, copy)
- `BKE_lib_query.hh` - ID relationship queries and foreach iteration
- `BKE_lib_override.hh` - Library override system (linked data local overrides)
- `BKE_main.hh` - Main database root structure operations
- `BKE_main_idmap.hh` / `BKE_main_namemap.hh` - ID lookup and naming maps
- `BKE_idtype.hh` - ID type registration and type info system
- `BKE_idprop.hh` - Custom ID properties (user-defined properties)

### Mesh / Geometry
- `BKE_mesh.hh` / `BKE_mesh.h` - Mesh data operations
- `BKE_editmesh.hh` - Edit mode mesh operations
- `BKE_editmesh_bvh.hh` - Edit mesh BVH acceleration
- `BKE_curve_to_mesh.hh` - Curve-to-mesh conversion
- `BKE_bvhutils.hh` - BVH tree construction for raycasting
- `BKE_attribute.hh` - Custom data attributes on geometry
- `BKE_attribute_math.hh` - Attribute math operations

### Object / Scene
- `BKE_object.hh` - Object operations and transforms
- `BKE_scene.hh` - Scene management
- `BKE_collection.hh` - Collection (group) management
- `BKE_layer.hh` - View layer management
- `BKE_camera.h` - Camera utilities

### Animation
- `BKE_action.hh` - Action (keyframe animation) operations
- `BKE_anim_data.hh` - Animation data management
- `BKE_animsys.hh` - Animation system (RNA path animation)
- `BKE_fcurve.hh` - F-Curve operations
- `BKE_key.hh` - Shape keys

### Material / Shader
- `BKE_material.hh` - Material assignment and management
- `BKE_node.hh` - Node tree operations
- `BKE_shader_fx.hh` - Shader effects

### Modifiers
- `BKE_modifier.hh` - Modifier stack operations
- `BKE_gpencil_modifier.hh` - Grease pencil modifiers
- `BKE_bake_geometry_nodes_modifier.hh` - Geometry nodes baking

### Armature / Deform
- `BKE_armature.hh` - Armature operations, bone calculations
- `BKE_armature_deform.cc` - Mesh deformation via armature

### File I/O
- `BKE_blendfile.hh` - .blend file read/write
- `BKE_blendfile_link_append.hh` - Link/append from other .blend files
- `BKE_bpath.hh` - File path management

### Asset System
- `BKE_asset.hh` - Asset browser data management
- `BKE_asset_edit.hh` - Asset editing operations

## Naming Conventions

### Function Naming
- **`BKE_<subsystem>_<action>`** - Standard pattern
- **`BKE_lib_id_*`** - High-level ID operations (safe, maintain consistency)
- **`BKE_lib_libblock_*`** - Lower-level ID operations (caller must ensure consistency)
- **`BKE_lib_main_*`** - Operations over all IDs in Main
- **`BKE_main_*`** - Main database operations

### Header Organization
- `.h` files: C-compatible headers (can be included from C code)
- `.hh` files: C++ headers (may use templates, classes, etc.)

### Test Files
- Unit tests are co-located in `intern/` with `_test.cc` suffix
- Example: `armature_test.cc`, `anim_data_test.cc`

## Key Patterns

### Main Database
```c
// Main is the root of all Blender data
struct Main;  // All ID data-blocks live here

// Iterate over all IDs of a type
FOREACH_ID_MAIN_BEGIN (main, id_iter) {
    // process id_iter
} FOREACH_ID_MAIN_END;
```

### ID Management
```c
// Create a new ID
ID *BKE_id_new(Main *bmain, short type, const char *name);

// Copy an ID
ID *BKE_id_copy(Main *bmain, const ID *id);

// Delete an ID (handles all references)
BKE_id_free(Main *bmain, ID *id);
```

### Library Overrides
```c
// Create override of linked data
BKE_lib_override_library_create(bmain, id_reference, ...);

// Make single property editable
BKE_lib_override_library_property(rna_path, ...);
```

## Dependencies

- **blenlib** (BLI_*) - Foundation utilities, math, data structures
- **makesdna** (DNA_*) - Data structure definitions
- **makesrna** (RNA_*) - Property system for animation/Python access

## Common Pitfalls

1. **Thread Safety**: Main database operations are NOT thread-safe. Use proper locking.
2. **ID References**: Always use `BKE_id_*` functions, never raw pointer manipulation.
3. **Library Overrides**: Understand the override hierarchy before modifying.
4. **Memory Management**: Use `BKE_id_free()` for IDs, `MEM_freeN()` for raw allocations.

## For AI Agents

- Always check if a `BKE_` function exists before implementing custom logic
- Use `BKE_lib_id_*` (high-level) over `BKE_lib_libblock_*` (low-level) unless you need fine control
- Prefer `.hh` headers for new C++ code, `.h` only when C compatibility is required
- Test files follow `*_test.cc` pattern in `intern/`
- When modifying ID behavior, consider impact on library overrides and linked data
