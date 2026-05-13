---
title: "CAAISysCircle"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAASystem.edu/PublicInterfaces/CAAISysCircle.h"
---

# CAAISysCircle

> Interface which characterizes a circle object. Inheritance: CATBaseUnknown (System Framework) Main Method: SetCenter/GetCenter SetRadius/GetRadius SetPlanar/GetPlanar

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetCenter

```cpp
virtual HRESULT SetCenter(const CATMathPoint & iCenter) = 0 ;
```

The circle is defined by: ------------------------ A point center -------------------

| 参数 | 类型 |
|------|------|
| iCenter | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetCenter

```cpp
virtual HRESULT GetCenter(CATMathPoint & oCenter) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oCenter | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetRadius

```cpp
virtual HRESULT SetRadius(const float iRadius) = 0 ;
```

A radius -------------------

| 参数 | 类型 |
|------|------|
| iRadius | `const float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetRadius

```cpp
virtual HRESULT GetRadius(float & oRadius) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oRadius | `float &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetPlanar

```cpp
virtual HRESULT SetPlanar(const CATMathVector & iNormal, const CATMathVector & iAxis) = 0 ;
```

A repere defined by its 2 vectors ---------------------------------- iNormal represents the normal of the plane iAxis   represents the beginning of the circle.

| 参数 | 类型 |
|------|------|
| iNormal | `const CATMathVector &` |
| iAxis | `const CATMathVector &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetPlanar

```cpp
virtual HRESULT GetPlanar(CATMathVector & oNormal, CATMathVector & oAxis) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oNormal | `CATMathVector &` |
| oAxis | `CATMathVector &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysCircle.h`
