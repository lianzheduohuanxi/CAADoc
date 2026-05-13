---
title: "CAAISysCuboid"
type: "PublicInterface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/PublicInterfaces/CAAISysCuboid.h"
---

# CAAISysCuboid

> Interface which characterizes a Cuboid object. Inheritance: CATBaseUnknown (System Framework) Main Method: SetOrigin/GetOrigin SetCuboid/GetCuboid Syteme Framework

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

## 纯虚方法 (接口契约)

### SetOrigin

```cpp
virtual HRESULT SetOrigin(const CATMathPoint & iOrigin) = 0 ;
```

The Cuboid is defined by: ------------------------ It's origin  in the space -------------------------

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

### SetVectors

```cpp
virtual HRESULT SetVectors(const CATMathVector & iV1, const CATMathVector & iV2, const CATMathVector & iV3) = 0 ;
```

V1 = Width V2 = Depth V3 = Height -------------------------

| 参数 | 类型 |
|------|------|
| iV1 | `const CATMathVector &` |
| iV2 | `const CATMathVector &` |
| iV3 | `const CATMathVector &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

### GetVectors

```cpp
virtual HRESULT GetVectors(CATMathVector & oV1, CATMathVector & oV2, CATMathVector & oV3) const = 0 ;
```

| 参数 | 类型 |
|------|------|
| oV1 | `CATMathVector &` |
| oV2 | `CATMathVector &` |
| oV3 | `CATMathVector &` |

**返回值**: `S_OK` 成功, `E_FAIL` 失败

---

**源文件**: `CAASystem.edu/PublicInterfaces/CAAISysCuboid.h`
