---
title: "CAAEMmrCatalogInstantiationForCombCrv"
type: "interface"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
visibility: "local"
verified: true
---

# CAAEMmrCatalogInstantiationForCombCrv

**基类**: CATBaseUnknown  
**模块**: CAAMechanicalModeler  
**可见性**: local  
**方法数**: 1

## 方法列表

### RunInstantiationCmd
```cpp
HRESULT RunInstantiationCmd(const CATICatalogLink    * ipCatalogLink,
                                       const CATICatalogBrowser * ipBrowser,
                                       int iInstantiateMode,
                                       int iRepeatMode,
                                       int & oNotDone);
```

## 依赖

- `CATBaseUnknown.h`

