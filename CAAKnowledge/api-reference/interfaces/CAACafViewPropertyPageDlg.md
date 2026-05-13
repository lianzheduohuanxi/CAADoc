---
title: "CAACafViewPropertyPageDlg"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATDlgFrame"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafViewToolsOptions.m/LocalInterfaces/CAACafViewPropertyPageDlg.h"
---

# CAACafViewPropertyPageDlg

> Class representing a Dialog object dedicated to a Tools/Options page.This page is managing by the  CAACafViewPropertyPageEdt editor. See CAACafElementPropertyPageDlg for all details. Usage: Launch CATIA V5, Tools/Options Inheritance: CATDlgFrame (Dialog Framework) CATDlgBox      (Dialog Framework) CATDialog    (Dialog Framework) CATCommand  ( System Framework) CATBaseUnknown (System Framework) Main Methods: Build         -> Construction of the Dialog object ValueSettings -> Valuation of the Dialog object from the setting file xxxxCB       -> All these methods modify the dialog object, and the setting file. With Repository mechanism, ( commit/rollback) it's easy to manage the save, no need to keep the old values from the last commit.

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

**源文件**: `CAACATIAApplicationFrm.edu/CAACafViewToolsOptions.m/LocalInterfaces/CAACafViewPropertyPageDlg.h`
