---
title: "Untitled"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScrBase", "CATIA", "CAAInfCloseDocument", "CAAInfReadDocument", "CAAScdInfUseCases"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCloseDocumentSource.htmmd"
converted: "2026-05-11T11:27:02.690868"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001

' *****************************************************************************
'   Purpose:       Close a  Document.
'   Assumtions:   Looks for CAAInfReadDocument.CATPart
'                         in the CATDocView   
'   Author: 
'   Languages:   VBScript
'   Locales:        English 
'   CATIA Level:  V5R7 
' *****************************************************************************

```cpp
Sub CATMain(#)

    ' -----------------------------------------------------------------------------------------------
```
    ' Optional: allows to find the sample wherever it may be installed
```cpp
    Dim sDocPath As String
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ------------------------------------------------------------------------------------------------ 
   
    'Open the document. 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
       "online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
```
```cpp
    Dim iPartDoc As Document
    Set iPartDoc = CATIA.Documents.Open(sFilePath)

    'Close the active document which is the document just opened.
```
```cpp
     CATIA.ActiveDocument.Close(#)

    'Open the same document again.
```
```cpp
     Set iPartDoc = CATIA.Documents.Open(sFilePath)

```

    'Close the document using the variable defined for it.
     iPartDoc.Close(#)

     'Open the same document a third time.
```cpp
      Set iPartDoc = CATIA.Documents.Open(sFilePath)

     'Close the document by specifying its name.
```
```cpp
      CATIA.Documents.Item("CAAInfReadDocument.CATPart").Close(#)
   
End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2001

' *****************************************************************************
'   Purpose:       Close a  Document.
'   Assumtions:   Looks for CAAInfReadDocument.CATPart
'                         in the CATDocView   
'   Author: 
'   Languages:   VBScript
'   Locales:        English 
'   CATIA Level:  V5R7 
' *****************************************************************************

```cpp
Sub CATMain(#)

    ' -----------------------------------------------------------------------------------------------
```
    ' Optional: allows to find the sample wherever it may be installed
```cpp
    Dim sDocPath As String
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ------------------------------------------------------------------------------------------------ 
   
    'Open the document. 
```cpp
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
       "online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
```
```cpp
    Dim iPartDoc As Document
    Set iPartDoc = CATIA.Documents.Open(sFilePath)

    'Close the active document which is the document just opened.
```
```cpp
     CATIA.ActiveDocument.Close(#)

    'Open the same document again.
```
```cpp
     Set iPartDoc = CATIA.Documents.Open(sFilePath)

```

    'Close the document using the variable defined for it.
     iPartDoc.Close(#)

     'Open the same document a third time.
```cpp
      Set iPartDoc = CATIA.Documents.Open(sFilePath)

     'Close the document by specifying its name.
```
```cpp
      CATIA.Documents.Item("CAAInfReadDocument.CATPart").Close(#)
   
End Sub
```
```