---
```vbscript
title: "CAADriDuplicateAView.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriDuplicateAView", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDuplicateAViewSource.htm"
converted: "2026-05-11T17:31:51.074314"
```

---
tags: ["CAADriDuplicateAView", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDuplicateAViewSource.htm"
converted: "2026-05-11T17:31:51.074314"
    Option Explicit

```vbscript
```vbscript
```vbscript
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
```

```

```

    Sub CATMain()
```vbscript
```vbscript
        ' Set the CATIA popup file alerts to False
        ' It prevents to stop the macro at each alert during its execution

```

```

```vbscript
        CATIA.DisplayFileAlerts = False
```

```vbscript
```vbscript
```vbscript
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
        ' Open the Drawing document
        Dim oDrawingSource As DrawingDocument
        Set oDrawingSource = CATIA.Documents.Open(sDocPath & _
```

```

```

                 "\online\CAAScdDriUseCases\samples\CAADriDuplicateAView.CATDrawing")
```vbscript
```vbscript
```vbscript
        ' Fit in window the opened document
        CATIA.ActiveWindow.ActiveViewer.Reframe
        ' Retrieve the sheet containing the view to be duplicated
        Dim oSheetSource As DrawingSheet
        Set oSheetSource = oDrawingSource.Sheets.Item("Sheet.1")
        ' Retrieve the view to be duplicated
        Dim oViewSource As DrawingView
        Set oViewSource = oSheetSource.Views.Item("Front view")
        ' Create an object of selection for the source document
        Dim oSelectionSource As Selection
        Set oSelectionSource = oDrawingSource.Selection
        ' Clear the selection
```

```

```

```vbscript
Dim oSelectionSource As Selection
```vbscript
```vbscript
Set oSelectionSource = oDrawingSource.Selection
' Clear the selection
```

```

        oSelectionSource.Clear
```vbscript
        ' Add the view to be duplicated in the selection
```

        oSelectionSource.Add oViewSource
```vbscript
        ' Copy the view
```

        oSelectionSource.Copy
```vbscript
        ' Clear the selection
```

        oSelectionSource.Clear
```

```vbscript
```vbscript
```vbscript
        ' Create the Drawing document where the view will be pasted
        Dim oDrawingTarget As DrawingDocument
        Set oDrawingTarget = CATIA.Documents.Add("Drawing")
        ' Retrieve the where the view will be pasted
        Dim oSheetTarget As DrawingSheet
        Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
        ' Set the sheet paper size
```

```

```

```vbscript
Dim oSheetTarget As DrawingSheet
```vbscript
```vbscript
Set oSheetTarget = oDrawingTarget.Sheets.Item("Sheet.1")
' Set the sheet paper size
        oSheetTarget.PaperSize = catPaperA0
```

```

```

```vbscript
```vbscript
```vbscript
        ' Create an object of selection for the source document
        Dim oSelectionTarget As Selection
        Set oSelectionTarget = oDrawingTarget.Selection
        ' Clear the selection
```

```

```

```vbscript
Dim oSelectionTarget As Selection
```vbscript
```vbscript
Set oSelectionTarget = oDrawingTarget.Selection
' Clear the selection
```

```

        oSelectionTarget.Clear
```vbscript
        ' Add the sheet where the view will be pasted in the selection
```

        oSelectionTarget.Add oSheetTarget
```vbscript
        ' Paste the clipboard
```

        oSelectionTarget.Paste
```vbscript
        ' Clear the selection
```

        oSelectionTarget.Clear
```

```vbscript
```vbscript
```vbscript
        ' Fit in window the active document
        CATIA.ActiveWindow.ActiveViewer.Reframe
        ' Clear the variables
        Set oSelectionTarget = Nothing
        Set oSheetTarget = Nothing
        Set oDrawingTarget = Nothing
        Set oSelectionSource = Nothing
        Set oViewSource = Nothing
        Set oSelectionSource = Nothing
        Set oDrawingSource = Nothing
```

```

```

```vbscript
    End Sub

```
