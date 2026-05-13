---
title: "CAACafCenterGraphCmd"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATStateCommand"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafCenterGraph.m/LocalInterfaces/CAACafCenterGraphCmd.h"
---

# CAACafCenterGraphCmd

> This state command illustrates how to use the CATCafCenterGraph class to center a node in the specification tree displayed in a CATFrmNavigGraphicWindow.

**基类**: CATStateCommand | **模块**: CAACATIAApplicationFrm | **方法数**: 2

## 依赖

- `CATStateCommand.h`

## 虚方法

### BuildGraph

```cpp
virtual void BuildGraph() ;
```

BuildGraph ----------- Implements the statechart. It is called once, even if the command is in repeat mode


## 公共方法

### CenterGraphOnObject

```cpp
CATBoolean CenterGraphOnObject(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafCenterGraph.m/LocalInterfaces/CAACafCenterGraphCmd.h`
