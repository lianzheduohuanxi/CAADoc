---
title: "CAAEV5V6ExtMmrMultiMeasureFactory"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 2
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasureFactory.h"
---

# CAAEV5V6ExtMmrMultiMeasureFactory

**基类**: CATBaseUnknown | **模块**: CAAV5V6MechanicalModeler | **方法数**: 2

## 依赖

- `CATBaseUnknown.h`

## 公共方法

### CreateMmrMultiMeasure

```cpp
HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure, CATBaseUnknown *&opMultiMeasureInstance) ;
```

| 参数 | 类型 |
|------|------|
| *ipGeometricalElementToMesure | `CATBaseUnknown` |
| *&opMultiMeasureInstance | `CATBaseUnknown` |


### CreateMmrMeasureSet

```cpp
HRESULT CreateMmrMeasureSet(CATBaseUnknown *&opMeasureSetInstance) ;
```

| 参数 | 类型 |
|------|------|
| *&opMeasureSetInstance | `CATBaseUnknown` |


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrMultiMeasure.m/LocalInterfaces/CAAEV5V6ExtMmrMultiMeasureFactory.h`
