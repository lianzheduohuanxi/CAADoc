---
title: "CAAISysPlane"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
visibility: "public"
verified: true
---

# CAAISysPlane

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 4

> Local Framework

## 方法列表

### SetOrigin
```cpp
HRESULT SetOrigin(const CATMathPoint & iOrigin);
```

### GetOrigin
```cpp
HRESULT GetOrigin(CATMathPoint & oOrigin) const;
```

### SetPlane
```cpp
HRESULT SetPlane(const CATMathVector & iU,
		                 const CATMathVector & iV);
```

### GetPlane
```cpp
HRESULT GetPlane(CATMathVector & iU,
		                 CATMathVector & iV) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

