---
title: "CAAISysCuboid"
type: "interface"
module: "CAASystem"
base: "CATBaseUnknown"
method_count: 4
verified: true
---

# CAAISysCuboid

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

### SetVectors
```cpp
HRESULT SetVectors(const CATMathVector & iV1,
		                 const CATMathVector & iV2,
						 const CATMathVector & iV3);
```

### GetVectors
```cpp
HRESULT GetVectors(CATMathVector & oV1,
		                 CATMathVector & oV2,
						 CATMathVector & oV3) const;
```

