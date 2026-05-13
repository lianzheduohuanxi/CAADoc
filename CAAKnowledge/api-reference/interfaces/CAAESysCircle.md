---
title: "CAAESysCircle"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysCircle.h"
---

# CAAESysCircle

> Data extension ofd the CAASysCircle component and implementing the CAAISysCircle interface. Main Method: SetCenter/GetCenter SetRadius/GetRadius SetPlanar/GetPlanar

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

The circle is defined by: ------------------------ A point center -------------------

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
virtual HRESULT SetRadius(const float iRadius) ;
```

A radius -------------------

| 参数 | 类型 |
|------|------|
| iRadius | `const float` |


### GetRadius

```cpp
virtual HRESULT GetRadius(float & oRadius) const ;
```

| 参数 | 类型 |
|------|------|
| oRadius | `float &` |


### SetPlanar

```cpp
virtual HRESULT SetPlanar(const CATMathVector & iNormal, const CATMathVector & iAxis) ;
```

A repere defined by its 2 vectors ---------------------------------- iNormal represents the normal of the plane iAxis   represents the beginning of the circle.

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

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysCircle.h`
