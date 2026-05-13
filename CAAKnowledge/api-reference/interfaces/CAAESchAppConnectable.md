---
title: "CAAESchAppConnectable"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 7
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppConnectable.h"
---

# CAAESchAppConnectable

**基类**: CATBaseUnknown | **模块**: CAASchPlatformModeler | **方法数**: 7

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`

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
virtual HRESULT AppListConnectables(CATICStringList *iLCntbleClassFilter, CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrsOnThisObj, CATIUnknownList **oLCntrsOnConnected) ;
```

| 参数 | 类型 |
|------|------|
| *iLCntbleClassFilter | `CATICStringList` |
| **oLCntbles | `CATIUnknownList` |
| **oLCntrsOnThisObj | `CATIUnknownList` |
| **oLCntrsOnConnected | `CATIUnknownList` |


### AppAddConnector

```cpp
virtual HRESULT AppAddConnector(const char *iClassType, CATISchAppConnector **oNewAppCntr) ;
```

| 参数 | 类型 |
|------|------|
| *iClassType | `const char` |
| **oNewAppCntr | `CATISchAppConnector` |


### AppRemoveConnector

```cpp
virtual HRESULT AppRemoveConnector(CATISchAppConnector *iCntrToRemove) ;
```

| 参数 | 类型 |
|------|------|
| *iCntrToRemove | `CATISchAppConnector` |


### AppListValidCntrTypes

```cpp
virtual HRESULT AppListValidCntrTypes(CATICStringList **oLValidCntrTypes) ;
```

| 参数 | 类型 |
|------|------|
| **oLValidCntrTypes | `CATICStringList` |


### AppGetReferenceName

```cpp
virtual HRESULT AppGetReferenceName(char **oReferenceName) ;
```

| 参数 | 类型 |
|------|------|
| **oReferenceName | `char` |


### AppSetReferenceName

```cpp
virtual HRESULT AppSetReferenceName(const char *iReferenceName) ;
```

| 参数 | 类型 |
|------|------|
| *iReferenceName | `const char` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppConnectable.h`
