---
title: "CAASchAppSampleConnection"
type: "interface"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAASchAppSampleConnection

**基类**: CATBaseUnknown  
**模块**: CAASchPlatformModeler  
**可见性**: local  
**方法数**: 4

> -----------------------------------------------------------------------------

## 方法列表

### AppListConnectors
```cpp
HRESULT AppListConnectors(CATICStringList *iLCntrClassFilter,
    CATIUnknownList **oLCntrs);
```

### AppListConnectables
```cpp
HRESULT AppListConnectables(CATICStringList *iLCntbleClassFilter,
    CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrs);
```

### AppAddConnector
```cpp
HRESULT AppAddConnector(CATISchAppConnector *iCntrToAdd);
```

### AppRemoveConnector
```cpp
HRESULT AppRemoveConnector(CATISchAppConnector *iCntrToRemove);
```

## 依赖

- `CATUnicodeString.h`
- `CATBaseUnknown.h`
- `CATErrorDef.h`
- `CATBooleanDef.h`
- `CATIConnector.h`

