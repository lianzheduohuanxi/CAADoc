---
```vbscript
title: "CAAPriPad.CATScript"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPad"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPadSource.htmmd"
converted: "2026-05-11T17:31:51.226971"
```

---
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPad"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPadSource.htmmd"
converted: "2026-05-11T17:31:51.226971"
    Option Explicit

```vbscript
```vbscript
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2001
    ' ***********************************************************************
    '   Purpose:      Creates constraints between assembly Parts using Publications
    '   Assumtions:   Looks for CAAPriPad.CATPart in the DocView
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

                     "/online/CAAScdPriUseCases/samples/CAAPriPad.CATPart")

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
    Set oSketch = oBody.Sketches.Item  ( "Sketch.1" )
    ' ------------
```
    ' Create the pad with a default first limit
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Create the pad with a default first limit
' ------------
```

```

```vbscript
    MsgBox "Click OK to create the pad."
    Dim oPad As Pad
```vbscript
```
```vbscript
    Set oPad = oPart.ShapeFactory.AddNewPad  ( oSketch, 20.000000 )
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
    ' Define the pad first limit
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Define the pad first limit
' ------------
```

```

```vbscript
    MsgBox "Click OK to set the pad first limit to 40mm."
    oPad.FirstLimit.Dimension.Value = 40.000000
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
    ' Define the pad to be symmetric relative to the sketch plane
    ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' Define the pad to be symmetric relative to the sketch plane
' ------------
```

```

```vbscript
    MsgBox "Click OK to mirror the extrusion offset."
    oPad.IsSymmetric = True
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
