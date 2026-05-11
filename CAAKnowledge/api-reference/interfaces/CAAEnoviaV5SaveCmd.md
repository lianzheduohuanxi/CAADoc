---
title: "CAAEnoviaV5SaveCmd"
type: "interface"
module: "CAAProductStructureE5i"
base: "CATStateCommand"
method_count: 4
visibility: "local"
verified: true
---

# CAAEnoviaV5SaveCmd

**基类**: CATStateCommand  
**模块**: CAAProductStructureE5i  
**可见性**: local  
**方法数**: 4

## 方法列表

### BuildGraph
```cpp
void BuildGraph();
```

### Activate
```cpp
CATStatusChangeRC Activate(CATCommand *iFromClient, CATNotification *iEvtDat);
```

### Desactivate
```cpp
CATStatusChangeRC Desactivate(CATCommand *iFromClient, CATNotification *iEvtDat);
```

### Cancel
```cpp
CATStatusChangeRC Cancel(CATCommand *iFromClient, CATNotification *iEvtDat);
```

## 依赖

- `CATStateCommand.h`
- `CATBoolean.h`

