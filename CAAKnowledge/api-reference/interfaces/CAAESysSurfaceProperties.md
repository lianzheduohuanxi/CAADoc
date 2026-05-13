---
title: "CAAESysSurfaceProperties"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAESysSurfaceProperties.h"
---

# CAAESysSurfaceProperties

> Data extension implementing the CAAISysSurfaceProperties interface.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetColor

```cpp
virtual HRESULT GetColor(int & oRed, int & oGreen, int & oBlue) ;
```

| 参数 | 类型 |
|------|------|
| oRed | `int &` |
| oGreen | `int &` |
| oBlue | `int &` |


### SetColor

```cpp
virtual HRESULT SetColor(const int iRed, const int iGreen, const int iBlue) ;
```

| 参数 | 类型 |
|------|------|
| iRed | `const int` |
| iGreen | `const int` |
| iBlue | `const int` |


---

**源文件**: `CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAESysSurfaceProperties.h`
