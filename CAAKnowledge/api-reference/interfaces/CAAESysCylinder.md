---
title: "CAAESysCylinder"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysCylinder.h"
---

# CAAESysCylinder

> Data extension ofd the CAASysCylinder component and implementing the CAAISysCylinder interface.

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`

## 虚方法

### SetRadius

```cpp
virtual HRESULT SetRadius(const float iRadius) ;
```

The Cylinder is defined by: ------------------------ A radius -------------------

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


### SetBasePoint

```cpp
virtual HRESULT SetBasePoint(const CATMathPoint & iBasePoint) ;
```

The extrusion line is defined between the base and the top point ----------------------------------------------------------------

| 参数 | 类型 |
|------|------|
| iBasePoint | `const CATMathPoint &` |


### GetBasePoint

```cpp
virtual HRESULT GetBasePoint(CATMathPoint & oBasePoint) const ;
```

| 参数 | 类型 |
|------|------|
| oBasePoint | `CATMathPoint &` |


### SetTopPoint

```cpp
virtual HRESULT SetTopPoint(const CATMathPoint & iTopPoint) ;
```

| 参数 | 类型 |
|------|------|
| iTopPoint | `const CATMathPoint &` |


### GetTopPoint

```cpp
virtual HRESULT GetTopPoint(CATMathPoint & oTopPoint) const ;
```

| 参数 | 类型 |
|------|------|
| oTopPoint | `CATMathPoint &` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysCylinder.h`
