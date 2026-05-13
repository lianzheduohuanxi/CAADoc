---
title: "CAAPstINFEditDlgPoint"
type: "LocalClass"
module: "CAAProductStructure"
base: "CATDlgDialog"
method_count: 1
source_file: "CAAProductStructure.edu/CAAPstINFCommands.m/LocalInterfaces/CAAPstINFEditDlgPoint.h"
---

# CAAPstINFEditDlgPoint

> Dialog box which edits a point (an CAAPstINFPoint component). This dialog box is called by the CAAPstINFEditCmdPoint command which is the Edit command of the CAAPstINFPoint component, that is to say the command returned by the CAAPstINFPoint implementation of the CATIEdit interface. Illustrates programming a dialog which edits an object. The dialog box does not manage its life cycle. The calling command must request its destruction. Inheritance: CATDlgDialog ( Dialog Framework) CATDlgWindow ( Dialog Framework) CATDialog   (Dialog Framework) CATCommand  (System Framework) CATBaseUnknown (System Framework). Main Method: Build        -> Construction of the dialog objects. ClickPreview -> Modifies the object and sends a notification to update the display. ClickOk      -> Modifies the object, sends a notification to update the display and closes the dialog box. ClickCancel  -> Restores the initial values, sends a notification to update the display and closes the dialog box. CloseBox     -> Hides the dialog box and sends a close notification. ******************************************************************************

**基类**: CATDlgDialog | **模块**: CAAProductStructure | **方法数**: 1

## 依赖

- `CATDlgDialog.h`

## 公共方法

### Build

```cpp
void Build() ;
```


---

**源文件**: `CAAProductStructure.edu/CAAPstINFCommands.m/LocalInterfaces/CAAPstINFEditDlgPoint.h`
