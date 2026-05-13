---
title: "CAAAfrProgressTaskSampleCmd"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATDlgDialog"
method_count: 3
source_file: "CAAApplicationFrame.edu/CAAAfrProgressTask.m/LocalInterfaces/CAAAfrProgressTaskSampleCmd.h"
---

# CAAAfrProgressTaskSampleCmd

> This class is a command ( a dialog comand ) which contains two objects: a check button to indicate if the task is interruptible or not a button to launch the task During the task, a dialog box (modal) is displayed. This dialog box contains a progress bar and some informations about the task and the progression. If the task is interruptible, a Cancel button enables the end user to interrupt the task. If the task is interrupted the dialog box with the progress bar is closed The command implements the CATIProgressTask How to launch the sample: Launch CATIA Start Menu, Infrastructure / CAA V5 Geometrical Analysis In the "Mathematic Analysis" toolbar or in the Analysis menu launch the "Progress Task" command Click or nor the Interruptible Task check button Push the Compute button To finish the command, click Close

**基类**: CATDlgDialog | **模块**: CAAApplicationFrame | **方法数**: 3

## 依赖

- `CATDlgDialog.h`

## 虚方法

### PerformTask

```cpp
virtual HRESULT PerformTask(CATIProgressTaskUI * iUI, void * iUserData) ;
```

CATIProgressTask interface -------------------------- The task is included in this method. The dialog box which contains the progress bar is controlled by the CATIProgressTaskUI interface. So in this method you give the order to the dialog box to: - Give the range of the progress bar ( once ) - At each step you set the index of the process If the task is interruptible, the method return E_FAIL and the dialog box will be closed.

| 参数 | 类型 |
|------|------|
| iUI | `CATIProgressTaskUI *` |
| iUserData | `void *` |


### GetCatalogName

```cpp
virtual HRESULT GetCatalogName(CATString * oCatalogName) ;
```

which contains: - The title of the  dialog box which contains the progress bar keyword: ProgressTaskUI.Title - The object concerned by the task keyword: ProgressTaskUI.ObjectName - The comment keyword: ProgressTaskUI.Comment Note: in this use case, the comment is not the default comment, those set in the ProgressTaskUI.Comment. We have choosen to change the comment at each step: Step i .... The comment is built from the keyword ProgresstaskUI.CommentRuntime set in the same NLS file as the current command.

| 参数 | 类型 |
|------|------|
| oCatalogName | `CATString *` |


### GetIcon

```cpp
virtual HRESULT GetIcon(CATString * oIcon) ;
```

Returns the name of the icon displayed in the dialog box which contains the progress bar

| 参数 | 类型 |
|------|------|
| oIcon | `CATString *` |


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrProgressTask.m/LocalInterfaces/CAAAfrProgressTaskSampleCmd.h`
