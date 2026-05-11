---
title: "CAAMmrMultiMeasureStCmd"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATMMUIStateCommand"
method_count: 3
visibility: "local"
verified: true
---

# CAAMmrMultiMeasureStCmd

**基类**: CATMMUIStateCommand  
**模块**: CAAMechanicalModeler  
**可见性**: local  
**方法数**: 3

## 方法列表

### BuildGraph
```cpp
void BuildGraph();
```

### OkAction
```cpp
CATBoolean OkAction(void * data);
```

### Cancel
```cpp
CATBoolean Cancel(void * data);
```

## 依赖

- `CATMMUIStateCommand.h`

