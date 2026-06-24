<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 -->
<!-- Updated: 2026-06-25 -->

# scripts/ - Blender Python Scripting Layer

## Purpose

This directory contains Blender's entire Python scripting layer: bundled add-ons, core Python modules, startup scripts executed on launch, built-in presets, line-rendering (Freestyle) modules, and user-facing script/OSL/TOML templates. It is the backbone of Blender's Python API surface (`bpy`) and UI registration system.

## Subdirectories

| Directory | Description |
|---|---|
| `addons_core/` | Bundled add-ons shipped with Blender (e.g. `bl_pkg`, `io_scene_gltf2`, `node_wrangler`, `rigify`) |
| `freestyle/` | Freestyle line-rendering Python modules and predefined stroke styles |
| `modules/` | Core Python modules: `bpy`, `bpy_types`, `bpy_extras`, `mathutils` (C-side), `gpu_extras`, `addon_utils`, internal helpers (`_bpy_internal/`) |
| `presets/` | Built-in presets for cameras, Cycles, EEVEE, keyconfigs, operators, render settings, etc. |
| `site/` | Python `sitecustomize.py` for Blender's embedded Python interpreter |
| `startup/` | Startup scripts run at launch: `bl_ui/` (UI panels/menus), `bl_operators/` (built-in operators), `bl_app_templates_system/`, and `keyingsets_builtins.py` / `nodeitems_builtins.py` |
| `templates_osl/` | Open Shading Language (OSL) script templates for the text editor |
| `templates_py/` | Python script templates (operators, UI panels, gizmos, bmesh, import/export, etc.) |
| `templates_toml/` | TOML extension manifest template (`blender_manifest.toml`) |

## Key Files (top-level)

No top-level Python files exist; all content lives in the subdirectories above.

## For AI Agents

### Common Patterns

- **Add-on structure**: Each add-on in `addons_core/` follows the standard Blender add-on convention with an `__init__.py` containing `register()` / `unregister()` functions and a `bl_info` dict (or `blender_manifest.toml` for extensions).
- **Startup registration**: Files under `startup/bl_ui/` and `startup/bl_operators/` register UI classes and operators at Blender launch. They are auto-imported by Blender's startup sequence.
- **Module hierarchy**: `modules/bpy/` is the thin Python wrapper around the C-defined `bpy` module. `modules/bpy_extras/` provides helper utilities (object utils, space types, etc.). `modules/bpy_types.py` defines Python-side type stubs.
- **Presets**: Preset files under `presets/` are plain Python or config files loaded by Blender's preset system. Subdirectory names correspond to preset categories (e.g. `cycles/`, `keyconfig/`).
- **Freestyle styles**: `freestyle/styles/` contains standalone Python scripts defining stroke shaders; `freestyle/modules/freestyle/` contains the Freestyle Python API wrappers.

### When Modifying This Tree

- Changes to `startup/bl_ui/` or `startup/bl_operators/` affect every Blender session immediately.
- Changes to `modules/` affect the Python API available to all scripts and add-ons.
- New add-ons in `addons_core/` should follow the existing add-on structure and include proper `register`/`unregister` lifecycle.
- Preset files are user-facing; maintain backward compatibility with existing Blender versions where possible.

### Dependencies

- This tree depends on Blender's C/C++ Python modules (`bpy`, `mathutils`, `gpu`, `bmesh`, etc.) compiled into the Blender binary.
- `modules/_bpy_internal/` contains internal implementation details not intended for external use.
- `addons_core/bl_pkg/` depends on Blender's extension/PackageManager infrastructure.

<!-- MANUAL: Add custom notes, project-specific conventions, or override any section above -->
