---
title: "CAADegCreateLineCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 5
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateLineCmd.h"
---

# CAADegCreateLineCmd

> State command which creates a line from two indications. Illustrates: Creation of a State command Use of CATIndicationAgent Use of the CATISO for the temporary objects Usage: Click in the background ==> A temporary point is created. Click in the background => The line is created between the two selected points Graph: Is composed of 2 states: * stStartState containing one agent a CATIndicationAgent to react to the first point indication * stEndState containing one agent the same CATIndicationAgent to react to the second point indication These states are consecutive. One transition enables to progress from the first state to the second one. Another transition leaves the stEndState and reaches the NULL state to end the command. +------------------+ ! IndicationAgent  ! +--------+---------+ !   CreatePoint +--------V---------+ ! IndicationAgent  ! +--------+---------+ !   CreateLine V NULL Inheritance: CATStateCommand (DialogEngine Framework) CATCommand (System Framework) CATEventSubscriber (System Framework) CATBaseUnknown (System Framework) Main Method: BuilGraph   : Implement the state chart CreatePoint : Creates a temporary point at the start point of the line CreateLine  : Creates the line between the two selected points. DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 5

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode 1- Creates the Dialog Agent 2- Creates the Start state 3- Creates the End   state 4- Defines a transition from Start to End State 5- Defines a transition from End To Final State


## 公共方法

### CheckStartPoint

```cpp
CATBoolean CheckStartPoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckEndPoint

```cpp
CATBoolean CheckEndPoint(void * iUsefulData) ;
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


### CreateLine

```cpp
CATBoolean CreateLine(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateLineCmd.h`
