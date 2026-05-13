---
title: "CAAAfrChangeViewNormalCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 2
source_file: "CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrChangeViewNormalCmd.h"
---

# CAAAfrChangeViewNormalCmd

> Command which changes the view point according to its constructor's argument. This command is used three times in the workshop for the three directions (Normal X, Normal Y, Normal Z). The command header which launches this function is instantiated three times with a different argument and passes this argument to the command. Illustrates: creating a simple exclusive command derived from CATCommand and parameterized by an argument. Using cameras. Inheritance: CATCommand  (System Framework) CATBaseUnknown (System Framework) Main Method: Activate : Creates a camera and gives it to the current window.

**基类**: CATCommand | **模块**: CAAApplicationFrame | **方法数**: 2

## 依赖

- `CATCommand.h`

## 虚方法

### Activate

```cpp
virtual CATStatusChangeRC Activate(CATCommand * iFromClient, CATNotification * iEvtData) ;
```

Activate: -------- Contains the command code. The method is called when the command gets the focus.

| 参数 | 类型 |
|------|------|
| iFromClient | `CATCommand *` |
| iEvtData | `CATNotification *` |


### Cancel

```cpp
virtual CATStatusChangeRC Cancel(CATCommand * iFromClient, CATNotification * iEvtData) ;
```

Cancel: -------- This method is called when the command loses the focus definitively because an excluse command requires it. This method must request explicitely the deallocation of the current command.

| 参数 | 类型 |
|------|------|
| iFromClient | `CATCommand *` |
| iEvtData | `CATNotification *` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrChangeViewNormalCmd.h`
