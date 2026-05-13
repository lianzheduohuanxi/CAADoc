---
title: "CAASysSprocketImpl"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseObject"
method_count: 2
source_file: "CAASystem.edu/CAASysAutomationImpl.m/LocalInterfaces/CAASysSprocketImpl.h"
---

# CAASysSprocketImpl

**基类**: CATBaseObject | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseObject.h`
- `CATBSTR.h`
- `CATUnicodeString.h`

## 虚方法

### get_Name

```cpp
virtual HRESULT get_Name(CATBSTR & oNameBSTR) ;
```

Implementation of the CAAIASysSprocket interface

| 参数 | 类型 |
|------|------|
| oNameBSTR | `CATBSTR &` |


## 静态方法

### CreateSprocket

```cpp
static HRESULT __stdcall CreateSprocket(const CATUnicodeString& iName, CAAIASysSprocket*& oCAAIASysSprocket) ;
```

| 参数 | 类型 |
|------|------|
| iName | `const CATUnicodeString&` |
| oCAAIASysSprocket | `CAAIASysSprocket*&` |


---

**源文件**: `CAASystem.edu/CAASysAutomationImpl.m/LocalInterfaces/CAASysSprocketImpl.h`
