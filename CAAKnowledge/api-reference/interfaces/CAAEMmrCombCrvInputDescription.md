---
title: "CAAEMmrCombCrvInputDescription"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATIniInputDescriptionAdaptor"
method_count: 3
visibility: "local"
verified: true
---

# CAAEMmrCombCrvInputDescription

**基类**: CATIniInputDescriptionAdaptor  
**模块**: CAAMechanicalModeler  
**可见性**: local  
**方法数**: 3

> COPYRIGHT DASSAULT SYSTEMES 2000

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

