---
title: "CAAPriChangeHoleModule.bas"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAPriChangeHoleModule", "CATIA", "CAAPriChangeHoleForm", "CAAPriChangeHoleVBA"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleModuleSource.md"
converted: "2026-05-11T17:31:51.194040"
---

    Option Explicit
```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2004
    ' ***********************************************************************
    '   Purpose:      Changes hole description
    '   Assumptions:   Looks for CAAPriChangeHoleVBA.md in the DocView
    '   Author:
    '   Languages:    MS VBA
    '   Locales:      English
    '   CATIA Level:  V5R13
    
    Public oPartDocument As PartDocument
    Public i As Long
    Public sDocPath As String
```

    
```vbscript
    Sub CATMain()
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
    sDocPath = CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
      Err.Raise 9999, , "No Doc Path Defined"
    End If
```vbscript
    ' -----------------------------------------------------------
    ' ------------
    ' Get the part document
    ' ------------
    Set oPartDocument = CATIA.ActiveDocument
    ' ------------
    ' Test the selection content
    ' ------------
    If oPartDocument.Selection.Count = 0 Then
        ' ------------
        ' The selection content is empty, the macro ends
        ' ------------
```

        MsgBox "Select the holes you wish to transform before running the macro.", vbOKOnly, "Warning"
    Else
```vbscript
        ' ------------
        ' The selection content is not empty
        ' Show the dialog box
        ' ------------
```

        CAAPriChangeHoleForm.Show
    End If
    
```

```vbscript
    End Sub
    
```

    Public Function CatObjectExistsInSelection(CatSelection As Selection, CatObjectName As String, CatObject As Object) As Boolean
    
    On Error Resume Next
```vbscript
    Set CatObject = CatSelection.FindObject(CatObjectName)
    CatObjectExistsInSelection = (Err.Number = 0)
    Err.Clear
    
```

```vbscript
    End Function
    
```

    Public Function ParameterExists(ItemIndex As String, ItemCollection As Object) As Boolean
    
```vbscript
    Dim TmpItem As Variant
    On Error Resume Next
    Set TmpItem = ItemCollection.Item(ItemIndex)
    ParameterExists = (Err.Number = 0)
    Err.Clear
        
```

```vbscript
    End Function
    
```

```