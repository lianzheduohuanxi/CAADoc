---
title: "CAAInfSaveDocument.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: "["CAAScdInfUseCases", "CATIA", "CAAInfSaveDocument", "CAAInfReadDocument"]"
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveDocumentSource.htm"
converted: "2026-05-11T17:31:52.396971"
---
tags: ["CAAScdInfUseCases", "CATIA", "CAAInfSaveDocument", "CAAInfReadDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveDocumentSource.htmmd"
converted: "2026-05-11T17:31:52.396971"
Option Explicit

```vbscript
```vbscript
```cpp
     ' COPYRIGHT DASSAULT SYSTEMES 2001
     ' *****************************************************************************
     '   Purpose:       Save an Existing Document.
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
         'Open the document and add it as the last item of the collection of documents.
         'Create and display a new window for the document.
         'Activate the document and its window.
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
         'The document just opened is the active document.
         'Save the active document and then close it.
```cpp
          CATIA.ActiveDocument.Save(#)
          CATIA.ActiveDocument.Close(#)
         'Open the same document again.
```
```cpp
          Set iPartDoc = CATIA.Documents.Open(sFilePath)
         'Save the document just opened using the variable name defined for it.
```
         'Close the document in the same way.
```

```

```

```vbscript
```cpp
Set iPartDoc = CATIA.Documents.Open(sFilePath)
```vbscript
```
```vbscript
'Save the document just opened using the variable name defined for it.
'Close the document in the same way.
```

```

          iPartDoc.Save(#)
          iPartDoc.Close(#)
```

```vbscript
```vbscript
```vbscript
         'Open the same document a third time.
```cpp
          Set iPartDoc = CATIA.Documents.Open(sFilePath)
         'Save the document by specifying its name and then close it.
```
```cpp
          CATIA.Documents.Item("CAAInfReadDocument.CATPart").Save(#)
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
