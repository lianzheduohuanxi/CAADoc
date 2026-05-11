---
title: "CAAIMmrMultiMeasureAndMeasureSetFactory"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 2
verified: true
---

# CAAIMmrMultiMeasureAndMeasureSetFactory

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**方法数**: 2

## 方法列表

### CreateMmrMultiMeasure
```cpp
HRESULT CreateMmrMultiMeasure(CATBaseUnknown *ipGeometricalElementToMesure ,
                                            CATISpecObject **opMultiMeasureInstance);
```

### CreateMmrMeasureSet
```cpp
HRESULT CreateMmrMeasureSet(CATISpecObject **opMeasureSetInstance);
```

