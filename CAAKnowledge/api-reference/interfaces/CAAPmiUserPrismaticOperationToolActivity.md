---
title: "CAAPmiUserPrismaticOperationToolActivity"
type: "LocalClass"
module: "CAAPrismaticMachiningItf"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAPrismaticMachiningItf.edu/CAAPmiCreateUserPrismaticOperationCommand.m/LocalInterfaces/CAAPmiUserPrismaticOperationToolActivity.h"
---

# CAAPmiUserPrismaticOperationToolActivity

**基类**: CATBaseUnknown | **模块**: CAAPrismaticMachiningItf | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATUnicodeString.h`

## 公共方法

### GetAuthorizedToolTypeList

```cpp
HRESULT GetAuthorizedToolTypeList(CATListOfCATUnicodeString & oToolTypeList) ;
```

| 参数 | 类型 |
|------|------|
| oToolTypeList | `CATListOfCATUnicodeString &` |


### CreateDefaultTool

```cpp
HRESULT CreateDefaultTool(CATBaseUnknown_var & oTool) ;
```

| 参数 | 类型 |
|------|------|
| oTool | `CATBaseUnknown_var &` |


### GetFirstToolCompensation

```cpp
HRESULT GetFirstToolCompensation(int & oFirstNumber) ;
```

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

**源文件**: `CAAPrismaticMachiningItf.edu/CAAPmiCreateUserPrismaticOperationCommand.m/LocalInterfaces/CAAPmiUserPrismaticOperationToolActivity.h`
