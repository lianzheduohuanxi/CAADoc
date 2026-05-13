---
title: "CAADegCreateCylinder1Cmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 3
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateCylinder1Cmd.h"
---

# CAADegCreateCylinder1Cmd

> State command which creates a Cylinder Illustrates: Creation of a state command Use of a selection Agent Use of an agent to select in another editor. Use of the CATBasicMultiDocumentCommand class Usage: Select a line in the current editor Select a circle in the current or in another editor. The command is ended when you have selected the 2 elements. (The first element can be changed) Graph: +------------------+ !                  ! !                  ! - CATPathElementAgent !                  ! - CATOtherDocumentAgent !                  ! !                  ! +---------+--------+ ! Ok: CreateCylinder ! V NULL

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 3

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode


## 公共方法

### CreateCylinder

```cpp
CATBoolean CreateCylinder(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


### GetValuation

```cpp
void GetValuation(CATMathPoint & oBasePoint, CATMathPoint & oTopPoint, float & oRadius) ;
```

| 参数 | 类型 |
|------|------|
| oBasePoint | `CATMathPoint &` |
| oTopPoint | `CATMathPoint &` |
| oRadius | `float &` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateCylinder1Cmd.h`
