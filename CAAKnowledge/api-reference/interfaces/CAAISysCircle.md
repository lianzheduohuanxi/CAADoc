---
title: "CAAISysCircle"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
visibility: "public"
verified: true
---

# CAAISysCircle

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 6

> Mathematics framework

## 方法列表

### SetCenter
```cpp
HRESULT SetCenter(const CATMathPoint & iCenter);
```

### GetCenter
```cpp
HRESULT GetCenter(CATMathPoint & oCenter) const;
```

### SetRadius
```cpp
HRESULT SetRadius(const float iRadius);
```

### GetRadius
```cpp
HRESULT GetRadius(float & oRadius) const;
```

### SetPlanar
```cpp
HRESULT SetPlanar(const CATMathVector & iNormal , 
		                           const CATMathVector & iAxis);
```

### GetPlanar
```cpp
HRESULT GetPlanar(CATMathVector & oNormal ,
		                           CATMathVector & oAxis) const;
```

## 依赖

- `CATBaseUnknown.h`
- `CAASysGeoModelInf.h`

