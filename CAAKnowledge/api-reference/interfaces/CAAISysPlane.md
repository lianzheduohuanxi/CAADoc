---
title: "CAAISysPlane"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
verified: true
---

# CAAISysPlane

**基类**: CATBaseUnknown  
**模块**: CAASystem  
**方法数**: 4

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

