---
title: "CAAIMmrMultiMeasure"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
visibility: "protected"
verified: true
---

# CAAIMmrMultiMeasure

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**可见性**: protected  
**方法数**: 5

## 方法列表

### SetInputGeomFeature
```cpp
HRESULT SetInputGeomFeature(CATBaseUnknown * ipGeomFeature);
```

### GetGeomFeature
```cpp
HRESULT GetGeomFeature(CATISpecObject** ioGeomFeature);
```

### GetLengthParameter
```cpp
HRESULT GetLengthParameter(CATICkeParm_var &oLengthParm);
```

### GetWetAreaParameter
```cpp
HRESULT GetWetAreaParameter(CATICkeParm_var &oWetAreaParm);
```

### GetVolumeParameter
```cpp
HRESULT GetVolumeParameter(CATICkeParm_var &oVolumeParm);
```

## 依赖

- `CAAMmrMultiMeasureAndMeasureSet.h`
- `CATBaseUnknown.h`

