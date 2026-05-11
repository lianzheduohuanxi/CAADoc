---
title: "CAAICafGeometryEltSettingAtt"
type: "interface"
module: "CAACATIAApplicationFrm"
base: "IUnknown"
method_count: 10
visibility: "protected"
verified: true
---

# CAAICafGeometryEltSettingAtt

**基类**: IUnknown  
**模块**: CAACATIAApplicationFrm  
**可见性**: protected  
**方法数**: 10

> Global Unique IDentifier defined in .cpp

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
HRESULT GetInfoMaxPointCurve(CATSettingInfo ** oInfoArray, int * iNbInfo);
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

- `CAACafCtrlToolsOptions.h`

