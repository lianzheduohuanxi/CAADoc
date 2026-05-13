---
title: "CAAEMmrMultiMeasureAndMeasureSetFactory"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSet.m/LocalInterfaces/CAAEMmrMultiMeasureAndMeasureSetFactory.h"
---

# CAAEMmrMultiMeasureAndMeasureSetFactory

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### CreateMmrMultiMeasure

```cpp
HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure, CATISpecObject **opMultiMeasureInstance) ;
```

| 参数 | 类型 |
|------|------|
| *ipGeometricalElementToMesure | `CATBaseUnknown` |
| **opMultiMeasureInstance | `CATISpecObject` |


### CreateMmrMeasureSet

```cpp
HRESULT CreateMmrMeasureSet(CATISpecObject **opMeasureSetInstance) ;
```

| 参数 | 类型 |
|------|------|
| **opMeasureSetInstance | `CATISpecObject` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSet.m/LocalInterfaces/CAAEMmrMultiMeasureAndMeasureSetFactory.h`
