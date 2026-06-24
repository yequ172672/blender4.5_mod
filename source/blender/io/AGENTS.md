<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# io - Import/Export Modules

Import/export framework for various 3D file formats. Each format has its own subdirectory with dedicated importers and exporters.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `alembic/` | Alembic (.abc) format - animated geometry cache |
| `collada/` | COLLADA (.dae) format - XML-based 3D interchange |
| `common/` | Shared I/O utilities across format modules |
| `csv/` | CSV format import/export |
| `fbx/` | FBX format - Autodesk interchange format |
| `grease_pencil/` | Grease Pencil specific I/O operations |
| `ply/` | PLY format - polygon mesh data |
| `stl/` | STL format - stereolithography mesh data |
| `usd/` | Universal Scene Description (USD) by Pixar |
| `wavefront_obj/` | Wavefront OBJ format - text-based mesh format |

## Key Files

| File | Description |
|------|-------------|
| `CMakeLists.txt` | Top-level build configuration for all I/O modules |

## Common Patterns

- Each format subdirectory contains its own `CMakeLists.txt`
- Most modules have `intern/` for implementation and may expose public headers
- Importers and exporters are typically registered as operators in Blender's operator system
- `common/` provides shared utilities (axis conversion, coordinate system transforms, etc.)

## For AI Agents

- Each format is self-contained in its own subdirectory
- USD and Alembic are the most complex modules with extensive C++ code
- OBJ, STL, PLY are simpler text/binary mesh formats
- Look at `common/` for shared I/O infrastructure used across formats
- FBX support includes both binary and ASCII variants
