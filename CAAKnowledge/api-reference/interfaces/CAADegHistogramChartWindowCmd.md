---
title: "CAADegHistogramChartWindowCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 4
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegHistogramChartWindowCmd.h"
---

# CAADegHistogramChartWindowCmd

> State command which creates a window with a Histogram Chart. This window is dedicated to the current document. Illustrates: Creation of a State command Use of a CATPanelState Usage: Graph: Is composed of 1 state which is a CATPanelState. It's a state associated with 3 transitions created beforehand and linked to the Ok, Apply, Cancel buttons of a given dialog. The transition triggered by the Ok button goes to the NULL state. The transition triggered by the Cancel button goes to the Cancel state. The Cancel states ends the command and execute a global undo on the command. +------------------+ !                  ! !                  ! ! IndicationAgent  ! !                  ! !                  ! +----+--------+----+ !        ! Cancel !        ! Ok: CreateWindow !        ! V        V Cancel    NULL Inheritance: CATStateCommand (DialogEngine Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) Main Method: BuildGraph             : Implements the state chart CreateWindow           : Creates the window

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 4

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode Creates the dialog to customize the window Creates the State associated with the dialog box Completes the Ok transition


## 公共方法

### Editor1Selected

```cpp
CATBoolean Editor1Selected(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### Editor1Deselected

```cpp
CATBoolean Editor1Deselected(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateHistogramChartWindow

```cpp
CATBoolean CreateHistogramChartWindow(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegHistogramChartWindowCmd.h`
