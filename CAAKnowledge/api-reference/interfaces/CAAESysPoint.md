---
title: "CAAESysPoint"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAESysPoint

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 2

> ===========================================================================

## 方法列表

### SetCoord
```cpp
HRESULT SetCoord(const float iX, const float iY, const float iZ);
```

### GetCoord
```cpp
HRESULT GetCoord(float     & oX, float     & oY, float     & oZ) const;
```

## 依赖

- `CATBaseUnknown.h`

