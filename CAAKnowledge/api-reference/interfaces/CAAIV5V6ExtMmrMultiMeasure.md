---
title: "CAAIV5V6ExtMmrMultiMeasure"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 5
verified: true
---

# CAAIV5V6ExtMmrMultiMeasure

**基类**: CATBaseUnknown  
**模块**: CAAV5V6MechanicalModeler  
**方法数**: 5

## 方法列表

### SetInputGeomFeature
```cpp
HRESULT SetInputGeomFeature(CATBaseUnknown * ipGeomFeature);
```

### GetGeomFeature
```cpp
HRESULT GetGeomFeature(CATBaseUnknown *& oGeomFeature);
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

