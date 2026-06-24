<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# Blender 4.5

## Purpose
Blender 是一款免费开源的 3D 创作套件，支持建模、雕刻、动画、模拟、渲染、合成、运动跟踪、视频编辑和 2D 动画制作。此仓库为 Blender v4.5 发行版源码。

## Key Files
| File | Description |
|------|-------------|
| `CMakeLists.txt` | 顶层 CMake 构建配置 |
| `make.bat` | Windows 构建快捷脚本 |
| `pyproject.toml` | Python 项目配置（工具链/格式化） |
| `README.md` | 项目说明 |

## Subdirectories
| Directory | Purpose |
|-----------|---------|
| `assets/` | 内置资产（笔刷、几何节点预设） |
| `build_files/` | 构建系统配置（CMake、平台脚本、CI） |
| `doc/` | 文档（文件格式、Doxygen、Python API、许可证） |
| `extern/` | 第三方依赖库（Bullet、Eigen、OpenVDB 等） |
| `intern/` | 内部共享库（Cycles 渲染器、GHOST 窗口系统、BMesh 等） |
| `lib/` | 预编译依赖库（按平台：win/mac/linux） |
| `locale/` | 国际化翻译文件（.po） |
| `release/` | 发布相关资源（数据文件、桌面集成、安装包） |
| `scripts/` | Python 脚本（插件、启动脚本、预设、模板） |
| `source/` | **核心源码**（Blender 内核 + 创建器入口） |
| `tests/` | 测试套件（单元测试、Python 测试、性能测试） |
| `tools/` | 开发工具（代码检查、调试、维护脚本） |

## For AI Agents

### Working In This Directory
- 使用 CMake 构建系统，构建目录通常为 `../build/`
- Python 脚本位于 `scripts/`，插件系统基于 Python
- 核心 C/C++ 源码在 `source/blender/`，是最常修改的区域
- `source/blender/makesdna/` 定义数据结构，`source/blender/makesrna/` 定义 RNA 属性系统

### Testing Requirements
- C++ 测试在 `tests/gtests/`
- Python 测试在 `tests/python/`
- 运行测试：`ctest` 或直接执行 Python 测试脚本

### Common Patterns
- DNA/RNA 系统：`makesdna` 定义数据布局，`makesrna` 提供属性访问接口
- 编辑器操作通过 `editors/` 中的 operator 注册
- 节点系统在 `nodes/` 中，支持着色器、几何节点、合成器
- 渲染管线：`render/` + `intern/cycles/`

## Build Requirements
- CMake 3.20+
- C++20 编译器（MSVC 2022 / GCC 12+ / Clang 15+）
- Python 3.11+
- 详见 `build_files/cmake/` 和 `doc/guides/`

<!-- MANUAL: -->
