---
title: "CAAEMmrCCDataExtension"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAEMmrCCDataExtension.h"
---

# CAAEMmrCCDataExtension

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### SetGeomFeature

```cpp
HRESULT SetGeomFeature(const CATBaseUnknown * ipGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| ipGeomFeature | `const CATBaseUnknown *` |


### GetGeomFeature

```cpp
HRESULT GetGeomFeature(CATISpecObject **ioGeomFeature) ;
```

| 参数 | 类型 |
|------|------|
| **ioGeomFeature | `CATISpecObject` |


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

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAEMmrCCDataExtension.h`
