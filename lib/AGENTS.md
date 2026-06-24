<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# lib

## Purpose
Pre-compiled third-party dependency libraries for each supported platform. These are downloaded separately and not committed to git.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| linux_x64/ | Pre-built libraries for Linux x86-64 |
| macos_arm64/ | Pre-built libraries for macOS Apple Silicon (ARM64) |
| macos_x64/ | Pre-built libraries for macOS Intel (x86-64) |
| windows_arm64/ | Pre-built libraries for Windows ARM64 |
| windows_x64/ | Pre-built libraries for Windows x86-64 |

## For AI Agents
### Working In This Directory
This directory is not present in a fresh git clone. It is populated by the `make update` command or the `lib/` update scripts. Do not attempt to edit files here directly. If a dependency change is needed, modify the build configuration in `build_files/` instead. These libraries are version-locked and managed by Blender's build system.

<!-- MANUAL: -->
