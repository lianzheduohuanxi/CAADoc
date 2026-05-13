---
title: "CAADegAnalysisNumericCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 4
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisNumericCmd.h"
---

# CAADegAnalysisNumericCmd

> State command to display the count of selected elements Illustrates: Creation of a State command Use of CATPathElementAgent and CATDialogAgent Use of the CATCSO Use of multi acquisition behavior CATDlgEngMultiAcquisitionSelModes,CATDlgEngMultiAcquisitionCtrl, CATDlgEngMultiAcquisitionUserCtrl Usage: Choose the behavior of the CATPathElementAgent agent in the dialog box make selections ==> The objects of this type are highlighted. and in the dialog box the count of each element selected are displayed Graph Is composed of 5 states: * stChoiceBehaviorState containing three agents three CATDialogAgent to react to events sent by the CATDlgChoiceBehaviorDlg dialog box Close or Cancel event -> Null state OK -> depends on the choice we go to: stMultiAcquisitionSelModesState or stMultiAcquisitionCtrlState or stMultiAcquisitionuserCtrlState * sMultiAcquisitionSelModesState containing three agents two CATDialogAgent to react to events sent by the CATDlgAnalysisNumericDlg dialog box Close or Cancel event -> Null state one CATPathElementAgent to react to the multi-sel -> stEndState * stMultiAcquisitionCtrlState containing three agents two CATDialogAgent to react to events sent by the CATDlgAnalysisNumericDlg dialog box Close or Cancel event -> Null state one CATPathElementAgent to react to the multi-sel -> stEndState * stMultiAcquisitionuserCtrlState containing three agents two CATDialogAgent to react to events sent by the CATDlgAnalysisNumericDlg dialog box Close or Cancel event -> Null state one CATPathElementAgent to react to the multi-sel -> stEndState * stEndState containing two agents two CATDialogAgent to react to events sent by the CATDlgAnalysisNumericDlg dialog box Close or Cancel event -> Null state Inheritance: CATStateCommand (DialogEngine Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 4

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. Shows a contextual menu only when you click in the background viewer.


## 公共方法

### DisplaySelectedElement

```cpp
CATBoolean DisplaySelectedElement(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckCase

```cpp
CATBoolean CheckCase(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### EndChoice

```cpp
CATBoolean EndChoice(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisNumericCmd.h`
