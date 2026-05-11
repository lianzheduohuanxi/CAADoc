---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAPriPocket", "CAAScdPriUseCases", "CAAInfLauchMacro", "CAAPriPocketSource", "CAAlink"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPocket.htm"
converted: "2026-05-11T11:27:02.727402"
---

---

      

Once the part document has been loaded, the `oPart`, `oBody`
      and `oSketch` variables are declared to receive the instance of
      the part, the partbody and the sketch.
      

#### Creating the Pocket
      
      

The *Pocket* object is created from the o`Sketch`
      object with a default first limit of 20mm. The *Pocket* object
      is created using the `AddNewPocket` method of the *ShapeFactory*
      object.
      

The *Pocket* is then updated with the following result.
      

![](images/img006.jpg)
      

#### Modifying the pad first limit
      
      

The `FirstLimit` property of the *Pocket* object is set
      to 30mm.
      

![](images/img007.jpg)
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create and modify a pocket using macros.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
...
' ------------
' Get the part
' ------------
Dim oPart As Part
Set oPart = CATIA.ActiveDocument.Part

' ------------
' Get the part body in the part
' ------------
Dim oBody As Body
Set oBody = oPart.Bodies.Item  ( &quot;PartBody&quot; ) 

' ------------
' Get the sketch in the body
' ------------
Dim oSketch As Sketch
Set oSketch = oBody.Sketches.Item  ( &quot;Sketch.1&quot; ) 
   ...
```

```vbscript
...
' ------------
' Create the pocket with a default first limit
' ------------
MsgBox &quot;Click OK to create the pocket.&quot;
Dim oPocket As Pocket
Set oPocket= oPart.ShapeFactory.AddNewPocket    ( oSketch, 20.000000 ) 

' ------------
' Update the part
' ------------
oPart.Update 
...
```

```vbscript
...
' ------------
' Define the pocket first limit
' ------------
MsgBox &quot;Click OK to set the pocket first limit to 30mm.&quot;
oPocket.FirstLimit.Dimension.Value = 30.000000

' ------------
' Update the part
' ------------
oPart.Update 
  ...
```