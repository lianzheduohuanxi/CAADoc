---
```vbscript
title: "Modifying Cutouts"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrEditCutout", "CAAScdStrUseCases"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCutout.htmmd"
converted: "2026-05-11T17:31:50.895570"
```

---
## Structure Design

|
## Modifying Cutouts

* * *

  This macro shows you how to edit existing cutout on Structure Objects. This macro replaces the contour and direction used for creating existing cutout. ![Starting Product](images/CAAScdStrCutout02.png)
---|---
  CAAStrEditCutout is launched in CATIA [1]. Some documents are needed.

  * You have to run CreateCutout.CATScript macro before running this macro.
  * [CAAStrEditCutout.CATScript](CAAStrModificationOfCutoutSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrEditCutout.CATScript) (Windows only).
  * The document Product1.CATProduct is located in the CAAScdStrUseCases module in the samples directory. Grid.CATPart is linked to the previous document and it contains the grid, sketches and surfaces used by the macro.
  * The CATPart containing the section is located in the samples directory.

  CAAStrEditCutout includes three steps:

CAAStrEditCutout includes three steps:
  1. Prolog
  2. Retrieving Existing Cutout
  3. Modifying the Cutout

#### Prolog

```vbscript
```vbscript
```vbscript
    Dim doc As Document

    Dim StrWorkbench As StrWorkbench
```
```

```vbscript
```vbscript
```vbscript
    Dim strFactory As StrObjectFactory

    Set doc = CATIA.ActiveDocument

    Dim rootProduct As Product
    Set rootProduct = doc.Product

    Set StrWorkbench = doc.GetWorkbench("StrWorkbench")

    Dim strPlates As strPlates
    Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")

```
```

```

```

#### Retrieving Existing Cutout

The Existing cutout can be searched by using the search method on selection.”StrCutout.1” is searched for in the entire product. We will modify the first cutout retrieved.

```vbscript
```vbscript
    Dim selection1 As Selection
```vbscript
```
```vbscript
```vbscript
    Set selection1 = doc.Selection

```
```

```

```

```vbscript
```vbscript
Dim selection1 As Selection
```vbscript
```
```vbscript
Set selection1 = doc.Selection
```
```

    selection1.Search "Name='StrCutout.1',all"

```

```vbscript
```vbscript
    Dim CutoutToEdit As StrCutoutFeature
```vbscript
```
```vbscript
```vbscript
    Set CutoutToEdit = selection1.Item(1).Value

```
```

```

```

#### Modifying the Cutout

```vbscript
```vbscript
Set CutoutToEdit = selection1.Item(1).Value
```
```

Replace the existing contour of the cutout with a new one and also change the direction.

```vbscript
```vbscript
    'Get the Cutout Type

```

```

```vbscript
```vbscript
    Dim FormingMode As String
    FromingMode = CutoutToEdit.CutoutType
```
```

```vbscript
```vbscript
```vbscript
    'Get the Current Contour
```vbscript
    Dim CurrentContour As Reference
    Set CurrentContour = CutoutToEdit.Contour
    'Get the Current Direction Element
```
```vbscript
    Dim CurrentDirElement As Reference
    Set CurrentDirElement = CutoutToEdit.DirectionElement
    'Set the New Direction Element

    Set documents1 = CATIA.Documents
    Set partDocument1 = documents1.Item("Grid.CATPart")
    Set part1 = partDocument1.Part

    Set Newdir = part1.FindObjectByName("Sketch.4")
    Set NewDirElement = part1.CreateReferenceFromObject(Newdir)
```
```

```

```

```vbscript
```vbscript
Set Newdir = part1.FindObjectByName("Sketch.4")
```vbscript
```
```vbscript
```vbscript
Set NewDirElement = part1.CreateReferenceFromObject(Newdir)
    CutoutToEdit.DirectionElement = NewDirElement
```
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
    'Set the New Contour
    Dim NewContour As Reference
    Set NewContour = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.2")
```
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
'Set the New Contour
Dim NewContour As Reference
Set NewContour = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.2")
    CutoutToEdit.Contour = NewContour
```

```

```

```

```vbscript
```vbscript
    End Sub

```
```

![End Task Icon](./assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to edit Cutouts on structure Objects.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

[Top]

* * *

_Copyright 1999-2010, Dassault Systmes. All rights reserved._
