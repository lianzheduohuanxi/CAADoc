---
title: "CAAISysPoint"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAASystem.edu/PublicInterfaces/CAAISysPoint.h"
---

# CAAISysPoint

> Interface which characterizes a point object. Inheritance: CATBaseUnknown (System Framework) Main Method: SetCoord/GetCoord System Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetCoord

```cpp
virtual HRESULT SetCoord(const float iX, const float iY, const float iZ) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iX | `const float` |
| iY | `const float` |
| iZ | `const float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCoord

```cpp
virtual HRESULT GetCoord(float & oX, float & oY, float & oZ) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oX | `float &` |
| oY | `float &` |
| oZ | `float &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysPoint.h`
