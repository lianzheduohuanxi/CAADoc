---
```vbscript
title: "Creating and Modifying an Assembly Hole"
category: "use-case"
module: "CAAScdAsmUseCases"
tags: ["CAAScdAsmUseCases", "CATIA", "CAAAsmCreateAssyHole"]
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCreateAssyHole.htmmd"
converted: "2026-05-11T17:31:50.843187"
```

---
## Assembly

|
## Creating and Modifying an Assembly Hole

* * *

  This macro shows you how to create an assembly hole and valuate its parameters. This macro opens the [AssemblyHole.CATProduct](samples/AssemblyHole.CATProduct) document that contains three parts: a skeletton, Skeletton.CATPart, and two plates, Plaque1.CATPart and Plaque2.CATPart.
This macro shows you how to create an assembly hole and valuate its parameters. This macro opens the [AssemblyHole.CATProduct](samples/AssemblyHole.CATProduct) document that contains three parts: a skeletton, Skeletton.CATPart, and two plates, Plaque1.CATPart and Plaque2.CATPart.
It retrieves each _Product_ object corresponding to the product instances in the assembly and the _Sketch_ object which will define the position of the assembly hole. It creates an _AssemblyHole_ object in the assembly. It sets the main parameters of the new _AssemblyHole_ object. To finish the whole assembly is updated.

This macro shows you how to create an assembly hole and valuate its parameters. This macro opens the [AssemblyHole.CATProduct](samples/AssemblyHole.CATProduct) document that contains three parts: a skeletton, Skeletton.CATPart, and two plates, Plaque1.CATPart and Plaque2.CATPart.
It retrieves each _Product_ object corresponding to the product instances in the assembly and the _Sketch_ object which will define the position of the assembly hole. It creates an _AssemblyHole_ object in the assembly. It sets the main parameters of the new _AssemblyHole_ object. To finish the whole assembly is updated.
  CAAAsmCreateAssyHole is launched in CATIA [1]. No open document is needed. [CAAAsmCreateAssyHole.CATScript](CAAAsmCreateAssyHoleSource.md) is located in the CAAScdAsmUseCases module. [Execute macro](macros/CAAAsmCreateAssyHole.CATScript) (Windows only).
  CAAAsmCreateAssyHole includes the following steps:

  1. Prolog
  2. Creating Assembly Hole
  3. Setting Assembly Hole parameters

#### Prolog

2. Creating Assembly Hole
3. Setting Assembly Hole parameters
The macro first loads AssemblyHole.CATProduct that contains three parts: a skeletton, Skeletton.CATPart, and two plates, Plaque1.CATPart and Plaque2.CATPart. ![](images/AssyHoleBefore.jpg)

    ...
```vbscript
```vbscript
```vbscript
    ' --------------------------
    ' Get the different products
    ' --------------------------
```

```

```

```vbscript
```vbscript
    Dim oRootProduct As Product
```vbscript
```
```vbscript
```vbscript
    Set oRootProduct = CATIA.ActiveDocument.Product

    Dim oSkeletton As Product
    Set oSkeletton = oRootProduct.Products.Item  ( "Skeletton.1" )

    Dim oPlaque1 As Product
    Set oPlaque1 = oRootProduct.Products.Item  ( "Plaque1.1" )

    Dim oPlaque2 As Product
    Set oPlaque2 = oRootProduct.Products.Item  ( "Plaque2.1" )
```
```

```

```

    ...

---

Once the product document has been loaded, the `oSkeletton`, `oPlaque1` and `oPlaque2` variables are declared to receive the instances of Skeletton, Plaque1 and Plaque2. Those instances are fetched in the _Products_ collection [2] of the root _Product_ [2] using their names.

    ...
```vbscript
```vbscript
```vbscript
    ' -----------------------------------------
    ' Get the positioning sketch to create hole
    ' -----------------------------------------
```

```

```

```vbscript
```vbscript
    Dim oSkelDocument As PartDocument
```vbscript
```
```vbscript
```vbscript
    Set oSkelDocument = CATIA.Documents.Item("Skeletton.CATPart")

    Dim oBody As Body
    Set oBody = oSkelDocument.Part.Bodies.Item("PartBody")

    Dim oPosSketch As Sketch
    Set oPosSketch = oBody.Sketches.Item("Positioning sketch for assembly hole")
```
```

```

```

    ...

---

The `oPosSketch` object will be used to determine the positioning point of the hole. The sketch only needs to contain one point.
#### Creating Assembly Hole.

    ...
```vbscript
```vbscript
```vbscript
    ' -----------------------------------------
    ' Get the AssemblyFeatures technical object
    ' -----------------------------------------
```

```

```

```vbscript
```vbscript
    Dim oAssemblyFeatures As AssemblyFeatures
```vbscript
```
```vbscript
    Set oAssemblyFeatures = oRootProduct.GetTechnologicalObject("AssemblyFeatures")
```
```

```

