---
title: "CAAEV5V6ExtMmrCCDataExtension"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAEV5V6ExtMmrCCDataExtension.h"
---

# CAAEV5V6ExtMmrCCDataExtension

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATFmCredentials.h`

## 公共方法

### SetGeomFeature

```cpp
HRESULT SetGeomFeature(CATBaseUnknown * ipGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| ipGeomFeature | `CATBaseUnknown *` |


### GetGeomFeature

```cpp
HRESULT GetGeomFeature(CATBaseUnknown *&opGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| *&opGeomFeature | `CATBaseUnknown` |


### AggregateParam

```cpp
HRESULT AggregateParam(CATICkeParm_var ispParmToAggregate) ;
```

| 参数 | 类型 |
|------|------|
| ispParmToAggregate | `CATICkeParm_var` |


### GetValuatedParam

```cpp
HRESULT GetValuatedParam(CATICkeParm_var& iospValuatedParm) ;
```

| 参数 | 类型 |
|------|------|
| iospValuatedParm | `CATICkeParm_var&` |


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAEV5V6ExtMmrCCDataExtension.h`
