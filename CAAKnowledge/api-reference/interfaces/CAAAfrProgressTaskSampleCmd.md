---
title: "CAAAfrProgressTaskSampleCmd"
type: "interface"
module: "CAAApplicationFrame"
base: "CATDlgDialog"
method_count: 3
visibility: "local"
verified: true
---

# CAAAfrProgressTaskSampleCmd

**基类**: CATDlgDialog  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 3

> Dialog Framework

## 方法列表

### PerformTask
```cpp
HRESULT PerformTask(CATIProgressTaskUI  * iUI, void * iUserData);
```

### GetCatalogName
```cpp
HRESULT GetCatalogName(CATString           * oCatalogName);
```

### GetIcon
```cpp
HRESULT GetIcon(CATString           * oIcon);
```

## 依赖

- `CATDlgDialog.h`

