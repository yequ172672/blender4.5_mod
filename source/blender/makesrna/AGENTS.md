<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md - Make RNA (Property System)

## Overview

`makesrna` implements Blender's RNA property system - the introspection, animation, and Python access layer that sits on top of DNA structs. RNA provides runtime type information, property access, enumeration types, and the bridge between C data and Python/bpy.

- **Prefix**: `RNA_` (all public functions and types)
- **License**: GPL-2.0-or-later
- **Language**: C++ (`.cc`) with C-compatible headers (`.hh`)

## Directory Structure

```
makesrna/
├── RNA_access.hh          # RNA access API (get/set properties)
├── RNA_define.hh          # RNA definition API (define types/properties)
├── RNA_types.hh           # Core RNA types (PointerRNA, PropertyRNA, etc.)
├── RNA_path.hh            # RNA path resolution for animation
├── RNA_enum_items.hh      # Enum item definitions
├── RNA_enum_types.hh      # Enum type declarations
├── RNA_documentation.hh   # Documentation macros
├── intern/                # Implementation files (108 .cc files)
│   ├── makesrna.cc        # RNA code generator
│   ├── rna_access.cc      # Property access implementation
│   ├── rna_define.cc      # Property definition implementation
│   ├── rna_ID.cc          # Base ID RNA definition
│   ├── rna_mesh.cc        # Mesh RNA definition
│   ├── rna_object.cc      # Object RNA definition
│   ├── rna_scene.cc       # Scene RNA definition
│   ├── rna_*_api.cc       # Python API functions
│   └── ...
├── rna_cleanup/           # Cleanup utilities
└── CMakeLists.txt         # Build configuration
```

## Key Concepts

### RNA vs DNA
- **DNA** = Binary data layout (file format, memory)
- **RNA** = Runtime property system (introspection, animation, Python)

RNA wraps DNA structs to provide:
1. **Property access** - Get/set values with validation
2. **Type information** - Runtime introspection
3. **Animation** - Properties can be keyed/animated
4. **Python access** - `bpy.types.Object.location`, etc.
5. **UI display** - Properties automatically appear in UI

### Core Types (from RNA_types.hh)
```cpp
struct PointerRNA {
    ID *owner_id;      // Owning data-block
    StructRNA *type;   // Runtime type info
    void *data;        // Pointer to actual data
};

struct PropertyRNA;    // Base property type
struct BoolPropertyRNA;
struct IntPropertyRNA;
struct FloatPropertyRNA;
struct StringPropertyRNA;
struct EnumPropertyRNA;
struct PointerPropertyRNA;
struct CollectionPropertyRNA;
struct FunctionRNA;    // Callable function
struct StructRNA;      // Type information
```

## Key Files

### Public API Headers
- `RNA_access.hh` - Main API: `RNA_int_get()`, `RNA_float_set()`, `RNA_collection_begin()`, etc.
- `RNA_define.hh` - Definition API: `RNA_def_struct()`, `RNA_def_property()`, etc.
- `RNA_types.hh` - Type definitions
- `RNA_path.hh` - Animation path resolution

### Implementation (intern/)
- `rna_access.cc` - Property get/set implementation
- `rna_define.cc` - Property definition implementation
- `rna_ID.cc` - Base ID properties (name, users, etc.)
- `rna_<type>.cc` - Per-type RNA definitions (108 files total)

## Naming Conventions

### Function Naming
- **`RNA_<action>`** - Access functions (RNA_int_get, RNA_float_set)
- **`RNA_def_<type>`** - Definition functions (RNA_def_struct, RNA_def_property)
- **`RNA_<type>_<action>`** - Type-specific operations

### File Naming (intern/)
- **`rna_<type>.cc`** - RNA definition for DNA type
- **`rna_<type>_api.cc`** - Python API functions for type
- **`rna_access.cc`** - Core access implementation
- **`rna_define.cc`** - Core definition implementation

## Defining RNA Types

### Pattern
```cpp
// In rna_mesh.cc
static void rna_def_mesh(BlenderRNA *brna)
{
    StructRNA *srna;
    PropertyRNA *prop;

    // Register struct
    srna = RNA_def_struct(brna, "Mesh", "ID");
    RNA_def_struct_ui_text(srna, "Mesh", "Mesh data-block");
    RNA_def_struct_ui_icon(srna, ICON_MESH_DATA);

    // Define properties
    prop = RNA_def_property(srna, "vertices", PROP_COLLECTION, PROP_NONE);
    RNA_def_property_collection_sdna(prop, NULL, "mvert", "totvert");
    RNA_def_property_struct_type(prop, "MeshVertex");
    RNA_def_property_ui_text(prop, "Vertices", "");

    // Define functions
    FunctionRNA *func;
    func = RNA_def_function(srna, "calc_normals", "rna_Mesh_calc_normals");
    RNA_def_function_ui_description(func, "Calculate mesh normals");
}
```

### Property Types
- **`PROP_BOOLEAN`** - Bool property
- **`PROP_INT`** - Integer property
- **`PROP_FLOAT`** - Float property
- **`PROP_STRING`** - String property
- **`PROP_ENUM`** - Enumeration
- **`PROP_POINTER`** - Pointer to another RNA type
- **`PROP_COLLECTION`** - Collection of RNA types

## Python Access

### How RNA Maps to Python
```python
# Python (bpy)
obj = bpy.data.objects["Cube"]
obj.location.x = 5.0
obj.location = (1.0, 2.0, 3.0)

# Underlying RNA calls (simplified)
# RNA_float_set(ptr, prop, 5.0)
# RNA_float_set_array(ptr, prop, [1.0, 2.0, 3.0])
```

### Animation Paths
```python
# Animation path format
"location.x"
"rotation_euler"
"data.materials[0].diffuse_color"
```

## Dependencies

- **makesdna** (DNA_*) - Data structure definitions
- **blenlib** (BLI_*) - Utility functions
- **blenkernel** (BKE_*) - Some ID operations

## Common Pitfalls

1. **Property Registration Order** - Properties must be registered in specific order for UI
2. **SDNA Mapping** - `RNA_def_property_*_sdna()` must match actual DNA struct layout
3. **Pointer Validation** - Always validate RNA pointers before use
4. **Collection Iteration** - Use proper iteration API, don't assume contiguous storage
5. **Thread Safety** - RNA access is generally NOT thread-safe

## For AI Agents

- New RNA definitions go in `intern/rna_<type>.cc`
- Python API functions go in `intern/rna_<type>_api.cc`
- Use `RNA_def_struct()` to register new types
- Use `RNA_def_property()` to add properties
- Always set UI text and descriptions for user-facing properties
- Test Python access via `bpy.types.<Type>.<property>`
- Check existing `rna_*.cc` files for patterns before writing new ones
