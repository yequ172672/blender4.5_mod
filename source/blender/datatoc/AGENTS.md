<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# datatoc - Data-to-C Array Tool

Build-time utility that converts data files (shaders, icons, fonts, etc.) into C arrays for embedding in the Blender binary. No public API prefix - standalone build tool.

## Subdirectories

None - single source file module.

## Key Files

| File | Description |
|------|-------------|
| `datatoc.cc` | Main tool - reads binary/text files, outputs C array source |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- Runs at build time, not at runtime
- Converts files like GLSL shaders, SVG icons, font files into `unsigned char[]` or `char[]` constants
- Generated C files are compiled into the Blender binary
- Supports both binary data and text data modes
- This eliminates runtime file dependencies for core resources

## For AI Agents

- Build tool only - never linked into Blender at runtime
- Usage: `datatoc input_file output_file array_name [--text]`
- The `--text` flag treats input as text (null-terminated string) vs binary data
- Generated output is a C source file with a const array and size variable
- Used extensively in CMake build to embed GLSL shaders, icons, startup scripts, etc.
