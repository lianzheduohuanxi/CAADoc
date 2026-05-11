---
title: "CAAVisBaseDocument"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 6
visibility: "local"
verified: true
---

# CAAVisBaseDocument

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**可见性**: local  
**方法数**: 6

> Visualization Framework

## 方法列表

### GetView
```cpp
CAAVisBaseView * GetView();
```

### InsertModel
```cpp
void InsertModel(const char *iCGRFileName);
```

### AddRepToViewer
```cpp
void AddRepToViewer();
```

### CreateModel
```cpp
void CreateModel();
```

### DeleteModel
```cpp
void DeleteModel();
```

### CreateDocView
```cpp
void CreateDocView(CATDialog *iDialogParent, const char *iDocViewName);
```

## 依赖

- `CATBaseUnknown.h`

