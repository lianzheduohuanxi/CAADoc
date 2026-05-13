---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdPriUseCases", "CAAPriPadSource", "CAAInfLauchMacro", "CAAPriPad", "CAAlink"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPad.htmmd"
converted: "2026-05-11T11:27:02.726351"
---

---

      

Once the part document has been loaded, the `oPart`, `oBody`
      and `oSketch` variables are declared to receive the instance of
      the part, the partbody and the sketch.
      

#### Creating the Pad
      
      

The *Pad* object is created from the o`Sketch` object
      with a default first limit of 20mm. The *Pad* object is created
      using the `AddNewPad` method of the *ShapeFactory* object.
      

The *Pad* is then updated with the following result.
      

![](images/img002.jpg)
      

#### Modifying the pad first limit
      
      

The `FirstLimit` property of the *Pad* object is set to
      40mm.
      

![](images/img003.jpg)
      

#### Mirroring the pad
      
      

The `IsSymmetric` property of the *Pad* object is set
      to 40mm.
      

![](images/img004.jpg)
    
  

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create and modify a pad using macros.

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
```cpp
Dim oPart As Part
Set oPart = CATIA.ActiveDocument.Part

```

' ------------
' Get the part body in the part
' ------------
```vbscript
Dim oBody As Body
Set oBody = oPart.Bodies.Item  ( &quot;PartBody&quot; ) 

```

' ------------
' Get the sketch in the body
' ------------
```vbscript
Dim oSketch As Sketch
Set oSketch = oBody.Sketches.Item  ( &quot;Sketch.1&quot; ) 
   ...
```
```

```vbscript
...
' ------------
' Create the pad with a default first limit
' ------------
```vbscript
MsgBox &quot;Click OK to create the pad.&quot;
Dim oPad As Pad
Set oPad = oPart.ShapeFactory.AddNewPad  ( oSketch, 20.000000 ) 

```

' ------------
' Update the part
' ------------
oPart.Update 
...
```

```vbscript
...
' ------------
' Define the pad first limit
' ------------
```vbscript
MsgBox &quot;Click OK to set the pad first limit to 40mm.&quot;
oPad.FirstLimit.Dimension.Value = 40.000000
```

' ------------
' Update the part
' ------------
oPart.Update 
  ...
```

```vbscript
...
' ------------
' Define the pad to be symmetric relative to the sketch plane
' ------------
```vbscript
MsgBox &quot;Click OK to mirror the extrusion offset.&quot;
oPad.IsSymmetric = True
```

' ------------
' Update the part
' ------------
oPart.Update 
  ...
```