<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# locale

## Purpose
Internationalization (i18n) translation files in .po format for Blender's UI strings.

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| po/ | Gettext .po translation files, one per supported language |

## For AI Agents
### Working In This Directory
Translation files are in standard gettext .po format. Each .po file corresponds to one target language. Strings are extracted from the Blender source code and translated via an external translation platform. Avoid manually editing .po files unless performing a targeted fix; use the translation workflow tools instead. When adding new translatable strings to the source, ensure they use the proper `IFACE_()` or `N_()` macros so they are picked up by `xgettext`.

<!-- MANUAL: -->
