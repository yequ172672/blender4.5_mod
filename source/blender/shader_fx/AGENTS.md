<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# shader_fx - Grease Pencil Shader Effects

Shader effects system for Grease Pencil objects providing post-processing visual effects. Public API uses the `FX_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Individual shader effect implementations |

## Key Files

| File | Description |
|------|-------------|
| `FX_shader_types.h` | Shader effect type definitions and registration |
| `CMakeLists.txt` | Build configuration |

## Available Effects (intern/)

| File | Effect |
|------|--------|
| `FX_shader_blur.cc` | Blur effect |
| `FX_shader_colorize.cc` | Colorize/tint effect |
| `FX_shader_flip.cc` | Mirror/flip effect |
| `FX_shader_glow.cc` | Glow/bloom effect |
| `FX_shader_pixel.cc` | Pixelation effect |
| `FX_shader_rim.cc` | Rim/outline lighting effect |
| `FX_shader_shadow.cc` | Drop shadow effect |
| `FX_shader_swirl.cc` | Swirl distortion effect |
| `FX_shader_wave.cc` | Wave distortion effect |
| `FX_shader_util.cc` | Shared shader utilities |
| `FX_shader_util.h` | Utility header |
| `FX_ui_common.cc` | Common UI panel code for effects |
| `FX_ui_common.h` | UI common header |

## Common Patterns

- Each effect is a self-contained C++ file in `intern/`
- Effects are registered as Grease Pencil modifiers in the UI
- Effects apply as screen-space post-processing on Grease Pencil renders
- `FX_ui_common.cc/h` provides shared UI panel construction
- `FX_shader_util.cc/h` provides shared shader code and helpers

## For AI Agents

- This module is specific to Grease Pencil rendering pipeline
- Each effect file follows a consistent pattern: type registration, draw callback, panel UI
- Effects stack on top of each other (applied in order)
- `FX_shader_types.h` defines the effect type enum and metadata
- To add a new effect: create `FX_shader_neweffect.cc` in intern/, register in types
