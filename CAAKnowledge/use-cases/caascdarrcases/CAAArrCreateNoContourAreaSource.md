---
```vbscript
title: "CAAArrCreateNoContourArea.CATScript"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CATIA", "CAAArrCreateNoContourArea"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateNoContourAreaSource.htm"
converted: "2026-05-11T17:31:51.557571"
```

---
tags: ["CATIA", "CAAArrCreateNoContourArea"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateNoContourAreaSource.htm"
converted: "2026-05-11T17:31:51.557571"
    Option Explicit

```vbscript
    '// COPYRIGHT DASSAULT SYSTEMES  2000
    '******************************************************************************
    ' Purpose:       This CATScript demonstrates how to create an Area without
    '                a contour.
    ' Assumptions:   This assumes that a macro is being executed interactively.
    ' Author     :                               
    ' Languages  :   VBScript
    ' CATIA Level:   V5R6
    ' Locale     :   English
    '******************************************************************************

```

    Sub CATMain()

```vbscript
       ' On Error Resume Next
       '----------------------------------------------
       'Create a new product document
```

```vbscript
       Dim objProdDoc        As ProductDocument
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
```

```vbscript
       '----------------------------------------------
       'Retrieving Root Product's Relative Axis and Position Information
       Dim objMove           As Move
       Dim objPosition       As Position
       Set objMove      = objRootProd.Move
       Set objPosition  = objRootProd.Position
       '----------------------------------------------
       ' Get ArrangementProduct
       Dim objArrProd        As ArrangementProduct
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
       '----------------------------------------------
       ' Create Area without a contour under the Root Product
       Dim objArea              As ArrangementArea
       Dim dblAreaPosition(11)  As Double
```

       objPosition.GetComponents dblAreaPosition
       dblAreaPosition(9)    = 300.0
       dblAreaPosition(10)   = 400.0
       dblAreaPosition(11)   = 300.0

```vbscript
       Set objArea     = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPosition, 50.0)

```

    End Sub 
