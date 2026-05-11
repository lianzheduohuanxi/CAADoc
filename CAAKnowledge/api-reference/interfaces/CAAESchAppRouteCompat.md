---
title: "CAAESchAppRouteCompat"
type: "interface"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 3
visibility: "local"
verified: true
---

# CAAESchAppRouteCompat

**基类**: CATBaseUnknown  
**模块**: CAASchPlatformModeler  
**可见性**: local  
**方法数**: 3

## 方法列表

### AppIsTargetOKForRoute
```cpp
HRESULT AppIsTargetOKForRoute(const char *iRouteCntrClassType,
    CATIUnknownList **oLOKCntrs, boolean *oBYes);
```

### AppIsTargetOKForPlace
```cpp
HRESULT AppIsTargetOKForPlace(CATIUnknownList *iLCompSourceCntrs,
    CATIUnknownList **oLTargetCntrs, boolean *oBYes);
```

### AppIsTargetOKForInsert
```cpp
HRESULT AppIsTargetOKForInsert(CATIUnknownList *iLCompSourceCntrs,
    CATIUnknownList **oLSourceCntrs, boolean *oBYes);
```

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`

