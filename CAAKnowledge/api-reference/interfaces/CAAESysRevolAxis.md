---
title: "CAAESysRevolAxis"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAESysRevolAxis.h"
---

# CAAESysRevolAxis

> Data extension of the CAASysRevolSurface component, implementing the CAAISysRevolAxis interface.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetAxis

```cpp
virtual HRESULT GetAxis(float &oX, float &oY, float &oZ) ;
```

| 参数 | 类型 |
|------|------|
| &oX | `float` |
| &oY | `float` |
| &oZ | `float` |


### SetAxis

```cpp
virtual HRESULT SetAxis(const float iX, const float iY, const float iZ) ;
```

| 参数 | 类型 |
|------|------|
| iX | `const float` |
| iY | `const float` |
| iZ | `const float` |


---

**源文件**: `CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAESysRevolAxis.h`
