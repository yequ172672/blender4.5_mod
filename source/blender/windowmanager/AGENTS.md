<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# Window Manager Module (`source/blender/windowmanager/`)

Core window manager handling the event loop, operator system, window/screen management, and input processing. Central coordination layer between the OS, editors, and Blender's event-driven architecture.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `gizmo/` | Gizmo framework (interactive manipulators in 3D viewport) |
| `intern/` | Internal implementation of WM subsystems |
| `message_bus/` | Message bus for inter-module pub/sub notifications |
| `xr/` | XR/VR session management |

## Key Files

| File | Description |
|------|-------------|
| `WM_api.hh` | Main public API header for the window manager |
| `WM_keymap.hh` | Keymap definitions and shortcut handling API |
| `WM_message.hh` | Message bus API for observer pattern |
| `WM_toolsystem.hh` | Tool system API (active tool per editor) |
| `WM_types.hh` | Core type definitions (wmWindow, wmEvent, etc.) |
| `wm.hh` | Internal WM header |
| `wm_cursors.hh` | Cursor shape definitions |
| `wm_draw.hh` | Window/region drawing internals |
| `wm_event_system.hh` | Event dispatch internals |
| `wm_event_types.hh` | Event type constants |
| `wm_files.hh` | File I/O (open, save, revert) internals |
| `wm_surface.hh` | Offscreen surface internals |
| `wm_window.hh` | Window management internals |
| `CMakeLists.txt` | Build configuration |

## Key Internal Files (`intern/`)

| File | Description |
|------|-------------|
| `wm_event_system.cc` | Core event loop and operator dispatch |
| `wm_operators.cc` | Operator execution and property handling |
| `wm_window.cc` | Window creation, resizing, multi-window |
| `wm_draw.cc` | Draw manager and swap chain |
| `wm_keymap.cc` | Keymap processing and shortcut matching |
| `wm_files.cc` | File open/save/revert operations |
| `wm_init_exit.cc` | Blender initialization and shutdown |
| `wm_jobs.cc` | Background job system |
| `wm_gesture.cc` | Gesture recognition (box, circle, line) |
| `wm_dragdrop.cc` | Drag and drop system |
| `wm_toolsystem.cc` | Active tool management |
| `wm_operator_type.cc` | Operator type registration |
| `wm_operator_props.cc` | Operator property handling |
| `wm_stereo.cc` | Stereo 3D display support |
| `wm_splash_screen.cc` | Splash screen display |

## Common Patterns

- **WM_ prefix**: All public API functions use `WM_` prefix
- **Event loop**: `wm_event_system.cc` drives the main loop: OS events -> wmEvent -> operator dispatch
- **Operator dispatch**: Operators are invoked via `WM_operator_name_call()`, `WM_operator_properties_alloc()`
- **Window structure**: `wmWindow` -> `bScreen` -> `ScrArea` -> `ARegion` hierarchy
- **Keymaps**: Per-editor keymaps registered via `WM_keymap_add_item()`, stored in `wmKeyConfig`
- **Messages**: `WM_msg_*` API for loose-coupling between subsystems
- **Gizmos**: `WM_gizmo_*` API for interactive viewport tools
- **Jobs**: `WM_jobs_*` API for background threading with progress reporting

## For AI Agents

- `wm_event_system.cc` is the heart of Blender's main loop - understand this file to trace any operator invocation
- Operator registration happens in `wm_operator_type.cc`; each operator type defines poll/exec/invoke/modal callbacks
- The window hierarchy is: `wmWindow` (OS window) -> `bScreen` (layout) -> `ScrArea` (editor area) -> `ARegion` (subdivision)
- Keymaps are context-sensitive: modifiers, editor type, and mode determine which operator fires
- The message bus (`message_bus/`) enables reactive updates without tight coupling
- The tool system (`WM_toolsystem.hh`) manages the active tool per editor type, replacing older modal tool patterns
