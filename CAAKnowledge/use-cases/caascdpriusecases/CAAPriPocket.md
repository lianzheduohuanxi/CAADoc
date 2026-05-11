---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CAAPriPocketSource", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAlink", "CAAScdPriUseCases", "CAAPriPocket", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPocket.htm"
converted: "2026-05-11T11:06:32.853214"
---

## Part Design
 
 
## []Creating Pocket
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create a pocket from a
 sketch.
 

This macro opens the [CAAPriPocket.CATPart]
 document that contains a pad with a sketch on one of its faces. 

  It creates [*Pocket*]
 object from a [*Sketch*]*
 *object with a [*ShapeFactory*]
 method and a update it.
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAPriPocket is launched in CATIA [[1]].
 No open document is needed.
 

[CAAPriPocket.CATScript] is located
 in the CAAScdPriUseCases module. [Execute
 macro] (windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAPriPocket includes the following steps:
 

 
- [Prolog]
 
- [Creating the Pocket]
 
- [Modifying the Pocket First Limit]
 
 
#### Prolog[]
 

The macro first loads CAAPriPocket.CATPart that contains a sketch:
 Sketch.2 
 

This object have been created with the Sketcher workbench. 
 

![](images/img005.jpg)
 
 
 
```
...

' ------------

' Get the part

' ------------

Dim 
oPart
 As 
Part

Set 
oPart = CATIA.ActiveDocument.Part

' ------------

' Get the part body in the part

' ------------

Dim 
oBody
 As 
Body

Set 
oBody = oPart.Bodies.Item ( "PartBody" ) 

' ------------

' Get the sketch in the body

' ------------

Dim 
oSketch
 As 
Sketch

Set 
oSketch = oBody.Sketches.Item ( "Sketch.1" ) 
 ...
```

 
 
 
 

Once the part document has been loaded, the `oPart`, `oBody`
 and `oSketch` variables are declared to receive the instance of
 the part, the partbody and the sketch.
 
#### Creating the Pocket[]
 
 
 
```
...

' ------------

' Create the pocket with a default first limit

' ------------

MsgBox "Click OK to create the pocket."

Dim 
oPocket
 As 
Pocket

Set 
oPocket= oPart.ShapeFactory.AddNewPocket ( oSketch, 20.000000 ) 

' ------------

' Update the part

' ------------

oPart.Update 
...
```

 
 
 
 

The *Pocket* object is created from the o`Sketch`
 object with a default first limit of 20mm. The *Pocket* object
 is created using the `AddNewPocket` method of the *ShapeFactory*
 object.
 

The *Pocket* is then updated with the following result.
 

![](images/img006.jpg)
 
#### Modifying the pad first limit[]
 
 
 
```
...

' ------------

' Define the pocket first limit

' ------------

MsgBox "Click OK to set the pocket first limit to 30mm."
oPocket.FirstLimit.Dimension.Value = 30.000000

' ------------

' Update the part

' ------------

oPart.Update 
 ...
```

 
 
 
 

The `FirstLimit` property of the *Pocket* object is set
 to 30mm.
 

![](images/img007.jpg)
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create and modify a pocket using macros.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a macro]
 
 
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*