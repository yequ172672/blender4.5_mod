<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# AGENTS.md - Blender Library (BLI)

## Overview

Blender's foundational utility library (`blenlib`) provides math, data structures, memory management, string operations, path utilities, threading primitives, and other low-level infrastructure used throughout Blender. This is the lowest-level library that other Blender modules depend on.

- **Prefix**: `BLI_` (all public functions)
- **License**: GPL-2.0-or-later
- **Language**: C++ (`.cc`) with C-compatible headers (`.h` / `.hh`)

## Directory Structure

```
blenlib/
├── BLI_*.h / BLI_*.hh    # Public API headers (239 files)
├── intern/                # Implementation files (148 .cc files)
├── tests/                 # Unit tests
│   ├── *_test.cc          # Test files
│   └── performance/       # Performance benchmarks
└── CMakeLists.txt         # Build configuration
```

## Key Subsystems

### Math
- `BLI_math_base.h` / `.hh` - Basic math operations (min, max, clamp, lerp)
- `BLI_math_vector.h` / `.hh` - Vector math (2D, 3D, 4D)
- `BLI_math_matrix.h` / `.hh` - Matrix operations
- `BLI_math_rotation.h` / `.hh` - Quaternion, euler, axis-angle rotations
- `BLI_math_color.h` / `.hh` - Color space conversions
- `BLI_math_geom.h` - Geometry utilities (intersections, projections)
- `BLI_math_interp.hh` - Interpolation functions
- `BLI_math_bits.h` - Bit manipulation utilities

### Data Structures
- `BLI_listbase.h` - Doubly-linked list (ListBase) - fundamental Blender container
- `BLI_ghash.h` - Generic hash table (GHash)
- `BLI_gset.h` - Generic hash set (GSet)
- `BLI_map.hh` - C++ hash map wrapper
- `BLI_set.hh` - C++ hash set wrapper
- `BLI_vector.hh` - Dynamic array (Vector)
- `BLI_stack.hh` - Stack container
- `BLI_heap.h` - Priority queue (heap)
- `BLI_kdopbvh.hh` - BVH tree for spatial queries

### Memory Management
- `BLI_memarena.h` - Memory arena (bulk allocation)
- `BLI_mempool.h` - Memory pool (fixed-size allocations)
- `BLI_mmap.h` - Memory-mapped file I/O
- `BLI_allocator.hh` - Custom allocators

### Strings
- `BLI_string.h` - String utilities (copy, compare, format)
- `BLI_string_utf8.h` - UTF-8 string operations
- `BLI_string_cursor_utf8.h` - Cursor-aware string operations
- `BLI_string_ref.hh` - Non-owning string reference (C++)

### Paths / Files
- `BLI_path_util.h` - File path manipulation
- `BLI_fileops.h` - File operations (copy, delete, stat)
- `BLI_filelist.h` - Directory listing

### Threading
- `BLI_task.h` - Task-based parallelism
- `BLI_threads.h` - Thread utilities
- `BLI_mutex.h` - Mutex primitives
- `BLI_atomic_disjoint_set.hh` - Lock-free data structures

### Utility
- `BLI_args.h` - Command-line argument parsing
- `BLI_utildefines.h` - Common utility macros
- `BLI_compiler_attrs.h` - Compiler attribute macros (ATTR_WARN_UNUSED_RESULT, etc.)
- `BLI_compiler_compat.h` - Cross-compiler compatibility
- `BLI_build_config.h` - Build configuration detection
- `BLI_sys_types.h` - System type definitions

### Geometry / Spatial
- `BLI_convexhull_2d.h` - 2D convex hull
- `BLI_boxpack_2d.h` - 2D box packing
- `BLI_delaunay_2d.hh` - Delaunay triangulation
- `BLI_kdopbvh.hh` - BVH acceleration structure

### Color
- `BLI_color.hh` - Color types and operations
- `BLI_color_mix.hh` - Color blending modes

## Naming Conventions

### Function Naming
- **`BLI_<subsystem>_<action>`** - Standard pattern
- **`BLI_math_*`** - Math operations
- **`BLI_*` for data structures** - `BLI_ghash_new()`, `BLI_gset_add()`, etc.
- **`BLI_path_*`** - Path operations

### Header Organization
- `.h` files: C-compatible headers (can be included from C code)
- `.hh` files: C++ headers (may use templates, classes, etc.)

### Test Files
- Unit tests in `tests/` directory with `_test.cc` suffix
- Performance tests in `tests/performance/`

## Key Patterns

### ListBase (Doubly-Linked List)
```c
ListBase list = {NULL, NULL};

// Add to end
BLI_addtail(&list, element);

// Iterate
for (Link *link = list.first; link; link = link->next) {
    // process link
}

// Find
void *found = BLI_findstring(&list, "name", offsetof(ID, name));
```

### GHash (Hash Table)
```c
GHash *gh = BLI_ghash_new(hash_fn, cmp_fn, "my hash");

BLI_ghash_insert(gh, key, value);
void *value = BLI_ghash_lookup(gh, key);

BLI_ghash_free(gh, NULL, NULL);
```

### Math Types
```c
float vec[3] = {1.0f, 2.0f, 3.0f};
float result[3];

normalize_v3_v3(result, vec);
float len = len_v3(vec);
```

### Memory Arena
```c
MemArena *arena = BLI_memarena_new(BLI_MEMARENA_STD_BUFSIZE, "arena");

void *data = BLI_memarena_alloc(arena, size);

// All arena memory freed at once
BLI_memarena_free(arena);
```

## Dependencies

- **No Blender-specific dependencies** - This is the foundation library
- External: standard C/C++ library, platform APIs

## Common Pitfalls

1. **ListBase Ownership**: Elements added to ListBase must be allocated with `MEM_mallocN()` or similar
2. **GHash Lifetime**: Keys/values are NOT copied - caller must manage lifetime
3. **Math Precision**: Use `float` for most operations, `double` only when necessary
4. **Thread Safety**: Most data structures are NOT thread-safe by default

## For AI Agents

- Prefer C++ containers (`BLI::Vector`, `BLI::Map`, `BLI::Set`) over C equivalents for new code
- Use `BLI_math_*.hh` headers for C++ code, `BLI_math_*.h` for C code
- Test files are in `tests/` directory, not co-located with source
- `BLI_utildefines.h` contains essential macros - include it when needed
- When working with paths, always use `BLI_path_*` functions for cross-platform compatibility
