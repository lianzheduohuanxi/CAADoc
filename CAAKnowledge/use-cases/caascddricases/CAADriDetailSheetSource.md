---
title: "CAADriDetailSheet.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAADriDetailSheet", "CATIA", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriDetailSheetSource.md"
converted: "2026-05-11T17:31:51.048875"
---

    Option Explicit
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

    
```vbscript
    Sub CATMain()
    
```

```vbscript
        ' ----------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```vbscript
        ' ----------------------------------------------------------- 
        ' Open the Drawing document 
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sDocPath & _
```

                     "\online\CAAScdDriUseCases\samples\CAADriDetailSheet.CATDrawing")
    
```

```vbscript
    ' ------------
    ' Get the sheets collection of the drawing
    ' ------------
```

```vbscript
    Dim oDrawingSheets As DrawingSheets
    Set oDrawingSheets = oDoc.Sheets
```vbscript
    ' ------------
    ' Add the detail sheet with a default name to the sheets collection of the drawing
    ' ------------
```

    MsgBox "Click OK to create the new sheet."
    Dim oDrawingSheet As DrawingSheet
    Set oDrawingSheet = oDrawingSheets.AddDetail("New Detail Sheet") 
```vbscript
    ' ------------
    ' Activate the detail sheet
    ' ------------
```

    MsgBox "Click OK to activate the new detail sheet."
    oDrawingSheet.Activate 
    
```

```vbscript
    End Sub
    
```

```