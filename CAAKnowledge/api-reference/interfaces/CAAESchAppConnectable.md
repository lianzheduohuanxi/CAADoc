---
title: "CAAESchAppConnectable"
type: "interface"
module: "CAASchPlatformModeler"
base: "CATBaseUnknown"
method_count: 7
visibility: "local"
verified: true
---

# CAAESchAppConnectable

**基类**: CATBaseUnknown  
**模块**: CAASchPlatformModeler  
**可见性**: local  
**方法数**: 7

## 方法列表

### AppListConnectors
```cpp
HRESULT AppListConnectors(CATICStringList *iLCntrClassFilter,
    CATIUnknownList **oLCntrs);
```

### AppListConnectables
```cpp
HRESULT AppListConnectables(CATICStringList *iLCntbleClassFilter,
    CATIUnknownList **oLCntbles, CATIUnknownList **oLCntrsOnThisObj,
    CATIUnknownList **oLCntrsOnConnected);
```

### AppAddConnector
```cpp
HRESULT AppAddConnector(const char *iClassType,
    CATISchAppConnector **oNewAppCntr);
```

### AppRemoveConnector
```cpp
HRESULT AppRemoveConnector(CATISchAppConnector *iCntrToRemove);
```

### AppListValidCntrTypes
```cpp
HRESULT AppListValidCntrTypes(CATICStringList **oLValidCntrTypes);
```

### AppGetReferenceName
```cpp
HRESULT AppGetReferenceName(char **oReferenceName);
```

### AppSetReferenceName
```cpp
HRESULT AppSetReferenceName(const char *iReferenceName);
```

## 依赖

- `CATBaseUnknown.h`
- `CATBooleanDef.h`

