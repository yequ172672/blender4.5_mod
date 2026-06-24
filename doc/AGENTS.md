<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# doc

## Purpose
Documentation for developers and contributors, including file format specs, Doxygen config, coding guides, Python API reference generation, and license information.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| blender_file_format/ | Specifications for the .blend file format |
| doxygen/ | Doxygen configuration for generating C/C++ API documentation |
| guides/ | Coding style guides, contribution guidelines, and developer documentation |
| license/ | License texts and related legal documentation |
| manpage/ | Unix man page source for the blender command |
| python_api/ | Sphinx configuration and templates for generating the Python API reference |

## For AI Agents
### Working In This Directory
This is a documentation-only directory with no runtime code. When updating docs, ensure cross-references remain valid. The python_api/ subdirectory uses Sphinx with a custom Blender-specific extension to auto-generate API docs from Python docstrings. Guide documents in guides/ establish coding conventions that apply across the entire source tree.

<!-- MANUAL: -->
