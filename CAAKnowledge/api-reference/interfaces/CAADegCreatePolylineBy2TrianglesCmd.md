---
title: "CAADegCreatePolylineBy2TrianglesCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 5
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePolylineBy2TrianglesCmd.h"
---

# CAADegCreatePolylineBy2TrianglesCmd

> State command which creates a polyline from 2 triangles created by the CAADegCreateTriangleCmd command during this command. At the end of the command we have 3 new elements in the model: the 2 news triangles and the new polyline. The polyline is created from the 6 points. Illustrates: Creation of a State command Use of an agent which is a CATStateCommand too Undo/Redo management Graph: Is composed of 2 states containing each an agent to create a Triangle. These states are consecutive. One transition enables to progress from one state to the following. The second transition leaves the second state and reaches the NULL state to end the command. Undo/Redo is managed at local and global levels. +---------------------------+ !  CAADegCreateTriangleCmd  ! +--------+------------------+ ! +--------V------------------+ !  CAADegCreateTriangleCmd  ! +--------+------------------+ ! !   CreatePolyline V NULL DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 5

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode


## 静态方法

### DesallocatPolyline

```cpp
static void DesallocatPolyline(void * iUsefulData) ;
```

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the Polyline. To redefine to have Undo/Redo on the command. It is called just after the Cncel method of the command. UndoCreatePolyline,

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoCreatePolyline

```cpp
static void UndoCreatePolyline(void * iUsefulData) ;
```

UndoCreateParent ------------------- Static method called when the command is ended. Must undo the command so it removes the Polyline and the the 2 triangles of the document

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreatePolyline

```cpp
static void RedoCreatePolyline(void * iUsefulData) ;
```

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the Polyline. To redefine to have Undo/Redo on the command. It is called just after the Cncel method of the command. UndoCreatePolyline,

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


## 公共方法

### CreatePolyline

```cpp
CATBoolean CreatePolyline(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePolylineBy2TrianglesCmd.h`
