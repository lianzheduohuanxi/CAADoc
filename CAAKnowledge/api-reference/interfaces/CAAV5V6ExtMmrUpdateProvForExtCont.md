---
title: "CAAV5V6ExtMmrUpdateProvForExtCont"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATIUpdateProvider"
method_count: 4
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAV5V6ExtMmrUpdateProvForExtCont.h"
---

# CAAV5V6ExtMmrUpdateProvForExtCont

> CAAV5V6ExtMmrUpdateProvForExtCont: CATIUpdateProviderExtension Extends UpdateMechanism to FeatureExtensions Contained in V5V6ExtMmrDataExtensionCont

**基类**: CATIUpdateProvider | **模块**: CAAV5V6MechanicalModeler | **方法数**: 4

## 依赖

- `CATIUpdateProvider.h`
- `CATIAV5Level.h`

## 公共方法

### Update

```cpp
int Update(CATBaseUnknown* iWorkingObj, CATBaseUnknown_var iDomain = NULL_var) ;
```

| 参数 | 类型 |
|------|------|
| iWorkingObj | `CATBaseUnknown*` |
| NULL_var | `CATBaseUnknown_var iDomain =` |


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

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCCDataExtension.m/LocalInterfaces/CAAV5V6ExtMmrUpdateProvForExtCont.h`
