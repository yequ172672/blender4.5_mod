<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# source

## Purpose
Contains all Blender source code. blender/ is the core library with all modules; creator/ contains the main() entry point.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| blender/ | Core Blender library - all functional modules (rendering, modeling, animation, IO, etc.) |
| creator/ | Application entry point (main function), startup, and argument parsing |

## For AI Agents
### Working In This Directory
The blender/ subdirectory is the heart of the codebase and contains dozens of modules (see its own AGENTS.md for details). The creator/ subdirectory is small and contains only the application bootstrap code. Most development work happens inside blender/. When navigating the source, start from blender/AGENTS.md to understand the module structure. The build system (CMake) is configured in build_files/, not here.

<!-- MANUAL: -->
