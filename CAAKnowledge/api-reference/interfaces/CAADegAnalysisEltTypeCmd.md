---
title: "CAADegAnalysisEltTypeCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 7
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisEltTypeCmd.h"
---

# CAADegAnalysisEltTypeCmd

> State command which highlights the objects of a given type. Illustrates: Creation of a State command Use of CATPathElementAgent and CATDialogAgent Use of the CATPSO Creation of a contextual menu Usage: Right click ==> A contextual menu displays a list of object types. Select a type ==> The objects of this type are highlighted. Graph: Is composed of one state containing 2 agents: a CATPathElementAgent to react to right clicks on an object a CATDialogAgent to react to other right clicks (so on the background) Any right click triggers a transition which displays the contextual menu. Each menu item is associated with a callback which highlights the the objects of the specified type by putting this objects into the Set of Prehighlighted Objects (CATPSO). The CATPSO is emptied at the end of the command. The command ends when the user selects another command. +--------------------------+<--+ ! PathAgent   DialogAgent  !   !  CreateCntxMenu +--------------------------+---+ Inheritance: CATStateCommand (DialogEngine Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) Main Method: BuilGraph CreateCntxMenu : Display the contextual menu ShowLine, ShowPoint, ShowCircle, ShowEllipse ShowPlane: callbacks associated the menu items. Highlight the objects of a given type. DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 7

## 依赖

- `CATStateCommand.h`
- `CATPathElement.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. Shows a contextual menu only when you click in the background viewer.


## 公共方法

### CreateCntxMenu

```cpp
CATBoolean CreateCntxMenu(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### ShowPoint

```cpp
void ShowPoint(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### ShowLine

```cpp
void ShowLine(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### ShowCircle

```cpp
void ShowCircle(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### ShowEllipse

```cpp
void ShowEllipse(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


### ShowPlane

```cpp
void ShowPlane(CATCommand *iPublishingCommand, CATNotification *iNotification, CATCommandClientData iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| *iPublishingCommand | `CATCommand` |
| *iNotification | `CATNotification` |
| iUsefulData | `CATCommandClientData` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegAnalysisEltTypeCmd.h`
