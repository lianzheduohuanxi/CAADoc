---
title: "CAAArrCreateContourArea.CATScript"
category: "use-case"
module: "CAAScdArrUseCases"
tags: "["CAAArrCreateContourArea", "CATIA"]"
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateContourAreaSource.htm"
converted: "2026-05-11T17:31:51.546099"
---
tags: ["CAAArrCreateContourArea", "CATIA"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateContourAreaSource.htmmd"
converted: "2026-05-11T17:31:51.546099"
    Option Explicit

```vbscript
```vbscript
```cpp
    '// COPYRIGHT DASSAULT SYSTEMES  2000
    '******************************************************************************
    ' Purpose:       This CATScript demonstrates how to create an Area with
    '                a contour.
    ' Assumptions:   This assumes that a macro is being executed interactively.
    ' Author     :
    ' Languages  :   VBScript
    ' CATIA Level:   V5R6
    ' Locale     :   English
    '******************************************************************************

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
```vbscript
       ' On Error Resume Next
       '----------------------------------------------
```
       'Create a new product document
```

```

```

```vbscript
```vbscript
       Dim objProdDoc        As ProductDocument
```vbscript
```
```vbscript
```cpp
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
```
```

```

```

```vbscript
```vbscript
```vbscript
       '----------------------------------------------
       'Retrieving Root Product's Relative Axis and Position Information
```vbscript
       Dim objMove           As Move
       Dim objPosition       As Position
       Set objMove      = objRootProd.Move
       Set objPosition  = objRootProd.Position
       '----------------------------------------------
```
       ' Get ArrangementProduct
```vbscript
       Dim objArrProd        As ArrangementProduct
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
       '----------------------------------------------
```
       ' Create Area without a contour under the Root Product
```vbscript
       Dim objArea         As ArrangementArea
       Dim dblAreaPos(11)  As Double
```
```

```

```

       objPosition.GetComponents dblAreaPos
```vbscript
```vbscript
       Set objArea     = objArrProd.ArrangementAreas.AddArea(objMove, dblAreaPos, 50.0)
```
```

```vbscript
```vbscript
```vbscript
       '----------------------------------------------
       ' Create Rectangle
```vbscript
       Dim objRectangle      As ArrangementRectangle
       Dim objArrProd1       As ArrangementProduct
       Dim objAreaProd1      As Product
       Dim objMove1          As Move
       Dim objPosition1      As Position
       Dim dblRectPos(11)    As Double

       Set objAreaProd1  = objArea.GetTechnologicalObject("Product")
       Set objArrProd1   = objArea.GetTechnologicalObject("ArrangementProduct")
       Set objMove1      = objAreaProd1.Move
       Set objPosition1  = objAreaProd1.Position
```
```

```

```

       objPosition1.GetComponents dblRectPos
       dblRectPos(9)  = 100.0
```vbscript
       dblRectPos(10) = 100.0
       dblRectPos(11) = 0.0

```

```vbscript
```vbscript
       Set objRectangle = objArrProd1.ArrangementRectangles.AddRectangle (objMove1,dblRectPos, 50.0, 50.0)
```vbscript
```
```vbscript
       '---------------------------------------------
       ' Add Rectangular contour to Area
```

```

       objArea.ArrangementContours.AddRectangularContour(objRectangle)

```

```vbscript
```vbscript
    End Sub

```
```
