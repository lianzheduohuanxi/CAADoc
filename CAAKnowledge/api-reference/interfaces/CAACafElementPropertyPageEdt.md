---
title: "CAACafElementPropertyPageEdt"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATEditor"
method_count: 5
source_file: "CAACATIAApplicationFrm.edu/CAACafEltToolsOptions.m/LocalInterfaces/CAACafElementPropertyPageEdt.h"
---

# CAACafElementPropertyPageEdt

> Class representing a Tools Options Properties  Page, and implementing the CATIUserSettings interface. Who manages what?: Options of your page are kept in a setting file.This setting file is controlled by a component controller. You never acceed directly to the setting file. CAACafElementPropertyPageEdt retrieves this controller in its constructor and aks it a pointer to its CATIIniSettingManagment interface. CAACafElementPropertyPageDlg retrieves this controller in its constructor too and aks it a pointer to its CAAICafGeometryEltSettingAtt interface. The CAACafElementPropertyPageDlg class modifies the repository file (thanks to the CAAICafGeometryEltSettingAtt interface) at each interaction on the dialog objects of the page. The CAACafElementPropertyPageEdt class manages the repository (thanks to the CATIIniSettingManagment interface) for reset, cancel and ok. In the specific case of reset, the dialog class can be called to replace the values of the page, with the initial one. Nls/Rsc Files Located in the CNext/resources/msgcatalog of the framework, you find 2 files: CAACafElementPropertyPageEdt.CATNls: to define the title of the page CAACafElementPropertyPageEdt.CATRsc: to define the category which belongs this page.The category is the name of the workshop. Usage: Launch CATIA V5, Tools/Options Inheritance: CATEditor ( CATIAApplicationFrame Framework) CATImplementationAdapter ( ObjectModelerBase Framework) CATEventSubscriber      ( System Framework ) CATBaseUnknown          (System Framework). Main Methods: BuildEditor            -> Create and Build the dialog SetUserSettingsValue   -> Valuation of the Dialog object from settings file ResetUserSettingsValue -> After pushing RESET CancelModification     -> After pushing CANCEL CommitModification     -> After pushing OK

**基类**: CATEditor | **模块**: CAACATIAApplicationFrm | **方法数**: 5

## 依赖

- `CATEditor.h`

## 公共方法

### BuildEditor

```cpp
void BuildEditor(CATEditorPage * iTabPage) ;
```

| 参数 | 类型 |
|------|------|
| iTabPage | `CATEditorPage *` |


### SetUserSettingsValue

```cpp
void SetUserSettingsValue(CATSettingRepository * iUselessFileRep) ;
```

| 参数 | 类型 |
|------|------|
| iUselessFileRep | `CATSettingRepository *` |


### ResetUserSettingsValue

```cpp
void ResetUserSettingsValue() ;
```


### CancelModification

```cpp
void CancelModification(CATSettingRepository * iUselessFileRep) ;
```

| 参数 | 类型 |
|------|------|
| iUselessFileRep | `CATSettingRepository *` |


### CommitModification

```cpp
void CommitModification(CATSettingRepository * iUselessFileRep) ;
```

| 参数 | 类型 |
|------|------|
| iUselessFileRep | `CATSettingRepository *` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafEltToolsOptions.m/LocalInterfaces/CAACafElementPropertyPageEdt.h`
