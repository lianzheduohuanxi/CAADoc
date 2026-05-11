---
title: "CAAIPstINFLine"
type: "interface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
visibility: "protected"
verified: true
---

# CAAIPstINFLine

**基类**: CATBaseUnknown  
**模块**: CAAProductStructure  
**可见性**: protected  
**方法数**: 2

> ObjectSpecsModeler Framework

## 方法列表

### GetPoint
```cpp
HRESULT GetPoint(int iNum, CATISpecObject **opiPoint);
```

### SetPoint
```cpp
HRESULT SetPoint(int iNum, CATISpecObject *ipiPoint);
```

## 依赖

- `CAAPstINFInterfaces.h`
- `CATBaseUnknown.h`
- `CATISpecObject.h`