```vbscript
```vbscript
```vbscript
    ' -------------------------------------------------------------
    ' Create assembly hole
    '   positioning sketch : oPosSketch
    '   instance containing the positioning sketch : oSkeletton
    '   instance defining the positioning of the hole : oSkeletton
    '   depth : 10 mm
    ' -------------------------------------------------------------

```vbscript
    Dim oAssemblyHole As AssemblyHole
    Set oAssemblyHole = oAssemblyFeatures.AddAssemblyHole(oPosSketch, oSkeletton, 10.000000, oSkeletton)
    ' ------------------------------------------------------------
```
    ' Affects parts to the assembly hole : Plaque1.1 and Plaque2.1
    ' ------------------------------------------------------------
```

```

```

    oAssemblyHole.AddAffectedComponent oPlaque1
    oAssemblyHole.AddAffectedComponent oPlaque2
    ...

---

The _AssemblyFeatures_ collection [2] `oAssemblyFeatures` is retrieved from the root _Product_ using the method `GetTechnologicalObject`. This object allows you to retrieve all the assembly features of `oRootProduct` and to create new ones.

The _AssemblyFeatures_ collection [2] `oAssemblyFeatures` is retrieved from the root _Product_ using the method `GetTechnologicalObject`. This object allows you to retrieve all the assembly features of `oRootProduct` and to create new ones.
A new _AssemblyHole_ object [2] is created using the `AddAssemblyHole` method.

The first and second arguments define the positioning _Sketch_ [2] and one _Product_ containing it; is could be any instance of Skeletton.CATPart. The third argument is the depth of the hole as a double. The fourth argument is a _Product_ instance of Skeletton.CATPart defining the real position of the hole in the assembly context.

The two _product_ Plaque1.1 and Plaque2.1 are affected using the `AddAffectedComponent` method.

#### Setting Assembly Hole parameters

    ...
```vbscript
```vbscript
```vbscript
    ' --------------------------------------------
    ' modify the hole parameters
    '   - diameter 10 mm
    '   - counterbored
    '   - V-bottom
    '   - length
    ' --------------------------------------------
```

```

```

```vbscript
```vbscript
    Dim oDiameter As Length
```vbscript
```
```vbscript
```vbscript
    Set oDiameter = oAssemblyHole.Diameter
    oDiameter.Value = 10.000000
```

```

```

```

```vbscript
```vbscript
Set oDiameter = oAssemblyHole.Diameter
```
```

oDiameter.Value = 10.000000
```vbscript
```vbscript
    oAssemblyHole.Type = catCounterboredHole
    oAssemblyHole.AnchorMode = catExtremPointHoleAnchor

```

```

```vbscript
```vbscript
    Dim oHeadDiameter As Length
```vbscript
```
```vbscript
```vbscript
    Set oHeadDiameter = oAssemblyHole.HeadDiameter
    oHeadDiameter.Value = 15.000000
```

```vbscript
    Dim oHeadDepth As Length
    Set oHeadDepth = oAssemblyHole.HeadDepth
    oHeadDepth.Value = 5.000000
```

```vbscript
    Dim oBottomLimit As Limit
    Set oBottomLimit = oAssemblyHole.BottomLimit
    oBottomLimit.LimitMode = catOffsetLimit
```

```vbscript
    Dim oDepth As Length
    Set oDepth = oBottomLimit.Dimension
    oDepth.Value = 30.000000
```

```

```

```

```vbscript
```vbscript
Set oDepth = oBottomLimit.Dimension
```
```

oDepth.Value = 30.000000
```vbscript
```vbscript
    oAssemblyHole.BottomType = catVHoleBottom

```

```

```vbscript
```vbscript
    Dim oBottomAngle As Angle
```vbscript
```
```vbscript
```vbscript
    Set oBottomAngle = oAssemblyHole.BottomAngle
    oBottomAngle.Value = 120.000000
```
```

```

```

    ...

---

The diameter of the hole is set using the `Diameter` property and the _Length_ object [2].

The diameter of the hole is set using the `Diameter` property and the _Length_ object [2].
The type is set using `Type` property; hole types are defined in the _CatHoleType_ enum [2]. In the case of a counter bored hole the anchor mode is set by `AnchorMode`; hole anchor modes are defined in the _CatHoleAnchorMode_ enum [2]. The head depth is valuated using `HeadDiameter` property and the _Length_ object.

The Limit is defined by `BottomLimit` property and _Limit_ object [2].

    ...
```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Update the Product
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
' Update the Product
' --------------------------------------
```

```

    oRootProduct.Update
```

    ...

---

The root _Product_ is then updated; it propagates the Update to the affected parts so that the resulting holes appears in the CATParts.

![](images/AssyHoleAfter.jpg)

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create an assembly hole and set its parameters using macros.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _Products_ _,_ _Product_ _,_ _AssemblyFeatures_ _,_ _AssemblyHole_ _,_ _Sketch_ _,_ _CatHoleType_ _,_ _CatHoleAnchorMode_ _,_ _Limit_ _,_ _Length_ _,_ _Angle_ _._
[Top]

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
