<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# blenloader - .blend File Loading/Saving

File I/O module for Blender's native .blend file format. Handles reading, writing, versioning (data migration across Blender versions), and undo file management. Public API uses the `BLO_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Core read/write implementation and versioning code |
| `tests/` | Unit tests |

## Key Files

| File | Description |
|------|-------------|
| `BLO_readfile.hh` | Main file reading API - open, read, setup .blend files |
| `BLO_read_write.hh` | Read/write helpers for DNA struct serialization |
| `BLO_writefile.hh` | File writing API - save .blend files |
| `BLO_undofile.hh` | Undo file/memory management |
| `BLO_blend_validate.hh` | .blend file validation |
| `BLO_userdef_default.h` | Default user preferences |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `readfile.cc` | Main .blend file reading logic |
| `readblenentry.cc` | Entry-level read operations |
| `writefile.cc` | Main .blend file writing logic |
| `undofile.cc` | Undo buffer management |
| `blend_validate.cc` | File integrity validation |
| `versioning_*.cc` | Version-specific data migration (250 through 450) |
| `versioning_common.cc` | Shared versioning utilities |
| `versioning_dna.cc` | DNA struct versioning |
| `versioning_defaults.cc` | Default value versioning |
| `versioning_userdef.cc` | User preferences versioning |
| `readfile_tempload.cc` | Temporary file loading for link/append |

## Common Patterns

- .blend files use a DNA (Structure DNA) system for self-describing data
- Versioning code migrates old file data to current format (versioning_250.cc through versioning_450.cc)
- `readfile.cc` and `writefile.cc` are the core pair handling file I/O
- BHead blocks form the chunked structure of .blend files

## For AI Agents

- `BLO_readfile.hh` is the main API for opening .blend files
- Versioning files (`intern/versioning_*.cc`) are updated each release - add migration code here for new releases
- `BLO_read_write.hh` provides the serialization interface for DNA types
- Undo system relies on in-memory .blend file snapshots (`BLO_undofile.hh`)
- Depends on `blenloader_core` for low-level header/block parsing
