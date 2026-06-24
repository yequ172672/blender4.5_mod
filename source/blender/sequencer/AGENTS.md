<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# sequencer - Video Sequence Editor (VSE)

Video Sequence Editor module for non-linear video editing. Handles strips, effects, transitions, rendering, and timeline management. Public API uses the `SEQ_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Internal implementation of all sequencer operations |

## Key Files

| File | Description |
|------|-------------|
| `SEQ_add.hh` | Adding strips to the sequencer (movie, audio, scene, etc.) |
| `SEQ_animation.hh` | Animation data for strips |
| `SEQ_channels.hh` | Channel management |
| `SEQ_connect.hh` | Strip connection/dependency management |
| `SEQ_edit.hh` | Editing operations (cut, duplicate, etc.) |
| `SEQ_effects.hh` | Effect strip management |
| `SEQ_iterator.hh` | Iteration over strips and sequences |
| `SEQ_modifier.hh` | Strip modifiers (color correction, etc.) |
| `SEQ_offscreen.hh` | Offscreen rendering for strips |
| `SEQ_prefetch.hh` | Frame prefetching for smooth playback |
| `SEQ_proxy.hh` | Proxy/low-res preview generation |
| `SEQ_relations.hh` | Strip dependency relationships |
| `SEQ_render.hh` | Strip rendering pipeline |
| `SEQ_retiming.hh` | Speed/time remapping for strips |
| `SEQ_select.hh` | Strip selection |
| `SEQ_sequencer.hh` | Main sequencer management |
| `SEQ_sound.hh` | Audio strip handling |
| `SEQ_thumbnail_cache.hh` | Strip thumbnail caching |
| `SEQ_time.hh` | Time/frame calculations for strips |
| `SEQ_transform.hh` | Strip position/scale transforms |
| `SEQ_utils.hh` | General utilities |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

- `strip_add.cc`, `strip_edit.cc`, `strip_select.cc`, `strip_transform.cc` - Strip operations
- `effects/` - Built-in effect implementations
- `cache/` - Frame caching system
- `render.cc` - Rendering pipeline
- `prefetch.cc` - Background frame prefetching

## Common Patterns

- `Strip` is the fundamental data type representing a clip on the timeline
- Strips are organized in channels (layers) with dependency ordering
- Effects and modifiers are applied per-strip in the render pipeline
- Proxy system generates low-resolution previews for performance

## For AI Agents

- `SEQ_sequencer.hh` is the main management API
- Rendering pipeline: `SEQ_render.hh` coordinates strip evaluation
- Effects system: `SEQ_effects.hh` manages video/audio effects
- Retiming: `SEQ_retiming.hh` handles speed changes and time remapping
- Intern files use `SEQ_` prefix in function names with `static` linkage
