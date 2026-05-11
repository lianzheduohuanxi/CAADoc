---
title: "CAAEAfrCollection"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 5
visibility: "local"
verified: true
---

# CAAEAfrCollection

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 5

> RemoveObject

## 方法列表

### GetNumberOfObjects
```cpp
HRESULT GetNumberOfObjects(int * oCount);
```

### GetObject
```cpp
HRESULT GetObject(int                  iRank,
                                  CATBaseUnknown    ** oObject);
```

### AddObject
```cpp
HRESULT AddObject(CATBaseUnknown     * iObject);
```

### RemoveObject
```cpp
HRESULT RemoveObject(CATBaseUnknown     * iObject);
```

### Empty
```cpp
HRESULT Empty();
```

## 依赖

- `CATBaseUnknown.h`
- `CATCollec.h`

