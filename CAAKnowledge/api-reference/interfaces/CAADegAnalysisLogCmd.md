---
title: "CAADegAnalysisLogCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 5
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisLogCmd.h"
---

# CAADegAnalysisLogCmd

> State command which creates a temporary point on a selected line, at at a given location. Illustrates: Creation of a State command Use of CATPathElementAgent Use of the CATISO Creation of a contextual menu Usage: Right click on a line ==> A contextual menu displays a choice of 3 points: Start point, Medium point, End point. Select a point type ==> A temporary point is created at the specified location. Graph: Is composed of one state containing 1 agent: a CATPathElementAgent which reacts to right clicks on lines A right click on a line triggers a transition which displays the contextual menu. Each menu item is associated with a callback which creates a temporary point at the requested location and puts it into the Set of Interactive Objects (CATISO). The CATISO is emptied at the end of the command. The command ends when the user selects another command. +--------------------------+<--+ !         PathAgent        !   !  CreateCntxMenu +--------------------------+---+ Inheritance: CATStateCommand (DialogEngine Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) Main Method: BuilGraph CreateCntxMenu: Display the contextual menu StartPoint, MediumPoint, EndPoint: callbacks associated the menu items. Creates the temporary point. DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 5

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart.


## 公共方法

### CreateCntxMenu

```cpp
CATBoolean CreateCntxMenu(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### StartPoint

```cpp
void StartPoint(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### MediumPoint

```cpp
void MediumPoint(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### EndPoint

```cpp
void EndPoint(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisLogCmd.h`
