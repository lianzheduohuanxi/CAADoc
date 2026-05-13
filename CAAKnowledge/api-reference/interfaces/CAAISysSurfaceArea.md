---
title: "CAAISysSurfaceArea"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAISysSurfaceArea.h"
---

# CAAISysSurfaceArea

> Interface to compute the area of a surface.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### ComputeArea

```cpp
virtual HRESULT ComputeArea(float & oArea) = 0 ;
```

| 参数 | 类型 |
|------|------|
| oArea | `float &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAISysSurfaceArea.h`
