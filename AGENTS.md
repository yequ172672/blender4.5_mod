<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# Blender 4.5

## Pinned Rules
- **禁止全量编译**：除非用户在当前对话中明确提出“全量编译/完整构建 Blender”，否则绝对不要运行 `blender`、`ALL_BUILD`、`INSTALL`、`PACKAGE`、`make.bat` 默认目标等可能触发全量构建或链接全量 Blender 的命令。
- **增量编译必须使用 Release**：需要验证源码时，只能在用户明确同意后运行受影响的最小目标，并且必须使用 `--config Release`。禁止使用 Debug 增量编译；禁止并行启动多个 CMake/MSBuild 构建。
- **优先轻量验证**：默认使用源码级测试、Python 单元测试、静态检查、单个库/模块目标的最小验证；任何高负载构建命令都必须先说明目标、配置和预计影响，并等待用户确认。

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

### Git Push Rules
此仓库是 GitHub fork（`yequ172672/blender4.5_mod`），fork 时 LFS 二进制文件未完整迁移，直接 `git push` 会因 LFS 配额限制失败。

**推送方式**：必须跳过 LFS 上传
```bash
GIT_LFS_SKIP_PUSH=1 git push origin blender-v4.5-release
```
注意：`git push --no-verify` 不能解决此问题（LFS 配额是 GitHub 服务端限制）。

**同步上游官方 Blender**：
```bash
git remote add upstream https://github.com/blender/blender.git
git fetch upstream blender-v4.5-release
git merge upstream/blender-v4.5-release
# 推送时同样需要 GIT_LFS_SKIP_PUSH=1
```

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
