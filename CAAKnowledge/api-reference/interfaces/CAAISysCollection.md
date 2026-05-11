---
title: "CAAISysCollection"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 5
visibility: "public"
verified: true
---

# CAAISysCollection

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 5

> System Framework

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

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

