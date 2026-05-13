---
title: "Windows Object"
category: "tech-article"
module: "CAAScdInfTechArticles"
tags: "[]"
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfObjWindows.htm"
converted: "2026-05-11T17:31:52.432118"
---
# Windows Object

 See Also | Use Cases | Properties | Methods
 ---|---|---|---

 ![](../CAAScrAutomationImages/images/windows.gif)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/window.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parderiv.gif)![](../CAAScrAutomationImages/images/specwin.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/specview.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/viewers.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/pagestup.gif)
 ---

 **_A collection of all the Window objects currently managed by the application._**

 The **Windows** collection gathers **Window** objects which make the link with the windowing system and display documents in a viewable form, mainly in 3D or 2D modes, or as a specification tree in graph or tree mode. Windows in a collection can be arranged in the frame. A **Viewers** collection enables the window to display the application data in the appropriate modes using viewers. A **SpecsAndGeomWindow** object features altogether a 2D or a 3D viewer and a specification tree viewer. A window can be activated, that is becomes the active one, using the **Activate** method. This implies that the document displayed is this window is also activated if it was not, and that subsequent interactions will affect it until another window is activated instead. The **Viewers** property returns the aggregated **Viewers** collection, and the **ActiveViewer** property returns the active viewer in the window.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
