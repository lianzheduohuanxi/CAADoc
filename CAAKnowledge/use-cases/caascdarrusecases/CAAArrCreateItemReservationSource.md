---
title: "Untitled"
category: "use-case"
module: "CAAScdArrUseCases"
tags: ["CAAScrBase", "CATIA", "CAAArrCreateItemReservation"]
source_file: "Doc/online/CAAScdArrUseCases/CAAArrCreateItemReservationSource.htm"
converted: "2026-05-11T11:06:32.724866"
---

```
Option Explicit

'// COPYRIGHT DASSAULT SYSTEMES 2000

'******************************************************************************

' Purpose: This CATScript demonstrates how to create an Item Reservation.

' and change it's visualization to "Flat" mode.

' Assumptions: This assumes that a macro is being executed interactively.

' 

' Author : 

' Languages : VBScript

' CATIA Level: V5R6

' Locale : English

'******************************************************************************

Sub 
CATMain()
 
 
' On Error Resume Next

 
'----------------------------------------------

 
'Create a new product document

 Dim 
objProdDoc 
 As 
ProductDocument

 Dim 
objRootProd 
 As 
Product

 Set 
objProdDoc = CATIA.Documents.Add("Product")

 Set 
objRootProd = objProdDoc.Product

 
'----------------------------------------------

 
'Retrieving Root Product's Relative Axis and Position Information

 Dim 
objMove 
 As 
Move

 Dim 
objPosition 
 As 
Position

 Set 
objMove = objRootProd.Move

 Set 
objPosition = objRootProd.Position

 
'----------------------------------------------

 
' Get ArrangementProduct

 Dim 
objArrProd 
 As 
ArrangementProduct

 Set 
objArrProd = objRootProd.GetTechnologicalObject("ArrangementProduct")

 
'----------------------------------------------

 
' Create Item Reservation under the Root Product

 Dim 
dblItemResPos(11) 
 As 
Double

 Dim 
objItemRes 
 As 
ArrangementItemReservation

 objPosition.GetComponents dblItemResPos

 Set 
objItemRes = objArrProd.ArrangementItemReservations.AddItemReservation(objMove, dblItemResPos, 200.0, 500.0, 200.0, 500.0, 0.0, 0.0)

 
'----------------------------------------------

 
' Change Properties of ArrangementItemReservation

 objItemRes.VisuMode = CatArrangementItemReservationVisuModeFlat

End Sub
```