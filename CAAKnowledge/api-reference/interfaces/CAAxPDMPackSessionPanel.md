---
title: "CAAxPDMPackSessionPanel"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATDlgDialog"
method_count: 8
source_file: "CAAxPDMInterfaces.edu/CAAxPDMUICommands.m/LocalInterfaces/CAAxPDMPackSessionPanel.h"
---

# CAAxPDMPackSessionPanel

**基类**: CATDlgDialog | **模块**: CAAxPDMInterfaces | **方法数**: 8

## 依赖

- `CATDlgDialog.h`
- `CATListOfCATString.h`

## 公共方法

### BuildPanel

```cpp
void BuildPanel() ;
```


### SetListInfo

```cpp
void SetListInfo(const CATListOfCATUnicodeString& ListName, const CATListOfCATUnicodeString& ListStatus, const CATListOfCATString& ListAccess) ;
```

| 参数 | 类型 |
|------|------|
| ListName | `const CATListOfCATUnicodeString&` |
| ListStatus | `const CATListOfCATUnicodeString&` |
| ListAccess | `const CATListOfCATString&` |


### SetCurrentPath

```cpp
void SetCurrentPath(const CATUnicodeString& iCurEnv) ;
```

| 参数 | 类型 |
|------|------|
| iCurEnv | `const CATUnicodeString&` |


### GetCurrentPath

```cpp
CATUnicodeString GetCurrentPath() ;
```


### SelectDirCB

```cpp
void SelectDirCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData) ;
```

| 参数 | 类型 |
|------|------|
| iCmd | `CATCommand*` |
| iNotif | `CATNotification*` |
| iData | `CATCommandClientData` |


### DirSelectedCB

```cpp
void DirSelectedCB(CATCommand* , CATNotification* iNotif, CATCommandClientData iData) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCommand*` |
| iNotif | `CATNotification*` |
| iData | `CATCommandClientData` |


### DirCancelledCB

```cpp
void DirCancelledCB(CATCommand* , CATNotification* iNotif, CATCommandClientData iData) ;
```

| 参数 | 类型 |
|------|------|
|  | `CATCommand*` |
| iNotif | `CATNotification*` |
| iData | `CATCommandClientData` |


### ActivateLineCB

```cpp
void ActivateLineCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData) ;
```

| 参数 | 类型 |
|------|------|
| iCmd | `CATCommand*` |
| iNotif | `CATNotification*` |
| iData | `CATCommandClientData` |


---

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMUICommands.m/LocalInterfaces/CAAxPDMPackSessionPanel.h`
