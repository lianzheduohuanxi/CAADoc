---
title: "CAAISysCollection"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 5
verified: true
---

# CAAISysCollection

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**方法数**: 5

## 方法列表

### GetNumberOfObjects
```cpp
HRESULT GetNumberOfObjects(int * oCount);
```

### GetObject
```cpp
HRESULT GetObject(int iRank,
                                  CATBaseUnknown ** oObject);
```

### AddObject
```cpp
HRESULT AddObject(CATBaseUnknown * iObject);
```

### RemoveObject
```cpp
HRESULT RemoveObject(CATBaseUnknown * iObject);
```

### Empty
```cpp
HRESULT Empty();
```

