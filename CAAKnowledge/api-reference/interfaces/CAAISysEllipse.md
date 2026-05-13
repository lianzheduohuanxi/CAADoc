---
title: "CAAISysEllipse"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAASystem.edu/PublicInterfaces/CAAISysEllipse.h"
---

# CAAISysEllipse

> Interface which characterizes an ellipse object. Inheritance: CATBaseUnknown (System Framework) Main Method: SetCenter/GetCenter SetRadius/GetRadius SetPlanar/GetPlanar System Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetCenter

```cpp
virtual HRESULT SetCenter(const CATMathPoint & iCenter) = 0 ;
```

The ellipse is represented by: ------------------------------ A Point center ---------------

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
virtual HRESULT SetRadius(const float iXRadius, const float iYRadius) = 0 ;
```

A radius along X and Y axis ---------------------------

| 参数 | 类型 |
|------|------|
| iXRadius | `const float` |
| iYRadius | `const float` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetRadius

```cpp
virtual HRESULT GetRadius(float & oXRadius, float & oYRadius) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oXRadius | `float &` |
| oYRadius | `float &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetPlanar

```cpp
virtual HRESULT SetPlanar(const CATMathVector & iNormal, const CATMathVector & iAxis) = 0 ;
```

A Repere -------- iNormal defined the normal of the plane iAxis   defined the X axis. The Y axis = iNormal ^ iAxis .

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

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysEllipse.h`
