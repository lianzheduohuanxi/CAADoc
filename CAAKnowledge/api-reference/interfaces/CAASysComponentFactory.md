---
title: "CAASysComponentFactory"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAASysComponentFactory

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 2

> By implementing IClassFactory interface,

## 方法列表

### CreateInstance
```cpp
HRESULT __stdcall CreateInstance(IUnknown * iUnkOuter, const IID &iIid, void ** oObject);
```

### LockServer
```cpp
HRESULT __stdcall LockServer(int iLock);
```

## 依赖

- `CATBaseUnknown.h`

