---
title: "CAAECafContextualMenuEllipse"
type: "LocalClass"
module: "CAACATIAApplicationFrm"
base: "CATExtIContextualMenu"
method_count: 0
source_file: "CAACATIAApplicationFrm.edu/CAACafContextualMenu.m/LocalInterfaces/CAAECafContextualMenuEllipse.h"
---

# CAAECafContextualMenuEllipse

> Implementation of the CATIContextualMenu interface for the CAASysEllipse object. ****************************************************************************** Usage: Launch a CATIA V5. Create a new CAAGeometry document. Create an ellipse Click the right button: the contextual menu appears. ****************************************************************************** Explanation for contextual menu In general the contextual menu dedicated to your object completes the default contextual menu. This default menu is the same that the default menu of the UI active object. If you call CATExtIContextualMenu::GetContextualMenu, you get the default contextual menu and you can complete it. So to do that, in the constructor of the data extension of your object, you retrieve the contextual menu of CATExtIContextualMenu and you create several items, that you chain to it. The life cycle of the menu is managed by the  CATExtIContextualMenu class. The contextual menu dedicaded to the UI active object is defined in the CAAApplicationFrame.edu/CAAAfrGeoDocument/src/CAAEAfrUIActiveRootObj.cpp ******************************************************************************

**基类**: CATExtIContextualMenu | **模块**: CAACATIAApplicationFrm | **方法数**: 0

## 依赖

- `CATExtIContextualMenu.h`

---

**源文件**: `CAACATIAApplicationFrm.edu/CAACafContextualMenu.m/LocalInterfaces/CAAECafContextualMenuEllipse.h`
