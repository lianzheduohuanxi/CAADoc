---
title: "CAAPriPocket.CATScript"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScdPriUseCases", "CATIA", "CAAPriPocket"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPocketSource.md"
converted: "2026-05-11T17:31:51.233955"
---

    Option Explicit
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

                     "\online\CAAScdPriUseCases\samples\CAAPriPocket.CATPart")
    
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
    Set oSketch = oBody.Sketches.Item  ( "Sketch.2" ) 
    ' ------------
    ' Create the pocket with a default first limit
    ' ------------
```

    MsgBox "Click OK to create the pocket."
    Dim oPocket As Pocket
    Set oPocket= oPart.ShapeFactory.AddNewPocket    ( oSketch, 20.000000 ) 
```vbscript
    ' ------------
    ' Update the part
    ' ------------
```

    oPart.Update 
```vbscript
    ' ------------
    ' Define the pocket first limit
    ' ------------
```

    MsgBox "Click OK to set the pocket first limit to 30mm."
    oPocket.FirstLimit.Dimension.Value = 30.000000
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