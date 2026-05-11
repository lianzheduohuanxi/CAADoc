---
title: "Prism Object"
category: "use-case"
module: "CAAScdPriTechArticles"
tags: []
source_file: "Doc/online/CAAScdPriTechArticles/CAAPriObjPrism.htm"
converted: "2026-05-11T17:31:51.237447"
---
# Prism Object

See Also | UseCases | Properties | Methods  
---|---|---|---  
  
 

![](../CAAScrAutomationImages/images/shape.gif)  
![](../CAAScrAutomationImages/images/parderiv.gif)![](../CAAScrAutomationImages/images/sketshap.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parderil.gif)![](../CAAScrAutomationImages/images/parchila.gif)![](../CAAScrAutomationImages/images/sketch.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/prism.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parderil.gif)![](../CAAScrAutomationImages/images/parmult.gif)FirstLimit![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/limit.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)SecondLimit ![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/limit.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/pad.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/pocket.gif)  
---  
  
Represent a prism.

 The **Prism** object provides to the **Pad** or to the **Pocket** the extrusion direction set or retrieved thanks to the SetDirection or GetDirection methods. This extrusion direction can be normal to the sketch plane or not. This is expressed using the CatPrismExtrusionDirection enumeration in the DirectionType property. The extrusion direction has an orientation expressed using the CatPrismOrientation enumeration in the DirectionOrientation property. The **Pad** or the **Pocket** object can be symmetric to the skecth plane. This is stored in the IsSymmetric property. Finally, the pad or the pocket has two limits stored in the FirstLimit and SecondLimit properties as Limit objects. The **Pad** and the **Pocket** objects do not hold specific properties or methods.  
---|---  
  
* * *

_Copyright © 1999-2013, Dassault Systèmes. All rights reserved._
