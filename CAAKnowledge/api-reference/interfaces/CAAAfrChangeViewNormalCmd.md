---
title: "CAAAfrChangeViewNormalCmd"
type: "interface"
module: "CAAApplicationFrame"
base: "CATCommand"
method_count: 2
visibility: "local"
verified: true
---

# CAAAfrChangeViewNormalCmd

**基类**: CATCommand  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 2

> Main Method:

## 方法列表

### Activate
```cpp
CATStatusChangeRC Activate(CATCommand       * iFromClient,
                                      CATNotification * iEvtData);
```

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand         * iFromClient,
                                    CATNotification * iEvtData);
```

## 依赖

- `CATCommand.h`

