---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CAAScdPriUseCases", "CATIA", "CAAPriPad"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriPadSource.htmmd"
converted: "2026-05-11T11:27:02.722533"
---

Option Explicit
' COPYRIGTH DASSAULT SYSTEMES 2001

' ***********************************************************************
'   Purpose:      Creates constraints between assembly Parts using Publications
'   Assumtions:   Looks for CAAPriPad.CATPart in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R7 
' ***********************************************************************

```vbscript
Sub CATMain(#)

```

    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ----------------------------------------------------------- 

    ' Open the Part document 
```vbscript
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sDocPath & _
                 "/online/CAAScdPriUseCases/samples/CAAPriPad.CATPart")
```

' ------------
' Get the part
' ------------
```vbscript
Dim oPart As Part
Set oPart = oDoc.Part

```

' ------------
' Get the part body in the part
' ------------
```vbscript
Dim oBody As Body
Set oBody = oPart.Bodies.Item  ( "PartBody" ) 

```

' ------------
' Get the sketch in the body
' ------------
```vbscript
Dim oSketch As Sketch
Set oSketch = oBody.Sketches.Item  ( "Sketch.1" ) 

```

' ------------
' Create the pad with a default first limit
' ------------
```vbscript
MsgBox "Click OK to create the pad."
Dim oPad As Pad
Set oPad = oPart.ShapeFactory.AddNewPad  ( oSketch, 20.000000 ) 

```

' ------------
' Update the part
' ------------
oPart.Update 

' ------------
' Define the pad first limit
' ------------
```vbscript
MsgBox "Click OK to set the pad first limit to 40mm."
oPad.FirstLimit.Dimension.Value = 40.000000
```

' ------------
' Update the part
' ------------
oPart.Update 

' ------------
' Define the pad to be symmetric relative to the sketch plane
' ------------
```vbscript
MsgBox "Click OK to mirror the extrusion offset."
oPad.IsSymmetric = True
```

' ------------
' Update the part
' ------------
oPart.Update 

```vbscript
End Sub

```

```vbscript
Option Explicit
' COPYRIGTH DASSAULT SYSTEMES 2001

' ***********************************************************************
'   Purpose:      Creates constraints between assembly Parts using Publications
'   Assumtions:   Looks for CAAPriPad.CATPart in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R7 
' ***********************************************************************

```vbscript
Sub CATMain(#)

```

    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```vbscript
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
    ' ----------------------------------------------------------- 

    ' Open the Part document 
```vbscript
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sDocPath &amp; _
                 &quot;/online/CAAScdPriUseCases/samples/CAAPriPad.CATPart&quot;)
```

' ------------
' Get the part
' ------------
```vbscript
Dim oPart As Part
Set oPart = oDoc.Part

```

' ------------
' Get the part body in the part
' ------------
```vbscript
Dim oBody As Body
Set oBody = oPart.Bodies.Item  ( &quot;PartBody&quot; ) 

```

' ------------
' Get the sketch in the body
' ------------
```vbscript
Dim oSketch As Sketch
Set oSketch = oBody.Sketches.Item  ( &quot;Sketch.1&quot; ) 

```

' ------------
' Create the pad with a default first limit
' ------------
```vbscript
MsgBox &quot;Click OK to create the pad.&quot;
Dim oPad As Pad
Set oPad = oPart.ShapeFactory.AddNewPad  ( oSketch, 20.000000 ) 

```

' ------------
' Update the part
' ------------
oPart.Update 

' ------------
' Define the pad first limit
' ------------
```vbscript
MsgBox &quot;Click OK to set the pad first limit to 40mm.&quot;
oPad.FirstLimit.Dimension.Value = 40.000000
```

' ------------
' Update the part
' ------------
oPart.Update 

' ------------
' Define the pad to be symmetric relative to the sketch plane
' ------------
```vbscript
MsgBox &quot;Click OK to mirror the extrusion offset.&quot;
oPad.IsSymmetric = True
```

' ------------
' Update the part
' ------------
oPart.Update 

```vbscript
End Sub
```
```