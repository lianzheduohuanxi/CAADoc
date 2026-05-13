---
title: "CAADegCreateRectangleCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 7
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateRectangleCmd.h"
---

# CAADegCreateRectangleCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 7

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`
- `CATMathPlane.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode 1- Creates the dialog agents 2- Creates states 3- Defines transitions


## 公共方法

### TestPoint1

```cpp
CATBoolean TestPoint1(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### TestPoint2

```cpp
CATBoolean TestPoint2(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateCamera

```cpp
CATBoolean CreateCamera(void * iUsefulData) ;
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


### UpdateRectangle

```cpp
CATBoolean UpdateRectangle(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### NewRectangle

```cpp
CATBoolean NewRectangle(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateRectangleCmd.h`
