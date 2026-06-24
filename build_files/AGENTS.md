<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# build_files

## Purpose
Blender's build system infrastructure. Contains CMake configuration, platform-specific build files, third-party dependency compilation scripts, CI/CD pipeline definitions, packaging specifications, and developer utility scripts. This directory does not contain Blender source code -- it drives how the source is compiled, tested, and packaged across all supported platforms.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `build_environment/` | Scripts and patches to build Blender's third-party library dependencies from source (Linux/Windows). Includes a top-level `CMakeLists.txt`, per-platform subdirectories, and patch files. |
| `buildbot/` | Buildbot CI/CD configuration used by Blender's official build farm. Contains `pipeline_config.yaml` for branch/commit/submodule settings per pipeline step. |
| `cmake/` | Core CMake build logic. `Modules/` holds `Find*.cmake` for all external dependencies. `platform/` has per-OS toolchain files (`platform_win32.cmake`, `platform_apple.cmake`, `platform_unix.cmake`). `config/` defines build presets (release, lite, full, developer, headless, bpy, cycles standalone). Also includes `macros.cmake`, `packaging.cmake`, `testing.cmake`, and `buildinfo.cmake`. |
| `config/` | Buildbot pipeline YAML configuration for the `update-code` step (branch pinning, submodule/SVN artifact versions). Not used by `utils/make_update.py`. |
| `package_spec/` | Packaging specifications and archive scripts for release builds. |
| `utils/` | Developer-facing Python/shell utilities: `make_update.py` (source/lib update), `make_source_archive.py`, `make_bpy_wheel.py`, `make_test.py`, `make_utils.py` (shared helpers). |
| `windows/` | Windows `.cmd` batch scripts wrapping common developer workflows: configure, build (MSBuild/Ninja), detect MSVC/LLVM/dependencies, run tests, format code, manage SVN libs, etc. |

## For AI Agents
### Working In This Directory
- Most changes here affect how Blender is compiled, not what it compiles. Expect impact on all platforms.
- CMake modules in `cmake/Modules/` follow the `FindXxx.cmake` convention. When adding a new external dependency, create a corresponding `Find*.cmake` module and add an `option(WITH_XXX ...)` in the top-level `CMakeLists.txt`.
- Platform-specific logic lives in `cmake/platform/`. The `dependency_targets.cmake` file centralizes imported target definitions.
- Build presets in `cmake/config/` (e.g., `blender_release.cmake`, `blender_lite.cmake`) set collections of `WITH_*` options. These are passed via `-C` at configure time.
- Windows scripts in `windows/` are `.cmd` batch files. They parse arguments with `parse_arguments.cmd` and detect the MSVC toolchain via `detect_msvc*.cmd` / `autodetect_msvc.cmd`.
- `build_environment/` compiles all third-party libs. Its `CMakeLists.txt` is a standalone project, not included in the main Blender build.

### Common Patterns
- **Finding dependencies**: Each `Find*.cmake` module sets `XXX_FOUND`, `XXX_INCLUDE_DIRS`, `XXX_LIBRARIES`, and optionally imported targets. Follow this pattern when adding new ones.
- **Build options**: Feature toggles use `option(WITH_XXX "description" ON/OFF)` and are checked with `if(WITH_XXX)` guards throughout the build.
- **Platform branching**: `platform_win32.cmake`, `platform_apple.cmake`, and `platform_unix.cmake` are included conditionally based on `CMAKE_SYSTEM_NAME`.
- **Build info**: `buildinfo.cmake` extracts git hash/branch info and generates `buildinfo_static.h` for embedding in the Blender binary.
- **Packaging**: `packaging.cmake` and `package_spec/` handle CPack configuration and platform-specific installer generation.

## Dependencies
- Top-level `CMakeLists.txt` (includes `build_files/cmake/` modules)
- `source/` directories (what gets compiled by this build system)
- `lib/` directory (pre-built third-party libraries on Windows/macOS, populated by `make_update.py` or SVN)
- Git submodules and SVN externals (managed by `utils/make_update.py` and `config/pipeline_config.yaml`)

<!-- MANUAL -->
