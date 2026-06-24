<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# simulation - Simulation Framework

Physics simulation framework providing mass-spring systems and implicit solvers. Primarily used for cloth and soft body simulation. Public API uses the `SIM_` prefix.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Internal simulation solver implementations |

## Key Files

| File | Description |
|------|-------------|
| `SIM_mass_spring.h` | Mass-spring simulation API - cloth, soft body dynamics |
| `CMakeLists.txt` | Build configuration |

## Key Implementation Files (intern/)

| File | Description |
|------|-------------|
| `SIM_mass_spring.cc` | Mass-spring system implementation |
| `implicit_blender.cc` | Blender-native implicit solver |
| `implicit_eigen.cc` | Eigen-based implicit solver |
| `implicit.h` | Implicit solver interface |
| `hair_volume.cc` | Hair volume/collision simulation |
| `ConstrainedConjugateGradient.h` | Constrained CG solver |
| `eigen_utils.h` | Eigen math utilities |

## Common Patterns

- Two solver backends: native Blender and Eigen library
- Implicit integration for stable cloth/soft body simulation
- Mass-spring model with constraint solving
- Hair simulation includes volume preservation

## For AI Agents

- `SIM_mass_spring.h` is the only public header - API is intentionally minimal
- Most simulation logic lives in `intern/`
- Two parallel solver implementations: `implicit_blender.cc` (legacy) and `implicit_eigen.cc` (Eigen-based)
- Hair simulation support via `intern/hair_volume.cc`
- The module is focused on cloth/soft-body - rigid body and fluid are elsewhere
