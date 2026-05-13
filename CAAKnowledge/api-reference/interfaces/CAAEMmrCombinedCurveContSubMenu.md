---
title: "CAAEMmrCombinedCurveContSubMenu"
type: "LocalClass"
module: "CAAMechanicalModeler"
base: "CATBaseUnknown"
method_count: 1
source_file: "CAAMechanicalModeler.edu/CAAMmrCombinedCurveUI.m/LocalInterfaces/CAAEMmrCombinedCurveContSubMenu.h"
---

# CAAEMmrCombinedCurveContSubMenu

> Implementation of CATIContextualSubMenu for the Combined Curve You are adding commands which appears in the <CombinedCurve> object menu of the contextual menu. To do this, we create and arrange command starters that we associate with commands using command headers. These command headers are referred to using their identifiers. Here each command header is defined in the Part Document workshop ****************************************************************************** Explanation: The sub menu must be a data member to manage its life cycle. It can be identical or different from a call to another. . If it is identical, it can be created in the constructor, returned in the GetContextualSubMenu method, and deleted in the destructor. This is the case here . Otherwise, it must be created in the GetContextualSubMenu method. To correctly manage its life cycle, it must be deleted: . whenever calling GetContextualSubMenu . in the destructor when the class itself is deleted ****************************************************************************** Main Methods: Constructor            -> Builds the  sub menu Destructor             -> Deletes it GetContextualSubMenu() -> Returns it ******************************************************************************

**基类**: CATBaseUnknown | **模块**: CAAMechanicalModeler | **方法数**: 1

## 依赖

- `CATBaseUnknown.h`

## 虚方法

### GetContextualSubMenu

```cpp
virtual CATCmdAccess * GetContextualSubMenu() ;
```


---

**源文件**: `CAAMechanicalModeler.edu/CAAMmrCombinedCurveUI.m/LocalInterfaces/CAAEMmrCombinedCurveContSubMenu.h`
