---
title: "CAAESysLine"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAESysLine

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 4

> ===========================================================================

## 方法列表

### SetStartPoint
```cpp
HRESULT SetStartPoint(const CATMathPoint  & iStartPoint);
```

### GetStartPoint
```cpp
HRESULT GetStartPoint(CATMathPoint  & oStartPoint) const;
```

### SetEndPoint
```cpp
HRESULT SetEndPoint(const CATMathPoint  & iEndPoint);
```

### GetEndPoint
```cpp
HRESULT GetEndPoint(CATMathPoint  & oEndPoint) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`

