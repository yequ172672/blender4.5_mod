<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md - Make SDNA (DNA Data Structures)

## Overview

`makesdna` defines ALL Blender data structures using the SDNA (Structure DNA) system. This binary-compatible data layout system enables forward and backward file compatibility - Blender can open files from any version because it knows the exact memory layout of every struct at the time the file was written.

- **Prefix**: `DNA_` (all headers and defines)
- **License**: GPL-2.0-or-later
- **Language**: C headers (`.h`) with strict rules for SDNA compatibility

## Directory Structure

```
makesdna/
├── DNA_*_types.h          # Data structure definitions (80 files)
├── DNA_*_defaults.h       # Default value definitions
├── DNA_*_enums.h          # Enumerations
├── DNA_defs.h             # Common defines and macros
├── DNA_genfile.h          # SDNA file I/O declarations
├── DNA_documentation.h    # Documentation conventions
├── intern/                # SDNA generation and I/O
│   ├── makesdna.cc        # SDNA code generator
│   ├── dna_genfile.cc     # SDNA file reading/writing
│   ├── dna_defaults.c     # Default value implementations
│   └── dna_utils.cc       # Utility functions
└── CMakeLists.txt         # Build configuration
```

## Key Concepts

### SDNA System
SDNA (Structure DNA) is Blender's binary compatibility system:
1. Every `.blend` file contains a copy of all struct definitions at write time
2. When reading, Blender compares file SDNA with current SDNA
3. Automatic struct conversion handles added/removed/reordered fields
4. This enables opening files from Blender 2.0 in Blender 4.x

### Header Naming Convention
- **`DNA_<type>_types.h`** - Main struct definitions
- **`DNA_<type>_defaults.h`** - Default values for struct fields
- **`DNA_<type>_enums.h`** - Enumerations used by the struct

## Key Data Structure Files

### Core Identity
- `DNA_ID.h` - Base ID struct (all data-blocks inherit from this)
- `DNA_ID_enums.h` - ID type enumerations (ID_ME, ID_OB, ID_MA, etc.)

### Object / Scene
- `DNA_object_types.h` - Object struct
- `DNA_scene_types.h` - Scene struct
- `DNA_collection_types.h` - Collection (group) struct
- `DNA_layer_types.h` - View layer struct
- `DNA_camera_types.h` - Camera struct
- `DNA_light_types.h` - Light struct

### Mesh / Geometry
- `DNA_mesh_types.h` - Mesh struct
- `DNA_meshdata_types.h` - Mesh custom data types
- `DNA_curve_types.h` - Curve struct
- `DNA_curves_types.h` - Curves (new) struct
- `DNA_pointcloud_types.h` - Point cloud struct
- `DNA_volume_types.h` - Volume struct
- `DNA_customdata_types.h` - Custom data layer types

### Material / Shader
- `DNA_material_types.h` - Material struct
- `DNA_node_types.h` - Node tree structs
- `DNA_texture_types.h` - Texture struct
- `DNA_image_types.h` - Image struct

### Animation
- `DNA_action_types.h` - Action struct
- `DNA_anim_types.h` - Animation data structs
- `DNA_key_types.h` - Shape key struct
- `DNA_curveprofile_types.h` - Curve profile struct

### Armature / Physics
- `DNA_armature_types.h` - Armature struct
- `DNA_constraint_types.h` - Constraint structs
- `DNA_modifier_types.h` - Modifier structs
- `DNA_cloth_types.h` - Cloth simulation
- `DNA_fluid_types.h` - Fluid simulation
- `DNA_rigidbody_types.h` - Rigid body simulation

### World / Environment
- `DNA_world_types.h` - World struct
- `DNA_screen_types.h` - Screen layout struct
- `DNA_space_types.h` - Space types (3D View, Properties, etc.)
- `DNA_windowmanager_types.h` - Window manager struct

## Naming Conventions

### Struct Naming
- **`<TypeName>`** - PascalCase for struct names (e.g., `Mesh`, `Object`, `Scene`)
- **`ID`** - Base struct for all data-blocks
- **`IDProperty`** - Custom property system

### Field Naming
- **`snake_case`** - All struct fields use snake_case
- **`float loc[3]`** - Arrays for vectors/quaternions
- **`char name[64]`** - Fixed-size name buffers (MAX_NAME)

### Header Guards
```c
#pragma once  // Preferred in modern code
// or
#ifndef __DNA_MESH_TYPES_H__
#define __DNA_MESH_TYPES_H__
// ...
#endif
```

## SDNA Rules (CRITICAL)

### What Breaks SDNA Compatibility
1. **Reordering fields** - Changes binary layout
2. **Changing field types** - `int` to `float`, pointer to array, etc.
3. **Removing fields** - Old files can't map to new struct
4. **Changing array sizes** - `float loc[3]` to `float loc[4]`

### Safe Changes
1. **Adding fields at END of struct** - Old files get default values
2. **Adding new structs** - Only affects new data
3. **Deprecating fields** - Use `DNA_DEPRECATED` attribute

### Best Practices
```c
// GOOD: Adding new field at end
struct Mesh {
    // ... existing fields ...
    float new_feature;  /* Added in 4.5 */
};

// BAD: Inserting field in middle
struct Mesh {
    float loc[3];
    float new_field;  // BREAKS SDNA - shifts all subsequent fields
    float size[3];
};
```

## Default Values

### Pattern
```c
// DNA_<type>_defaults.h
extern const Mesh DNA_mesh_defaults;

// DNA_defaults.c (intern/)
const Mesh DNA_mesh_defaults = {
    .flag = ME_TWOSIDED,
    .smoothresh = DEG2RADF(180.0f),
    // ...
};
```

## Dependencies

- **blenlib** (BLI_*) - `BLI_sys_types.h` for type definitions
- **No other Blender dependencies** - This is foundational

## Common Pitfalls

1. **NEVER reorder struct fields** - This breaks all existing .blend files
2. **NEVER change field types** - Use deprecation + new field instead
3. **Always add new fields at END** - Preserves binary compatibility
4. **Use `DNA_DEPRECATED` for old fields** - Enables compiler warnings
5. **Fixed-size arrays only** - No flexible array members in SDNA structs

## For AI Agents

- **READ-ONLY for struct field order** - Never reorder existing fields
- New fields MUST be added at the end of structs
- Use `DNA_<type>_defaults.h` for default values, not inline initialization
- Check `DNA_defs.h` for common macros (MAX_NAME, DNA_DEPRECATED, etc.)
- When modifying existing structs, consider impact on file compatibility
- Test with old .blend files after any struct changes
