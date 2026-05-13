---
title: "CAAEV5V6ExtMmrMultiMeasure"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasure.h"
---

# CAAEV5V6ExtMmrMultiMeasure

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 5

## 依赖

- `CATBaseUnknown.h`
- `CATFmCredentials.h`

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
HRESULT GetGeomFeature(CATBaseUnknown *&oGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| *&oGeomFeature | `CATBaseUnknown` |


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

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasure.h`
