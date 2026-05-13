---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAStrCreationOfStructureObjects"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfStructureFoundationSource.htmmd"
converted: "2026-05-11T11:27:02.584456"
---

Option Explicit
' COPYRIGTH DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Create structure foundation
'   Assumtions:   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R7 
' ***********************************************************************

```vbscript
Sub CATMain(#)

    Dim doc As Document

    Dim StrWorkbench As StrWorkbench
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
```

```vbscript
    Dim foundation As StrFoundation 
    Set foundation = strFactory.ExtendProductAsFoundation("")

    ' Retreiving the created foundation assembly
```

```vbscript
    Dim foundations As StrFoundations
    Set foundations = rootProduct.GetTechnologicalObject("StructureFoundations")		
	
    Set foundation = foundations.Item(1)

End Sub

```

```vbscript
Option Explicit
' COPYRIGTH DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Create structure foundation
'   Assumtions:   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R7 
' ***********************************************************************

```vbscript
Sub CATMain(#)

    Dim doc As Document

    Dim StrWorkbench As StrWorkbench
    Dim strFactory As StrObjectFactory

    Set doc = CATIA.ActiveDocument
    Dim rootProduct As Product
    Set rootProduct = doc.Product

    Dim products As Products
    Set products = rootProduct.Products

    Dim component As Product
    Set component = products.AddNewProduct(&quot;Foundation&quot;)

    Set strFactory = component.GetTechnologicalObject(&quot;StructureObjectFactory&quot;)

    ' Creating a foundation assembly
```

```vbscript
    Dim foundation As StrFoundation 
    Set foundation = strFactory.ExtendProductAsFoundation(&quot;&quot;)

    ' Retreiving the created foundation assembly
```

```vbscript
    Dim foundations As StrFoundations
    Set foundations = rootProduct.GetTechnologicalObject(&quot;StructureFoundations&quot;)		
	
    Set foundation = foundations.Item(1)

End Sub
```
```