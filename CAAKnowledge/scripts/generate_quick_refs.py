#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CATIA CAA V5 知识库蒸馏 - Phase 4: 生成快速参考卡和故障排除知识库
"""

import json
import os
import re
from pathlib import Path
from collections import defaultdict

def generate_quick_refs():
    """生成快速参考卡"""
    base_dir = Path("CAAKnowledge")
    output_dir = base_dir / "quick-refs"
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # 1. 通用CAA模式快速参考
    patterns_content = '''---
title: "CAA开发常用模式"
type: "quick-reference"
---

# CAA开发常用模式

## 1. 接口声明与实现

### 接口头文件 (.h)
```cpp
// LocalFramework include
#include "YourModule.h"

// IID声明
extern IID ExportedByYourModule IID_CATIYourInterface;

class ExportedByYourModule CATIYourInterface : public CATBaseUnknown
{
  CATDeclareInterface;
  
public:
  virtual HRESULT YourMethod(int iParam) = 0;
};
```

### 接口实现文件 (.cpp)
```cpp
#include "TIE_CATIYourInterface.h"
CATImplementInterface(ClassName, CATBaseUnknown)
  CATImplementInterfaceMethod(YourMethod)
EndCATImplementInterface
```

## 2. 命令实现模式

### 命令类声明
```cpp
class ExportedByModule ClassName : public CATCommand
{
  CATDeclareClass;
  
public:
  ClassName();
  virtual ~ClassName();
  
  virtual CATStatusChangeRC Activate   (CATCommand * iCmd, CATNotification * iNotif);
  virtual CATStatusChangeRC Desactivate (CATCommand * iCmd, CATNotification * iNotif);
  virtual void Execute();
};
```

### 命令实现
```cpp
CATImplementClass(ClassName, DataExtension, CATCommand, NULL);

ClassName::ClassName() : CATCommand(NULL, "ClassName")
{
  // 初始化
}

void ClassName::Execute()
{
  // 命令逻辑
}
```

## 3. QueryInterface 模式

```cpp
STDMETHODIMP CYourClass::QueryInterface(REFIID iid, void **ppv)
{
  if (iid == IID_CATBaseUnknown || iid == IID_CATIYourInterface)
  {
    *ppv = (CATBaseUnknown*)this;
    ((CATBaseUnknown*)*ppv)->AddRef();
    return S_OK;
  }
  return E_NOINTERFACE;
}
```

## 4. 数据扩展模式

### 声明
```cpp
class ExportedByModule ClassName : public CATBaseUnknown
{
  CATDeclareClass;
  CATDeclareHeader;
  
public:
  ClassName();
  virtual ~ClassName();
  
  // 方法
};
```

### 实现
```cpp
CATImplementClass(ClassName, DataExtension, CATBaseUnknown, NULL);
```

## 5. 文档操作

### 打开文档
```cpp
CATDocument *pDoc = NULL;
CATInstantiateDocument("path/to/file.CATPart", pDoc);
```

### 获取活动文档
```cpp
CATDocument *pDoc = NULL;
CATGlobalLayout *pLayout = CATGlobalLayout::GetGlobLayout();
if (pLayout) pLayout->GetActiveDocument(&pDoc);
```

### 获取Product
```cpp
CATBaseUnknown *pRoot = NULL;
CATIDocId *pDocId = NULL;
pDoc->QueryInterface(IID_CATIDocId, (void**)&pDocId);
if (pDocId)
{
  CATIPLMNavReference *pRef = NULL;
  pDocId->GetRelatedPrincipalObject(IID_CATIPLMNavReference, (void**)&pRef);
  if (pRef) pRef->GetReferencedProduct(&pRoot);
}
```

## 6. 选择操作

### 添加选择
```cpp
CATPathElement &Path = GetInitEditor()->GetUIActiveObject();
AddUICallback(CATISO_SelectionNotify, (CATCommandMethod)&YourClass::SelectionMethod);
```

### 获取选择
```cpp
CATListOfCATBaseUnknown_var sel;
GetSelection(sel);
```

## 7. 错误处理

```cpp
#include "CATError.h"
#include "CATIACORBABBL.h"

HRESULT hr = YourFunction();
if (FAILED(hr))
{
  CATError *pErr = NULL;
  CATUnicodeString msg;
  CATGetErrorMessage(hr, msg);
  // 处理错误
}
```

## 8. CATIA 路径

常用头文件路径:
- `CATBaseUnknown.h` - COM基础
- `CATDocument.h` - 文档
- `CATSession.h` - 会话
- `CATInterfaceObject.h` - 接口对象
- `CATCommand.h` - 命令
- `CATDialog.h` - 对话框
- `CATPathElement.h` - 路径元素
- `CATFrmEditor.h` - 编辑器
- `CATFrmLayout.h` - 布局

---
'''
    
    with open(output_dir / "common-patterns.md", 'w', encoding='utf-8') as f:
        f.write(patterns_content)
    
    print(f"Generated common-patterns.md")
    
    # 2. 接口继承层次快速参考
    inheritance_content = '''---
title: "CAA核心接口继承层次"
type: "quick-reference"
---

# CAA核心接口继承层次

## 基础接口

```
CATBaseUnknown
    │
    ├── CATIObject (对象)
    │    │
    │    └── CATIDocId (文档标识)
    │
    ├── CATIDocument (文档)
    │    ├── CATIPart (零件)
    │    ├── CATIProduct (产品)
    │    └── CATIAssembly (装配)
    │
    ├── CATIEditor (编辑器)
    │
    ├── CATIAlias (别名)
    │
    └── CATIAttribute (属性)
```

## 产品结构接口

```
CATBaseUnknown
    │
    └── CATIPLMNavReference (引用)
         │
         ├── CATIPLMNavOccurrence (实例)
         │
         └── CATIPLMNavProduct (产品)
              │
              ├── CATIPLMNavInstance (实例)
              │
              └── CATIPLMNavEntity (实体)
```

## 几何与拓扑接口

```
CATBaseUnknown
    │
    ├── CATIGeometricObject (几何对象)
    │    ├── CATICurve (曲线)
    │    │    ├── CATICircle
    │    │    ├── CATIEllipse
    │    │    ├── CATILine
    │    │    └── CATISpline
    │    │
    │    └── CATISurface (曲面)
    │         ├── CATICylinder
    │         ├── CATIPlane
    │         └── CATISphere
    │
    └── CATIBasicTopology (基础拓扑)
         ├── CATIFace (面)
         ├── CATIEdge (边)
         ├── CATIWire (线框)
         └── CATIBody (体)
```

## 工作台与命令接口

```
CATBaseUnknown
    │
    ├── CATIWorkbench (工作台)
    │
    ├── CATICommand (命令)
    │
    └── CATICommandHeader (命令头)
```

---
'''
    
    with open(output_dir / "interface-hierarchy.md", 'w', encoding='utf-8') as f:
        f.write(inheritance_content)
    
    print(f"Generated interface-hierarchy.md")
    
    # 3. 开发环境快速参考
    env_content = '''---
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

CATIncludeFiles(ModuleName1) = \\
  LocalInterfaces/*.h        \\
  PublicInterfaces/*.h

CATSourcesFiles(ModuleName1) = \\
  src/*.cpp

CATDllSymbLinks(ModuleName1) = \\
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
'''
    
    with open(output_dir / "development-env.md", 'w', encoding='utf-8') as f:
        f.write(env_content)
    
    print(f"Generated development-env.md")


def generate_troubleshooting():
    """生成故障排除知识库"""
    base_dir = Path("CAAKnowledge")
    output_dir = base_dir / "troubleshooting"
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # 编译器错误
    compiler_errors = '''---
title: "编译器错误排查指南"
type: "troubleshooting"
---

# 编译器错误排查指南

## 常见编译器错误

### C1001: 语法错误

**原因**: 代码中存在语法错误

**解决方案**:
- 检查括号匹配 `{}`, `()`, `[]`
- 检查分号 `;` 是否遗漏
- 检查逗号 `,` 是否应为分号

### C2065: 未声明的标识符

**原因**: 使用了未声明的变量或函数

**解决方案**:
- 检查 `#include` 是否正确
- 检查拼写是否正确
- 检查头文件是否包含该声明

### C2512: 没有默认构造函数

**原因**: 类没有默认构造函数

**解决方案**:
```cpp
// 添加默认构造函数
class MyClass {
public:
    MyClass() {}  // 添加
    MyClass(int param) { /* ... */ }
};
```

### LNK2001: 无法解析的外部符号

**原因**: 链接器找不到符号定义

**解决方案**:
1. 检查符号拼写
2. 确认库文件已链接
3. 检查 `CATImplementClass` 是否正确

### C2248: 无法访问私有成员

**原因**: 尝试访问类的私有成员

**解决方案**:
- 使用公共方法访问
- 检查友元声明

### C2664: 参数类型转换错误

**原因**: 参数类型不匹配

**解决方案**:
- 检查函数签名
- 使用正确的类型转换

---
'''
    
    with open(output_dir / "compiler-errors.md", 'w', encoding='utf-8') as f:
        f.write(compiler_errors)
    
    print(f"Generated compiler-errors.md")
    
    # 链接器错误
    linker_errors = '''---
title: "链接器错误排查指南"
type: "troubleshooting"
---

# 链接器错误排查指南

## 常见链接器错误

### LNK2001: 无法解析的外部符号

**最常见原因**:

1. **TIE文件未包含**
```cpp
// 在实现文件中添加
#include "TIE_CATIYourInterface.h"
```

2. **CATImplementClass缺失**
```cpp
CATImplementClass(ClassName, DataExtension, CATBaseUnknown, NULL);
```

3. **Imakefile.mk配置错误**
```makefile
CATSourcesFiles(ModuleName) = src/*.cpp
```

### LNK2019: 无法解析的外部符号

**检查清单**:
- [ ] 符号拼写正确
- [ ] 库文件已添加到链接
- [ ] 导出宏正确 (`ExportedByModule`)

### LNK1104: 无法打开文件

**解决方案**:
```bash
# 清理并重新编译
mkmk -clean
mkmk -build
```

### LNK1168: 无法打开写入

**原因**: 文件被占用

**解决方案**:
- 关闭正在使用的CATIA
- 关闭依赖该DLL的进程

### 多重定义

**原因**: 多个源文件定义了同一符号

**解决方案**:
- 使用 `extern` 声明
- 使用 `#ifndef` 保护

---
'''
    
    with open(output_dir / "linker-errors.md", 'w', encoding='utf-8') as f:
        f.write(linker_errors)
    
    print(f"Generated linker-errors.md")
    
    # 运行时错误
    runtime_errors = '''---
title: "运行时错误排查指南"
type: "troubleshooting"
---

# 运行时错误排查指南

## 常见运行时错误

### E_NOINTERFACE (0x80004002)

**原因**: QueryInterface失败

**解决方案**:
```cpp
// 确保正确实现QueryInterface
STDMETHODIMP CYourClass::QueryInterface(REFIID iid, void **ppv)
{
    if (iid == IID_CATBaseUnknown || iid == IID_CATIYourInterface)
    {
        *ppv = (CATBaseUnknown*)this;
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}
```

### CATNullPtr (NULL指针)

**预防措施**:
```cpp
if (NULL_var == NULL) return E_FAIL;

// 或使用CATSafeRef
CATSafeRef(CATIYourInterface) spYourIntf;
```

### CATInvalidType (类型无效)

**原因**: 类型转换失败

**解决方案**:
- 检查对象是否实现了目标接口
- 使用 `IsKindOf` 验证类型

### CATAccessError (访问错误)

**原因**: 访问权限问题

**解决方案**:
- 检查接口是否为公共接口
- 确认组件是否正确实例化

### CATDocument 数据丢失

**预防措施**:
```cpp
// 保存前检查
if (pDoc->IsModified())
{
    pDoc->Save();
}
```

### 内存泄漏 (MLK)

**检测方法**:
- 使用 `CATMemoryManager`
- 检查 `AddRef()` / `Release()` 平衡

**常见原因**:
```cpp
// 错误: 每次都AddRef
CATBaseUnknown *p = obj;
p->AddRef();  // 不需要

// 正确: QueryInterface后需要AddRef
CATBaseUnknown *p = NULL;
obj->QueryInterface(IID_CATIUnknown, (void**)&p);
// p已经AddRef，不需要再次AddRef
```

---
'''
    
    with open(output_dir / "runtime-errors.md", 'w', encoding='utf-8') as f:
        f.write(runtime_errors)
    
    print(f"Generated runtime-errors.md")


def generate_summary():
    """生成汇总索引"""
    base_dir = Path("CAAKnowledge")
    output_dir = base_dir / "quick-refs"
    
    index_content = '''---
title: "快速参考索引"
type: "index"
---

# 快速参考索引

## 📌 常用模式
- [CAA开发常用模式](common-patterns.md)
- [核心接口继承层次](interface-hierarchy.md)
- [开发环境配置](development-env.md)

## 🔧 故障排除
- [编译器错误](troubleshooting/compiler-errors.md)
- [链接器错误](troubleshooting/linker-errors.md)
- [运行时错误](troubleshooting/runtime-errors.md)

## 📚 相关资源
- [API接口参考](../api-reference/interfaces/)
- [使用案例](../use-cases/)
- [知识库数据](../data/knowledge_base.json)
'''
    
    with open(output_dir / "index.md", 'w', encoding='utf-8') as f:
        f.write(index_content)
    
    print(f"Generated quick-refs/index.md")


if __name__ == "__main__":
    print("=" * 60)
    print("生成快速参考卡和故障排除知识库")
    print("=" * 60)
    
    generate_quick_refs()
    generate_troubleshooting()
    generate_summary()
    
    print("\n完成!")
