---
title: "CAAAsmCreateAssyHole.CATScript"
category: "use-case"
module: "CAAScdAsmUseCases"
tags: "["CAAScdAsmUseCases", "CATIA", "CAAAsmCreateAssyHole"]"
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCreateAssyHoleSource.htm"
converted: "2026-05-11T17:31:50.846178"
---
tags: ["CAAScdAsmUseCases", "CATIA", "CAAAsmCreateAssyHole"]
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmCreateAssyHoleSource.htmmd"
converted: "2026-05-11T17:31:50.846178"
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2004
```

    Option Explicit

```vbscript
```vbscript
```cpp
    ' ***********************************************************************
    '   Purpose:      Creates and modifies an assembly hole
    '   Assumtions:   Looks for AssemblyHole.CATProduct in the DocView
    '   Languages:    VBSCRIPT
    '   Locales:      English
    '   CATIA Level:  V5R13
    ' ***********************************************************************

```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
    ' -----------------------------------------------------------

    dim sDocPath As String
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```cpp
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```vbscript
```vbscript
      Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
    End If
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Open the Product document
    ' -----------------------------------------------------------

```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

                "online/CAAScdAsmUseCases/samples/AssemblyHole.CATProduct")

```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```vbscript
```
```vbscript
```cpp
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sFilePath)
```
```

```

```

```vbscript
```vbscript
```vbscript
    ' --------------------------
    ' Get the different products
    ' --------------------------

```cpp
    Dim oRootProduct As Product
    Set oRootProduct = CATIA.ActiveDocument.Product

    Dim oSkeletton As Product
    Set oSkeletton = oRootProduct.Products.Item  ( "Skeletton.1" )

    Dim oPlaque1 As Product
    Set oPlaque1 = oRootProduct.Products.Item  ( "Plaque1.1" )

    Dim oPlaque2 As Product
    Set oPlaque2 = oRootProduct.Products.Item  ( "Plaque2.1" )
    ' -----------------------------------------
```
    ' Get the positioning sketch to create hole
    ' -----------------------------------------

```cpp
    Dim oSkelDocument As PartDocument
    Set oSkelDocument = CATIA.Documents.Item("Skeletton.CATPart")

    Dim oBody As Body
    Set oBody = oSkelDocument.Part.Bodies.Item("PartBody")

    Dim oPosSketch As Sketch
    Set oPosSketch = oBody.Sketches.Item("Positioning sketch for assembly hole")
    ' -----------------------------------------
```
    ' Get the AssemblyFeatures technical object
    ' -----------------------------------------

```vbscript
    Dim oAssemblyFeatures As AssemblyFeatures
    Set oAssemblyFeatures = oRootProduct.GetTechnologicalObject("AssemblyFeatures")
    ' -------------------------------------------------------------
```
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

```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' Update the Product
    ' --------------------------------------
```

```

```

    oRootProduct.Update
```vbscript
```vbscript
```vbscript
    ' --------------------------------------
    ' The end...
    ' --------------------------------------
```

```

```

```vbscript
```vbscript
    End Sub

```
```
