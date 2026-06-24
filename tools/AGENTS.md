<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# tools

## Purpose
Developer tools for code quality, debugging, maintenance, and release processes.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| check_blender_release/ | Validation scripts for release builds |
| check_docs/ | Documentation consistency and link checking tools |
| check_source/ | Source code linting, style checking, and static analysis |
| config/ | Shared configuration files for tools and scripts |
| debug/ | Debugging utilities and helper scripts |
| git/ | Git workflow scripts and hooks |
| modules/ | Shared Python modules used by multiple tool scripts |
| svn_rev_map/ | SVN-to-git revision mapping (historical migration data) |
| triage/ | Bug triage and issue management utilities |
| utils/ | General-purpose developer utility scripts |
| utils_api/ | API documentation generation tools |
| utils_build/ | Build system helper scripts and configuration |
| utils_doc/ | Documentation generation and maintenance tools |
| utils_ide/ | IDE project file generators and configuration helpers |
| utils_maintenance/ | Codebase maintenance scripts (refactoring, cleanup) |

## For AI Agents
### Working In This Directory
These are developer-facing scripts, not shipped with Blender. Most scripts are Python and can be run standalone. The check_source/ tools enforce coding standards - run them before submitting patches. Build utilities in utils_build/ wrap CMake and platform-specific build commands. When adding new developer tools, place them in the most specific subdirectory and ensure they are documented with a brief header comment.

<!-- MANUAL: -->
