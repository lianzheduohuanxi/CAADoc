---
title: "CAAEAfrCommandHeaderRepForEltCount"
type: "interface"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 3
visibility: "local"
verified: true
---

# CAAEAfrCommandHeaderRepForEltCount

**基类**: CATBaseUnknown  
**模块**: CAAApplicationFrame  
**可见性**: local  
**方法数**: 3

> ===========================================================================

## 方法列表

### CreateToolbarRep
```cpp
HRESULT CreateToolbarRep(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep);
```

### CreateMenuRep
```cpp
HRESULT CreateMenuRep(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep);
```

### CreateCtxMenuRep
```cpp
HRESULT CreateCtxMenuRep(const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep);
```

## 依赖

- `CATBaseUnknown.h`

