<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# blenloader_core - Core File Loading Utilities

Low-level .blend file parsing utilities providing BHead block and blend header handling. Lower-level than `blenloader`, used by it. Public API uses the `BLO_core_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Implementation of core file parsing |

## Key Files

| File | Description |
|------|-------------|
| `BLO_core_bhead.hh` | BHead block reading/writing - fundamental .blend file chunk |
| `BLO_core_blend_header.hh` | .blend file header parsing (magic, version, endianness) |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `blo_core_bhead.cc` | BHead block I/O implementation |
| `blo_core_blend_header.cc` | Header parsing implementation |

## Common Patterns

- Extracted from `blenloader` to allow use by other modules (e.g., thumbnail extraction)
- BHead blocks are the fundamental chunk type in .blend files
- Header parsing handles endianness detection and byte swapping
- Minimal dependencies - can be used without the full blenloader stack

## For AI Agents

- This is a low-level extraction from the larger `blenloader` module
- `BLO_core_blend_header.hh` handles the file header: file code, pointer size, endianness, version
- `BLO_core_bhead.hh` handles individual blocks: code, size, SDNA index, count
- Used by `blendthumb` for thumbnail extraction without full file parsing
- Used by `blenloader` as the foundation for complete file reading
- Keep this module minimal - it should only contain parsing primitives
