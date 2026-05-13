---
title: "CAAInfGettingStarted.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: "["CATIA", "CAAInfGettingStarted"]"
source_file: "Doc/online/CAAScdInfUseCases/CAAInfGettingStartedSource.htm"
converted: "2026-05-11T17:31:52.376020"
---
tags: ["CATIA", "CAAInfGettingStarted"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfGettingStartedSource.htmmd"
converted: "2026-05-11T17:31:52.376020"
    Language="VBSCRIPT"
```vbscript
```vbscript
    'My macro creates five cylinders

```

```

```vbscript
```cpp
    Sub CATMain(#)

```
```

```vbscript
```vbscript
    Dim documents1 As Documents
```vbscript
```
```vbscript
```cpp
    Set documents1 = CATIA.Documents

    Dim partDocument1 As Document
    Set partDocument1 = documents1.Add("Part")

    Dim part1 As Part
    Set part1 = partDocument1.Part

    Dim bodies1 As Bodies
    Set bodies1 = part1.Bodies

    Dim body1 As Body
    Set body1 = bodies1.Item("MechanicalTool.1")

    Dim sketches1 As Sketches
    Set sketches1 = body1.Sketches

    Dim originElements1 As OriginElements
    Set originElements1 = part1.OriginElements

    Dim reference1 As AnyObject
    Set reference1 = originElements1.PlaneXY

```
```

```

```

```vbscript
```vbscript
Dim reference1 As AnyObject
```vbscript
```
```vbscript
Set reference1 = originElements1.PlaneXY
```
```

    x = 0

```

```vbscript
```vbscript
    Dim arrayOfVariantOfDouble1(8)
```vbscript
```
    arrayOfVariantOfDouble1(0) = 0.000000
    arrayOfVariantOfDouble1(1) = 0.000000
    arrayOfVariantOfDouble1(2) = 0.000000
    arrayOfVariantOfDouble1(3) = 1.000000
    arrayOfVariantOfDouble1(4) = 0.000000
    arrayOfVariantOfDouble1(5) = 0.000000
    arrayOfVariantOfDouble1(6) = 0.000000
    arrayOfVariantOfDouble1(7) = 1.000000
    arrayOfVariantOfDouble1(8) = 0.000000

```

```

```vbscript
```vbscript
    For I = 1 To 5

```vbscript
      Dim sketch1 As Sketch
```
```

```vbscript
```vbscript
```vbscript
      Set sketch1 = sketches1.Add(reference1)

```
```

```

```

```vbscript
```vbscript
Dim sketch1 As Sketch
```vbscript
```
```vbscript
Set sketch1 = sketches1.Add(reference1)
```
```

      sketch1.SetAbsoluteAxisData arrayOfVariantOfDouble1

```

```vbscript
```vbscript
      Dim factory2D1 As Factory2D
```vbscript
```
```vbscript
```vbscript
      Set factory2D1 = sketch1.OpenEdition(#)

      Dim geometricElements1 As GeometricElements
      Set geometricElements1 = sketch1.GeometricElements

      Dim axis2D1 As GeometricElement
      Set axis2D1 = geometricElements1.Item("AbsoluteAxis")

      Dim line2D1 As AnyObject
      Set line2D1 = axis2D1.GetItem("HDirection")

```
```

```

```

```vbscript
```vbscript
Dim line2D1 As AnyObject
```vbscript
```
```vbscript
```vbscript
Set line2D1 = axis2D1.GetItem("HDirection")
      line2D1.ReportName = 1
```

```

```

```

```vbscript
```vbscript
      Dim line2D2 As AnyObject
```vbscript
```
```vbscript
```vbscript
      Set line2D2 = axis2D1.GetItem("VDirection")

```
```

```

```

```vbscript
```vbscript
Dim line2D2 As AnyObject
```vbscript
```
```vbscript
```vbscript
Set line2D2 = axis2D1.GetItem("VDirection")
      line2D2.ReportName = 2
```

```

```

```

```vbscript
```vbscript
      Dim circle2D1 As Circle2D
```vbscript
```
```vbscript
```vbscript
      Set circle2D1 = factory2D1.CreateClosedCircle(x, 0.000000, 10.000000)

```
```

```

```

```vbscript
```vbscript
Dim circle2D1 As Circle2D
```vbscript
```
```vbscript
```vbscript
Set circle2D1 = factory2D1.CreateClosedCircle(x, 0.000000, 10.000000)
      circle2D1.ReportName = 3
```

```

```

```

      sketch1.CloseEdition

      part1.Update

```vbscript
```vbscript
      Dim shapeFactory1 As Factory
```vbscript
```
```vbscript
```vbscript
      Set shapeFactory1 = part1.ShapeFactory

      Dim pad1 As Pad
      Set pad1 = shapeFactory1.AddNewPad(sketch1, 20.000000)

```
```

```

```

```vbscript
```vbscript
Dim pad1 As Pad
```vbscript
```
```vbscript
Set pad1 = shapeFactory1.AddNewPad(sketch1, 20.000000)
```
```

      part1.Update

```

      x = x + 25

```vbscript
    Next
```vbscript
    End Sub

```
```
