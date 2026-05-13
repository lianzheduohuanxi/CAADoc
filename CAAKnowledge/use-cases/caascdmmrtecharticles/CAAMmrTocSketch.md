---
title: "Sketch Automation Objects"
category: "tech-article"
module: "CAAScdMmrTechArticles"
tags: "[]"
source_file: "Doc/online/CAAScdMmrTechArticles/CAAMmrTocSketch.htm"
converted: "2026-05-11T17:31:51.158125"
---
# Sketch Automation Objects

![](../CAAScrAutomationImages/images/sketch.gif)![Multiple Object Diagrams](../CAAScrAutomationImages/images/uparrow.gif)
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/fact2d.gif)
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/geoelts.gif)
![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/geoelt.gif)[![GeometricElement Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](CAAMmrTocGeometricElement.md)
![](../CAAScrAutomationImages/images/parmult.gif)[![](../CAAScrAutomationImages/images/constrs.gif)](CAAMmrObjConstraints.md)
![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/constrnt.gif)](CAAMmrObjConstraints.md)
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/line2d.gif)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/axis2d.gif)
**Legend** ![](../CAAScrAutomationImages/images/yellbox.gif) Collection
![](../CAAScrAutomationImages/images/purpbox.gif) Abstract object
![](../CAAScrAutomationImages/images/bluebox.gif) Object ![right arrow](../CAAScrAutomationImages/images/rtarrow.gif) Click arrow to expand chart
![](../CAAScrAutomationImages/images/uparrow.gif) Click arrow to return to previous chart The **Sketch** object contains 2D geometric elements that define the sketch. These elements are created using the **Factory2D** object and contained in a **GeometricElements** collection aggregrated by the sketch. To create 2D geometric elements, you need first to "open the sketch edition" using the **OpenEdition** method that returns the **Factory2D** object which supplies the appropriate methods to create 2D geometric elements. Once you have finished creating 2D geometric elements, "close the sketch edition" using the **CloseEdition** method. These two methods correspond to the commands that let you interactively enter ![](images/I_SketcherP2.gif) and leave ![](images/I_CloseP2.gif) the sketch. You can set constraints to the 2D geometric elements using the methods supplied by the **Constraints** collection aggregated to the sketch.

* * *

_Copyright © 1999-2013, Dassault Systèmes. All rights reserved._
