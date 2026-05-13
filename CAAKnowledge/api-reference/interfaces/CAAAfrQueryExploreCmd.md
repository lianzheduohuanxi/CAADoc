---
title: "CAAAfrQueryExploreCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 3
source_file: "CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrQueryExploreCmd.h"
---

# CAAAfrQueryExploreCmd

> Shared command which inserts a progress bar in the status bar and simulates its use. Illustrates: creating a simple shared command derived from CATCommand Using a progress bar Inheritance: CATCommand  (System Framework) CATBaseUnknown (System Framework) Main Method: Activates Contains nearly all the code. Creates the progress bar and simulates a long task to show a progression.

**基类**: CATCommand | **模块**: CAAApplicationFrame | **方法数**: 3

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


### Compute

```cpp
virtual void Compute() ;
```

Simulates a long task.


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrQueryExploreCmd.h`
