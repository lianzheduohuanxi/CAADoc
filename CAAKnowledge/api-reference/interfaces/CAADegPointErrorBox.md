---
title: "CAADegPointErrorBox"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATDlgNotify"
method_count: 1
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegPointErrorBox.h"
---

# CAADegPointErrorBox

> Dialog window which displays an error message indicating that 2 points given by the user are equal. This window is used by the CAADegCreatePlaneCmd, CAADegCreateTriangleCmd, CAADegCreatePolylineCmd. Main Method: Build  : Displays the message and subscribes to the Ok notification. ClickOK: Callback which requests the dialog box destruction.

**基类**: CATDlgNotify | **模块**: CAADialogEngine | **方法数**: 1

## 依赖

- `CATDlgNotify.h`

## 公共方法

### Build

```cpp
void Build() ;
```


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegPointErrorBox.h`
