---
```vbscript
title: "CAADriDetailSheet.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriDetailSheet", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDetailSheetSource.htmmd"
converted: "2026-05-11T17:31:51.048875"
```

---
tags: ["CAADriDetailSheet", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDetailSheetSource.htmmd"
converted: "2026-05-11T17:31:51.048875"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2001
    ' ***********************************************************************
    '   Purpose:      Creates constraints between assembly Parts using Publications
    '   Assumptions:   Looks for CAADriDetailSheet.CATDrawing in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R7
    ' ***********************************************************************

```

```

```

```vbscript
```vbscript
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```vbscript
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
        End If
```

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Open the Drawing document
```vbscript
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sDocPath & _
```
```

```

```

                     "/online/CAAScdDriUseCases/samples/CAADriDetailSheet.CATDrawing")

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the sheets collection of the drawing
    ' ------------
```

```

```

```vbscript
```vbscript
    Dim oDrawingSheets As DrawingSheets
```vbscript
```
```vbscript
    Set oDrawingSheets = oDoc.Sheets
```
```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Add the detail sheet with a default name to the sheets collection of the drawing
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Add the detail sheet with a default name to the sheets collection of the drawing
' ------------
```

```

```vbscript
    MsgBox "Click OK to create the new sheet."
    Dim oDrawingSheet As DrawingSheet
```vbscript
```
```vbscript
    Set oDrawingSheet = oDrawingSheets.AddDetail("New Detail Sheet")
```
```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Activate the detail sheet
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Activate the detail sheet
' ------------
```

```

```vbscript
    MsgBox "Click OK to activate the new detail sheet."
    oDrawingSheet.Activate
```

```

```vbscript
```vbscript
    End Sub

```
```
