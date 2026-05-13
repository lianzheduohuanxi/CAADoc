---
title: "CAADegCreatePolylineCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 21
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePolylineCmd.h"
---

# CAADegCreatePolylineCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 21

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`
- `CATMathPlane.h`

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

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the polyline. Must be redefined to have Undo/Redo on the command. It is called just after the Cancel method.

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UndoCreatePolyline

```cpp
static void UndoCreatePolyline(void * iUsefulData) ;
```

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the polyline. Must be redefined to have Undo/Redo on the command. It is called just after the Cancel method.

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreatePolyline

```cpp
static void RedoCreatePolyline(void * iUsefulData) ;
```

GetGlobalUndo ------------- Gives to the dialog engine the methods name to call for the global Undo and Redo, and to release the polyline. Must be redefined to have Undo/Redo on the command. It is called just after the Cancel method.

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


## 公共方法

### CheckPointNumber

```cpp
CATBoolean CheckPointNumber(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckFirstPoint

```cpp
CATBoolean CheckFirstPoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckPointBySelect

```cpp
CATBoolean CheckPointBySelect(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckPointByBox

```cpp
CATBoolean CheckPointByBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckPointByIndic

```cpp
CATBoolean CheckPointByIndic(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateFirstPointBySelect

```cpp
CATBoolean CreateFirstPointBySelect(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateFirstPointByIndic

```cpp
CATBoolean CreateFirstPointByIndic(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateFirstPointByBox

```cpp
CATBoolean CreateFirstPointByBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RubberLine

```cpp
CATBoolean RubberLine(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateLineBySelect

```cpp
CATBoolean CreateLineBySelect(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateLineByIndic

```cpp
CATBoolean CreateLineByIndic(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateLineByBox

```cpp
CATBoolean CreateLineByBox(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreatePolyline

```cpp
CATBoolean CreatePolyline(void * iUsefulData) ;
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


### UndoCreateFirstPoint

```cpp
CATBoolean UndoCreateFirstPoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### RedoCreateFirstPoint

```cpp
CATBoolean RedoCreateFirstPoint(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePolylineCmd.h`
