---
title: "Untitled"
category: "use-case"
module: "CAAScdPriUseCases"
tags: ["CAAScrBase", "CAAPriChangeHoleModule", "CATIA", "CAAPriChangeHoleForm", "CAAPriChangeHoleVBA"]
source_file: "Doc/online/CAAScdPriUseCases/CAAPriChangeHoleModuleSource.htmmd"
converted: "2026-05-11T11:27:02.731821"
---

Option Explicit

' COPYRIGTH DASSAULT SYSTEMES 2004

' ***********************************************************************
'   Purpose:      Changes hole description
'   Assumptions:   Looks for CAAPriChangeHoleVBA.htm in the DocView
'   Author:
'   Languages:    MS VBA
'   Locales:      English
'   CATIA Level:  V5R13

Public oPartDocument As PartDocument
Public i As Long
Public sDocPath As String

```vbscript
Sub CATMain(#)

' -----------------------------------------------------------
```
' Optional: allows to find the sample wherever it's installed
```vbscript
sDocPath = CATIA.SystemService.Environ("CATDocView")
If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
  Err.Raise 9999, , "No Doc Path Defined"
End If
```
' -----------------------------------------------------------

' ------------
' Get the part document
' ------------
```vbscript
Set oPartDocument = CATIA.ActiveDocument
' ------------
```
' Test the selection content
' ------------
If oPartDocument.Selection.Count = 0 Then
    ' ------------
    ' The selection content is empty, the macro ends
    ' ------------
```vbscript
    MsgBox "Select the holes you wish to transform before running the macro.", vbOKOnly, "Warning"
Else
```
    ' ------------
    ' The selection content is not empty
    ' Show the dialog box
    ' ------------
    CAAPriChangeHoleForm.Show
End If

```vbscript
End Sub

Public Function CatObjectExistsInSelection(CatSelection As Selection, CatObjectName As String, CatObject As Object) As Boolean

On Error Resume Next
Set CatObject = CatSelection.FindObject(CatObjectName)
CatObjectExistsInSelection = (Err.Number = 0)
```
Err.Clear

```vbscript
End Function

Public Function ParameterExists(ItemIndex As String, ItemCollection As Object) As Boolean

Dim TmpItem As Variant
On Error Resume Next
Set TmpItem = ItemCollection.Item(ItemIndex)
ParameterExists = (Err.Number = 0)
```
Err.Clear
    
```vbscript
End Function

```

```vbscript
Option Explicit

' COPYRIGTH DASSAULT SYSTEMES 2004

' ***********************************************************************
'   Purpose:      Changes hole description
'   Assumptions:   Looks for CAAPriChangeHoleVBA.htm in the DocView
'   Author:
'   Languages:    MS VBA
'   Locales:      English
'   CATIA Level:  V5R13

Public oPartDocument As PartDocument
Public i As Long
Public sDocPath As String

```vbscript
Sub CATMain(#)

' -----------------------------------------------------------
```
' Optional: allows to find the sample wherever it's installed
```vbscript
sDocPath = CATIA.SystemService.Environ(&quot;CATDocView&quot;)
If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
  Err.Raise 9999, , &quot;No Doc Path Defined&quot;
End If
```
' -----------------------------------------------------------

' ------------
' Get the part document
' ------------
```vbscript
Set oPartDocument = CATIA.ActiveDocument
' ------------
```
' Test the selection content
' ------------
If oPartDocument.Selection.Count = 0 Then
    ' ------------
    ' The selection content is empty, the macro ends
    ' ------------
```vbscript
    MsgBox &quot;Select the holes you wish to transform before running the macro.&quot;, vbOKOnly, &quot;Warning&quot;
Else
```
    ' ------------
    ' The selection content is not empty
    ' Show the dialog box
    ' ------------
    CAAPriChangeHoleForm.Show
End If

```vbscript
End Sub

Public Function CatObjectExistsInSelection(CatSelection As Selection, CatObjectName As String, CatObject As Object) As Boolean

On Error Resume Next
Set CatObject = CatSelection.FindObject(CatObjectName)
CatObjectExistsInSelection = (Err.Number = 0)
```
Err.Clear

```vbscript
End Function

Public Function ParameterExists(ItemIndex As String, ItemCollection As Object) As Boolean

Dim TmpItem As Variant
On Error Resume Next
Set TmpItem = ItemCollection.Item(ItemIndex)
ParameterExists = (Err.Number = 0)
```
Err.Clear
    
```vbscript
End Function
```
```