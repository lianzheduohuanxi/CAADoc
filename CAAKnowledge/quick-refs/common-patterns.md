---
title: "CAA开发常用模式"
type: "quick-reference"
verified: true
verified_source: "CAAApplicationFrame.edu 源码"
---

# CAA开发常用模式

> ⚠️ 本文档中所有代码模式均从 .edu 源码中验证提取。

## 1. 接口声明与实现

### 接口头文件 (.h)

**源码来源**: `CAAApplicationFrame.edu/PublicInterfaces/CAAIAfrMRUManagement.h`

```cpp
#ifndef CAAIAfrMRUManagement_h
#define CAAIAfrMRUManagement_h

#include <CATBaseUnknown.h>       // Needed to derive from

class CATUnicodeString;
#include <CATListOfCATUnicodeString.h>

// Local Framework
#include "CAAAfrCustCommandHdrModel.h"  // Needed to export the IID

// Global Unique IDentifier defined in .cpp
extern IID ExportedByCAAAfrCustCommandHdrModel IID_CAAIAfrMRUManagement;

class ExportedByCAAAfrCustCommandHdrModel CAAIAfrMRUManagement : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;

public:
  virtual HRESULT AddElement(CATUnicodeString &iNewElement) = 0;
  virtual HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const = 0;
  virtual HRESULT SelectElement(int iPosition) = 0;
};

#endif
```

**关键点**:
- `extern IID ExportedByModule IID_InterfaceName;` — IID 声明
- `CATDeclareInterface;` — 必须在类体内，用于声明这是一个COM接口
- 所有方法都是 `virtual ... = 0` 纯虚函数
- 返回类型通常是 `HRESULT`

### 接口实现文件 (.cpp)

**源码来源**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/src/CAAIAfrMRUManagement.cpp`

```cpp
#include "CAAIAfrMRUManagement.h"   // 接口头文件
#include "TIE_CAAIAfrMRUManagement.tsrc"  // TIE文件

// 一行即可完成接口实现注册
CATImplementInterface(CAAIAfrMRUManagement, CATBaseUnknown);
```

**关键点**:
- `CATImplementInterface(InterfaceName, BaseClass);` — 就这一行，无其他
- 必须包含对应的 `TIE_InterfaceName.tsrc` 文件
- ❌ **不存在的宏**: `CATImplementInterfaceMethod`, `EndCATImplementInterface`

## 2. 类声明与实现

### 类头文件 (.h)

**源码来源**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/LocalInterfaces/CAAAfrMRUManager.h`

```cpp
#include "CATBaseUnknown.h"   // To derive from
class CATUnicodeString;
#include "CATListOfCATUnicodeString.h"

class CAAAfrMRUManager : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

public:
   CAAAfrMRUManager();
   virtual ~CAAAfrMRUManager();

   static HRESULT GetMRUManager(CAAAfrMRUManager ** oManager);

   // CAAIAfrMRUManagement
   virtual HRESULT AddElement(CATUnicodeString &iNewElement);
   virtual HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const;
   virtual HRESULT SelectElement(int iPosition);

private:
   // Copy constructor, not implemented
   CAAAfrMRUManager(const CAAAfrMRUManager &iObjectToCopy);
   CAAAfrMRUManager & operator = (const CAAAfrMRUManager &iObjectToCopy);
};
```

**关键点**:
- `CATDeclareClass;` — 在类体内声明
- 拷贝构造和赋值运算符放在 `private` 中禁止编译器自动生成

### 类实现文件 (.cpp)

**源码来源**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/src/CAAAfrMRUManager.cpp`

```cpp
// CATImplementClass 参数: (类名, 扩展类型, 基类, 挚友类)
CATImplementClass(CAAAfrMRUManager, Implementation, CATBaseUnknown, CATNull);

CAAAfrMRUManager::CAAAfrMRUManager() : CATBaseUnknown()
{
}

CAAAfrMRUManager::~CAAAfrMRUManager()
{
}
```

**关键点**:
- `CATImplementClass` 的4个参数:
  - `类名` — 类的名称
  - `扩展类型` — `Implementation` / `DataExtension` / `CodeExtension`
  - `基类` — 继承的父类
  - `挚友类` — 通常为 `CATNull` 或某个Late Type名
- ❌ **不存在的宏**: `CATDeclareHeader`

## 3. 命令实现模式

### 命令类声明

**源码来源**: `CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrChangeViewNormalCmd.h`

```cpp
#include "CATCommand.h"

class CAAAfrChangeViewNormalCmd : public CATCommand
{
   CATDeclareClass;

public:
   CAAAfrChangeViewNormalCmd();
   virtual ~CAAAfrChangeViewNormalCmd();

   // 命令生命周期方法
   virtual CATStatusChangeRC Activate(CATCommand *iFromClient, CATNotification *iEvtData);
   // Desactivate 不是拼写错误，CAA就这样拼
};
```

**关键点**:
- `CATStatusChangeRC` — 返回类型
- `Activate` 参数是 `(CATCommand *, CATNotification *)`
- ❌ **不存在的参数名**: `iCmd`, `iNotif` — 正确应为 `iFromClient`, `iEvtData`

## 4. TIE 文件

TIE 文件是 CAA 用来将接口绑定到实现类的机制。

### TIE 文件格式 (.tsrc)

**源码来源**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/src/TIE_CAAIAfrMRUManagement.tsrc`

```cpp
// 通常只包含两行
#include "CAAIAfrMRUManagement.h"      // 接口头文件
#include "CAAAfrMRUManager.h"          // 实现类头文件
// 然后在对应的 .cpp 中用 CATImplementInterface 绑定
```

## 5. 编辑器与文档操作

### 获取当前编辑器

**源码来源**: `CAAApplicationFrame.edu/CAAAfrGeoCommands.m/` 中多个命令类

```cpp
// 在CATCommand派生类中:
CATFrmEditor * pEditor = GetEditor();
// GetEditor() 是 CATCommand 的成员方法
```

### 获取当前文档

```cpp
CATFrmEditor * pEditor = GetEditor();
if (NULL != pEditor)
{
  CATDocument * pDoc = pEditor->GetDocument();
}
```

## 6. 常用头文件引用

以下头文件从源码中验证存在:

| 头文件 | 用途 | 验证来源 |
|--------|------|----------|
| `CATBaseUnknown.h` | COM基类 | 所有模块 |
| `CATCommand.h` | 命令基类 | CAAApplicationFrame |
| `CATFrmEditor.h` | 编辑器 | CAAApplicationFrame |
| `CATNotification.h` | 通知 | CAAApplicationFrame |
| `CATUnicodeString.h` | 字符串 | 所有模块 |
| `CATPathElement.h` | 路径元素 | CAAApplicationFrame |
| `CATDocument.h` | 文档 | CAAProductStructure |
| `CATCallbackManager.h` | 回调管理 | CAAApplicationFrame |
| `CATListOfCATUnicodeString.h` | 字符串列表 | CAAApplicationFrame |

## 7. Imakefile.mk 构建

**源码来源**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/Imakefile.mk`

```makefile
# 模块类型
BUILT_OBJECT_TYPE = SHARED LIBRARY

# 链接的库
LINK_WITH = \
  CATApplicationFrame \
  CATVisualization \
  CATViz \
  SystemTS \

# 源文件
LOCAL_SRCPATH = src

# 头文件搜索路径
LOCAL_HDRPATH = LocalInterfaces PublicInterfaces
```

---
