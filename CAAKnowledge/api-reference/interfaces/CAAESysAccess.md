---
title: "CAAESysAccess"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAESysAccess

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 2

> SetContainer: Sets the container

## 方法列表

### SetContainer
```cpp
HRESULT SetContainer(CATBaseUnknown * iContainer);
```

### GetContainer
```cpp
HRESULT GetContainer(CATBaseUnknown  ** oContainer);
```

## 依赖

- `CATBaseUnknown.h`

