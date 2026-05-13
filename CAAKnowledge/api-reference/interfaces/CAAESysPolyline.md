---
title: "CAAESysPolyline"
type: "LocalClass"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPolyline.h"
---

# CAAESysPolyline

> Data extension ofd the CAASysPolyline component and implementing the CAAISysPolyline interface. Main Method: GetListPoint/SetListPoint SetCloseStatus/SetCloseStatus

**基类**: CATBaseUnknown | **模块**: CAASystem | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### SetListPoint

```cpp
virtual HRESULT SetListPoint(const int iPointCount, CATMathPoint * iList) ;
```

A polyline is a list of 3D points ---------------------------------

| 参数 | 类型 |
|------|------|
| iPointCount | `const int` |
| iList | `CATMathPoint *` |


### GetListPoint

```cpp
virtual HRESULT GetListPoint(int * oPointCount, CATMathPoint ** oList) ;
```

Returns E_FAIL if oPointCount or oList is NULL else S_OK

| 参数 | 类型 |
|------|------|
| oPointCount | `int *` |
| oList | `CATMathPoint **` |


### SetCloseStatus

```cpp
virtual HRESULT SetCloseStatus(const int iIsClosed) ;
```

this polyline can be closed, so it's a polygone ------------------------------------------------ Set 0 the object is a polyline else it's a polygone

| 参数 | 类型 |
|------|------|
| iIsClosed | `const int` |


### GetCloseStatus

```cpp
virtual HRESULT GetCloseStatus(int * oIsClosed) ;
```

Returns E_FAIL if oIsClosed is NULL else S_OK

| 参数 | 类型 |
|------|------|
| oIsClosed | `int *` |


---

**源文件**: `CAASystem.edu/CAASysGeoModelImpl.m/LocalInterfaces/CAAESysPolyline.h`
