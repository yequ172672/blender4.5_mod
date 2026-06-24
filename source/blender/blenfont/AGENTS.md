<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# blenfont - Font Loading and Text Rendering

Font library handling font loading, glyph rasterization, and text rendering for Blender's UI and 3D viewport. Public API uses the `BLF_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Font loading, glyph cache, and rendering implementation |
| `tests/` | Unit tests |

## Key Files

| File | Description |
|------|-------------|
| `BLF_api.hh` | Complete public API - font init, draw text, measure, search |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `blf.cc` | Top-level API implementation (draw, measure, etc.) |
| `blf_default.cc` | Default font selection and management |
| `blf_dir.cc` | Font directory scanning and font discovery |
| `blf_font.cc` | Font loading and management (FreeType integration) |
| `blf_font_default.cc` | Default font initialization |
| `blf_font_win32_compat.cc` | Windows font compatibility |
| `blf_glyph.cc` | Glyph caching and rasterization |
| `blf_internal.hh` | Internal function declarations |
| `blf_internal_types.hh` | Internal data structures |
| `blf_thumbs.cc` | Font preview thumbnail generation |

## Common Patterns

- Uses FreeType library for font file parsing and glyph rasterization
- Glyph atlas caching for efficient text rendering
- Supports multiple font formats (TTF, OTF, etc.)
- Default fonts are loaded from Blender's bundled resources
- `BLF_api.hh` provides both immediate-mode drawing and measurement functions

## For AI Agents

- `BLF_api.hh` is the single public header - all APIs are here
- Key functions: `BLF_draw()`, `BLF_width()`, `BLF_height()`, `BLF_boundbox()`
- Font IDs are used to reference loaded fonts (integers)
- Default font access: `BLF_default()` returns the default font ID
- Glyph caching in `intern/blf_glyph.cc` is performance-critical
- Windows has special font handling in `blf_font_win32_compat.cc`
