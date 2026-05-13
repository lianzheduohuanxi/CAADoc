---
title: "CAAGSMCircleSweepTgDlg"
type: "LocalClass"
module: "CAAGSMInterfaces"
base: "CATDlgDialog"
method_count: 9
source_file: "CAAGSMInterfaces.edu/CAAGsiFeaturesSplCircleSweepTgUI.m/LocalInterfaces/CAAGSMCircleSweepTgDlg.h"
---

# CAAGSMCircleSweepTgDlg

**基类**: CATDlgDialog | **模块**: CAAGSMInterfaces | **方法数**: 9

## 依赖

- `CATDlgDialog.h`
- `CATDlgInclude.h`
- `CAAGSMCircleSweepTgCmd.h`
- `CAAGSMCircleSweepTgUINotifications.h`

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


### SetUserSelectedFeature

```cpp
void SetUserSelectedFeature(int iFieldNumber, const CATISpecObject_var iSpInput) ;
```

| 参数 | 类型 |
|------|------|
| iFieldNumber | `int` |
| iSpInput | `const CATISpecObject_var` |


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


### GetTrimMode

```cpp
int GetTrimMode() ;
```


### SetRadiusValue

```cpp
void SetRadiusValue(double Rad) ;
```

| 参数 | 类型 |
|------|------|
| Rad | `double` |


### SetTrimMode

```cpp
void SetTrimMode(int iTrim, int sensitivity = 1) ;
```

| 参数 | 类型 |
|------|------|
| iTrim | `int` |
| 1 | `int sensitivity =` |


### UpdatePanel

```cpp
void UpdatePanel() ;
```


---

**源文件**: `CAAGSMInterfaces.edu/CAAGsiFeaturesSplCircleSweepTgUI.m/LocalInterfaces/CAAGSMCircleSweepTgDlg.h`
