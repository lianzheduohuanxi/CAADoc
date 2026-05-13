---
title: "CAAAfrPlaneEditCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATDlgDialog"
method_count: 4
source_file: "CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAAfrPlaneEditCmd.h"
---

# CAAAfrPlaneEditCmd

> Command which edits a plane (an CAASysPlane component). This command is returned by the CAASysPlane implementation of the CATIEdit interface. Illustrates: programming a command which edits an object. This command must manage its destruction itself. It must be deleted: when the end user closes the dialog box (Ok,Cancel,Close buttons). So the command must subscribe to the corresponding notifications and request the command destruction in the callbacks. when another command is launched. So the current command must take the focus in order to be called on the Cancel when it loses the focus. Cancel must request the command destruction as well. Inheritance: CATDlgDialog ( Dialog Framework) CATDlgWindow ( Dialog Framework) CATDialog   (Dialog Framework) CATCommand  (System Framework) CATBaseUnknown (System Framework). Main Method: constructor  -> requests the focus Build        -> Builds the dialog box and subscribes to its notifications. Cancel       -> Suicide Desactivate  -> Dialog box is hidden Activate     -> Dialog box is shown ClickPreview -> Modifies the object and sends a notification to update the display ClickOk      -> Modifies the object, sends a notification to update the display and closes the dialog box ClickCancel  -> Restores the initial values, sends a notification to update the display and closes the dialog box ClickClose   -> Closes the dialog box CloseBox     -> Suicide Dialog Framework

**基类**: CATDlgDialog | **模块**: CAAApplicationFrame | **方法数**: 4

## 依赖

- `CATDlgDialog.h`

## 虚方法

### Cancel

```cpp
virtual CATStatusChangeRC Cancel(CATCommand *iPublisher, CATNotification *iNotification) ;
```

Methods called by the Command Selector to manage the focus

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


## 公共方法

### Build

```cpp
void Build() ;
```


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoEdition.m/LocalInterfaces/CAAAfrPlaneEditCmd.h`
