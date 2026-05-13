---
title: "CAAESysEllipse"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysEllipse.h"
---

# CAAESysEllipse

> Data extension ofd the CAASysEllipse component and implementing the CAAISysEllipse interface. Main Method: SetCenter/GetCenter SetRadius/GetRadius SetPlanar/GetPlanar

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`
- `CATMathVector.h`

## 虚方法

### SetCenter

```cpp
virtual HRESULT SetCenter(const CATMathPoint & iCenter) ;
```

The ellipse is represented by: ------------------------------ A Point center ---------------

| 参数 | 类型 |
|------|------|
| iCenter | `const CATMathPoint &` |


### GetCenter

```cpp
virtual HRESULT GetCenter(CATMathPoint & oCenter) const ;
```

| 参数 | 类型 |
|------|------|
| oCenter | `CATMathPoint &` |


### SetRadius

```cpp
virtual HRESULT SetRadius(const float iXRadius, const float iYRadius) ;
```

A radius along X and Y axis ---------------------------

| 参数 | 类型 |
|------|------|
| iXRadius | `const float` |
| iYRadius | `const float` |


### GetRadius

```cpp
virtual HRESULT GetRadius(float &oXRadius, float & oYRadius) const ;
```

| 参数 | 类型 |
|------|------|
| &oXRadius | `float` |
| oYRadius | `float &` |


### SetPlanar

```cpp
virtual HRESULT SetPlanar(const CATMathVector & iNormal, const CATMathVector & iAxis) ;
```

A Repere -------- iNormal defined the normal of the plane iAxis   defined the X axis. The Y axis = iNormal ^ iAxis .

| 参数 | 类型 |
|------|------|
| iNormal | `const CATMathVector &` |
| iAxis | `const CATMathVector &` |


### GetPlanar

```cpp
virtual HRESULT GetPlanar(CATMathVector & oNormal, CATMathVector & oAxis) const ;
```

| 参数 | 类型 |
|------|------|
| oNormal | `CATMathVector &` |
| oAxis | `CATMathVector &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysEllipse.h`
