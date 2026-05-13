---
title: "CAADegClippingBySphereCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 6
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegClippingBySphereCmd.h"
---

# CAADegClippingBySphereCmd

> State command which Illustrates: Creation of a State command Use of a CATPathElementAgent Use acquisition filter Undo/Redo management Usage: Select a point Select a second point ==> Graph: Is composed of 3 states containing the same CATPathElement agent expecting a point. These states are consecutive. One transition enables to progress from one state to the following. The third transition leaves the third states and reaches the NULL state to end the command. Undo/Redo is managed at local and global levels. +------------------+ !  CenterPathAgent  ! +--------+---------+ ! +--------V---------+ !  RadiusPathAgent  ! +--------+---------+ !   Clipped the element out the sphere V NULL DialogEngine Framework

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 6

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`
- `CAT3DBoundingSphere.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode


## 静态方法

### DesallocatListOfDeletedElement

```cpp
static void DesallocatListOfDeletedElement(void * iUsefulData) ;
```

DesallocatListOfDeletedElement ------------------------------ Static method called when Redo/Undo for it is no more possible. You have staked more than 10 Undo/Redo, or the stack is unstaked, or the model has been modified after the Redo.

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoClippingBySphereTheModel

```cpp
static void UndoClippingBySphereTheModel(void * iUsefulData) ;
```

UndoClippingBySphereTheModel ------------------- Static method called when the command is ended. Must undo the command so it removes the triangle of the document

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoClippingBySphereTheModel

```cpp
static void RedoClippingBySphereTheModel(void * iUsefulData) ;
```

RedoClippingBySphereTheModel ---------------- Static method called when the command is ended. Must redo the command so it adds the triangle into the document

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


## 公共方法

### ClippingBySphereTheModel

```cpp
CATBoolean ClippingBySphereTheModel(void * iUsefulData) ;
```

UndoClippingBySphereTheModel ------------------- Static method called when the command is ended. Must undo the command so it removes the triangle of the document

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### TestRadiusPoint

```cpp
CATBoolean TestRadiusPoint(CATDialogAgent * iAgent, void *iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iAgent | `CATDialogAgent *` |
| *iUsefulData | `void` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegClippingBySphereCmd.h`
