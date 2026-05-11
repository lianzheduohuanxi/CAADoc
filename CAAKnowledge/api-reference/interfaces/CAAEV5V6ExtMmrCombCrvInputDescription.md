---
title: "CAAEV5V6ExtMmrCombCrvInputDescription"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATIniInputDescriptionAdaptor"
method_count: 3
visibility: "local"
verified: true
---

# CAAEV5V6ExtMmrCombCrvInputDescription

**基类**: CATIniInputDescriptionAdaptor  
**模块**: CAAV5V6MechanicalModeler  
**可见性**: local  
**方法数**: 3

> COPYRIGHT DASSAULT SYSTEMES 2012

## 方法列表

### GetListOfModifiedFeatures
```cpp
HRESULT GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures);
```

### GetMainInput
```cpp
HRESULT GetMainInput(CATBaseUnknown_var& oMainInput);
```

### GetFeatureType
```cpp
HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type);
```

## 依赖

- `CATIniInputDescriptionAdaptor.h`

