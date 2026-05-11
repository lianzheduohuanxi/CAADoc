---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CAAScdStrCoping02", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAAStrModificationOfCopingSource", "CAAScdStrUseCases", "CAAStrEditCoping"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCoping.htm"
converted: "2026-05-11T11:27:02.594168"
---

---

![End Task Icon](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to edit coping between structure objects.

[Top]

---

#### References

---

*Copyright  1999-2010, Dassault Systmes. All rights reserved.*



```vbscript
Sub CATMain()

  Dim StrWorkbench As StrWorkbench
  Dim strFactory As StrObjectFactory

  Set doc = CATIA.ActiveDocument
  Dim rootProduct As Product
  Set rootProduct = doc.Product

  Set StrWorkbench = doc.GetWorkbench("StrWorkbench")
    
  Dim strPlates As strPlates
  Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
   
  Dim strMembers As strMembers
  Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
```

```vbscript
Dim selection1 As Selection
  Set selection1 = doc.Selection

  selection1.Search "Name='Coping.1',all"

  Dim NibblingToEdit As StrNibblingFeature
  Set NibblingToEdit = selection1.Item(1).Value

  Dim SubTypeOfNibbling As String
  SubTypeOfNibbling = NibblingToEdit.SubType

  NibblingToEdit.SubType = "CurrCurr"

End Sub
```