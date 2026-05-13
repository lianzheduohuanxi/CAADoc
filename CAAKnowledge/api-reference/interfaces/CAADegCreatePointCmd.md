---
title: "CAADegCreatePointCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 4
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePointCmd.h"
---

# CAADegCreatePointCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 4

## 依赖

- `CATStateCommand.h`
- `CATMathPoint.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode 1- Creates the Indication Agent 2- Creates the dialog box to input xyz 3- Creates the State associated with the dialog box and containing the Indication Agent 4- Defines the transition triggered by the Indication Agent 5- Completes the Apply transition 6- Completes the Ok transition


## 公共方法

### CheckPoint

```cpp
CATBoolean CheckPoint(void * iBidon) ;
```

| 参数 | 类型 |
|------|------|
| iBidon | `void *` |


### CreatePointByIndication

```cpp
CATBoolean CreatePointByIndication(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


### CreatePointByBox

```cpp
CATBoolean CreatePointByBox(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreatePointCmd.h`
