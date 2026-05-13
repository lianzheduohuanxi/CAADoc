---
title: "CAASysRevolSurface"
type: "LocalClass"
module: "CAASystem"
base: "CAASysSurface"
method_count: 0
source_file: "CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAASysRevolSurface.h"
---

# CAASysRevolSurface

> Implementation class of the CAASysRevolSurface component. This class must C++ derives from the implementation class of the component CAASysSurface (ie the CAASysSurface class ). This class declares too, with the macros CATDeclareClass (in the header file) and CATImplementClass (in the cpp file), that's the component named, CAASysRevolSurface, Object Modeler (OM) derives from the CAASysSurface component. |                     | | CAASysSurface       |-o CAAISysSurfaceProperties |                     | | impl                |-o CAAISysSurfaceArea +-----------------+- |                 | | C++ Derivation  | OM Derivation | of the          | of the component | implementation  | |                 | |                 | |                 | ^-----------------^--- | impl                  | |                       |-o CAAISysRevolAxis |                       | |  CAASysRevolSurface   |-o CAAISysSurfaceArea |                       |

**基类**: CAASysSurface | **模块**: CAASystem | **方法数**: 0

## 依赖

- `CAASysSurface.h`

---

**源文件**: `CAASystem.edu/CAASysDerivationOM.m/LocalInterfaces/CAASysRevolSurface.h`
