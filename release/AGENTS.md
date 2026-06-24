<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# release

## Purpose
Release packaging resources - platform installers, data files shipped with Blender, desktop integration files, and release notes.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| bin/ | Binary wrapper scripts and launchers |
| darwin/ | macOS-specific packaging, Info.plist, and DMG configuration |
| datafiles/ | Data files bundled with releases (startup.blend, themes, icons, studiolights, etc.) |
| extensions/ | Default extensions and extension repository metadata |
| freedesktop/ | Linux desktop integration files (.desktop, icons, AppData) |
| license/ | License files included in release packages |
| lts/ | Long-term support release configuration and policies |
| pypi/ | Packaging configuration for the Blender Python module (pip) |
| release_notes/ | Templates and assets for release notes |
| text/ | Plain text files bundled with releases (README, changelog) |
| windows/ | Windows-specific packaging (installer scripts, signing config) |

## For AI Agents
### Working In This Directory
Files here control what ships with official Blender builds. The datafiles/ subdirectory is particularly important - it contains startup.blend, default themes, icons, and other essential data. Changes to datafiles/ affect all users. Platform-specific subdirectories (darwin/, windows/, freedesktop/) contain OS integration files. When modifying release packaging, verify changes work across all target platforms.

<!-- MANUAL: -->
