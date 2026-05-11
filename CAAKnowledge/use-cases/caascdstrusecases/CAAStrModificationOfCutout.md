---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdStrCutout02", "CAAStrEditCutout", "CAAStrModificationOfCutoutSource", "CAAScdStrUseCases", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCutout.htm"
converted: "2026-05-11T11:27:02.598896"
---

---

![End Task Icon](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to edit Cutouts on structure Objects.

[Top]

---

#### References

---

*Copyright  1999-2010, Dassault Systmes. All rights reserved.*



```vbscript
Dim doc As Document

Dim StrWorkbench As StrWorkbench
Dim strFactory As StrObjectFactory

Set doc = CATIA.ActiveDocument

Dim rootProduct As Product
Set rootProduct = doc.Product
   
Set StrWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
    
Dim strPlates As strPlates
Set strPlates = rootProduct.GetTechnologicalObject(&quot;StructurePlates&quot;)
```

```vbscript
Dim selection1 As Selection
Set selection1 = doc.Selection

selection1.Search &quot;Name=&#39;StrCutout.1&#39;,all&quot;

Dim CutoutToEdit As StrCutoutFeature
Set CutoutToEdit = selection1.Item(1).Value
```

```vbscript
&#39;Get the Cutout Type
Dim FormingMode As String
FromingMode = CutoutToEdit.CutoutType

&#39;Get the Current Contour
Dim CurrentContour As Reference
Set CurrentContour = CutoutToEdit.Contour

&#39;Get the Current Direction Element
Dim CurrentDirElement As Reference
Set CurrentDirElement = CutoutToEdit.DirectionElement

&#39;Set the New Direction Element

Set documents1 = CATIA.Documents
Set partDocument1 = documents1.Item(&quot;Grid.CATPart&quot;)
Set part1 = partDocument1.Part

Set Newdir = part1.FindObjectByName(&quot;Sketch.4&quot;)
Set NewDirElement = part1.CreateReferenceFromObject(Newdir)
CutoutToEdit.DirectionElement = NewDirElement

&#39;Set the New Contour
Dim NewContour As Reference
Set NewContour = rootProduct.CreateReferenceFromName(&quot;Product1/Grid/!Sketch.2&quot;)
CutoutToEdit.Contour = NewContour

End Sub
```