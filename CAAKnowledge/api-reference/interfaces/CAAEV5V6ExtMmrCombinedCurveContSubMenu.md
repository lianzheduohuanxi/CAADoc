---
title: "CAAEV5V6ExtMmrCombinedCurveContSubMenu"
type: "LocalClass"
module: "CAAV5V6MechanicalModeler"
base: "CATExtIContextualSubMenu"
method_count: 1
source_file: "CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCombinedCurveUI.m/LocalInterfaces/CAAEV5V6ExtMmrCombinedCurveContSubMenu.h"
---

# CAAEV5V6ExtMmrCombinedCurveContSubMenu

> Implementation of CATIContextualSubMenu for the Combined Curve You are adding commands which appears in the <CombinedCurve> object menu of the contextual menu. To do this, we create and arrange command starters that we associate with commands using command headers. These command headers are referred to using their identifiers. Here each command header is defined in the Part Document workshop Note : CAAEV5V6ExtMmrCombinedCurveContSubMenu is the same use case as CAAEMmrCombinedCurveContSubMenu. The objective is to have the same source delivered in V5 and V6. Any specific code to either V5 or V6 is flagged. ****************************************************************************** Explanation: The sub menu must be a data member to manage its life cycle. It can be identical or different from a call to another. . If it is identical, it can be created in the constructor, returned in the GetContextualSubMenu method, and deleted in the destructor. This is the case here . Otherwise, it must be created in the GetContextualSubMenu method. To correctly manage its life cycle, it must be deleted: . whenever calling GetContextualSubMenu . in the destructor when the class itself is deleted ****************************************************************************** Main Methods: Constructor            -> Builds the  sub menu Destructor             -> Deletes it GetContextualSubMenu() -> Returns it ******************************************************************************

**基类**: CATExtIContextualSubMenu | **模块**: CAAV5V6MechanicalModeler | **方法数**: 1

## 依赖

- `CATIAV5Level.h`
- `CATExtIContextualSubMenu.h`
- `CATBaseUnknown.h`

## 虚方法

### GetContextualSubMenu

```cpp
virtual CATCmdAccess * GetContextualSubMenu() ;
```


---

**源文件**: `CAAV5V6MechanicalModeler.edu/CAAV5V6ExtMmrCombinedCurveUI.m/LocalInterfaces/CAAEV5V6ExtMmrCombinedCurveContSubMenu.h`
