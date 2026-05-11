---
title: "CAAAfrQueryExploreCmd"
type: "interface"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 3
visibility: "local"
verified: true
---

# CAAAfrQueryExploreCmd

**基类**: CATCommand  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 3

> Activates

## 方法列表

### Activate
```cpp
CATStatusChangeRC Activate(CATCommand      * iFromClient,
                                       CATNotification * iEvtData);
```

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand        * iFromClient,
                                     CATNotification   * iEvtData);
```

### Compute
```cpp
void Compute();
```

## 依赖

- `CATCommand.h`

