---
title: "CAAAfrPlaneEditCmd"
type: "interface"
module: "CAAApplicationFrame"
base: "CATDlgDialog"
method_count: 3
visibility: "local"
verified: true
---

# CAAAfrPlaneEditCmd

**基类**: CATDlgDialog  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 3

> ===========================================================================

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

- `CATDlgDialog.h`

