---
title: "CAAISysLine"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
verified: true
---

# CAAISysLine

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**方法数**: 4

## 方法列表

### SetStartPoint
```cpp
HRESULT SetStartPoint(const CATMathPoint & iStartPoint);
```

### SetEndPoint
```cpp
HRESULT SetEndPoint(const CATMathPoint & iEndPoint);
```

### GetStartPoint
```cpp
HRESULT GetStartPoint(CATMathPoint & oStartPoint) const;
```

### GetEndPoint
```cpp
HRESULT GetEndPoint(CATMathPoint & oEndPoint) const;
```

