---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAArrCreateItemReservation", "CAAScrBase", "CATIA"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservationSource.htmmd"
converted: "2026-05-11T11:27:02.670803"
---

Option Explicit
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

```cpp
Sub CATMain(#)
   
   ' On Error Resume Next

   '----------------------------------------------
```
   'Create a new product document
```cpp
   Dim objProdDoc        As ProductDocument
   Dim objRootProd       As Product
   Set objProdDoc      = CATIA.Documents.Add("Product")
   Set objRootProd     = objProdDoc.Product

   '----------------------------------------------
```
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
   ' Create Item Reservation under the Root Product
```vbscript
   Dim dblItemResPos(11)  As Double
   Dim objItemRes     As ArrangementItemReservation

   objPosition.GetComponents dblItemResPos
```
```vbscript
   Set objItemRes      = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)

```

   '----------------------------------------------
   ' Change Properties of ArrangementItemReservation
   objItemRes.VisuMode = CatArrangementItemReservationVisuModeFlat

```vbscript
End Sub 

```

```cpp
Option Explicit
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

```cpp
Sub CATMain(#)
   
   ' On Error Resume Next

   '----------------------------------------------
```
   'Create a new product document
```cpp
   Dim objProdDoc        As ProductDocument
   Dim objRootProd       As Product
   Set objProdDoc      = CATIA.Documents.Add("Product")
   Set objRootProd     = objProdDoc.Product

   '----------------------------------------------
```
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
   ' Create Item Reservation under the Root Product
```vbscript
   Dim dblItemResPos(11)  As Double
   Dim objItemRes     As ArrangementItemReservation

   objPosition.GetComponents dblItemResPos
```
```vbscript
   Set objItemRes      = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)

```

   '----------------------------------------------
   ' Change Properties of ArrangementItemReservation
   objItemRes.VisuMode = CatArrangementItemReservationVisuModeFlat

```vbscript
End Sub
```
```