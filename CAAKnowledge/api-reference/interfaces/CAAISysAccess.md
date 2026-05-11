---
title: "CAAISysAccess"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "public"
verified: true
---

# CAAISysAccess

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 2

> System Framework

## 方法列表

### SetContainer
```cpp
HRESULT SetContainer(CATBaseUnknown * iContainer);
```

### GetContainer
```cpp
HRESULT GetContainer(CATBaseUnknown ** oContainer);
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

