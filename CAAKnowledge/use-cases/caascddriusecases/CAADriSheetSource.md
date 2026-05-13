---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScrBase", "CATIA", "CAADriSheet", "CAAScdDriUseCases"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriSheetSource.htmmd"
converted: "2026-05-11T11:27:02.743510"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001

' ***********************************************************************
'   Purpose:      Creates constraints between assembly Parts using Publications
'   Assumptions:   Looks for CAADriSheet.CATDrawing in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R7 
' ***********************************************************************

```cpp
Sub CATMain(#)

```

    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ----------------------------------------------------------- 

    ' Open the Drawing document 
```cpp
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sDocPath & _
                 "/online/CAAScdDriUseCases/samples/CAADriSheet.CATDrawing")
```

' ------------
' Get the sheets collection of the drawing
' ------------
```vbscript
Dim oDrawingSheets As DrawingSheets
Set oDrawingSheets = oDoc.Sheets

```

' ------------
' Add the sheet with a default name to the sheets collection of the drawing
' ------------
```vbscript
MsgBox "Click OK to create the new sheet."
Dim oDrawingSheet As DrawingSheet
Set oDrawingSheet = oDrawingSheets.Add("New Sheet") 

```

' ------------
' Activate the sheet
' ------------
```vbscript
MsgBox "Click OK to activate the new sheet."
oDrawingSheet.Activate 
```

```vbscript
End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001

' ***********************************************************************
'   Purpose:      Creates constraints between assembly Parts using Publications
'   Assumptions:   Looks for CAADriSheet.CATDrawing in the DocView   
'   Author: 
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R7 
' ***********************************************************************

```cpp
Sub CATMain(#)

```

    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    dim sDocPath As String 
```cpp
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
    ' ----------------------------------------------------------- 

    ' Open the Drawing document 
```cpp
    Dim oDoc As Document
    set oDoc = CATIA.Documents.Open(sDocPath &amp; _
                 &quot;/online/CAAScdDriUseCases/samples/CAADriSheet.CATDrawing&quot;)
```

' ------------
' Get the sheets collection of the drawing
' ------------
```vbscript
Dim oDrawingSheets As DrawingSheets
Set oDrawingSheets = oDoc.Sheets

```

' ------------
' Add the sheet with a default name to the sheets collection of the drawing
' ------------
```vbscript
MsgBox &quot;Click OK to create the new sheet.&quot;
Dim oDrawingSheet As DrawingSheet
Set oDrawingSheet = oDrawingSheets.Add(&quot;New Sheet&quot;) 

```

' ------------
' Activate the sheet
' ------------
```vbscript
MsgBox &quot;Click OK to activate the new sheet.&quot;
oDrawingSheet.Activate 
```

```vbscript
End Sub
```
```