---
title: "CAACafViewPropertyPageEdt"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATEditor"
method_count: 5
source_file: "CAACATIAApplicationFrm.edu/CAACafViewToolsOptions.m/LocalInterfaces/CAACafViewPropertyPageEdt.h"
---

# CAACafViewPropertyPageEdt

> Class representing a Tools Options Properties  Page, and implementing the CATIUserSettings interface. See CAACafElementPropertyPageEdt for all details. Usage: Launch CATIA V5, Tools/Options Inheritance: CATEditor ( CATIAApplicationFrame Framework) CATImplementationAdapter ( ObjectModelerBase Framework) CATEventSubscriber      ( System Framework ) CATBaseUnknown          (System Framework). Main Methods: BuildEditor            -> Create and Build the dialog SetUserSettingsValue   -> Valuation of the Dialog object from settings file ResetUserSettingsValue -> After push RESET CancelModification     -> After push CANCEL CommitModification     -> After push OK

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

**源文件**: `CAACATIAApplicationFrm.edu/CAACafViewToolsOptions.m/LocalInterfaces/CAACafViewPropertyPageEdt.h`
