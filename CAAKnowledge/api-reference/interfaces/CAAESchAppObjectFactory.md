---
title: "CAAESchAppObjectFactory"
type: "interface"
module: "CAASchPlatformModeler"
base: "CATEASchAppObjectFactory2"
method_count: 2
visibility: "local"
verified: true
---

# CAAESchAppObjectFactory

**基类**: CATEASchAppObjectFactory2  
**模块**: CAASchPlatformModeler  
**可见性**: local  
**方法数**: 2

> =============================================================================

## 方法列表

### AppCreateCompRef
```cpp
HRESULT AppCreateCompRef(const char *iAppCompClassType,
    const CATDocument *iDoc, IUnknown **oAppComp);
```

### AppCreateRoute2
```cpp
HRESULT AppCreateRoute2(const char *iAppRouteClassType,
     const CATDocument *iDoc, const CATUnicodeString *iLogLineID, 
     IUnknown **oAppRoute);
```

## 依赖

- `CATEASchAppObjectFactory2.h`

