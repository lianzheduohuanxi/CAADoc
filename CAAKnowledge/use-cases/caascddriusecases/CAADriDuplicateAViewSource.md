---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIA", "CAADriDuplicateAView", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDuplicateAViewSource.htmmd"
converted: "2026-05-11T11:27:02.740718"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2003

' ***********************************************************************
'   Purpose:      This macro allows you to copy a view from an 
'                      existing drawing document into a new drawing
'                      document
'   Author: 
'   Languages:   VBScript
'   Locales:       English 
'   CATIA Level: V5R11
' ***********************************************************************

```cpp
Sub CATMain(#)

    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```cpp
    CATIA.DisplayFileAlerts = False

    ' Optional: allows to find the sample wherever it's installed
```
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```

    ' Open the Drawing document
```cpp
    Dim oDrawingSource As DrawingDocument
    Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
             "/online/CAAScdDriUseCases/samples/CAADriDuplicateAView.CATDrawing")
```
    
    ' Fit in window the opened document
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
    
    ' Retrieve the sheet containing the view to be duplicated
```
```vbscript
    Dim oSheetSource As DrawingSheet
    Set oSheetSource = oDrawingSource.Sheets.Item("Sheet.1")
    
    ' Retrieve the view to be duplicated
```
```vbscript
    Dim oViewSource As DrawingView
    Set oViewSource = oSheetSource.Views.Item("Front view")
    
    ' Create an object of selection for the source document
```
```vbscript
    Dim oSelectionSource As Selection
    Set oSelectionSource = oDrawingSource.Selection
    
```
    
    ' Clear the selection
    oSelectionSource.Clear
    ' Add the view to be duplicated in the selection
    oSelectionSource.Add oViewSource
    ' Copy the view
    oSelectionSource.Copy
    ' Clear the selection
    oSelectionSource.Clear
    
    ' Create the Drawing document where the view will be pasted
```cpp
    Dim oDrawingTarget As DrawingDocument
    Set oDrawingTarget = CATIA.Documents.Add("Drawing")
    
    ' Retrieve the where the view will be pasted
```
```vbscript
    Dim oSheetTarget As DrawingSheet
    Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
    
    ' Set the sheet paper size
    oSheetTarget.PaperSize = catPaperA0
```
    
    ' Create an object of selection for the source document
```vbscript
    Dim oSelectionTarget As Selection
    Set oSelectionTarget = oDrawingTarget.Selection
    
```
    
    ' Clear the selection
    oSelectionTarget.Clear
    ' Add the sheet where the view will be pasted in the selection
    oSelectionTarget.Add oSheetTarget
    ' Paste the clipboard
    oSelectionTarget.Paste
    ' Clear the selection
    oSelectionTarget.Clear

    ' Fit in window the active document    
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
    
    ' Clear the variables
```
```vbscript
    Set oSelectionTarget = Nothing
    Set oSheetTarget = Nothing
    Set oDrawingTarget = Nothing
    Set oSelectionSource = Nothing
    Set oViewSource = Nothing
    Set oSelectionSource = Nothing
    Set oDrawingSource = Nothing
    
End Sub

```

```vbscript
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2003

' ***********************************************************************
'   Purpose:      This macro allows you to copy a view from an 
'                      existing drawing document into a new drawing
'                      document
'   Author: 
'   Languages:   VBScript
'   Locales:       English 
'   CATIA Level: V5R11
' ***********************************************************************

```cpp
Sub CATMain(#)

    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```cpp
    CATIA.DisplayFileAlerts = False

    ' Optional: allows to find the sample wherever it's installed
```
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```

    ' Open the Drawing document
```cpp
    Dim oDrawingSource As DrawingDocument
    Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
             "/online/CAAScdDriUseCases/samples/CAADriDuplicateAView.CATDrawing")
```
    
    ' Fit in window the opened document
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
    
    ' Retrieve the sheet containing the view to be duplicated
```
```vbscript
    Dim oSheetSource As DrawingSheet
    Set oSheetSource = oDrawingSource.Sheets.Item("Sheet.1")
    
    ' Retrieve the view to be duplicated
```
```vbscript
    Dim oViewSource As DrawingView
    Set oViewSource = oSheetSource.Views.Item("Front view")
    
    ' Create an object of selection for the source document
```
```vbscript
    Dim oSelectionSource As Selection
    Set oSelectionSource = oDrawingSource.Selection
    
```
    
    ' Clear the selection
    oSelectionSource.Clear
    ' Add the view to be duplicated in the selection
    oSelectionSource.Add oViewSource
    ' Copy the view
    oSelectionSource.Copy
    ' Clear the selection
    oSelectionSource.Clear
    
    ' Create the Drawing document where the view will be pasted
```cpp
    Dim oDrawingTarget As DrawingDocument
    Set oDrawingTarget = CATIA.Documents.Add("Drawing")
    
    ' Retrieve the where the view will be pasted
```
```vbscript
    Dim oSheetTarget As DrawingSheet
    Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
    
    ' Set the sheet paper size
    oSheetTarget.PaperSize = catPaperA0
```
    
    ' Create an object of selection for the source document
```vbscript
    Dim oSelectionTarget As Selection
    Set oSelectionTarget = oDrawingTarget.Selection
    
```
    
    ' Clear the selection
    oSelectionTarget.Clear
    ' Add the sheet where the view will be pasted in the selection
    oSelectionTarget.Add oSheetTarget
    ' Paste the clipboard
    oSelectionTarget.Paste
    ' Clear the selection
    oSelectionTarget.Clear

    ' Fit in window the active document    
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
    
    ' Clear the variables
```
```vbscript
    Set oSelectionTarget = Nothing
    Set oSheetTarget = Nothing
    Set oDrawingTarget = Nothing
    Set oSelectionSource = Nothing
    Set oViewSource = Nothing
    Set oSelectionSource = Nothing
    Set oDrawingSource = Nothing
    
End Sub
```
```