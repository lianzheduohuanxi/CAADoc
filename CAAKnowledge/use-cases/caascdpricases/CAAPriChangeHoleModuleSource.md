---
title: "CAAPriChangeHoleModule.bas"
category: "use-case"
module: "CAAScdPriUseCases"
tags: "["CAAPriChangeHoleModule", "CATIA", "CAAPriChangeHoleForm", "CAAPriChangeHoleVBA"]"
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleModuleSource.htm"
converted: "2026-05-11T17:31:51.194040"
---
tags: ["CAAPriChangeHoleModule", "CATIA", "CAAPriChangeHoleForm", "CAAPriChangeHoleVBA"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleModuleSource.htmmd"
converted: "2026-05-11T17:31:51.194040"
    Option Explicit

```vbscript
```vbscript
```cpp
    ' COPYRIGTH DASSAULT SYSTEMES 2004
    ' ***********************************************************************
    '   Purpose:      Changes hole description
    '   Assumptions:   Looks for CAAPriChangeHoleVBA.md in the DocView
    '   Author:
    '   Languages:    MS VBA
    '   Locales:      English
    '   CATIA Level:  V5R13

```

```

```vbscript
    Public oPartDocument As PartDocument
    Public i As Long
    Public sDocPath As String
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
```cpp
    sDocPath = CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```

```

```vbscript
```vbscript
      Err.Raise 9999, , "No Doc Path Defined"
```vbscript
```
    End If
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' ------------
    ' Get the part document
    ' ------------
```cpp
    Set oPartDocument = CATIA.ActiveDocument
    ' ------------
```
    ' Test the selection content
    ' ------------
    If oPartDocument.Selection.Count = 0 Then
        ' ------------
        ' The selection content is empty, the macro ends
        ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' ------------
' The selection content is empty, the macro ends
' ------------
```

```

```vbscript
        MsgBox "Select the holes you wish to transform before running the macro.", vbOKOnly, "Warning"
    Else
```
```

```vbscript
```vbscript
```vbscript
        ' ------------
        ' The selection content is not empty
        ' Show the dialog box
        ' ------------
```

```

```

```vbscript
```vbscript
```vbscript
' The selection content is not empty
' Show the dialog box
' ------------
```

```

        CAAPriChangeHoleForm.Show
```vbscript
    End If

```

```

```vbscript
```vbscript
    End Sub

End Sub
    Public Function CatObjectExistsInSelection(CatSelection As Selection, CatObjectName As String, CatObject As Object) As Boolean

```
```

```vbscript
    On Error Resume Next

```vbscript
```
```vbscript
    Set CatObject = CatSelection.FindObject(CatObjectName)
```vbscript
```
```vbscript
    CatObjectExistsInSelection = (Err.Number = 0)
    Err.Clear

```

```

```

```vbscript
```vbscript
    End Function

    Public Function ParameterExists(ItemIndex As String, ItemCollection As Object) As Boolean

```
```

```vbscript
```vbscript
    Dim TmpItem As Variant
    On Error Resume Next
    Set TmpItem = ItemCollection.Item(ItemIndex)
```vbscript
```
```vbscript
    ParameterExists = (Err.Number = 0)
    Err.Clear

```

```

```

```vbscript
```vbscript
    End Function

```
```
