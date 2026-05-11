---
title: "CAAIVisModelSphere"
type: "interface"
module: "CAAVisualization"
base: "CATBaseUnknown"
method_count: 4
visibility: "protected"
verified: true
---

# CAAIVisModelSphere

**基类**: CATBaseUnknown  
**模块**: CAAVisualization  
**可见性**: protected  
**方法数**: 4

> Mathematics FrameWork

## 方法列表

### SetCenter
```cpp
HRESULT SetCenter(const CATMathPointf & iCenter);
```

### GetCenter
```cpp
HRESULT GetCenter(CATMathPointf & oCenter) const;
```

### SetRadius
```cpp
HRESULT SetRadius(const float iRadius);
```

### GetRadius
```cpp
HRESULT GetRadius(float & oRadius) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CAAVisManagerInt.h`

