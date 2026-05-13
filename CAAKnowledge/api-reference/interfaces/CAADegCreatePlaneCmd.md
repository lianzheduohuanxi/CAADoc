---
title: "CAADegCreatePlaneCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 6
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePlaneCmd.h"
---

# CAADegCreatePlaneCmd

> State command which creates a plane from three selected points. Illustrates: Creation of a State command Use of a CATPathElementAgent several times Use of the CATCSO (Set of Current Objects) Usage: Select 3 points ==> The plane is created and becomes the current selected object. Graph: Is composed of 3 states containing the same CATPathElement agent expecting a point. These states are consecutive. One transition enables to progress from one state to the following. The third transition leaves the third states and reaches the NULL state to end the command. +------------------+ !  PointPathAgent  ! +--------+---------+ !   RetrievePoint +--------V---------+ !  PointPathAgent  ! +--------+---------+ !   RetrievePoint +--------V---------+ !  PointPathAgent  ! +--------+---------+ !   CreatePlane V NULL Inheritance: CATStateCommand (DialogEngine Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) Main Method: BuilGraph    : Implements the state chart RetrievePoint: Retrieves the point coordinates. CreatePlane  : Creates the plane. DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 6

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode 1- Creates the PathElement Agent 2- Creates the 3 states (Start, Second, End) 3- Defines a transition from 3-1 Start to Second State 3-2 Second to End State 3-3 End To Final State


## 公共方法

### CheckPoint1

```cpp
CATBoolean CheckPoint1(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckPoint2

```cpp
CATBoolean CheckPoint2(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckPoint3

```cpp
CATBoolean CheckPoint3(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreatePoint

```cpp
CATBoolean CreatePoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreatePlane

```cpp
CATBoolean CreatePlane(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePlaneCmd.h`
