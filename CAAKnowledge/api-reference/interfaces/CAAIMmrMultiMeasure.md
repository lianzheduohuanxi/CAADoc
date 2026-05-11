---
title: "CAAIMmrMultiMeasure"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
verified: true
---

# CAAIMmrMultiMeasure

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
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

