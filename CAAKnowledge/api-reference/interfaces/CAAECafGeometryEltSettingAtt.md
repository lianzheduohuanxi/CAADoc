---
title: "CAAECafGeometryEltSettingAtt"
type: "interface"
module: "CAACATIAApplicationFrm"
base: "CATBaseUnknown"
method_count: 10
visibility: "local"
verified: true
---

# CAAECafGeometryEltSettingAtt

**基类**: CATBaseUnknown  
**模块**: CAACATIAApplicationFrm  
**可见性**: local  
**方法数**: 10

> ===========================================================================

## 方法列表

### Initialize
```cpp
HRESULT Initialize();
```

### GetIdentifierVisibility
```cpp
HRESULT GetIdentifierVisibility(CATString & oIdVisibility);
```

### SetIdentifierVisibility
```cpp
HRESULT SetIdentifierVisibility(const CATString & iIdVisibility);
```

### GetInfoIdentifierVisibility
```cpp
HRESULT GetInfoIdentifierVisibility(CATSettingInfo * oInfo);
```

### GetMaxPointCurve
```cpp
HRESULT GetMaxPointCurve(int & oMaxPoint);
```

### SetMaxPointCurve
```cpp
HRESULT SetMaxPointCurve(const int iMaxPoint);
```

### GetInfoMaxPointCurve
```cpp
HRESULT GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray, int * oNbInfo);
```

### GetImplPointVisibility
```cpp
HRESULT GetImplPointVisibility(CATString & oImplPointVisibility);
```

### SetImplPointVisibility
```cpp
HRESULT SetImplPointVisibility(const CATString & iImplPointVisibility);
```

### GetInfoImplPointVisibility
```cpp
HRESULT GetInfoImplPointVisibility(CATSettingInfo * oInfo);
```

## 依赖

- `CATBaseUnknown.h`
- `CAAICafGeometryEltSettingAtt.h`

