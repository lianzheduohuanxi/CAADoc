---
```vbscript
title: "CAAArrCreateItemReservation.CATScript"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAArrCreateItemReservation", "CATIA"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservationSource.htm"
converted: "2026-05-11T17:31:51.552087"
```

---
tags: ["CAAArrCreateItemReservation", "CATIA"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservationSource.htm"
converted: "2026-05-11T17:31:51.552087"
    Option Explicit

```vbscript
```vbscript
```vbscript
    '// COPYRIGHT DASSAULT SYSTEMES  2000
    '******************************************************************************
    ' Purpose:       This CATScript demonstrates how to create an Item Reservation.
    '                and change it's visualization to "Flat" mode.
    ' Assumptions:   This assumes that a macro is being executed interactively.
    '
    ' Author     :
    ' Languages  :   VBScript
    ' CATIA Level:   V5R6
    ' Locale     :   English
    '******************************************************************************

```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
       ' On Error Resume Next
       '----------------------------------------------
       'Create a new product document
```

```

```

```vbscript
       Dim objProdDoc        As ProductDocument
```vbscript
```vbscript
       Dim objRootProd       As Product
       Set objProdDoc      = CATIA.Documents.Add("Product")
       Set objRootProd     = objProdDoc.Product
```

```

```

```vbscript
```vbscript
```vbscript
       '----------------------------------------------
       'Retrieving Root Product's Relative Axis and Position Information
       Dim objMove           As Move
       Dim objPosition       As Position
       Set objMove      = objRootProd.Move
       Set objPosition  = objRootProd.Position
```

```

```

```vbscript
       '----------------------------------------------
```

```vbscript
```vbscript
```vbscript
'----------------------------------------------
       ' Get ArrangementProduct
```

```

```

```vbscript
       Dim objArrProd        As ArrangementProduct
```vbscript
```vbscript
       Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")

```

```

```

```vbscript
Dim objArrProd        As ArrangementProduct
```vbscript
```vbscript
Set objArrProd   = objRootProd.GetTechnologicalObject("ArrangementProduct")
       '----------------------------------------------
       ' Create Item Reservation under the Root Product
```

```

```

```vbscript
       Dim dblItemResPos(11)  As Double
```vbscript
```vbscript
       Dim objItemRes     As ArrangementItemReservation

```

```

```

```vbscript
Dim dblItemResPos(11)  As Double
```vbscript
Dim objItemRes     As ArrangementItemReservation
```

       objPosition.GetComponents dblItemResPos
```

```vbscript
       Set objItemRes      = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)
```vbscript
```vbscript
       '----------------------------------------------
       ' Change Properties of ArrangementItemReservation
       objItemRes.VisuMode = CatArrangementItemReservationVisuModeFlat

```

```

```

```vbscript
    End Sub

```
