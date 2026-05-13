---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CAAPriPatternDescription", "CATIA", "CAAPriChangePattern"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangePatternSource.htmmd"
converted: "2026-05-11T11:27:02.715873"
---

Option Explicit
' COPYRIGTH DASSAULT SYSTEMES 2004

' ***********************************************************************
'   Purpose:      Changes pattern description
'   Assumptions:   Looks for CAAPriChangePattern.htm in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R14
' ***********************************************************************

```vbscript
Sub CATMain(#)

Dim oPartDocument As PartDocument
Dim oPart As Part
Dim oSelection As Selection
Dim InputObjectType(0) As String
Dim oStatus as String
Dim oCircularPattern as CircPattern

```

' ------------
' Get the part document
' ------------
```vbscript
Set oPartDocument = CATIA.ActiveDocument
' ------------
```
' Get the part
' ------------
```vbscript
Set oPart = oPartDocument.Part
' ------------
```
' Get the selection
' ------------
```vbscript
Set oSelection = oPartDocument.Selection
' ------------
```
```vbscript
' Set the selection type
' ------------
```
InputObjectType(0) = "CircPattern"
' ------------
' Get the status
' ------------
oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a circular pattern", True )
' ------------
' Get the object in the selection
' ------------
```vbscript
Set oCircularPattern = oSelection.Item(1).Value
' ------------
```
```vbscript
' Set the circular pattern instance number
' ------------
```
oCircularPattern.AngularRepartition.InstancesCount.Value = 6
' ------------
```vbscript
' Set the circular pattern instance as Unequal Angular Spacing mode
' ------------
```
oCircularPattern.CircularPatternParameters = catUnequalAngularSpacing
oCircularPattern.SetUnequalStep 6
' ------------
```vbscript
' Set the circular pattern Unequal Angular Spacing
' ------------
```
oCircularPattern.SetInstanceAngularSpacing 2, 30.000000
oCircularPattern.SetInstanceAngularSpacing 3, 75.000000
oCircularPattern.SetInstanceAngularSpacing 4, 75.000000
oCircularPattern.SetInstanceAngularSpacing 5, 30.000000
oCircularPattern.SetInstanceAngularSpacing 6, 75.000000
' ------------
' Update the part
' ------------
oPart.Update 

```vbscript
End Sub

```

```vbscript
Option Explicit
' COPYRIGTH DASSAULT SYSTEMES 2004

' ***********************************************************************
'   Purpose:      Changes pattern description
'   Assumptions:   Looks for CAAPriChangePattern.htm in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R14
' ***********************************************************************

```vbscript
Sub CATMain(#)

Dim oPartDocument As PartDocument
Dim oPart As Part
Dim oSelection As Selection
Dim InputObjectType(0) As String
Dim oStatus as String
Dim oCircularPattern as CircPattern

```

' ------------
' Get the part document
' ------------
```vbscript
Set oPartDocument = CATIA.ActiveDocument
' ------------
```
' Get the part
' ------------
```vbscript
Set oPart = oPartDocument.Part
' ------------
```
' Get the selection
' ------------
```vbscript
Set oSelection = oPartDocument.Selection
' ------------
```
```vbscript
' Set the selection type
' ------------
```
InputObjectType(0) = &quot;CircPattern&quot;
' ------------
' Get the status
' ------------
oStatus = oSelection.SelectElement2 ( InputObjectType, &quot;Select a circular pattern&quot;, True )
' ------------
' Get the object in the selection
' ------------
```vbscript
Set oCircularPattern = oSelection.Item(1).Value
' ------------
```
```vbscript
' Set the circular pattern instance number
' ------------
```
oCircularPattern.AngularRepartition.InstancesCount.Value = 6
' ------------
```vbscript
' Set the circular pattern instance as Unequal Angular Spacing mode
' ------------
```
oCircularPattern.CircularPatternParameters = catUnequalAngularSpacing
oCircularPattern.SetUnequalStep 6
' ------------
```vbscript
' Set the circular pattern Unequal Angular Spacing
' ------------
```
oCircularPattern.SetInstanceAngularSpacing 2, 30.000000
oCircularPattern.SetInstanceAngularSpacing 3, 75.000000
oCircularPattern.SetInstanceAngularSpacing 4, 75.000000
oCircularPattern.SetInstanceAngularSpacing 5, 30.000000
oCircularPattern.SetInstanceAngularSpacing 6, 75.000000
' ------------
' Update the part
' ------------
oPart.Update 

```vbscript
End Sub
```
```