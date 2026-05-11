---
title: "CAAPriPad.CATScript"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPad"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPadSource.htm"
converted: "2026-05-11T17:31:51.226971"
---

    Option Explicit
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
        ' Open the Part document 
        Dim oDoc As Document
        set oDoc = CATIA.Documents.Open(sDocPath & _
```

                     "\online\CAAScdPriUseCases\samples\CAAPriPad.CATPart")
    
```

```vbscript
    ' ------------
    ' Get the part
    ' ------------
```

```vbscript
    Dim oPart As Part
    Set oPart = oDoc.Part
```vbscript
    ' ------------
    ' Get the part body in the part
    ' ------------
    Dim oBody As Body
    Set oBody = oPart.Bodies.Item  ( "PartBody" ) 
    ' ------------
    ' Get the sketch in the body
    ' ------------
    Dim oSketch As Sketch
    Set oSketch = oBody.Sketches.Item  ( "Sketch.1" ) 
    ' ------------
    ' Create the pad with a default first limit
    ' ------------
```

    MsgBox "Click OK to create the pad."
    Dim oPad As Pad
    Set oPad = oPart.ShapeFactory.AddNewPad  ( oSketch, 20.000000 ) 
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
```vbscript
    ' ------------
    ' Define the pad first limit
    ' ------------
```

    MsgBox "Click OK to set the pad first limit to 40mm."
    oPad.FirstLimit.Dimension.Value = 40.000000
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
```vbscript
    ' ------------
    ' Define the pad to be symmetric relative to the sketch plane
    ' ------------
```

    MsgBox "Click OK to mirror the extrusion offset."
    oPad.IsSymmetric = True
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
    
```

```vbscript
    End Sub
    
```

```