---
title: "CAAAfrPointEditDlg"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATDlgDialog"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAAfrPointEditDlg.h"
---

# CAAAfrPointEditDlg

> Dialog box which edits a point (an CAASysPoint component). This dialog box is called by the CAAAfrPointEditCmd command which is the Edit command of the CAASysPoint component, that is to say the command returned by the CAASysPoint implementation of the CATIEdit interface. Illustrates: programming a dialog which edits an object. The dialog box does not manage its life cycle. The calling command must request its destruction. Inheritance: CATDlgDialog ( Dialog Framework) CATDlgWindow ( Dialog Framework) CATDialog   (Dialog Framework) CATCommand  (System Framework) CATBaseUnknown (System Framework). Main Method: Build        -> Construction of the dialog objects ClickPreview -> Modifies the object and sends a notification to update the display ClickOk      -> Modifies the object, sends a notification to update the display and closes the dialog box ClickCancel  -> Restores the initial values, sends a notification to update the display and closes the dialog box ClickClose   -> Closes the dialog box CloseBox     -> Hides the dialog box and sends a close notification. ****************************************************************************** Dialog Framework

**基类**: CATDlgDialog | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATDlgDialog.h`

## 公共方法

### Build

```cpp
void Build() ;
```


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAAfrPointEditDlg.h`
