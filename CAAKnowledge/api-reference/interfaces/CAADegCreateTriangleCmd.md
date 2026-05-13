---
title: "CAADegCreateTriangleCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 17
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateTriangleCmd.h"
---

# CAADegCreateTriangleCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 17

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode


## 静态方法

### DesallocatTriangle

```cpp
static void DesallocatTriangle(void * iUsefulData) ;
```

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the triangle. To redefine to have Undo/Redo on the command. It is called just after the Cncel method of the command. UndoCreateTriangle,

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoCreateTriangle

```cpp
static void UndoCreateTriangle(void * iUsefulData) ;
```

UndoCreateTriangle ------------------- Static method called when the command is ended. Must undo the command so it removes the triangle of the document

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreateTriangle

```cpp
static void RedoCreateTriangle(void * iUsefulData) ;
```

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the triangle. To redefine to have Undo/Redo on the command. It is called just after the Cncel method of the command. UndoCreateTriangle,

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


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


### CreateLine

```cpp
CATBoolean CreateLine(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateTriangle

```cpp
CATBoolean CreateTriangle(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoCreateLine

```cpp
CATBoolean UndoCreateLine(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreateLine

```cpp
CATBoolean RedoCreateLine(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoCreatePoint

```cpp
CATBoolean UndoCreatePoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreatePoint

```cpp
CATBoolean RedoCreatePoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### BeforeUndo

```cpp
void BeforeUndo() ;
```


### BeforeRedo

```cpp
void BeforeRedo() ;
```


### GetValue

```cpp
HRESULT GetValue(CAAISysPolyline ** oTriangle) ;
```

GetValue -------- When this command is an agent, this method allows you to retrieve the created triangle. if the triangle is valid, HRESULT is S_OK and oTriangle is valuated by _piEltTriangle, else HRESULT is E_FAIL . _IsAgentValuated is set TRUE when the triangle is created and at each Redo, but set a FALSE at the beginning of the command and at each Undo. GetValue takes account of this value to give the response.

| 参数 | 类型 |
|------|------|
| oTriangle | `CAAISysPolyline **` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateTriangleCmd.h`
