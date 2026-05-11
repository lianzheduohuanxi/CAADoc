---
title: "CAAESysPolyline"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAESysPolyline

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 4

> SetCloseStatus/SetCloseStatus

## 方法列表

### SetListPoint
```cpp
HRESULT SetListPoint(const int iPointCount, CATMathPoint  * iList);
```

### GetListPoint
```cpp
HRESULT GetListPoint(int * oPointCount    , CATMathPoint ** oList);
```

### SetCloseStatus
```cpp
HRESULT SetCloseStatus(const int iIsClosed);
```

### GetCloseStatus
```cpp
HRESULT GetCloseStatus(int * oIsClosed);
```

## 依赖

- `CATBaseUnknown.h`

