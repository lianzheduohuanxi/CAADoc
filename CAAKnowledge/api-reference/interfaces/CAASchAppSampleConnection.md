---
title: "CAASchAppSampleConnection"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAASchAppSampleConnection.h"
---

# CAASchAppSampleConnection

**基类**: CATBaseUnknown | **模块**: CAASchPlatformModeler | **方法数**: 4

## 依赖

- `CATUnicodeString.h`
- `CATBaseUnknown.h`
- `CATErrorDef.h`
- `CATBooleanDef.h`
- `CATIConnector.h`

## 虚方法

### AppListConnectors

```cpp
virtual HRESULT AppListConnectors(CATICStringList *iLCntrClassFilter, CATIUnknownList **oLCntrs) ;
```

| 参数 | 类型 |
|------|------|
| *iLCntrClassFilter | `CATICStringList` |
| **oLCntrs | `CATIUnknownList` |


### AppListConnectables

```cpp
virtual HRESULT AppListConnectables(CATICStringList *iLCntbleClassFilter, CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrs) ;
```

| 参数 | 类型 |
|------|------|
| *iLCntbleClassFilter | `CATICStringList` |
| **oLCntbles | `CATIUnknownList` |
| **oLCntrs | `CATIUnknownList` |


### AppAddConnector

```cpp
virtual HRESULT AppAddConnector(CATISchAppConnector *iCntrToAdd) ;
```

| 参数 | 类型 |
|------|------|
| *iCntrToAdd | `CATISchAppConnector` |


### AppRemoveConnector

```cpp
virtual HRESULT AppRemoveConnector(CATISchAppConnector *iCntrToRemove) ;
```

| 参数 | 类型 |
|------|------|
| *iCntrToRemove | `CATISchAppConnector` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAASchAppSampleConnection.h`
