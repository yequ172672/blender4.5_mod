<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# animrig - Animation Rigging System

Animation rigging module providing keying, drivers, actions, NLA, bone collections, and pose management. Public API uses the `ANIM_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Internal implementation files for all public APIs |

## Key Files

| File | Description |
|------|-------------|
| `ANIM_action.hh` | Action data management - strips, layers, keyframe data |
| `ANIM_action_iterators.hh` | Iterators for traversing action data structures |
| `ANIM_action_legacy.hh` | Legacy action API for backward compatibility |
| `ANIM_animdata.hh` | Animation data (AnimData) assignment and lookup |
| `ANIM_armature.hh` | Armature utilities for animation |
| `ANIM_armature_iter.hh` | Armature bone/PBone iteration helpers |
| `ANIM_bone_collections.hh` | Bone collection management (groups of bones) |
| `ANIM_bonecolor.hh` | Bone color/theme utilities |
| `ANIM_driver.hh` | Driver creation and management |
| `ANIM_evaluation.hh` | Animation evaluation - baking, evaluation pipeline |
| `ANIM_fcurve.hh` | F-Curve utilities - evaluation, interpolation, sampling |
| `ANIM_keyframing.hh` | Keyframe insertion, removal, and manipulation |
| `ANIM_keyingsets.hh` | Keying set definitions and registration |
| `ANIM_nla.hh` | Non-Linear Animation (NLA) strip and track management |
| `ANIM_pose.hh` | Pose library and pose manipulation |
| `ANIM_rna.hh` | RNA path utilities for animation |
| `ANIM_versioning.hh` | Versioning helpers for animation data |
| `ANIM_visualkey.hh` | Visual keying (recording transform from evaluated state) |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- All public headers use the `ANIM_` prefix and `.hh` extension
- Implementation files live in `intern/` with corresponding `_test.cc` files
- Functions operate on Blender DNA types (e.g., `bAction`, `AnimData`, `FCurve`)
- Integration with RNA system for property-based keyframing

## For AI Agents

- Start with `ANIM_keyframing.hh` and `ANIM_action.hh` for core animation workflows
- `ANIM_fcurve.hh` is central to curve-based animation evaluation
- `ANIM_bone_collections.hh` manages bone grouping (replaces old bone layers)
- Versioning files in `intern/versioning.cc` handle legacy data migration
