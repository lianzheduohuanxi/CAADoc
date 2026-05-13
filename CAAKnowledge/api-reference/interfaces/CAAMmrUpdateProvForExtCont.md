---
title: "CAAMmrUpdateProvForExtCont"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATIUpdateProvider"
method_count: 4
source_file: "CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAMmrUpdateProvForExtCont.h"
---

# CAAMmrUpdateProvForExtCont

> CAAMmrUpdateProvForExtCont: CATIUpdateProviderExtension Extends UpdateMechanism to FeatureExtensions Contained in MmrDataExtensionCont

**基类**: CATIUpdateProvider | **模块**: CAAMechanicalModeler | **方法数**: 4

## 依赖

- `CATIUpdateProvider.h`

## 公共方法

### Update

```cpp
int Update(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain = NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| iWorkingObj | `CATBaseUnknown*` |
| NULL_var | `CATIDomain_var iDomain =` |


### IsUpToDate

```cpp
CATBoolean IsUpToDate(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain=NULL_var) const ;
```

| 参数 | 类型 |
|------|------|
| iWorkingObj | `CATBaseUnknown*` |
| iDomain=NULL_var | `CATIDomain_var` |


### SetUpToDate

```cpp
void SetUpToDate(CATBaseUnknown* iWorkingObj, boolean iFlag) ;
```

| 参数 | 类型 |
|------|------|
| iWorkingObj | `CATBaseUnknown*` |
| iFlag | `boolean` |


### IsInactive

```cpp
int IsInactive(CATBaseUnknown* iWorkingObj) const ;
```

| 参数 | 类型 |
|------|------|
| iWorkingObj | `CATBaseUnknown*` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCCDataExtension.m/LocalInterfaces/CAAMmrUpdateProvForExtCont.h`
