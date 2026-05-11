---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAStrEditCoping", "CAAScrBase", "CATIA"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCopingSource.htm"
converted: "2026-05-11T11:27:02.603030"
---

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

Dim selection1 As Selection
Set selection1 = doc.Selection

selection1.Search "Name='Coping.1',all"

Dim NibblingToEdit As StrNibblingFeature
Set NibblingToEdit = selection1.Item(1).Value

Dim SubTypeOFNibbling As String
SubTypeOFNibbling = NibblingToEdit.SubType

NibblingToEdit.SubType = "CurrCurr"

End Sub



```vbscript
Sub CATMain()

Dim StrWorkbench As StrWorkbench
Dim strFactory As StrObjectFactory

Set doc = CATIA.ActiveDocument
Dim rootProduct As Product
Set rootProduct = doc.Product
   
Set StrWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
    
Dim strPlates As strPlates
Set strPlates = rootProduct.GetTechnologicalObject(&quot;StructurePlates&quot;)
   
Dim strMembers As strMembers
Set strMembers = rootProduct.GetTechnologicalObject(&quot;StructureMembers&quot;)

Dim selection1 As Selection
Set selection1 = doc.Selection

selection1.Search &quot;Name='Coping.1',all&quot;

Dim NibblingToEdit As StrNibblingFeature
Set NibblingToEdit = selection1.Item(1).Value

Dim SubTypeOFNibbling As String
SubTypeOFNibbling = NibblingToEdit.SubType

NibblingToEdit.SubType = &quot;CurrCurr&quot;

End Sub
```