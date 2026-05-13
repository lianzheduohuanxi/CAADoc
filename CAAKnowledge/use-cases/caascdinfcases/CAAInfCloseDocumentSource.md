---
title: "CAAInfCloseDocument.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: "["CAAScdInfUseCases", "CATIA", "CAAInfCloseDocument", "CAAInfReadDocument"]"
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCloseDocumentSource.htm"
converted: "2026-05-11T17:31:52.352570"
---
tags: ["CAAScdInfUseCases", "CATIA", "CAAInfCloseDocument", "CAAInfReadDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfCloseDocumentSource.htmmd"
converted: "2026-05-11T17:31:52.352570"
    Option Explicit

```vbscript
```vbscript
```cpp
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

```

```

```

```cpp
    Sub CATMain(#)
```vbscript
```
```vbscript
        ' -----------------------------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it may be installed

```

```

```vbscript
```vbscript
        Dim sDocPath As String
```vbscript
```
```vbscript
```cpp
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```
```

```

```

```vbscript
```vbscript
```vbscript
        ' ------------------------------------------------------------------------------------------------
        'Open the document.
```cpp
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

           "online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
```vbscript
```vbscript
Dim sFilePath
```vbscript
```
```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim iPartDoc As Document
        Set iPartDoc = CATIA.Documents.Open(sFilePath)
```
```

```

```

```vbscript
```vbscript
```vbscript
        'Close the active document which is the document just opened.
```cpp
         CATIA.ActiveDocument.Close(#)
        'Open the same document again.
```
```cpp
         Set iPartDoc = CATIA.Documents.Open(sFilePath)
        'Close the document using the variable defined for it.
```
```

```

```

```vbscript
```vbscript
```vbscript
'Open the same document again.
```cpp
Set iPartDoc = CATIA.Documents.Open(sFilePath)
'Close the document using the variable defined for it.
```
```

```

         iPartDoc.Close(#)
```

```vbscript
```vbscript
```vbscript
         'Open the same document a third time.
```cpp
          Set iPartDoc = CATIA.Documents.Open(sFilePath)
         'Close the document by specifying its name.
```
```cpp
          CATIA.Documents.Item("CAAInfReadDocument.CATPart").Close(#)
```
```

```

```

```vbscript
```vbscript
    End Sub

```
```
