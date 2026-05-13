---
title: "CAAEMmrMultiMeasure"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSet.m/LocalInterfaces/CAAEMmrMultiMeasure.h"
---

# CAAEMmrMultiMeasure

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 5

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### SetInputGeomFeature

```cpp
HRESULT SetInputGeomFeature(CATBaseUnknown * ipGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| ipGeomFeature | `CATBaseUnknown *` |


### GetGeomFeature

```cpp
HRESULT GetGeomFeature(CATISpecObject **ioGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| **ioGeomFeature | `CATISpecObject` |


### GetLengthParameter

```cpp
HRESULT GetLengthParameter(CATICkeParm_var &oLengthParm) ;
```

| 参数 | 类型 |
|------|------|
| &oLengthParm | `CATICkeParm_var` |


### GetWetAreaParameter

```cpp
HRESULT GetWetAreaParameter(CATICkeParm_var &oWetAreaParm) ;
```

| 参数 | 类型 |
|------|------|
| &oWetAreaParm | `CATICkeParm_var` |


### GetVolumeParameter

```cpp
HRESULT GetVolumeParameter(CATICkeParm_var &oVolumeParm) ;
```

| 参数 | 类型 |
|------|------|
| &oVolumeParm | `CATICkeParm_var` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSet.m/LocalInterfaces/CAAEMmrMultiMeasure.h`
