---
title: "Creating Pad"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPad"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPad.md"
converted: "2026-05-11T17:31:51.225469"
---
## Part Design

| 
## Creating Pad  
  
  
* * *

  This macro shows you how to create a pad from a sketch. This macro opens the [CAAPriPad.CATPart](samples/CAAPriPad.CATPart) document that contains a sketch only.   
It creates _Pad_ object from a _Sketch_ __ object with a _ShapeFactory_ method and a update it.  
---|---  
  CAAPriPad is launched in CATIA [1]. No open document is needed. [CAAPriPad.CATScript](CAAPriPadSource.md) is located in the CAAScdPriUseCases module. [Execute macro](macros/CAAPriPad.CATScript) (windows only).    
  CAAPriPad includes the following steps:

  1. Prolog
  2. Creating the Pad
  3. Modifying the Pad First Limit
  4. Mirroring the Pad

#### Prolog

The macro first loads CAAPriPad.CATPart that contains a sketch: Sketch.1  This object have been created with the Sketcher workbench.  ![](images/img001.jpg) 
    
    
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
#### Creating the Pad
    
    
    ...
```vbscript
    ' ------------
    ' Create the pad with a default first limit
    ' ------------
```

    MsgBox "Click OK to create the pad."
```vbscript
    Dim oPad As Pad
    Set oPad = oPart.ShapeFactory.AddNewPad  ( oSketch, 20.000000 ) 
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
  
The _Pad_ object is created from the o`Sketch` object with a default first limit of 20mm. The _Pad_ object is created using the `AddNewPad` method of the _ShapeFactory_ object.

The _Pad_ is then updated with the following result.

![](images/img002.jpg)
#### Modifying the pad first limit
    
    
    ...
```vbscript
    ' ------------
    ' Define the pad first limit
    ' ------------
```

    MsgBox "Click OK to set the pad first limit to 40mm."
    oPad.FirstLimit.Dimension.Value = 40.000000
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
      ...  
  
---  
  
The `FirstLimit` property of the _Pad_ object is set to 40mm.

![](images/img003.jpg)
#### Mirroring the pad
    
    
    ...
```vbscript
    ' ------------
    ' Define the pad to be symmetric relative to the sketch plane
    ' ------------
```

    MsgBox "Click OK to mirror the extrusion offset."
    oPad.IsSymmetric = True
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
      ...  
  
---  
  
The `IsSymmetric` property of the _Pad_ object is set to 40mm.

![](images/img004.jpg)  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create and modify a pad using macros.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
