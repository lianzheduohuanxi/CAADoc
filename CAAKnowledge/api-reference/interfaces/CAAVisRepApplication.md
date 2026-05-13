---
title: "CAAVisRepApplication"
type: "LocalClass"
module: "CAAVisualization"
base: "CATInteractiveApplication"
method_count: 2
source_file: "CAAVisualization.edu/CAAVisRep.m/LocalInterfaces/CAAVisRepApplication.h"
---

# CAAVisRepApplication

> This sample illustrates: I- Management of Graphic Representation (Rep) Creation of CAT3DBagRep (Bag) Creation of CAT3DCustomRep which can contain: CAT3DLineGP CAT3DMarkerGP CAT3DPlanarFaceGP Adding a Rep in a Bag to create a tree II- Management of Graphic Attributes Color , Thickness, Line Type show,no show Inheritance type : Volum, Skin or Edge How to launch : Type : CAAVisRep Inheritance: CATInteractiveApplication (Dialog Framework) CATApplication (System Framework)

**基类**: CATInteractiveApplication | **模块**: CAAVisualization | **方法数**: 2

## 依赖

- `CATInteractiveApplication.h`

## 虚方法

### BeginApplication

```cpp
virtual void BeginApplication() ;
```


### EndApplication

```cpp
virtual int EndApplication() ;
```

Returns the application return code.


---

**源文件**: `CAAVisualization.edu/CAAVisRep.m/LocalInterfaces/CAAVisRepApplication.h`
