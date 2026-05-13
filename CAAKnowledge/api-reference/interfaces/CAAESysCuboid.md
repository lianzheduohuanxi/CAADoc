---
title: "CAAESysCuboid"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysCuboid.h"
---

# CAAESysCuboid

> Data extension ofd the CAASysCuboid component and implementing the CAAISysCuboid interface. Main Method: SetOrigin/GetOrigin SetCuboid/GetCuboid

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`
- `CATMathVector.h`

## 虚方法

### SetOrigin

```cpp
virtual HRESULT SetOrigin(const CATMathPoint & iOrigin) ;
```

The Cuboid is defined by: ------------------------ It's origin  in the space -------------------------

| 参数 | 类型 |
|------|------|
| iOrigin | `const CATMathPoint &` |


### GetOrigin

```cpp
virtual HRESULT GetOrigin(CATMathPoint & oOrigin) const ;
```

| 参数 | 类型 |
|------|------|
| oOrigin | `CATMathPoint &` |


### SetVectors

```cpp
virtual HRESULT SetVectors(const CATMathVector & iV1, const CATMathVector & iV2, const CATMathVector & iV3) ;
```

Width, Depth, Height -------------------------

| 参数 | 类型 |
|------|------|
| iV1 | `const CATMathVector &` |
| iV2 | `const CATMathVector &` |
| iV3 | `const CATMathVector &` |


### GetVectors

```cpp
virtual HRESULT GetVectors(CATMathVector & oV1, CATMathVector & oV2, CATMathVector & oV3) const ;
```

| 参数 | 类型 |
|------|------|
| oV1 | `CATMathVector &` |
| oV2 | `CATMathVector &` |
| oV3 | `CATMathVector &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysCuboid.h`
