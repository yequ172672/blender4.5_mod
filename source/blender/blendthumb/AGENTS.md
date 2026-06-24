<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# blendthumb - .blend File Thumbnail Generator

Thumbnail extraction and generation for .blend files. Provides platform-specific thumbnail providers for file managers. No public prefix - internal tool.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `src/` | Source files for thumbnail extraction and platform integration |

## Key Files (src/)

| File | Description |
|------|-------------|
| `blender_thumbnailer.cc` | Command-line thumbnail generator (cross-platform) |
| `blendthumb.hh` | Shared header for thumbnail operations |
| `blendthumb_extract.cc` | Extract embedded thumbnail from .blend files |
| `blendthumb_png.cc` | PNG encoding for thumbnail output |
| `blendthumb_win32.cc` | Windows shell thumbnail provider |
| `blendthumb_win32_dll.cc` | Windows DLL entry point for shell extension |
| `blendthumb_win32.def` | Windows DLL exports definition |
| `blendthumb_win32.rc` | Windows resource file |
| `thumbnail_provider.h` | Thumbnail provider interface |
| `thumbnail_provider.mm` | macOS QuickLook thumbnail provider (Objective-C++) |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- Thumbnails are embedded in .blend files as PNG data
- Platform-specific shell integration: Windows Shell Extension, macOS QuickLook
- `blendthumb_extract.cc` reads the thumbnail from the .blend file header
- Command-line tool (`blender_thumbnailer.cc`) for batch thumbnail generation
- Cross-platform build with platform-specific source conditionally compiled

## For AI Agents

- This is a standalone tool, not a library used by Blender itself
- Windows: registers as a shell extension DLL for Explorer thumbnail previews
- macOS: implements QuickLook plugin via Objective-C++ (`thumbnail_provider.mm`)
- Linux: uses `blender_thumbnailer` command-line tool with .thumbnailer desktop entry
- .blend file format embeds a PNG thumbnail near the file beginning
