---
title: "CAAAfrPointEditCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 3
source_file: "CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAAfrPointEditCmd.h"
---

# CAAAfrPointEditCmd

> Command which edits a point (an CAASysPoint component). This command is returned by the CAASysPoint implementation of the CATIEdit interface. Illustrates: programming a command which edits an object. This command must manage its destruction itself. It must be deleted: when the end user closes the dialog box (Ok,Cancel,Close buttons). So the command must subscribe to the corresponding notifications and request the command destruction in the callbacks. when another command is launched. So the current command must take the focus in order to be called on the Cancel when it loses the focus. Cancel must request the command destruction as well. This command launches a dialog box to edit this object. It could have been the dialog object itself like the CAAAfrPlaneEditCmd in the same module. Inheritance: CATDlgDialog ( Dialog Framework) CATDlgWindow ( Dialog Framework) CATDialog   (Dialog Framework) CATCommand  (System Framework) CATBaseUnknown (System Framework). Main Method: constructor  -> requests the focus Cancel       -> Suicide of the command Desactivate  -> Dialog box is hidden. Activate     -> Creates and builds the dialog box if it doesn't exist and shows it. CloseBox     -> Suicide of the command System Framework

**基类**: CATCommand | **模块**: CAAApplicationFrame | **方法数**: 3

## 依赖

- `CATCommand.h`

## 虚方法

### Cancel

```cpp
virtual CATStatusChangeRC Cancel(CATCommand *iPublisher, CATNotification *iNotification) ;
```

Methods called by the command selector to manage the focus

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |


### Desactivate

```cpp
virtual CATStatusChangeRC Desactivate(CATCommand *iPublisher, CATNotification *iNotification) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |


### Activate

```cpp
virtual CATStatusChangeRC Activate(CATCommand *iPublisher, CATNotification *iNotification) ;
```

| 参数 | 类型 |
|------|------|
| *iPublisher | `CATCommand` |
| *iNotification | `CATNotification` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAAfrPointEditCmd.h`
