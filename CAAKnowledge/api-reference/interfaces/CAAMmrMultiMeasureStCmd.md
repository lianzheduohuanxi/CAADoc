---
title: "CAAMmrMultiMeasureStCmd"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATMMUIStateCommand"
method_count: 5
source_file: "CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSetUI.m/LocalInterfaces/CAAMmrMultiMeasureStCmd.h"
---

# CAAMmrMultiMeasureStCmd

**基类**: CATMMUIStateCommand | **模块**: CAAMechanicalModeler | **方法数**: 5

## 依赖

- `CATMMUIStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```


### OkAction

```cpp
virtual CATBoolean OkAction(void * data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void *` |


### Cancel

```cpp
virtual CATBoolean Cancel(void * data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void *` |


## 公共方法

### ComputeLength

```cpp
CATBoolean ComputeLength(void* data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void*` |


### ReplaceInput

```cpp
CATBoolean ReplaceInput(void* data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void*` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrMultiMeasureAndMeasureSetUI.m/LocalInterfaces/CAAMmrMultiMeasureStCmd.h`
