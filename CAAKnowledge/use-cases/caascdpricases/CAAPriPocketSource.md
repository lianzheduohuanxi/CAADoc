---
```vbscript
title: "CAAPriPocket.CATScript"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPocket"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPocketSource.htmmd"
converted: "2026-05-11T17:31:51.233955"
```

---
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPocket"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPocketSource.htmmd"
converted: "2026-05-11T17:31:51.233955"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2001
    ' ***********************************************************************
    '   Purpose:      Creates constraints between assembly Parts using Publications
    '   Assumtions:   Looks for CAAPriPocket.CATPart in the DocView
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
        ' Open the Part document
```vbscript
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sDocPath & _
```
```

```

```

                     "/online/CAAScdPriUseCases/samples/CAAPriPocket.CATPart")

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the part
    ' ------------
```

```

```

```vbscript
```vbscript
    Dim oPart As Part
```vbscript
```
```vbscript
    Set oPart = oDoc.Part
```
```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the part body in the part
    ' ------------
```vbscript
    Dim oBody As Body
    Set oBody = oPart.Bodies.Item  ( "PartBody" )
    ' ------------
```
    ' Get the sketch in the body
    ' ------------
```vbscript
    Dim oSketch As Sketch
    Set oSketch = oBody.Sketches.Item  ( "Sketch.2" )
    ' ------------
```
    ' Create the pocket with a default first limit
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Create the pocket with a default first limit
' ------------
```

```

```vbscript
    MsgBox "Click OK to create the pocket."
    Dim oPocket As Pocket
```vbscript
```
```vbscript
    Set oPocket= oPart.ShapeFactory.AddNewPocket    ( oSketch, 20.000000 )
```
```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Update the part
' ------------
```

```

    oPart.Update
```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Define the pocket first limit
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Define the pocket first limit
' ------------
```

```

```vbscript
    MsgBox "Click OK to set the pocket first limit to 30mm."
    oPocket.FirstLimit.Dimension.Value = 30.000000
```
```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Update the part
' ------------
```

```

    oPart.Update

```

```vbscript
```vbscript
    End Sub

```
```
