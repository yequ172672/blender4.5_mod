<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# asset_system - Asset Browser System

Asset browser infrastructure providing asset catalogs, library management, asset representation, and indexing. Public API uses the `AS_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Internal implementation of asset catalog and library systems |
| `tests/` | Unit tests |

## Key Files

| File | Description |
|------|-------------|
| `AS_asset_catalog.hh` | Asset catalog management - create, organize, assign catalogs |
| `AS_asset_catalog_path.hh` | Catalog path handling (hierarchical catalog addressing) |
| `AS_asset_catalog_tree.hh` | Tree representation of catalog hierarchy |
| `AS_asset_library.hh` | Asset library management - local, system, custom libraries |
| `AS_asset_representation.hh` | Asset representation - metadata, preview, type info |
| `AS_essentials_library.hh` | Built-in essentials asset library |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `asset_catalog.cc` | Catalog operations implementation |
| `asset_catalog_collection.cc` | Collection of catalogs for a library |
| `asset_catalog_definition_file.cc` | Catalog definition file I/O (.cats.txt) |
| `asset_catalog_path.cc` | Path parsing and manipulation |
| `asset_catalog_tree.cc` | Tree construction and traversal |
| `asset_library.cc` | Library management implementation |
| `asset_library_service.cc` | Singleton service for library access |
| `asset_representation.cc` | Asset data representation |
| `library_types/` | Different library type implementations |
| `utils.cc` | Shared utilities |

## Common Patterns

- Catalogs are organized hierarchically using path-based addressing
- Asset definitions are stored in .blend files alongside catalog definition files (.cats.txt)
- `AssetLibraryService` provides singleton access to asset libraries
- Asset representations wrap Blender data blocks with metadata for the browser

## For AI Agents

- `AS_asset_library.hh` and `AS_asset_catalog.hh` are the primary public APIs
- Catalog paths use `/` separator (e.g., `characters/humanoids/`)
- Library types: All, Current File, Essentials, User Library
- `intern/asset_library_service.cc` manages library lifecycle
- Integration point with the UI asset browser panel
