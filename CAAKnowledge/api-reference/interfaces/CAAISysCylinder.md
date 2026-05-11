---
title: "CAAISysCylinder"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
visibility: "public"
verified: true
---

# CAAISysCylinder

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 6

> Mathematics Framework

## 方法列表

### SetRadius
```cpp
HRESULT SetRadius(const float iRadius);
```

### GetRadius
```cpp
HRESULT GetRadius(float & oRadius) const;
```

### SetBasePoint
```cpp
HRESULT SetBasePoint(const CATMathPoint & iBasePoint);
```

### GetBasePoint
```cpp
HRESULT GetBasePoint(CATMathPoint & oBasePoint) const;
```

### SetTopPoint
```cpp
HRESULT SetTopPoint(const CATMathPoint & iTopPoint);
```

### GetTopPoint
```cpp
HRESULT GetTopPoint(CATMathPoint & oTopPoint) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

