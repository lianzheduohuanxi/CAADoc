---
title: "CAAISysPolyline"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
verified: true
---

# CAAISysPolyline

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**方法数**: 4

## 方法列表

### SetListPoint
```cpp
HRESULT SetListPoint(const int iPointCount, CATMathPoint *  iList);
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

