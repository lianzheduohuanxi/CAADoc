---
title: "CAAESmiUserOperationToolEditor"
type: "LocalClass"
module: "CAASurfaceMachiningItf"
base: "CATIMfgToolActivity"
method_count: 4
source_file: "CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m/LocalInterfaces/CAAESmiUserOperationToolEditor.h"
---

# CAAESmiUserOperationToolEditor

**基类**: CATIMfgToolActivity | **模块**: CAASurfaceMachiningItf | **方法数**: 4

## 依赖

- `CATIMfgToolActivity.h`
- `CATListOfCATUnicodeString.h`

## 公共方法

### GetAuthorizedToolTypeList

```cpp
HRESULT GetAuthorizedToolTypeList(CATListOfCATUnicodeString & oToolTypeList) ;
```

Gives informations relative to tools on the Activity.

| 参数 | 类型 |
|------|------|
| oToolTypeList | `CATListOfCATUnicodeString &` |


### CreateDefaultTool

```cpp
HRESULT CreateDefaultTool(CATBaseUnknown_var & oTool) ;
```

Creates default tool for an Activity.

| 参数 | 类型 |
|------|------|
| oTool | `CATBaseUnknown_var &` |


### GetFirstToolCompensation

```cpp
HRESULT GetFirstToolCompensation(int & oFirstNumber) ;
```

Useless

| 参数 | 类型 |
|------|------|
| oFirstNumber | `int &` |


### GetSecondToolCompensation

```cpp
HRESULT GetSecondToolCompensation(int & oSecondNumber) ;
```

| 参数 | 类型 |
|------|------|
| oSecondNumber | `int &` |


---

**源文件**: `CAASurfaceMachiningItf.edu/CAASmiUserOperationUI.m/LocalInterfaces/CAAESmiUserOperationToolEditor.h`
