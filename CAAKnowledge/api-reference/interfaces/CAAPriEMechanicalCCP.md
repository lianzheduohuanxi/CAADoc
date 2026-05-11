---
title: "CAAPriEMechanicalCCP"
type: "interface"
module: "CAAPartInterfaces"
base: "CATBaseUnknown"
method_count: 4
visibility: "local"
verified: true
---

# CAAPriEMechanicalCCP

**基类**: CATBaseUnknown  
**模块**: CAAPartInterfaces  
**可见性**: local  
**方法数**: 4

> ==========================================================================

## 方法列表

### IsElementValidForPaste
```cpp
int IsElementValidForPaste(CATPathElement* path) const;
```

### GetAnchorPoint
```cpp
CATMathPoint GetAnchorPoint() const;
```

### GetReferenceNormal
```cpp
CATMathDirection GetReferenceNormal() const;
```

### CanBeCopied
```cpp
int CanBeCopied() const;
```

## 依赖

- `CATLISTV_CATISpecObject.h`

