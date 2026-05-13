---
title: "CAACafElementPropertyPageDlg"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATDlgFrame"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafEltToolsOptions.m/LocalInterfaces/CAACafElementPropertyPageDlg.h"
---

# CAACafElementPropertyPageDlg

> Class representing a Dialog object dedicated to a Tools/Options page.This page is managed by the  CAACafElementPropertyPageEdt editor. Who manages what ?: Options of your page are kept in a repository file CAACafElementPropertyPageDlg gets the controller repository in its constructor. The CAACafElementPropertyPageDlg class modifies at each interaction on the dialog objects of the page the repository file thanks to the CAAICafGeometryEltSettingAtt interface. The CAACafElementPropertyPageEdt class manages the repository for reset, cancel and close. When resetting, the dialog class can be called to restore, with the saved values, the dialog objects of the page. Usage: Launch CATIA V5, Tools/Options Inheritance: CATDlgFrame (Dialog Framework) CATDlgBox      (Dialog Framework) CATDialog    (Dialog Framework) CATCommand  ( System Framework) CATBaseUnknown (System Framework) Main Methods: Build         -> Construction of the dialog object ValueSettings -> Valuation of the dialog object from the setting file xxxxCB       -> All these methods modify the dialog object, and the setting file. With Repository mechanism, ( commit/rollback) it's easy to manage the save, no need to keep the old values from the last commit.

**基类**: CATDlgFrame | **模块**: CAACATIAApplicationFrm | **方法数**: 2

## 依赖

- `CATDlgFrame.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### ValueSettings

```cpp
void ValueSettings() ;
```


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafEltToolsOptions.m/LocalInterfaces/CAACafElementPropertyPageDlg.h`
