---
title: "CAAISysEllipse"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
visibility: "public"
verified: true
---

# CAAISysEllipse

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: public  
**方法数**: 6

> local Framework

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
HRESULT SetRadius(const float iXRadius, 
                               const float iYRadius);
```

### GetRadius
```cpp
HRESULT GetRadius(float & oXRadius, 
                               float & oYRadius) const;
```

### SetPlanar
```cpp
HRESULT SetPlanar(const CATMathVector & iNormal, 
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

