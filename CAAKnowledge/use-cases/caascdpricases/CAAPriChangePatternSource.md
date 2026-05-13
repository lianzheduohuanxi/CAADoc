---
title: "CAAPriPatternDescription.CATScript"
category: "use-case"
module: "CAAScdPriUseCases"
tags: "["CATIA", "CAAPriChangePattern", "CAAPriPatternDescription"]"
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangePatternSource.htm"
converted: "2026-05-11T17:31:51.213996"
---
tags: ["CATIA", "CAAPriChangePattern", "CAAPriPatternDescription"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangePatternSource.htmmd"
converted: "2026-05-11T17:31:51.213996"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGTH DASSAULT SYSTEMES 2004
    ' ***********************************************************************
    '   Purpose:      Changes pattern description
    '   Assumptions:   Looks for CAAPriChangePattern.md in the DocView
    '   Author:
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R14
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
    Dim oPartDocument As PartDocument
```vbscript
```
```vbscript
```vbscript
    Dim oPart As Part
    Dim oSelection As Selection
    Dim InputObjectType(0) As String
    Dim oStatus as String
    Dim oCircularPattern as CircPattern
```
```

```

```

```vbscript
```vbscript
```vbscript
    ' ------------
    ' Get the part document
    ' ------------
```cpp
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
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
```vbscript
' Set the selection type
' ------------
```
```

    InputObjectType(0) = "CircPattern"
```

```

```vbscript
```vbscript
```vbscript
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
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
```vbscript
' Set the circular pattern instance number
' ------------
```
```

```

    oCircularPattern.AngularRepartition.InstancesCount.Value = 6
```

```vbscript
```vbscript
```vbscript
    ' ------------
```vbscript
    ' Set the circular pattern instance as Unequal Angular Spacing mode
    ' ------------
```
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
```vbscript
' Set the circular pattern instance as Unequal Angular Spacing mode
' ------------
```
    oCircularPattern.CircularPatternParameters = catUnequalAngularSpacing
```

```

    oCircularPattern.SetUnequalStep 6
```

```vbscript
```vbscript
```vbscript
    ' ------------
```vbscript
    ' Set the circular pattern Unequal Angular Spacing
    ' ------------
```
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
```vbscript
' Set the circular pattern Unequal Angular Spacing
' ------------
```
```

```

    oCircularPattern.SetInstanceAngularSpacing 2, 30.000000
    oCircularPattern.SetInstanceAngularSpacing 3, 75.000000
    oCircularPattern.SetInstanceAngularSpacing 4, 75.000000
    oCircularPattern.SetInstanceAngularSpacing 5, 30.000000
    oCircularPattern.SetInstanceAngularSpacing 6, 75.000000
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
