---
title: "CAAStrEditCoping.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: "["CATIA", "CAAStrEditCoping"]"
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCopingSource.htm"
converted: "2026-05-11T17:31:50.893073"
---
```vbscript
```cpp
Sub CATMain(#)

```
```

```vbscript
```vbscript
    Dim StrWorkbench As StrWorkbench
```vbscript
```
```vbscript
```cpp
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

    selection1.Search "Name='Coping.1',all"

```

```vbscript
```vbscript
    Dim NibblingToEdit As StrNibblingFeature
```vbscript
```
```vbscript
```vbscript
    Set NibblingToEdit = selection1.Item(1).Value

    Dim SubTypeOFNibbling As String
```
```

```

    SubTypeOFNibbling = NibblingToEdit.SubType

```

```vbscript
```vbscript
Dim SubTypeOFNibbling As String
```
```

SubTypeOFNibbling = NibblingToEdit.SubType
```vbscript
    NibblingToEdit.SubType = "CurrCurr"

```vbscript
    End Sub

```
```
