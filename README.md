# Blender 4.5 Mod - Enhanced Bone Mirror

基于 [Blender 4.5](https://www.blender.org/) 官方源码修改的版本，增强了骨骼镜像命名匹配功能。

![Blender screenshot](https://code.blender.org/wp-content/uploads/2018/12/springrg.jpg "Blender screenshot")

## 🚀 特色功能

### 增强的镜像骨骼名称匹配

修改了 `BLI_string_flip_side_name` 函数，支持更多命名模式：

| 格式 | 示例 | 说明 |
|------|------|------|
| 3ds Max BIP | `bip001-L-UpperArm` → `bip001-R-UpperArm` | 中间位置的 L/R 标记 |
| 驼峰命名 | `ManLeftHand` → `ManRightHand` | 驼峰边界检测 |
| 数字前缀 | `bip001RightHand` → `bip001LeftHand` | 数字+大写字母边界 |
| 后缀格式 | `Bone.L` → `Bone.R` | 传统后缀格式 |
| 前缀格式 | `L_Bone` → `R_Bone` | 传统前缀格式 |
| 全词格式 | `leftArm` → `rightArm` | 完整单词 |

### 使用场景

- 使用 3ds Max BIP 骨骼命名的角色绑定
- 使用驼峰命名的骨骼系统
- 需要跨软件导入骨骼的场景
- 姿态模式下的 X-Axis Mirror 功能

## 📦 下载与安装

### 方法一：覆盖安装（推荐）

1. 下载 [Release](https://github.com/yequ172672/blender4.5_mod/releases) 中的 `blender.exe`
2. 下载官方 [Blender 4.5](https://www.blender.org/download/)
3. 解压官方版本到任意目录
4. 用下载的 `blender.exe` 替换官方的 `blender.exe`

```
你的Blender目录/
├── blender.exe  ← 替换这个文件
├── 4.5/
└── ...
```

### 方法二：便携版

1. 下载官方便携版 Blender 4.5
2. 解压后直接替换 `blender.exe`

## ⚠️ 注意事项

- 本版本基于 Blender 4.5 官方源码编译
- 不包含 OptiX（NVIDIA）和 HIP（AMD）渲染支持
- 其他功能与官方版本完全一致
- 配置文件会读取 `%APPDATA%\Blender Foundation\Blender\4.5\`

## 🔧 技术细节

### 修改的文件

- `source/blender/blenlib/intern/string_utils.cc` - 镜像名称匹配算法
- `source/blender/blenlib/tests/BLI_string_utils_test.cc` - 测试用例

### 算法改进

**Phase 1**: 单字母扫描（从右向左）
- 支持中间位置的 `l/r/L/R` 标记
- 要求两侧为分隔符或字符串边界

**Phase 2**: 全词扫描（从右向左）
- 支持 `left/right/Left/Right/LEFT/RIGHT`
- 支持驼峰边界检测（`lowercase→Uppercase`）

### 测试覆盖

- ✅ 20 个测试用例全部通过
- ✅ 向后兼容所有原有格式
- ✅ 新增支持 BIP 和驼峰命名

## 📝 更新日志

### v4.5.0-mod (2026-06-25)

- 增强 `BLI_string_flip_side_name` 函数
- 支持 3ds Max BIP 命名格式
- 支持驼峰命名边界检测
- 添加 20 个单元测试用例

## 🔗 相关链接

- [Blender 官网](https://www.blender.org/)
- [Blender 手册](https://docs.blender.org/manual/en/latest/)
- [GitHub 仓库](https://github.com/yequ172672/blender4.5_mod)
- [问题反馈](https://github.com/yequ172672/blender4.5_mod/issues)

## 📄 许可证

Blender as a whole is licensed under the GNU General Public License, Version 3.
Individual files may have a different but compatible license.

See [blender.org/about/license](https://www.blender.org/about/license) for details.

## 🙏 致谢

- [Blender Foundation](https://www.blender.org/) - 原始 Blender 项目
- [Blender 开发者社区](https://devtalk.blender.org/) - 技术支持
