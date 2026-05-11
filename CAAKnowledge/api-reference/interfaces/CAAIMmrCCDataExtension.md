---
title: "CAAIMmrCCDataExtension"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 4
visibility: "public"
verified: true
---

# CAAIMmrCCDataExtension

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**可见性**: public  
**方法数**: 4

## 方法列表

### SetGeomFeature
```cpp
HRESULT SetGeomFeature(const CATBaseUnknown * ipGeomFeature);
```

### GetGeomFeature
```cpp
HRESULT GetGeomFeature(CATISpecObject** ioGeomFeature);
```

### AggregateParam
```cpp
HRESULT AggregateParam(CATICkeParm_var ispParmToAggregate);
```

### GetValuatedParam
```cpp
HRESULT GetValuatedParam(CATICkeParm_var& iospValuatedParm);
```

## 依赖

- `CAAMmrCCDataExtension.h`
- `CATBaseUnknown.h`

