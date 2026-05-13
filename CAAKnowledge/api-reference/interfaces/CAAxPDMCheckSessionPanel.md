---
title: "CAAxPDMCheckSessionPanel"
type: "LocalClass"
module: "CAAxPDMInterfaces"
base: "CATDlgDialog"
method_count: 4
source_file: "CAAxPDMInterfaces.edu/CAAxPDMUICommands.m/LocalInterfaces/CAAxPDMCheckSessionPanel.h"
---

# CAAxPDMCheckSessionPanel

**基类**: CATDlgDialog | **模块**: CAAxPDMInterfaces | **方法数**: 4

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
void SetListInfo(const CATListOfCATUnicodeString& ListName, const CATListOfCATUnicodeString& ListError, const CATListOfCATUnicodeString& ListStatus, CATListValCATIxPDMItem_var* _oItemsWithError) ;
```

| 参数 | 类型 |
|------|------|
| ListName | `const CATListOfCATUnicodeString&` |
| ListError | `const CATListOfCATUnicodeString&` |
| ListStatus | `const CATListOfCATUnicodeString&` |
| _oItemsWithError | `CATListValCATIxPDMItem_var*` |


### SelectLineCB

```cpp
void SelectLineCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData) ;
```

| 参数 | 类型 |
|------|------|
| iCmd | `CATCommand*` |
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

**源文件**: `CAAxPDMInterfaces.edu/CAAxPDMUICommands.m/LocalInterfaces/CAAxPDMCheckSessionPanel.h`
