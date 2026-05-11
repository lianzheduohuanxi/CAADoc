---
title: "CAAIPstINFRoot"
type: "interface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
visibility: "protected"
verified: true
---

# CAAIPstINFRoot

**基类**: CATBaseUnknown  
**模块**: CAAProductStructure  
**可见性**: protected  
**方法数**: 2

> ObjectSpecsModeler Framework

## 方法列表

### AddChild
```cpp
HRESULT AddChild(CATISpecObject *ipiFeature);
```

### GetChildren
```cpp
HRESULT GetChildren(CATListValCATBaseUnknown_var **opList);
```

## 依赖

- `CAAPstINFInterfaces.h`
- `CATLISTV_CATBaseUnknown.h`
- `CATBaseUnknown.h`
- `CATISpecObject.h`

