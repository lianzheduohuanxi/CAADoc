---
title: "CAAEVisModelSphere"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAEVisModelSphere

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**可见性**: local  
**方法数**: 4

> CAAIVisModelSphere interface.

## 方法列表

### GetCenter
```cpp
HRESULT GetCenter(CATMathPointf & iCenter) const;
```

### SetCenter
```cpp
HRESULT SetCenter(const CATMathPointf & oCenter);
```

### GetRadius
```cpp
HRESULT GetRadius(float & oRadius) const;
```

### SetRadius
```cpp
HRESULT SetRadius(const float iRadius);
```

## 依赖

- `CATBaseUnknown.h`
- `CATMathPointf.h`

