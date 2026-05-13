---
title: "CAAAfrDumpCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 1
source_file: "CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrDumpCmd.h"
---

# CAAAfrDumpCmd

> Command which launches a dialog box which displays the composition of the current document, that is to say the number of objects of each types (points, lines, circles...) This command takes the focus in shared mode. Illustrates: creating a simple command derived from CATCommand creating a dialog box Subscribing to send/receive events Inheritance: CATCommand  (System Framework) CATBaseUnknown (System Framework) Main Method: Activate Creates the dialog box Subscribes to the dialog box events Calls a method to display the model contents DumpContainer Scans the container Displays its contents.

**基类**: CATCommand | **模块**: CAAApplicationFrame | **方法数**: 1

## 依赖

- `CATCommand.h`

## 虚方法

### Activate

```cpp
virtual CATStatusChangeRC Activate(CATCommand *iFromClient, CATNotification *iNotification) ;
```

Activate --------- Creates a CATDlgNotify to display the model's contain. This dialog box is created modal , so the end user cannot do anything before to close it. When it is done, the dump command is killed and the dialog box too. If the dialog box were not modal, you should override : - the Cancel method: to do the same thing that the CloseBox Method - the Desactivate method to hide the dialog box

| 参数 | 类型 |
|------|------|
| *iFromClient | `CATCommand` |
| *iNotification | `CATNotification` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoCommands.m/LocalInterfaces/CAAAfrDumpCmd.h`
