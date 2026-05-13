---
title: "CAACafTexturePropertyPageDlg"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATDlgFrame"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafEditTextureProp.m/LocalInterfaces/CAACafTexturePropertyPageDlg.h"
---

# CAACafTexturePropertyPageDlg

> This class is a page of the Edit/Properties Dialog Box. This page is managing by the CAACafTexturePropertyPageEdt editor . Inheritance CATDlgFrame (Dialog Framework) CATDlgBox      (Dialog Framework) CATDialog     (Dialog Framework) CATCommand  ( System Framework) CATBaseUnknown (System Framework) Main Methods: 6 methods called by the CAACafTexturePropertyPageEdt class constructor           -> Initialization Build                 -> Construction of the Dialog object SetPropertyValue      -> Valuation of the Dialog object CommitModification    -> Set the current value to the extract object CancelModification    -> Empty for the sample CloseWindowFromEditor -> Empty for the sample 1 method  called by its Dialog's father destructor            -> delete object which are not dialog object /=========================================================================== CATDialog Framework

**基类**: CATDlgFrame | **模块**: CAACATIAApplicationFrm | **方法数**: 2

## 依赖

- `CATDlgFrame.h`
- `CATEditor.h`

## 公共方法

### Build

```cpp
void Build() ;
```


### CloseWindowFromEditor

```cpp
void CloseWindowFromEditor() ;
```


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafEditTextureProp.m/LocalInterfaces/CAACafTexturePropertyPageDlg.h`
