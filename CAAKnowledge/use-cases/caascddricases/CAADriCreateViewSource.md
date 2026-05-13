---
title: "CAADriCreateView.CATScript"
category: "use-case"
module: "CAAScdDriUseCases"
tags: "["CATIA", "CAADriCreateView", "CAAScdDriUseCases"]"
source_file: "Doc/online/CAAScdDriUseCases/CAADriCreateViewSource.htm"
converted: "2026-05-11T17:31:51.043880"
---
tags: ["CATIA", "CAADriCreateView", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriCreateViewSource.htmmd"
converted: "2026-05-11T17:31:51.043880"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGTH DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Create A Drawing document with a front view and a projection view
    '   Assumtions:   Looks for MyPart.CATPart in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R6
    ' ***********************************************************************

```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
        ' -----------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String
```cpp
        sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```cpp
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
        ' Open the Part document
```cpp
        Dim oPartToDraw As PartDocument
        Set oPartToDraw = CATIA.Documents.Open(sDocPath & _
```
```

```

```

                 "/online/CAAScdDriUseCases/samples/Cube.CATPart")
```vbscript
```vbscript
```vbscript
        ' Create a drawing document: it becomes the active document.
```cpp
        Dim oDrawing As DrawingDocument
        Set oDrawing = CATIA.Documents.Add("Drawing")
        ' Retrieve the active sheet
```
```vbscript
        Dim oSheet As DrawingSheet
        Set oSheet = oDrawing.Sheets.ActiveSheet
        ' Create a view called "Front View" in this sheet
```
```vbscript
        Dim oFrontView As DrawingView
        Set oFrontView = oSheet.Views.Add("Front View")
        ' Retrieve it generative behavior
```
```vbscript
        Dim oFrontViewGB As DrawingViewGenerativeBehavior
        Set oFrontViewGB = oFrontView.GenerativeBehavior
        ' Declare the part to draw in this front view
```
```

```

```

```vbscript
```vbscript
Dim oFrontViewGB As DrawingViewGenerativeBehavior
```vbscript
```
```vbscript
```vbscript
Set oFrontViewGB = oFrontView.GenerativeBehavior
' Declare the part to draw in this front view
```
        oFrontViewGB.Document = oPartToDraw
        ' Define this view as a front view, with the XY plane (in oPartToDraw) as projection plane
```

```

        oFrontViewGB.DefineFrontView 1, 0, 0, 0, 1, 0
```vbscript
```vbscript
        ' Position the View in the Sheet
        oFrontView.x = 300
        oFrontView.y = 150
        ' Update the view
```

```

        oFrontViewGB.Update

```

```vbscript
```vbscript
    End Sub

```
```
