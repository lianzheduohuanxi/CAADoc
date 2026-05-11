---
title: "CAAVisManagerWindow"
type: "interface"
module: "CAAVisualization"
base: "CATDlgDialog"
method_count: 4
visibility: "local"
verified: true
---

# CAAVisManagerWindow

**基类**: CATDlgDialog  
**模块**: CAAVisualization  
**可见性**: local  
**方法数**: 4

## 方法列表

### DuplicateWindow
```cpp
CAAVisManagerWindow * DuplicateWindow();
```

### GetEditor
```cpp
CAAVisManagerEditor * GetEditor();
```

### Build
```cpp
void Build();
```

### DeleteWindow
```cpp
void DeleteWindow();
```

## 依赖

- `CATDlgDialog.h`
- `CATString.h`

