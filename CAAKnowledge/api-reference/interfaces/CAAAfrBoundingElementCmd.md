---
title: "CAAAfrBoundingElementCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATDlgDialog"
method_count: 0
source_file: "CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrBoundingElementCmd.h"
---

# CAAAfrBoundingElementCmd

> Command which displays temporary bounding sheres around model objects. A dialog window enables the user to choose if the surrounding objects will the points, the lines or objects of both types. This command does not take the focus. Three spheres are created, one for each plane: x=0, y=0, z=0. Illustrates: creating a simple command derived from CATDlgDialog Arranging Dialog objects Subscribing to send/receive events Using a progress bar Using the Set of Interactive Objects (ISO) to display temporary objects Using cameras Inheritance: CATDlgDialog (Dialog Framework) CATDialog   (Dialog Framework) CATCommand  (System Framework) CATBaseUnknown (System Framework) Main Method: constructor Creates the dialog widgets Subscribes to the Apply and Close events Retrieves the Set of Interactive Objects and the model container Creates temporary circles to simulate bounding spheres ClickApply Updates the temporary bounding sphere Uses a progress bar to simulate a long task.

**基类**: CATDlgDialog | **模块**: CAAApplicationFrame | **方法数**: 0

## 依赖

- `CATDlgDialog.h`
- `CATBoolean.h`

---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrBoundingElementCmd.h`
