---
title: "CAAISysRevolAxis"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAISysRevolAxis.h"
---

# CAAISysRevolAxis

> Interface to manage an axis of revolution

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 纯虚方法 (接口契约)

### GetAxis

```cpp
virtual HRESULT GetAxis(float &oX, float &oY, float &oZ) = 0 ;
```

| 参数 | 类型 |
|------|------|
| &oX | `float` |
| &oY | `float` |
| &oZ | `float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetAxis

```cpp
virtual HRESULT SetAxis(const float iX, const float iY, const float iZ) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iX | `const float` |
| iY | `const float` |
| iZ | `const float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAAISysRevolAxis.h`
