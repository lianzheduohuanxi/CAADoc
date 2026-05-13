---
title: "CAADegCreateCircleCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 6
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateCircleCmd.h"
---

# CAADegCreateCircleCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 6

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`
- `CATMathPlane.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. 1- Creates dialog agents 2- Creates states 3- Defines transitions


## 公共方法

### CreateCamera

```cpp
CATBoolean CreateCamera(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateCircleCenter

```cpp
CATBoolean CreateCircleCenter(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### UpdateCircle

```cpp
CATBoolean UpdateCircle(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### NewCircle

```cpp
CATBoolean NewCircle(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CheckCircleCenter

```cpp
CATBoolean CheckCircleCenter(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateCircleCmd.h`
