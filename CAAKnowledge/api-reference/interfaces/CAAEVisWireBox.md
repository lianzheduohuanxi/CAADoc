---
title: "CAAEVisWireBox"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAEVisWireBox

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**可见性**: local  
**方法数**: 4

> CAAIVisWireBox interface.

## 方法列表

### SetDimBox
```cpp
HRESULT SetDimBox(const float iDimBox);
```

### GetDimBox
```cpp
HRESULT GetDimBox(float * oDimBox);
```

### SetCenterBox
```cpp
HRESULT SetCenterBox(const CATMathPoint  & iCenter);
```

### GetCenterBox
```cpp
HRESULT GetCenterBox(CATMathPoint        & oCenter) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`

