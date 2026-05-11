---
title: "CAAStrEditCutout.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrEditCutout"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCutoutSource.md"
converted: "2026-05-11T17:31:50.897562"
---

```vbscript
    Sub CATMain()
```vbscript
    Dim StrWorkbench As StrWorkbench
    Dim strFactory As StrObjectFactory
    
    Set doc = CATIA.ActiveDocument
    Dim rootProduct As Product
    Set rootProduct = doc.Product
       
    Set StrWorkbench = doc.GetWorkbench("StrWorkbench")
        
    Dim strPlates As strPlates
    Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
       
    Dim selection1 As Selection
    Set selection1 = doc.Selection
    
```

    selection1.Search "Name='StrCutout.1',all"
    
```vbscript
    Dim CutoutToEdit As StrCutoutFeature
    Set CutoutToEdit = selection1.Item(1).Value
```vbscript
    'Get the Cutout Type
    Dim FormingMode As String
    FromingMode = CutoutToEdit.CutoutType
    'Get the Current Contour
    Dim CurrentContour As Reference
    Set CurrentContour = CutoutToEdit.Contour
    'Get the Current Direction Element
    Dim CurrentDirElement As Reference
    Set CurrentDirElement = CutoutToEdit.DirectionElement
    'Set the New Direction Element
    Set documents1 = CATIA.Documents
    Set partDocument1 = documents1.Item("Grid.CATPart")
    Set part1 = partDocument1.Part
    
    Set Newdir = part1.FindObjectByName("Sketch.4")
    Set NewDirElement = part1.CreateReferenceFromObject(Newdir)
```

    CutoutToEdit.DirectionElement = NewDirElement
```vbscript
    'Set the New Contour
    Dim NewContour As Reference
    Set NewContour = rootProduct.CreateReferenceFromName("Product1/Grid/!Sketch.2")
```

    CutoutToEdit.Contour = NewContour
    
```

```vbscript
    End Sub
    
```

```