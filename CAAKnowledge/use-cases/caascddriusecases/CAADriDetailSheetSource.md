---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScdDriUseCases", "CAAScrBase", "CATIA", "CAADriDetailSheet"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDetailSheetSource.htm"
converted: "2026-05-11T11:06:32.900077"
---

```
Option Explicit

' COPYRIGHT DASSAULT SYSTEMES 2001

' ***********************************************************************

' Purpose: Creates constraints between assembly Parts using Publications

' Assumptions: Looks for CAADriDetailSheet.CATDrawing in the DocView 

' Author: 

' Languages: VBScript

' Locales: English 

' CATIA Level: V5R7 

' ***********************************************************************

Sub 
CATMain()

 
' ----------------------------------------------------------- 

 
' Optional: allows to find the sample wherever it's installed

 dim 
sDocPath
 As 
String 
 sDocPath=CATIA.SystemService.Environ("CATDocView")

 If 
(Not CATIA.FileSystem.FolderExists(sDocPath))
 Then

 Err.Raise 9999,,"No Doc Path Defined"

 End If

 
' ----------------------------------------------------------- 

 
' Open the Drawing document 

 Dim 
oDoc
 As 
Document

 set 
oDoc = CATIA.Documents.Open(sDocPath & _
 "\online\CAAScdDriUseCases\samples\CAADriDetailSheet.CATDrawing")

' ------------

' Get the sheets collection of the drawing

' ------------

Dim 
oDrawingSheets
 As 
DrawingSheets

Set 
oDrawingSheets = oDoc.Sheets

' ------------

' Add the detail sheet with a default name to the sheets collection of the drawing

' ------------

MsgBox "Click OK to create the new sheet."

Dim 
oDrawingSheet
 As 
DrawingSheet

Set 
oDrawingSheet = oDrawingSheets.AddDetail("New Detail Sheet") 

' ------------

' Activate the detail sheet

' ------------

MsgBox "Click OK to activate the new detail sheet."
oDrawingSheet.Activate 

End Sub
```