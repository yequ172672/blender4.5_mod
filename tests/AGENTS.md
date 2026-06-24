<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# tests

## Purpose
Test suites for Blender - C++ gtests, Python tests, performance benchmarks, and test data files.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| blender_as_python_module/ | Tests for using Blender as a Python module (import bpy) |
| coverage/ | Code coverage configuration and reporting tools |
| files/ | Test data files (.blend, images, etc.) used by test scripts |
| gtests/ | C++ Google Test unit tests for Blender's internal libraries |
| performance/ | Performance benchmarks and regression tests |
| python/ | Python-based test scripts covering operators, IO, UI, and scripting API |
| utils/ | Shared test utilities, helpers, and runner scripts |

## For AI Agents
### Working In This Directory
Run Python tests with `ctest` or via the Blender binary with `--python-tests`. C++ gtests are built when `WITH_GTESTS=ON` in CMake. Test data files in files/ are referenced by relative path from test scripts - do not move them without updating references. When adding new tests, follow the existing naming convention and place test data in the appropriate subdirectory under files/. Performance tests in performance/ track rendering and simulation timing.

<!-- MANUAL: -->
