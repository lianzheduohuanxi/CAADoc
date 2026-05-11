---
title: "CAATpiAccessGeometryCmd"
type: "interface"
module: "CAATPSInterfaces"
base: "CATStateCommand"
method_count: 2
visibility: "local"
verified: true
---

# CAATpiAccessGeometryCmd

**基类**: CATStateCommand  
**模块**: CAATPSInterfaces  
**可见性**: local  
**方法数**: 2

> -----------------------------------------------------------------------------

## 方法列表

### BuildGraph
```cpp
void BuildGraph();
```

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand * ipCmd,
                                      CATNotification * ipNotif);
```

## 依赖

- `CATStateCommand.h`

