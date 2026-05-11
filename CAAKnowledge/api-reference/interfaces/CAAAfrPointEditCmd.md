---
title: "CAAAfrPointEditCmd"
type: "interface"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 3
visibility: "local"
verified: true
---

# CAAAfrPointEditCmd

**基类**: CATCommand  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 3

> System Framework

## 方法列表

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand *iPublisher,CATNotification *iNotification);
```

### Desactivate
```cpp
CATStatusChangeRC Desactivate(CATCommand *iPublisher,CATNotification *iNotification);
```

### Activate
```cpp
CATStatusChangeRC Activate(CATCommand *iPublisher,CATNotification *iNotification);
```

## 依赖

- `CATCommand.h`

