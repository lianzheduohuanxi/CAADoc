---
title: "CAA开发环境快速参考"
type: "quick-reference"
---

# CAA开发环境快速参考

## 目录结构

```
FrameworkName.edu/
├── ModuleName.m/           # 模块目录
│   ├── src/               # 源文件
│   ├── LocalInterfaces/   # 本地接口
│   ├── PublicInterfaces/  # 公共接口
│   ├── LocalRsc/          # 本地资源
│   ├── PublicRsc/         # 公共资源
│   ├── ProtectedInterfaces/ # 受保护接口
│   └── LocalizedInterfaces/ # 本地化接口
│
├── FrameworkName.RscCNext.m/  # 框架资源
│
├── Imakefile              # 模块配置
│
└── IdentityCard           # 标识文件
```

## Imakefile.mk 示例

```makefile
TEMPLATES = C++AppPyMac

SUBDIRS = ModuleName1 ModuleName2

CATIncludeFiles(ModuleName1) = \
  LocalInterfaces/*.h        \
  PublicInterfaces/*.h

CATSourcesFiles(ModuleName1) = \
  src/*.cpp

CATDllSymbLinks(ModuleName1) = \
  $(GENERIC_FWK_DIR)/CATIAfrFoundationWindowing
```

## 编译命令

```bash
# 完整编译
mkmk -framework FrameworkName -build

# 单模块编译
mkmk -module ModuleName -build

# 清理
mkmk -framework FrameworkName -clean
```

## 常用宏

| 宏 | 说明 |
|-----|------|
| `CATDeclareClass` | 声明类 |
| `CATImplementClass` | 实现类 |
| `CATDeclareInterface` | 声明接口 |
| `CATImplementInterface` | 实现接口 |
| `CATAddRef` | 增加引用计数 |
| `CATRelease` | 减少引用计数 |

## 常用环境变量

| 变量 | 说明 |
|------|------|
| `CASROOT` | CAA安装根目录 |
| `CATAKit` | 工具包目录 |
| `FrameworkName` | 框架路径 |

---
