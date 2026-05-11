---
title: "CAAESysPlane"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAESysPlane

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**可见性**: local  
**方法数**: 4

> ===========================================================================

## 方法列表

### SetOrigin
```cpp
HRESULT SetOrigin(const CATMathPoint & iOrigin);
```

### GetOrigin
```cpp
HRESULT GetOrigin(CATMathPoint & oOrigin);
```

### SetPlane
```cpp
HRESULT SetPlane(const CATMathVector & iU ,
	                        const CATMathVector & iV);
```

### GetPlane
```cpp
HRESULT GetPlane(CATMathVector & oU ,
	                        CATMathVector & oV);
```

## 依赖

- `CATBaseUnknown.h`
- `CATMathPoint.h`
- `CATMathVector.h`

