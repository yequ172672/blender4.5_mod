<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# ikplugin - Inverse Kinematics Solver Plugin System

Inverse Kinematics (IK) plugin framework providing multiple IK solver backends. Public API uses the `BIK_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | IK solver plugin implementations |

## Key Files

| File | Description |
|------|-------------|
| `BIK_api.h` | Public IK API - initialize and solve IK chains |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `ikplugin_api.cc` | Plugin dispatch layer - routes to active solver |
| `ikplugin_api.h` | Internal plugin API |
| `iksolver_plugin.cc` | Standard IK solver plugin (Blender native) |
| `iksolver_plugin.h` | Standard solver interface |
| `itasc_plugin.cc` | iTaSC solver plugin (Instantaneous Task Specification using Constraints) |
| `itasc_plugin.h` | iTaSC solver interface |

## Common Patterns

- Plugin architecture allows multiple IK solver backends
- Two built-in solvers: standard (iksolver) and iTaSC (more advanced, constraint-based)
- `ikplugin_api.cc` acts as dispatcher selecting the active solver
- Solvers are registered and selected per-armature

## For AI Agents

- `BIK_api.h` is the minimal public interface
- The standard solver (`iksolver_plugin.cc`) is the default - simpler, faster
- iTaSC (`itasc_plugin.cc`) supports more complex constraint specifications
- Integration point: armature evaluation calls into this module for IK solving
- Module is small and focused - just the IK solving step of the animation pipeline
