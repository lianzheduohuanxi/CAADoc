---
title: "CAAEPstINFPoint"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 6
source_file: "CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFPoint.h"
---

# CAAEPstINFPoint

> Data extension of the CAAPstINFPoint component, implementing the CAAIPstINFPoint interface defined in the CAAProductStructure.edu framework, allowing the setting and retrieval of point coordinate values defining a CAAPstINFPoint feature. Illustrates programming the setting and retrieval methods necessary for the definition of a CAAPstINFPoint feature. Inheritance: CATBaseUnknown (System Framework)

**基类**: CATBaseUnknown | **模块**: CAAProductStructure | **方法数**: 6

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### GetX

```cpp
HRESULT GetX(double *opX) ;
```

Retrieves the value of the X coordinate of the point.

| 参数 | 类型 |
|------|------|
| *opX | `double` |


### GetY

```cpp
HRESULT GetY(double *opY) ;
```

Retrieves the value of the Y coordinate of the point.

| 参数 | 类型 |
|------|------|
| *opY | `double` |


### GetZ

```cpp
HRESULT GetZ(double *opZ) ;
```

Retrieves the value of the Z coordinate of the point.

| 参数 | 类型 |
|------|------|
| *opZ | `double` |


### SetX

```cpp
HRESULT SetX(double iX) ;
```

Valuates the X coordinate of the point.

| 参数 | 类型 |
|------|------|
| iX | `double` |


### SetY

```cpp
HRESULT SetY(double iY) ;
```

Valuates the Y coordinate of the point.

| 参数 | 类型 |
|------|------|
| iY | `double` |


### SetZ

```cpp
HRESULT SetZ(double iZ) ;
```

Valuates the Z coordinate of the point.

| 参数 | 类型 |
|------|------|
| iZ | `double` |


---

**源文件**: `CAAProductStructure.edu/CAAPstINFModeler.m/LocalInterfaces/CAAEPstINFPoint.h`
