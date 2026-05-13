---
title: "CAAMmrCCDataExtensionStCmd"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATMMUIStateCommand"
method_count: 4
source_file: "CAAMechanicalModeler.edu/CAAMmrCCDataExtensionUI.m/LocalInterfaces/CAAMmrCCDataExtensionStCmd.h"
---

# CAAMmrCCDataExtensionStCmd

**基类**: CATMMUIStateCommand | **模块**: CAAMechanicalModeler | **方法数**: 4

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

### SelectFeatureAndExtend

```cpp
CATBoolean SelectFeatureAndExtend(void* data) ;
```

| 参数 | 类型 |
|------|------|
| data | `void*` |


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCCDataExtensionUI.m/LocalInterfaces/CAAMmrCCDataExtensionStCmd.h`
