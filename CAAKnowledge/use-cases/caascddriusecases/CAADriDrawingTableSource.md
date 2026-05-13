---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIA", "CAADriDrawingTable"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDrawingTableSource.htmmd"
converted: "2026-05-11T11:27:02.757884"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2002

' ***********************************************************************
'   Purpose:      This macro allows you to create a title block 
'                       from Drawing Table
'   Author: 
'   Languages:   VBScript
'   Locales:       English 
'   CATIA Level: V5R10 
' ***********************************************************************

```vbscript
Sub CATMain(#)

    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```vbscript
    CATIA.DisplayFileAlerts = False

    ' Optional: allows to find the sample wherever it's installed
```
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```

    ' Variables declaration
```vbscript
    Dim oDrwDocument As DrawingDocument
    Dim oDrwSheets As DrawingSheets
    Dim oDrwSheet As DrawingSheet
    Dim oDrwView As DrawingView
    Dim oDrwTables As DrawingTables
    Dim oDrwTable As DrawingTable
    
    ' Create a new drawing document
```
```vbscript
    Set oDrwDocument = CATIA.Documents.Add("Drawing")

    ' Set the drawing document standard
    oDrwDocument.Standard = catISO
```
    
    ' Retrieve the drawing document's sheets collection
```vbscript
    Set oDrwSheets = oDrwDocument.Sheets

    ' Retrieve the active sheet
```
```vbscript
    Set oDrwSheet = oDrwSheets.ActiveSheet

    ' Set the sheet properties
    oDrwSheet.PaperSize = catPaperA4
```
    oDrwSheet.Orientation = catPaperLandscape
    oDrwSheet.Scale2 = 1
    
    ' Retrieve the active view of the sheet
```vbscript
    Set oDrwView = oDrwSheet.Views.ActiveView
    ' Retrieve the view's tables collection
```
```vbscript
    Set oDrwTables = oDrwView.Tables
    
    ' Create a new drawing table
```
```vbscript
    Set oDrwTable = oDrwTables.Add(107, 70, 9, 9, 5, 20)
    
    ' Set the drawing table's name
    oDrwTable.Name = "Title Block"
```

    ' Do not update drawing table modifications
    oDrwTable.ComputeMode = CatTableComputeOFF

    ' Merge drawing table's cells
    oDrwTable.MergeCells 1, 1, 2, 2
    oDrwTable.MergeCells 1, 3, 1, 7
    oDrwTable.MergeCells 2, 3, 2, 7
    oDrwTable.MergeCells 4, 3, 1, 7
    oDrwTable.MergeCells 5, 4, 1, 5
    oDrwTable.MergeCells 6, 3, 2, 1
    oDrwTable.MergeCells 6, 4, 2, 5
    oDrwTable.MergeCells 6, 9, 2, 1
    oDrwTable.MergeCells 7, 1, 2, 1
    oDrwTable.MergeCells 7, 2, 2, 1
    oDrwTable.MergeCells 8, 3, 2, 1
    oDrwTable.MergeCells 8, 4, 2, 1
    oDrwTable.MergeCells 8, 5, 2, 1
    oDrwTable.MergeCells 8, 6, 2, 1
    oDrwTable.MergeCells 8, 7, 2, 1
    oDrwTable.MergeCells 8, 8, 2, 1
    oDrwTable.MergeCells 8, 9, 2, 1

```vbscript
    ' Set the drawing table's row sizes
    oDrwTable.SetRowSize 1, 20
```
    oDrwTable.SetRowSize 2, 4
    oDrwTable.SetRowSize 3, 5
    oDrwTable.SetRowSize 4, 7
    oDrwTable.SetRowSize 5, 5
    oDrwTable.SetRowSize 6, 7
    oDrwTable.SetRowSize 7, 2
    oDrwTable.SetRowSize 8, 3
    oDrwTable.SetRowSize 9, 7

```vbscript
    ' Set the drawing table's column sizes
    oDrwTable.SetColumnSize 1, 45
```
    oDrwTable.SetColumnSize 2, 20
    oDrwTable.SetColumnSize 3, 15
    oDrwTable.SetColumnSize 4, 15
    oDrwTable.SetColumnSize 5, 27
    oDrwTable.SetColumnSize 6, 18
    oDrwTable.SetColumnSize 7, 20
    oDrwTable.SetColumnSize 8, 15
    oDrwTable.SetColumnSize 9, 15
    
    ' Update drawing table modifications
    oDrwTable.ComputeMode = CatTableComputeON

