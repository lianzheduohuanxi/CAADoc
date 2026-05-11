---
title: "CAAV5V6ExtMmrMultiMeasureStCmd"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATMmrStateCommand"
method_count: 3
visibility: "local"
verified: true
---

# CAAV5V6ExtMmrMultiMeasureStCmd

**基类**: CATMmrStateCommand  
**模块**: CAAV5V6MechanicalModeler  
**可见性**: local  
**方法数**: 3

> ==============================================

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

- `CATIAV5Level.h`
- `CATMmrStateCommand.h`
- `CATMMUIStateCommand.h`

