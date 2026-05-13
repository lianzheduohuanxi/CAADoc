---
title: "CAAESysPlane"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPlane.h"
---

# CAAESysPlane

> Data extension ofd the CAASysPlane component and implementing the CAAISysPlane interface. Main Method: SetOrigin/GetOrigin SetPlane/GetPlane

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

The plane is defined by: ------------------------ It's origin  in the space -------------------------

| 参数 | 类型 |
|------|------|
| iOrigin | `const CATMathPoint &` |


### GetOrigin

```cpp
virtual HRESULT GetOrigin(CATMathPoint & oOrigin) ;
```

| 参数 | 类型 |
|------|------|
| oOrigin | `CATMathPoint &` |


### SetPlane

```cpp
virtual HRESULT SetPlane(const CATMathVector & iU, const CATMathVector & iV) ;
```

It's U and V axis -------------------------

| 参数 | 类型 |
|------|------|
| iU | `const CATMathVector &` |
| iV | `const CATMathVector &` |


### GetPlane

```cpp
virtual HRESULT GetPlane(CATMathVector & oU, CATMathVector & oV) ;
```

| 参数 | 类型 |
|------|------|
| oU | `CATMathVector &` |
| oV | `CATMathVector &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPlane.h`
