---
title: "CAASysSprocketFactory"
type: "PublicInterface"
module: "CAASystem"
base: ""
method_count: 2
source_file: "CAASystem.edu/PublicInterfaces/CAASysSprocketFactory.h"
---

# CAASysSprocketFactory

**基类**: 无 | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CAASysAutomationImpl.h`
- `CATUnicodeString.h`

## 静态方法

### CreateSprocket

```cpp
static HRESULT __stdcall CreateSprocket(const CATUnicodeString& iName, CAAIASysSprocket*& oCAAIASysSprocket) ;
```

| 参数 | 类型 |
|------|------|
| iName | `const CATUnicodeString&` |
| oCAAIASysSprocket | `CAAIASysSprocket*&` |


### CreateSprockets

```cpp
static HRESULT __stdcall CreateSprockets(CAAIASysSprockets*& oCAAIASysSprockets) ;
```

| 参数 | 类型 |
|------|------|
| oCAAIASysSprockets | `CAAIASysSprockets*&` |


---

**源文件**: `CAASystem.edu/PublicInterfaces/CAASysSprocketFactory.h`
