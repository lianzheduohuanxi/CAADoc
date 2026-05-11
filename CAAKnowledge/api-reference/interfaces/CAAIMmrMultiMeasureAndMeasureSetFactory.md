---
title: "CAAIMmrMultiMeasureAndMeasureSetFactory"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 2
visibility: "protected"
verified: true
---

# CAAIMmrMultiMeasureAndMeasureSetFactory

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**可见性**: protected  
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

## 依赖

- `CAAMmrMultiMeasureAndMeasureSet.h`
- `CATBaseUnknown.h`

