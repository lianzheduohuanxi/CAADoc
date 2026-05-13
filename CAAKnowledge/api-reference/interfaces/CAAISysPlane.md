---
title: "CAAISysPlane"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/PublicInterfaces/CAAISysPlane.h"
---

# CAAISysPlane

> Interface which characterizes a plane object. Inheritance: CATBaseUnknown (System Framework) Main Method: SetOrigin/GetOrigin SetPlane/GetPlane Syteme Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetOrigin

```cpp
virtual HRESULT SetOrigin(const CATMathPoint & iOrigin) = 0 ;
```

The plane is defined by: ------------------------ It's origin  in the space -------------------------

| 参数 | 类型 |
|------|------|
| iOrigin | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetOrigin

```cpp
virtual HRESULT GetOrigin(CATMathPoint & oOrigin) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oOrigin | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetPlane

```cpp
virtual HRESULT SetPlane(const CATMathVector & iU, const CATMathVector & iV) = 0 ;
```

It's U and V axis -------------------------

| 参数 | 类型 |
|------|------|
| iU | `const CATMathVector &` |
| iV | `const CATMathVector &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetPlane

```cpp
virtual HRESULT GetPlane(CATMathVector & iU, CATMathVector & iV) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| iU | `CATMathVector &` |
| iV | `CATMathVector &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysPlane.h`
