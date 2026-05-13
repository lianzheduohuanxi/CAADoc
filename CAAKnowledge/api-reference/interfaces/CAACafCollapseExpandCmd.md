---
title: "CAACafCollapseExpandCmd"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATStateCommand"
method_count: 2
source_file: "CAACATIAApplicationFrm.edu/CAACafSpecTree.m/LocalInterfaces/CAACafCollapseExpandCmd.h"
---

# CAACafCollapseExpandCmd

> This state command illustrates how to carry out a collapse/expand in the specification tree displayed in a CATFrmNavigGraphicWindow.

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

### ExpandObject

```cpp
CATBoolean ExpandObject(void * iDummy) ;
```

| 参数 | 类型 |
|------|------|
| iDummy | `void *` |


---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafSpecTree.m/LocalInterfaces/CAACafCollapseExpandCmd.h`
