---
title: "CAADegCreateEllipseCmd"
type: "LocalClass"
module: "CAADialogEngine"
base: "CATStateCommand"
method_count: 3
source_file: "CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateEllipseCmd.h"
---

# CAADegCreateEllipseCmd

**基类**: CATStateCommand | **模块**: CAADialogEngine | **方法数**: 3

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


## 公共方法

### CreateCamera

```cpp
CATBoolean CreateCamera(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


### CreateEllipse

```cpp
CATBoolean CreateEllipse(void * iUsefulData) ;
```

| 参数 | 类型 |
|------|------|
| iUsefulData | `void *` |


---

**源文件**: `CAADialogEngine.edu/CAADegGeoCommands.m/LocalInterfaces/CAADegCreateEllipseCmd.h`
