---
title: "CAAISysCylinder"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAASystem.edu/PublicInterfaces/CAAISysCylinder.h"
---

# CAAISysCylinder

> Interface which characterizes a Cylinder object. Inheritance: CATBaseUnknown (System Framework) Syteme Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetRadius

```cpp
virtual HRESULT SetRadius(const float iRadius) = 0 ;
```

The Cylinder is defined by: ------------------------ It's radius in the space -------------------------

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

### SetBasePoint

```cpp
virtual HRESULT SetBasePoint(const CATMathPoint & iBasePoint) = 0 ;
```

The extrusion line is defined between the base and the top point ----------------------------------------------------------------

| 参数 | 类型 |
|------|------|
| iBasePoint | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetBasePoint

```cpp
virtual HRESULT GetBasePoint(CATMathPoint & oBasePoint) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oBasePoint | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### SetTopPoint

```cpp
virtual HRESULT SetTopPoint(const CATMathPoint & iTopPoint) = 0 ;
```

| 参数 | 类型 |
|------|------|
| iTopPoint | `const CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetTopPoint

```cpp
virtual HRESULT GetTopPoint(CATMathPoint & oTopPoint) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oTopPoint | `CATMathPoint &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysCylinder.h`
