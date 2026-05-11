---
title: "CAAIV5V6ExtMmrCCDataExtension"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
verified: true
---

# CAAIV5V6ExtMmrCCDataExtension

**基类**: CATBaseUnknown  
**模块**: CAAV5V6MechanicalModeler  
**方法数**: 4

## 方法列表

### SetGeomFeature
```cpp
HRESULT SetGeomFeature(CATBaseUnknown * ipGeomFeature);
```

### GetGeomFeature
```cpp
HRESULT GetGeomFeature(CATBaseUnknown*& opGeomFeature);
```

### AggregateParam
```cpp
HRESULT AggregateParam(CATICkeParm_var ispParmToAggregate);
```

### GetValuatedParam
```cpp
HRESULT GetValuatedParam(CATICkeParm_var& iospValuatedParm);
```

