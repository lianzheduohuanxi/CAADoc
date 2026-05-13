---
title: "CAAAfrMRUManager"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/LocalInterfaces/CAAAfrMRUManager.h"
---

# CAAAfrMRUManager

> Implementation class of the CAAAfrMRUManager component. This component is instantiated once in using the global function GetCAAAfrMRUManager. System framework

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 4

## 依赖

- `CATBaseUnknown.h`
- `CATListOfCATUnicodeString.h`
- `CATCallbackManager.h`
- `CATIniCleanerSettingCtrl.h`

## 虚方法

### AddElement

```cpp
virtual HRESULT AddElement(CATUnicodeString &iNewElement) ;
```

CAAIAfrMRUManagement

| 参数 | 类型 |
|------|------|
| &iNewElement | `CATUnicodeString` |


### GetElementList

```cpp
virtual HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const ;
```

| 参数 | 类型 |
|------|------|
| &ElementList | `CATListOfCATUnicodeString` |


### SelectElement

```cpp
virtual HRESULT SelectElement(int iPosition) ;
```

| 参数 | 类型 |
|------|------|
| iPosition | `int` |


## 静态方法

### GetMRUManager

```cpp
static HRESULT GetMRUManager(CAAAfrMRUManager ** oManager) ;
```

Retrieves or creates the unic instance class This method must only be called by the global function GetCAAAfrMRUManager defined in PublicInterfaces of this Framework

| 参数 | 类型 |
|------|------|
| oManager | `CAAAfrMRUManager **` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrCustCommandHdrModel.m/LocalInterfaces/CAAAfrMRUManager.h`
