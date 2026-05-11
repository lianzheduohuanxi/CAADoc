---
title: "CAAMcaUdfLoftEditCreateCmd"
type: "interface"
module: "CAAMechanicalCommands"
base: "CATPrtPanelStateCmd"
method_count: 8
visibility: "local"
verified: true
---

# CAAMcaUdfLoftEditCreateCmd

**基类**: CATPrtPanelStateCmd  
**模块**: CAAMechanicalCommands  
**可见性**: local  
**方法数**: 8

> MechanicalModelerUI framework

## 方法列表

### BuildGraph
```cpp
void BuildGraph();
```

### GiveMyPanel
```cpp
CATDlgDialog* GiveMyPanel();
```

### CheckInput
```cpp
CATBoolean CheckInput(void * iUsefuldata);
```

### OkAction
```cpp
CATBoolean OkAction(void * iUsefuldata);
```

### CancelAction
```cpp
CATBoolean CancelAction(void * iUsefuldata);
```

### PreviewAction
```cpp
CATBoolean PreviewAction(void * iUsefuldata);
```

### SelectPoint
```cpp
CATBoolean SelectPoint(void * iUsefuldata);
```

### CloseErrorDialogBox
```cpp
CATBoolean CloseErrorDialogBox(void * iUsefuldata);
```

## 依赖

- `CATPrtPanelStateCmd.h`

