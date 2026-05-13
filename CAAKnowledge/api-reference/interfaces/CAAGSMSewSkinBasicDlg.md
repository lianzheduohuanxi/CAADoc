---
title: "CAAGSMSewSkinBasicDlg"
type: "LocalClass"
module: "CAAGSMInterfaces"
base: "CATDlgDialog"
method_count: 5
source_file: "CAAGSMInterfaces.edu/CAAGsiFeaturesSplSewSkinBasicUI.m/LocalInterfaces/CAAGSMSewSkinBasicDlg.h"
---

# CAAGSMSewSkinBasicDlg

**基类**: CATDlgDialog | **模块**: CAAGSMInterfaces | **方法数**: 5

## 依赖

- `CATDlgDialog.h`
- `CATDlgInclude.h`
- `CAAGSMSewSkinBasicCmd.h`
- `CAAGSMSewSkinBasicUINotifications.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### HighLightCurrentPanelField

```cpp
void HighLightCurrentPanelField(int iFieldNumber) ;
```

| 参数 | 类型 |
|------|------|
| iFieldNumber | `int` |


### SetName

```cpp
void SetName(int iFieldNumber, CATUnicodeString iName) ;
```

| 参数 | 类型 |
|------|------|
| iFieldNumber | `int` |
| iName | `CATUnicodeString` |


### AnalyseNotifs

```cpp
void AnalyseNotifs(CATCommand* fromClient, CATNotification* Notif, CATCommandClientData modifId) ;
```

| 参数 | 类型 |
|------|------|
| fromClient | `CATCommand*` |
| Notif | `CATNotification*` |
| modifId | `CATCommandClientData` |


### AutoFieldSelection

```cpp
void AutoFieldSelection(CATDlgSelectorList* SelectField) ;
```

| 参数 | 类型 |
|------|------|
| SelectField | `CATDlgSelectorList*` |


---

**源文件**: `CAAGSMInterfaces.edu/CAAGsiFeaturesSplSewSkinBasicUI.m/LocalInterfaces/CAAGSMSewSkinBasicDlg.h`
