---
title: "CAAEGSMFeaturesSplInputDescription"
type: "LocalClass"
module: "CAAGSMInterfaces"
base: "CATIniInputDescriptionAdaptor"
method_count: 3
source_file: "CAAGSMInterfaces.edu/CAAGsiFeaturesSplModel.m/LocalInterfaces/CAAEGSMFeaturesSplInputDescription.h"
---

# CAAEGSMFeaturesSplInputDescription

**基类**: CATIniInputDescriptionAdaptor | **模块**: CAAGSMInterfaces | **方法数**: 3

## 依赖

- `CATIniInputDescriptionAdaptor.h`

## 公共方法

### GetListOfModifiedFeatures

```cpp
HRESULT GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures) ;
```

| 参数 | 类型 |
|------|------|
| oListOfModifiedFeatures | `CATListValCATBaseUnknown_var&` |


### GetMainInput

```cpp
HRESULT GetMainInput(CATBaseUnknown_var& oMainInput) ;
```

| 参数 | 类型 |
|------|------|
| oMainInput | `CATBaseUnknown_var&` |


### GetFeatureType

```cpp
HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type) ;
```

| 参数 | 类型 |
|------|------|
| oFeature_type | `CATIInputDescription::FeatureType&` |


---

**源文件**: `CAAGSMInterfaces.edu/CAAGsiFeaturesSplModel.m/LocalInterfaces/CAAEGSMFeaturesSplInputDescription.h`
