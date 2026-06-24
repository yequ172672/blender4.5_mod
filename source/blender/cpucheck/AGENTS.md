<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# cpucheck - CPU Feature Detection

Runtime CPU feature detection to verify the host CPU supports required instruction sets before Blender starts. No public API prefix - standalone check.

## Subdirectories

None - single source file module.

## Key Files

| File | Description |
|------|-------------|
| `cpu_check.cc` | CPU feature detection and compatibility check |
| `CMakeLists.txt` | Build configuration |

## Common Patterns

- Runs early in Blender startup before main initialization
- Checks for required CPU instruction sets (SSE, AVX, etc.)
- Exits with an error message if CPU requirements are not met
- Platform-specific detection using CPUID or equivalent intrinsics

## For AI Agents

- Single-file module - straightforward to understand
- `cpu_check.cc` is called very early in the startup sequence
- If Blender fails to start with a CPU compatibility error, this module is responsible
- Minimum CPU requirements vary by platform and build configuration
- This is a pass/fail check - not a feature dispatch system
