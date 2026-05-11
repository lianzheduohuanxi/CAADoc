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

    Sub CATMain()

```vbscript
        ' ----------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```

```vbscript
        ' ----------------------------------------------------------- 
        ' Open the Drawing document 
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sDocPath & _
```

                     "\online\CAAScdDriUseCases\samples\CAADriSheet.CATDrawing")

```vbscript
    ' ------------
    ' Get the sheets collection of the drawing
    ' ------------
```

```vbscript
    Dim oDrawingSheets As DrawingSheets
    Set oDrawingSheets = oDoc.Sheets
```

```vbscript
    ' ------------
    ' Add the sheet with a default name to the sheets collection of the drawing
    ' ------------
```

```vbscript
' ------------
' Add the sheet with a default name to the sheets collection of the drawing
' ------------
    MsgBox "Click OK to create the new sheet."
    Dim oDrawingSheet As DrawingSheet
    Set oDrawingSheet = oDrawingSheets.Add("New Sheet") 
```

```vbscript
    ' ------------
    ' Activate the sheet
    ' ------------
```

```vbscript
' ------------
' Activate the sheet
' ------------
    MsgBox "Click OK to activate the new sheet."
    oDrawingSheet.Activate 

```

    End Sub
