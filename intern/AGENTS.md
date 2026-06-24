<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# intern/

## Purpose
Blender 的内部共享库集合，包含渲染引擎、窗口系统抽象、内存管理、音频播放、物理模拟、运动跟踪等核心子系统。这些库是 Blender 项目自身的组成部分（区别于 `extern/` 中的第三方依赖），通过顶层 `CMakeLists.txt` 按功能开关条件编译。

## Key Files
| File | Description |
|------|-------------|
| `CMakeLists.txt` | 顶层构建配置，按功能开关条件编译各子库 |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `atomic/` | 跨平台原子操作库（头文件库，源自 jemalloc） |
| `audaspace/` | 音频播放集成（Python 音频 API、声音烘焙） |
| `clog/` | C 日志库（分类日志、严重级别、过滤控制） |
| `cycles/` | **Cycles 路径追踪渲染器**（GPU+CPU 渲染、SVM/OSL 着色、去噪、USD Hydra 代理） |
| `dualcon/` | 双轮廓重网格化算法（Remesh 修改器的块状/平滑/锐边模式） |
| `eigen/` | Eigen 线性代数库的 C/C++ 封装（特征值、稀疏求解器、SVD） |
| `ghost/` | **通用操作系统工具包**（窗口/输入/光标/事件管理的跨平台抽象层） |
| `guardedalloc/` | **受保护内存分配器**（MEM_mallocN/MEM_freeN、泄漏检测、越界写入检测） |
| `iksolver/` | 基础逆运动学求解器（基于雅可比矩阵的骨骼 IK） |
| `itasc/` | iTaSC 高级 IK 求解器（基于 KDL 的约束 IK、加权 DLS/WLS 求解） |
| `libc_compat/` | Linux glibc 兼容层（为旧 glibc 提供 -ffast-math 符号） |
| `libmv/` | **运动跟踪库**（相机跟踪、物体跟踪、平面跟踪、光束平差） |
| `mantaflow/` | **流体模拟引擎**（烟雾/火焰/液体模拟，基于 Python 脚本的模拟步进） |
| `memutil/` | 内存工具类（缓存限制器、引用计数、字符串存储） |
| `mikktspace/` | MikkTSpace 切线空间计算（法线贴图烘焙的行业标准） |
| `opensubdiv/` | OpenSubdiv 集成（细分曲面评估，支持 CPU+GPU 加速） |
| `openvdb/` | OpenVDB 集成（稀疏体积数据处理的薄封装层） |
| `quadriflow/` | QuadriFlow 重网格化（四边形主导的场对齐重网格化） |
| `renderdoc_dynload/` | RenderDoc 动态加载（GPU 帧捕获调试集成） |
| `rigidbody/` | **刚体物理**（Bullet 物理引擎集成、碰撞检测、约束求解） |
| `sky/` | 天空模型（Hosek-Wilkie 解析模型、Nishita 大气散射） |
| `slim/` | SLIM UV 参数化（保角展平 + 面积补偿的最小失真 UV 映射） |
| `uriconvert/` | URI 转文件路径（仅 Windows） |
| `utfconv/` | UTF-8/16 编码转换（仅 Windows） |
| `wayland_dynload/` | Wayland 动态加载（运行时加载 Wayland 客户端库，仅 Linux） |

## For AI Agents

### Working In This Directory
- 顶层 `CMakeLists.txt` 控制构建顺序和条件编译开关
- **始终构建**：atomic、clog、ghost、guardedalloc、libmv、memutil、opensubdiv、mikktspace、eigen、sky
- **条件构建**：audaspace（`WITH_AUDASPACE`）、dualcon（`WITH_MOD_REMESH`）、iksolver（`WITH_IK_SOLVER`）、itasc（`WITH_IK_ITASC`）、cycles（多个依赖）、rigidbody（`WITH_BULLET`）、mantaflow（`WITH_MOD_FLUID`）、slim（`WITH_UV_SLIM`）、openvdb（`WITH_OPENVDB`）、quadriflow（`WITH_QUADRIFLOW`）、renderdoc_dynload（`WITH_RENDERDOC`）、wayland_dynload（`WITH_GHOST_WAYLAND`）
- 平台特定库：libc_compat（Linux）、utfconv/uriconvert（Windows）、wayland_dynload（Linux Wayland）

### Common Patterns
- **C API 封装**：大多数 C++ 库通过 `extern/` 或顶层头文件提供 C API（如 `RBI_api.h`、`IK_solver.h`、`openvdb_capi.h`）
- **CMake 别名**：部分库定义了 `bf::intern::*` 别名目标（如 `bf::intern::guardedalloc`、`bf::intern::clog`）
- **GHOST 后端架构**：`ghost/intern/` 下按平台组织（Win32、Cocoa、X11、Wayland、SDL、Headless），通过条件编译选择
- **Cycles 多设备架构**：`cycles/device/` 下按后端组织（cpu、cuda、optix、hip、metal、oneapi），kernel 代码需要同时支持 CPU 和多种 GPU
- **内存管理**：所有 Blender C/C++ 代码应使用 `MEM_mallocN`/`MEM_freeN`（来自 guardedalloc），而非直接 malloc/free

### Testing Requirements
- 测试分散在各子目录的 `tests/` 文件夹中
- 主要测试：`guardedalloc/tests/`（内存分配器）、`atomic/tests/`（原子操作）、`opensubdiv/internal/topology/`（拓扑管理）
- Cycles 有独立测试在 `cycles/test/`

## Dependencies
| Library | Used By | Purpose |
|---------|---------|---------|
| Eigen (extern) | eigen, dualcon, iksolver, itasc, quadriflow, slim | 线性代数基础 |
| Bullet (extern) | rigidbody | 刚体物理引擎 |
| OpenSubdiv (extern) | opensubdiv, cycles | 细分曲面 |
| OpenVDB (extern) | openvdb, mantaflow, cycles | 稀疏体积数据 |
| Boost | cycles | 算法和数据结构 |
| TBB | cycles, mantaflow | 并行计算 |
| Python | mantaflow, audaspace | 脚本绑定 |
| Embree/OIDN | cycles | 光线追踪/去噪 |
| CUDA/HIP/Metal/oneAPI | cycles | GPU 计算后端 |
| Bullet (extern) | rigidbody | 刚体物理 |

<!-- MANUAL: -->
