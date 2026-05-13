---
title: "CAAPriEMechanicalCCP"
type: "LocalClass"
module: "CAAPartInterfaces"
base: "CATBaseUnknown"
method_count: 4
source_file: "CAAPartInterfaces.edu/CAAPriCutCopyPaste.m/LocalInterfaces/CAAPriEMechanicalCCP.h"
---

# CAAPriEMechanicalCCP

> In this sample we have implemented the mandatory methods to allow User Pad to be pasted GiveMeYourFavoriteSpecifications method returns the sketch associated to the profile IsElementValidForPaste returns 1 if the path element represents a sketch CanBeDeleted returns 1 and indicates that the UserPad can be deleted CanBeCopied returns 1 and indicates that the UserPad can be copied

**基类**: CATBaseUnknown | **模块**: CAAPartInterfaces | **方法数**: 4

## 依赖

- `CATLISTV_CATISpecObject.h`

## 虚方法

### IsElementValidForPaste

```cpp
virtual int IsElementValidForPaste(CATPathElement* path) const ;
```

returns 1 if the element is valid

| 参数 | 类型 |
|------|------|
| path | `CATPathElement*` |


### GetAnchorPoint

```cpp
virtual CATMathPoint GetAnchorPoint() const ;
```

returns the anchor point of the sketch


### GetReferenceNormal

```cpp
virtual CATMathDirection GetReferenceNormal() const ;
```

returns the normal of the sketch


### CanBeCopied

```cpp
virtual int CanBeCopied() const ;
```

returns 1


---

**源文件**: `CAAPartInterfaces.edu/CAAPriCutCopyPaste.m/LocalInterfaces/CAAPriEMechanicalCCP.h`
