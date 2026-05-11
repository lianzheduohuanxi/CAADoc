---
title: "Optimizations Automation Objects"
category: "use-case"
module: "CAAScdKniTechArticles"
tags: []
source_file: "Doc/online/CAAScdKniTechArticles/CAAKniTocOptimizations.htm"
converted: "2026-05-11T17:31:52.003484"
---
# Optimizations Automation Objects

![](../CAAScrAutomationImages/images/relatns.gif)  
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/kwoptims.gif)[![Relation Object Diagram](../CAAScrAutomationImages/images/uparrow.gif)](CAAKniTocRelation.md)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/kwoptim.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/kwoptics.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/kwoptic.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)DistanceToSatisfaction![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/param.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)InParameters![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parlina.gif)![](../CAAScrAutomationImages/images/param.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)OutParameters![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parline.gif)![](../CAAScrAutomationImages/images/parlina.gif)![](../CAAScrAutomationImages/images/param.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/kwofpars.gif)  
![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/kwofpar.gif)  
![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchila.gif)![](../CAAScrAutomationImages/images/param.gif)[![Parameter Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)  
](CAAKniTocParameter.md)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)ObjectiveParameter![](../CAAScrAutomationImages/images/parlina.gif)![](../CAAScrAutomationImages/images/param.gif)  
---  
  
**Legend**

![](../CAAScrAutomationImages/images/yellbox.gif) Collection  
![](../CAAScrAutomationImages/images/purpbox.gif) Abstract object  
![](../CAAScrAutomationImages/images/bluebox.gif) Object

![right arrow](../CAAScrAutomationImages/images/rtarrow.gif) Click arrow to expand chart  
![](../CAAScrAutomationImages/images/uparrow.gif) Click arrow to return to previous chart

The _Optimizations_ collection is aggregated by the _Relations_ collection. Each _Optimization_ object aims to minimize or maximize the value of an objective parameter by modifying the values other parameters, called _free parameters,_ with respect to constraints. A constraint is a relationship between parameters equivalent to one of the following expressions:
    
    
    foo(param1, param2, ...) < constantValue
    
    foo(param1, param2, ...) = constantValue

Those constraints are seen as an aggregated collection of _OptimizationConstraint_ objects. An _OptimizationConstraint_ aggregates a list of input parameters and a list of output parameters and inherits the methods and properties of a _Check_ object, allowing to retrieve the equivalent relationship as a string, using the `Value` property.

Free parameters are represented by an aggregated collection of _FreeParameter_ objects pointing on the parameter itself. Its allows to specify a step and a range to monitor the variations of the parameter value.

* * *

_Copyright 1999-2013, Dassault Systmes. All rights reserved._
