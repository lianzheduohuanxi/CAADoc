---
```vbscript
title: "CAAStrCreationOfStructureObjects.CATScript"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAStrCreationOfStructureObjects", "CATIA"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfStructureFoundationSource.htm"
converted: "2026-05-11T17:31:50.879106"
```

---
tags: ["CAAStrCreationOfStructureObjects", "CATIA"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfStructureFoundationSource.htm"
converted: "2026-05-11T17:31:50.879106"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Create structure foundation
    '   Assumtions:
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R7
    ' ***********************************************************************
```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
```vbscript
        Dim doc As Document

        Dim StrWorkbench As StrWorkbench
```

```vbscript
```vbscript
        Dim strFactory As StrObjectFactory

        Set doc = CATIA.ActiveDocument
        Dim rootProduct As Product
        Set rootProduct = doc.Product

        Dim products As Products
        Set products = rootProduct.Products

        Dim component As Product
        Set component = products.AddNewProduct("Foundation")

        Set strFactory = component.GetTechnologicalObject("StructureObjectFactory")
        ' Creating a foundation assembly

        Dim foundation As StrFoundation
        Set foundation = strFactory.ExtendProductAsFoundation("")
        ' Retreiving the created foundation assembly

        Dim foundations As StrFoundations
        Set foundations = rootProduct.GetTechnologicalObject("StructureFoundations")

        Set foundation = foundations.Item(1)

```

```

```

```vbscript
    End Sub

```
