<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# creator - Blender Executable Entry Point

Main entry point for the Blender application. Contains the `main()` function, command-line argument parsing, signal handling, and application initialization/shutdown.

## Subdirectories

None - top-level source directory.

## Key Files

| File | Description |
|------|-------------|
| `creator.cc` | Main entry point - `main()` function, init/shutdown sequence |
| `creator_args.cc` | Command-line argument parsing (extensive - all CLI flags) |
| `creator_intern.h` | Internal header shared between creator source files |
| `creator_signals.cc` | OS signal handling (crash, interrupt, etc.) |
| `blender_launcher_win32.c` | Windows launcher - handles DPI, console, path setup |
| `buildinfo.c` | Build information (git hash, date, etc.) |
| `symbols_apple.map` | macOS symbol export map |
| `symbols_unix.map` | Unix symbol export map |
| `CMakeLists.txt` | Build configuration (67KB - comprehensive build setup) |

## Common Patterns

- `creator.cc` orchestrates the full Blender lifecycle: init -> event loop -> exit
- `creator_args.cc` is one of the largest files - parses all CLI arguments
- Signal handlers in `creator_signals.cc` catch crashes for debugging
- Windows has a separate launcher (`blender_launcher_win32.c`) for Win32-specific init
- Symbol maps control exported symbols for plugin loading on Unix/macOS

## For AI Agents

- `creator.cc` is the starting point for understanding Blender's initialization
- `creator_args.cc` (~98KB) defines ALL command-line flags - reference for CLI behavior
- Build configuration in `CMakeLists.txt` (~68KB) links all Blender modules together
- The main loop uses Blender's `WM` (Window Manager) event system
- Exit codes and error handling are defined here
- `blender_launcher_win32.c` handles Windows-specific entry before `main()`
