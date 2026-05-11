---
title: "CAAESysEllipse"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 6
visibility: "local"
verified: true
---

# CAAESysEllipse

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 6

> ===========================================================================

## 方法列表

### SetCenter
```cpp
HRESULT SetCenter(const CATMathPoint  & iCenter);
```

### GetCenter
```cpp
HRESULT GetCenter(CATMathPoint & oCenter) const;
```

### SetRadius
```cpp
HRESULT SetRadius(const float  iXRadius, const float iYRadius);
```

### GetRadius
```cpp
HRESULT GetRadius(float &oXRadius, float & oYRadius) const;
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
- `CATMathPoint.h`
- `CATMathVector.h`

