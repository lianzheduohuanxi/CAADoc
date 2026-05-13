---
title: "CAAESchAppConnector"
type: "LocalClass"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 8
source_file: "CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppConnector.h"
---

# CAAESchAppConnector

**基类**: CATBaseUnknown | **模块**: CAASchPlatformModeler | **方法数**: 8

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`

## 虚方法

### AppIsCntrConnected

```cpp
virtual HRESULT AppIsCntrConnected(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


## 公共方法

### AppGetAssociatedConnectable

```cpp
HRESULT AppGetAssociatedConnectable(CATISchAppConnectable **oConnectable) ;
```

| 参数 | 类型 |
|------|------|
| **oConnectable | `CATISchAppConnectable` |


### AppListCompatibleTypes

```cpp
HRESULT AppListCompatibleTypes(CATICStringList **oLCntrCompatClassTypes) ;
```

| 参数 | 类型 |
|------|------|
| **oLCntrCompatClassTypes | `CATICStringList` |


### AppListConnections

```cpp
HRESULT AppListConnections(CATICStringList *iLCntnClassFilter, CATIUnknownList **oLConnections) ;
```

| 参数 | 类型 |
|------|------|
| *iLCntnClassFilter | `CATICStringList` |
| **oLConnections | `CATIUnknownList` |


### AppConnect

```cpp
HRESULT AppConnect(CATISchAppConnector *iCntrToConnect, CATISchAppConnection **oConnection) ;
```

| 参数 | 类型 |
|------|------|
| *iCntrToConnect | `CATISchAppConnector` |
| **oConnection | `CATISchAppConnection` |


### AppConnectBranch

```cpp
HRESULT AppConnectBranch(CATISchAppConnector *iCntrToConnect, CATISchAppConnection **oConnection) ;
```

| 参数 | 类型 |
|------|------|
| *iCntrToConnect | `CATISchAppConnector` |
| **oConnection | `CATISchAppConnection` |


### AppDisconnect

```cpp
HRESULT AppDisconnect(CATISchAppConnector *iCntrToDisConnect) ;
```

| 参数 | 类型 |
|------|------|
| *iCntrToDisConnect | `CATISchAppConnector` |


### AppOKToNoShowConnectedCntr

```cpp
HRESULT AppOKToNoShowConnectedCntr(boolean *oBYes) ;
```

| 参数 | 类型 |
|------|------|
| *oBYes | `boolean` |


---

**源文件**: `CAASchPlatformModeler.edu/CAASchAppBase.m/LocalInterfaces/CAAESchAppConnector.h`
