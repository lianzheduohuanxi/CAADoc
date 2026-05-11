---
title: "CAAPstINFEditCmdPoint"
type: "interface"
module: "CAAProductStructure"
base: "CATCommand"
method_count: 3
visibility: "local"
verified: true
---

# CAAPstINFEditCmdPoint

**基类**: CATCommand  
**模块**: CAAProductStructure  
**可见性**: local  
**方法数**: 3

> ===========================================================================

## 方法列表

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand *ipPublisher,CATNotification *ipNotification);
```

### Desactivate
```cpp
CATStatusChangeRC Desactivate(CATCommand *ipPublisher,CATNotification *ipNotification);
```

### Activate
```cpp
CATStatusChangeRC Activate(CATCommand *ipPublisher,CATNotification *ipNotification);
```

## 依赖

- `CATCommand.h`

