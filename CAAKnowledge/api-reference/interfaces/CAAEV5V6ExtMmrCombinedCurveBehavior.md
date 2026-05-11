---
title: "CAAEV5V6ExtMmrCombinedCurveBehavior"
type: "interface"
module: "CAAV5V6MechanicalModeler"
base: "CATIFmFeatureBehaviorCustomization"
method_count: 9
visibility: "local"
verified: true
---

# CAAEV5V6ExtMmrCombinedCurveBehavior

**基类**: CATIFmFeatureBehaviorCustomization  
**模块**: CAAV5V6MechanicalModeler  
**可见性**: local  
**方法数**: 9

> This is the implementation of the CATIFmFeatureBehaviorCustomization interface for the

## 方法列表

### CanBeRemoved
```cpp
HRESULT CanBeRemoved(CATBoolean & oDeletable) const;
```

### BeforeRemove
```cpp
HRESULT BeforeRemove();
```

### Build
```cpp
HRESULT Build();
```

### CcpRegisterAdditionalObjectsForCopy
```cpp
HRESULT CcpRegisterAdditionalObjectsForCopy(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const;
```

### CcpUpdate
```cpp
HRESULT CcpUpdate(const CATFmCCPContext & iContext);
```

### CcpUpdate
```cpp
HRESULT CcpUpdate(CATFmCCPContext & iContext);
```

### CcpPaste
```cpp
HRESULT CcpPaste(const CATFmCCPContext & iContext);
```

### CcpPaste
```cpp
HRESULT CcpPaste(CATFmCCPContext & iContext);
```

### CcpRegisterAdditionalObjectsForRemove
```cpp
HRESULT CcpRegisterAdditionalObjectsForRemove(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const;
```

## 依赖

- `CATIFmFeatureBehaviorCustomization.h`

