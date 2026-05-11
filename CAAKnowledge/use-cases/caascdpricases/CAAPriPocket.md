---
title: "Creating Pocket"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPocket"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPocket.htm"
converted: "2026-05-11T17:31:51.231457"
---

| 
## Part Design

| 
## Creating Pocket  
  
  
* * *

  This macro shows you how to create a pocket from a sketch. This macro opens the [CAAPriPocket.CATPart](samples/CAAPriPocket.CATPart) document that contains a pad with a sketch on one of its faces.   
 It creates _Pocket_ object from a _Sketch_ __ object with a _ShapeFactory_ method and a update it.  
---|---  
  CAAPriPocket is launched in CATIA [1]. No open document is needed. [CAAPriPocket.CATScript](CAAPriPocketSource.md) is located in the CAAScdPriUseCases module. [Execute macro](macros/CAAPriPocket.CATScript) (windows only).    
  CAAPriPocket includes the following steps:

  1. Prolog
  2. Creating the Pocket
  3. Modifying the Pocket First Limit

#### Prolog

The macro first loads CAAPriPocket.CATPart that contains a sketch: Sketch.2  This object have been created with the Sketcher workbench.  ![](images/img005.jpg) 
    
    
      ...
```vbscript
    ' ------------
    ' Get the part
    ' ------------
```

```vbscript
    Dim oPart As Part
    Set oPart = CATIA.ActiveDocument.Part
```vbscript
    ' ------------
    ' Get the part body in the part
    ' ------------
    Dim oBody As Body
    Set oBody = oPart.Bodies.Item  ( "PartBody" ) 
    ' ------------
    ' Get the sketch in the body
    ' ------------
    Dim oSketch As Sketch
    Set oSketch = oBody.Sketches.Item  ( "Sketch.1" ) 
```

       ...  
  
```

```

---  
  
Once the part document has been loaded, the `oPart`, `oBody` and `oSketch` variables are declared to receive the instance of the part, the partbody and the sketch.
#### Creating the Pocket
    
    
    ...
```vbscript
    ' ------------
    ' Create the pocket with a default first limit
    ' ------------
```

    MsgBox "Click OK to create the pocket."
```vbscript
    Dim oPocket As Pocket
    Set oPocket= oPart.ShapeFactory.AddNewPocket    ( oSketch, 20.000000 ) 
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
    ...
      
```

  
```

---  
  
The _Pocket_ object is created from the o`Sketch` object with a default first limit of 20mm. The _Pocket_ object is created using the `AddNewPocket` method of the _ShapeFactory_ object.

The _Pocket_ is then updated with the following result.

![](images/img006.jpg)
#### Modifying the pad first limit
    
    
    ...
```vbscript
    ' ------------
    ' Define the pocket first limit
    ' ------------
```

    MsgBox "Click OK to set the pocket first limit to 30mm."
    oPocket.FirstLimit.Dimension.Value = 30.000000
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
      ...  
  
---  
  
The `FirstLimit` property of the _Pocket_ object is set to 30mm.

![](images/img007.jpg)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create and modify a pocket using macros.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
