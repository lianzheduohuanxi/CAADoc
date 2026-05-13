---
title: "CAAEMmrCombCrvInputDescription"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATIniInputDescriptionAdaptor"
method_count: 3
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurve.m/LocalInterfaces/CAAEMmrCombCrvInputDescription.h"
---

# CAAEMmrCombCrvInputDescription

**基类**: CATIniInputDescriptionAdaptor | **模块**: CAAMechanicalModeler | **方法数**: 3

## 依赖

- `CATIniInputDescriptionAdaptor.h`

## 虚方法

### GetListOfModifiedFeatures

```cpp
virtual HRESULT GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures) ;
```

| 参数 | 类型 |
|------|------|
| oListOfModifiedFeatures | `CATListValCATBaseUnknown_var&` |


### GetMainInput

```cpp
virtual HRESULT GetMainInput(CATBaseUnknown_var& oMainInput) ;
```

| 参数 | 类型 |
|------|------|
| oMainInput | `CATBaseUnknown_var&` |


### GetFeatureType

```cpp
virtual HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type) ;
```

| 参数 | 类型 |
|------|------|
| oFeature_type | `CATIInputDescription::FeatureType&` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurve.m/LocalInterfaces/CAAEMmrCombCrvInputDescription.h`
