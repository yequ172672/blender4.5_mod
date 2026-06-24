<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# Editors Module (`source/blender/editors/`)

Editor implementations for all Blender editor types. Each subdirectory is a self-contained editor module providing operators, drawing code, and UI logic.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `animation/` | Animation editor operators and keyframe tools |
| `armature/` | Armature editing and bone operations |
| `asset/` | Asset browser and asset management |
| `curve/` | Legacy curve editing |
| `curves/` | New curves object editing |
| `datafiles/` | Embedded data files for editors |
| `geometry/` | Geometry node editor utilities |
| `gizmo_library/` | Reusable gizmo implementations (cursors, manipulators) |
| `gpencil_legacy/` | Legacy Grease Pencil editor |
| `grease_pencil/` | New Grease Pencil editor |
| `id_management/` | ID data block management operators |
| `include/` | Public headers (`ED_*.hh`, `UI_*.hh`) |
| `interface/` | UI widget system (buttons, panels, layouts) |
| `io/` | Import/export operators |
| `lattice/` | Lattice editing |
| `mask/` | Mask editor |
| `mesh/` | Mesh editing operators |
| `metaball/` | Metaball editing |
| `object/` | Object mode operators and transforms |
| `physics/` | Physics simulation operators |
| `pointcloud/` | Point cloud editing |
| `render/` | Render result display and operators |
| `scene/` | Scene management operators |
| `screen/` | Screen area management, headers, toolbars |
| `sculpt_paint/` | Sculpting and painting tools |
| `sound/` | Sound editing operators |
| `space_action/` | Action editor space |
| `space_api/` | Common space type registration API |
| `space_buttons/` | Properties editor space |
| `space_clip/` | Clip editor space |
| `space_console/` | Python console space |
| `space_file/` | File browser space |
| `space_graph/` | Graph editor space |
| `space_image/` | Image editor space |
| `space_info/` | Info editor space |
| `space_nla/` | NLA editor space |
| `space_node/` | Node editor space |
| `space_outliner/` | Outliner space |
| `space_script/` | Script editor space |
| `space_sequencer/` | Video sequence editor space |
| `space_spreadsheet/` | Spreadsheet editor space |
| `space_statusbar/` | Status bar space |
| `space_text/` | Text editor space |
| `space_topbar/` | Top bar space |
| `space_userpref/` | User preferences space |
| `space_view3d/` | 3D Viewport space |
| `transform/` | Transform system (grab, rotate, scale) |
| `undo/` | Undo/redo system for editors |
| `util/` | Shared editor utility functions |
| `uvedit/` | UV editor |

## Key Files

| File | Description |
|------|-------------|
| `include/ED_*.hh` | Public editor API headers (one per editor domain) |
| `include/UI_interface.hh` | UI widget API |
| `include/UI_interface_layout.hh` | UI layout API |
| `include/UI_icons.hh` | Icon definitions |
| `include/UI_view2d.hh` | 2D view scrolling/zooming |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- **Operator classes**: `WM_OT_*` naming convention, registered via `WM_OT_*` struct definitions
- **Public API**: `ED_*` prefix functions declared in `include/ED_*.hh` headers
- **UI API**: `UI_*` prefix functions from `include/UI_interface*.hh`
- **Space types**: Each `space_*` directory registers a `SpaceType` with draw, operator, and keymap callbacks
- **Draw functions**: `ED_region_*_draw()` for region rendering, `draw_handler_add` for overlays
- **Keymaps**: `ED_keymap_*` functions and keymap definitions in each space type
- **Poll functions**: `CTX_*` context queries to check editor state before operator execution

## For AI Agents

- Each `space_*` directory is a distinct editor type with its own draw pipeline, operators, and keymaps
- Operators follow Blender's `wmOperatorType` pattern: poll, exec, invoke, modal callbacks
- Editor headers in `include/` define the public API consumed by other modules
- The `transform/` module is shared across all editors for object/edit transforms
- `interface/` provides the immediate-mode UI widget system used by all editors
- When adding a new operator, register it in the appropriate editor's `edit.cc` or `*_ops.cc` file