```vbscript
    CATIA.ActiveWindow.ActiveViewer.Reframe 

End Sub

```

```vbscript
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2002

' ***********************************************************************
'   Purpose:      This macro allows you to create a title block 
'                       from Drawing Table
'   Author: 
'   Languages:   VBScript
'   Locales:       English 
'   CATIA Level: V5R10 
' ***********************************************************************

```vbscript
Sub CATMain(#)

    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```vbscript
    CATIA.DisplayFileAlerts = False

    ' Optional: allows to find the sample wherever it's installed
```
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```

    ' Variables declaration
```vbscript
    Dim oDrwDocument As DrawingDocument
    Dim oDrwSheets As DrawingSheets
    Dim oDrwSheet As DrawingSheet
    Dim oDrwView As DrawingView
    Dim oDrwTables As DrawingTables
    Dim oDrwTable As DrawingTable
    
    ' Create a new drawing document
```
```vbscript
    Set oDrwDocument = CATIA.Documents.Add(&quot;Drawing&quot;)

    ' Set the drawing document standard
    oDrwDocument.Standard = catISO
```
    
    ' Retrieve the drawing document's sheets collection
```vbscript
    Set oDrwSheets = oDrwDocument.Sheets

    ' Retrieve the active sheet
```
```vbscript
    Set oDrwSheet = oDrwSheets.ActiveSheet

    ' Set the sheet properties
    oDrwSheet.PaperSize = catPaperA4
```
    oDrwSheet.Orientation = catPaperLandscape
    oDrwSheet.Scale2 = 1
    
    ' Retrieve the active view of the sheet
```vbscript
    Set oDrwView = oDrwSheet.Views.ActiveView
    ' Retrieve the view's tables collection
```
```vbscript
    Set oDrwTables = oDrwView.Tables
    
    ' Create a new drawing table
```
```vbscript
    Set oDrwTable = oDrwTables.Add(107, 70, 9, 9, 5, 20)
    
    ' Set the drawing table's name
    oDrwTable.Name = &quot;Title Block&quot;
```

    ' Do not update drawing table modifications
    oDrwTable.ComputeMode = CatTableComputeOFF

    ' Merge drawing table's cells
    oDrwTable.MergeCells 1, 1, 2, 2
    oDrwTable.MergeCells 1, 3, 1, 7
    oDrwTable.MergeCells 2, 3, 2, 7
    oDrwTable.MergeCells 4, 3, 1, 7
    oDrwTable.MergeCells 5, 4, 1, 5
    oDrwTable.MergeCells 6, 3, 2, 1
    oDrwTable.MergeCells 6, 4, 2, 5
    oDrwTable.MergeCells 6, 9, 2, 1
    oDrwTable.MergeCells 7, 1, 2, 1
    oDrwTable.MergeCells 7, 2, 2, 1
    oDrwTable.MergeCells 8, 3, 2, 1
    oDrwTable.MergeCells 8, 4, 2, 1
    oDrwTable.MergeCells 8, 5, 2, 1
    oDrwTable.MergeCells 8, 6, 2, 1
    oDrwTable.MergeCells 8, 7, 2, 1
    oDrwTable.MergeCells 8, 8, 2, 1
    oDrwTable.MergeCells 8, 9, 2, 1

```vbscript
    ' Set the drawing table's row sizes
    oDrwTable.SetRowSize 1, 20
```
    oDrwTable.SetRowSize 2, 4
    oDrwTable.SetRowSize 3, 5
    oDrwTable.SetRowSize 4, 7
    oDrwTable.SetRowSize 5, 5
    oDrwTable.SetRowSize 6, 7
    oDrwTable.SetRowSize 7, 2
    oDrwTable.SetRowSize 8, 3
    oDrwTable.SetRowSize 9, 7

```vbscript
    ' Set the drawing table's column sizes
    oDrwTable.SetColumnSize 1, 45
```
    oDrwTable.SetColumnSize 2, 20
    oDrwTable.SetColumnSize 3, 15
    oDrwTable.SetColumnSize 4, 15
    oDrwTable.SetColumnSize 5, 27
    oDrwTable.SetColumnSize 6, 18
    oDrwTable.SetColumnSize 7, 20
    oDrwTable.SetColumnSize 8, 15
    oDrwTable.SetColumnSize 9, 15
    
    ' Update drawing table modifications
    oDrwTable.ComputeMode = CatTableComputeON

```vbscript
    CATIA.ActiveWindow.ActiveViewer.Reframe 

End Sub
```
```