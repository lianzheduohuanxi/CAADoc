---
```vbscript
title: "CAADriSheet.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CATIA", "CAADriSheet", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSheetSource.htm"
converted: "2026-05-11T17:31:51.107736"
```

---
tags: ["CATIA", "CAADriSheet", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSheetSource.htm"
converted: "2026-05-11T17:31:51.107736"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2001
    ' ***********************************************************************
    '   Purpose:      Creates constraints between assembly Parts using Publications
    '   Assumptions:   Looks for CAADriSheet.CATDrawing in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R7
    ' ***********************************************************************

```

```

```

```vbscript
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```

```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
        End If
```

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Open the Drawing document
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sDocPath & _
```

```

```

                     "\online\CAAScdDriUseCases\samples\CAADriSheet.CATDrawing")

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
    Dim oDrawingSheets As DrawingSheets
```vbscript
    Set oDrawingSheets = oDoc.Sheets
```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Add the sheet with a default name to the sheets collection of the drawing
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Add the sheet with a default name to the sheets collection of the drawing
' ------------
```

```

    MsgBox "Click OK to create the new sheet."
    Dim oDrawingSheet As DrawingSheet
```vbscript
    Set oDrawingSheet = oDrawingSheets.Add("New Sheet")
```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Activate the sheet
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Activate the sheet
' ------------
```

```

    MsgBox "Click OK to activate the new sheet."
    oDrawingSheet.Activate

```

```vbscript
    End Sub

```
