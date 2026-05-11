---
title: "CAAPstProductIconInit"
type: "interface"
module: "CAAProductStructure"
base: "CATBaseUnknown"
method_count: 2
visibility: "local"
verified: true
---

# CAAPstProductIconInit

**基类**: CATBaseUnknown  
**模块**: CAAProductStructure  
**可见性**: local  
**方法数**: 2

> CAAPstProductIconInit: CATInit implementation for container

## 方法列表

### Init
```cpp
void Init(CATBoolean iDestroyExistingData);
```

### GetRootContainer
```cpp
CATBaseUnknown* GetRootContainer(const CATIdent iInterfaceID);
```

## 依赖

- `CATBaseUnknown.h`
- `CATBoolean.h`

