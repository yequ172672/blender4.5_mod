<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# blentranslation - Internationalization/Translation

Internationalization (i18n) support for Blender's user interface. Handles language selection, string translation via gettext, and locale management. Public API uses the `BLT_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Translation implementation |
| `msgfmt/` | Message format tool for .po/.mo files |

## Key Files

| File | Description |
|------|-------------|
| `BLT_lang.hh` | Language initialization and locale management |
| `BLT_translation.hh` | String translation API - translate UI strings |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `blt_lang.cc` | Language setup, locale initialization |
| `blt_translation.cc` | Translation lookup and caching |
| `messages.cc` | Built-in message catalog |
| `messages.hh` | Message catalog header |
| `messages_apple.mm` | macOS-specific locale handling |

## Common Patterns

- Uses gettext-style translation (.po/.mo files)
- `BLT_translation.hh` provides `BLT_translate()` and related macros
- Translation context support for disambiguation (same English string, different translations)
- Language catalogs loaded at startup based on user preferences
- `msgfmt/` tool compiles .po translation files to binary .mo format

## For AI Agents

- `BLT_translation.hh` is the main API - provides `BLT_translate()` and CTX macros
- Translation contexts (`BLT_translate_ctxt()`) disambiguate identical source strings
- Built-in messages in `intern/messages.cc` for system-level strings
- macOS has special handling in `messages_apple.mm` for locale detection
- Integration: UI code calls `BLT_translate()` for all user-visible strings
