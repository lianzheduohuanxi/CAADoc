---
title: "Constraints Object"
category: "use-case"
module: "CAAScdMmrTechArticles"
tags: ["CATIAConstraints"]
source_file: "Doc/online/CAAScdMmrTechArticles/CAAMmrObjConstraints.md"
converted: "2026-05-11T17:31:51.139670"
---
# Constraints Object

See Also | UseCases | Properties | Methods  
---|---|---|---  
  
 

![](../CAAScrAutomationImages/images/constrs.gif)  
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/constrnt.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/dimens.gif)  
---  
  

The **Constraints** collection provides methods to create constraints. A **Constraint** can constrain one, two or three elements. Broken and unupdated constraints can be retrieved from the collection, as well as the number of constraints that fall in these categories in the collection. A given constraint is defined using properties to set its type, its mode, its side and orientation, its dimension and configuration, its reference axis, and its status. The type of a constraints defines its nature, that is how the constraint works, and how many elements can be involved in defining the constraint. The constraint status indicates if the constraint is valid, if something goes wrong with the constraint, or if the constraint is broken. Other properties make sense for certain types of constraints only. The constraint visualization location can be set or retrieved in the 3D space using the two methods **GetConstraintVisuLocation** and **SeConstraintVisuLocation**.

To retrieve the **Constraints** collection, use the `Connections` method of the root product object. Assuming `product1` is the root product, write:
    
    
```vbscript
    Dim constraints1 As Constraints
    Set constraints1 = product1.Connections("CATIAConstraints")

```

* * *

_Copyright © 1999-2013, Dassault Systèmes. All rights reserved._

```