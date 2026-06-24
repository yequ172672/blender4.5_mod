<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# extern/ — Third-Party Dependencies

## Purpose
Blender 捆绑的第三方库（vendored dependencies）。每个子目录对应一个独立的外部项目，通常不建议直接修改，升级时应从上游同步。大部分库通过 CMake 的 `WITH_*` 选项条件编译。

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `Eigen3/` | 线性代数库（矩阵、向量运算），Cycles 渲染器和 libmv 依赖 |
| `audaspace/` | 音频处理库，支持多后端（OpenAL、SDL、WASAPI 等） |
| `binreloc/` | Linux 二进制路径重定位，用于便携式安装 |
| `bullet2/` | Bullet 物理引擎，用于刚体模拟和碰撞检测 |
| `ceres/` | Google 非线性最小二乘优化库，用于 libmv 运动跟踪 |
| `cuew/` | CUDA Extension Wrangler，动态加载 CUDA 运行时 |
| `curve_fit_nd/` | N 维曲线拟合库，用于笔刷曲线和路径简化 |
| `draco/` | Google 网格压缩库，用于 glTF 网格压缩/解压 |
| `fast_float/` | 高性能浮点数解析库，比 strtod 快 4 倍 |
| `fmtlib/` | {fmt} 格式化库，C++ 的 printf 替代方案 |
| `gflags/` | Google 命令行参数解析库，ceres/glog 依赖 |
| `glew-es/` | OpenGL ES Extension Wrangler，GLES 扩展加载 |
| `glog/` | Google 日志库，用于 libmv 和 Cycles 日志 |
| `gmock/` | Google Mock 框架，用于 C++ 模拟测试 |
| `gtest/` | Google Test 框架，用于 C++ 单元测试 |
| `hipew/` | HIP Extension Wrangler，动态加载 AMD HIP 运行时 |
| `json/` | nlohmann/json，现代 C++ JSON 解析/序列化库 |
| `lzma/` | LZMA 压缩算法，用于 .blend 文件压缩 |
| `lzo/` | LZO 快速压缩算法，用于 .blend 文件压缩 |
| `mantaflow/` | Mantaflow 流体模拟框架，用于烟雾/火焰/液体模拟 |
| `nanosvg/` | 轻量 SVG 解析库，用于 SVG 文件导入 |
| `quadriflow/` | QuadriFlow 四边形重网格化算法 |
| `rangetree/` | 区间树数据结构，用于内部范围查询 |
| `renderdoc/` | RenderDoc 图形调试器 API 头文件 |
| `tinygltf/` | glTF 2.0 文件格式加载/保存库 |
| `ufbx/` | FBX 文件格式解析库，用于 FBX 导入 |
| `vulkan_memory_allocator/` | Vulkan 显存分配器（VMA），用于 Vulkan 后端 |
| `wcwidth/` | Unicode 字符宽度计算，用于终端/文本对齐 |
| `wintab/` | Wintab API 头文件，Windows 数位板支持 |
| `xdnd/` | X11 拖放协议实现，Linux 拖放支持 |
| `xxhash/` | xxHash 快速哈希算法，用于数据去重和校验 |

## For AI Agents

### Working In This Directory
- **不要直接修改这些库的源码**，除非修复明确的 Blender 集成 bug
- 升级第三方库时，保留 `README.blender` 中记录的本地修改说明
- 库的构建通过 `CMakeLists.txt` 中的 `WITH_*` 选项控制（如 `WITH_BULLET`、`WITH_DRACO`）
- 部分库支持系统版本替代（`WITH_SYSTEM_BULLET`、`WITH_SYSTEM_LZO` 等）

### Common Patterns
- 每个库有独立的 `CMakeLists.txt`，顶层 `extern/CMakeLists.txt` 按条件引入
- Cycles 渲染器相关：`cuew`（CUDA）、`hipew`（HIP）、`glew-es`（OpenGL）
- 运动跟踪相关：`ceres` + `gflags` + `glog`
- 文件压缩：`lzma` + `lzo`
- 测试框架：`gtest` + `gmock`

### Conditional Build Flags
| Flag | Libraries |
|------|-----------|
| `WITH_BULLET` | bullet2 |
| `WITH_DRACO` | draco |
| `WITH_LIBMV` | ceres, gflags, glog |
| `WITH_MOD_FLUID` | mantaflow |
| `WITH_CYCLES` | cuew, hipew |
| `WITH_GTESTS` | gtest, gmock |
| `WITH_VULKAN_BACKEND` | vulkan_memory_allocator |
| `WITH_QUADRIFLOW` | quadriflow |
| `WITH_IO_FBX` | ufbx |

## Dependencies
- `ceres` 依赖 `gflags` 和 `glog`
- `glog` 依赖 `gflags`
- `cuew` 和 `hipew` 仅在动态加载 CUDA/HIP 时构建（`WITH_CUDA_DYNLOAD`/`WITH_HIP_DYNLOAD`）
- `audaspace` 使用自定义 CMake 配置（`blender_config.cmake`）

<!-- MANUAL: -->
