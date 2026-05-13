---
title: "CAAInfSaveAsDocument.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: "["CAAInfSaveAsDocument", "CAAScdInfUseCases", "CAAInfReadDocument", "CATIA", "CAAInfWriteDocument3", "CAAInfWriteDocument2", "CAAInfWriteDocument1"]"
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveAsDocumentSource.htm"
converted: "2026-05-11T17:31:52.390982"
---
tags: ["CAAInfSaveAsDocument", "CAAScdInfUseCases", "CAAInfReadDocument", "CATIA", "CAAInfWriteDocument3", "CAAInfWriteDocument2", "CAAInfWriteDocument1"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveAsDocumentSource.htmmd"
converted: "2026-05-11T17:31:52.390982"
Option Explicit

```vbscript
```vbscript
```cpp
     ' COPYRIGHT DASSAULT SYSTEMES 2001
     ' *****************************************************************************
     '   Purpose:       Save a New Document.
     '   Assumtions:   None
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
         ' -----------------------------------------------------------------------------------------------
         ' Optional: allows to specify where document should be saved
```cpp
         Dim sTmpPath As String
         sTmpPath=CATIA.SystemService.Environ("CATTemp")
         If (Not CATIA.FileSystem.FolderExists(sTmpPath)) Then
           Err.Raise 9999,,"No Tmp Path Defined"
         End If
```
         ' ------------------------------------------------------------------------------------------------
         'Create a new part document.
         'Add the new document to the end of the collection of documents.
         'Create and display a new window for the new document.
         'Activate the new document and the window.
```cpp
         Dim oFirstNewPartDoc As Document
         Set oFirstNewPartDoc = CATIA.Documents.Add("Part")
         'The document just created is the active one.
```
         'Save the new document.
```cpp
         Dim sFilePath
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
```
```

```

```

            "CAAInfWriteDocument1.CATPart")
```vbscript
```vbscript
Dim sFilePath
```vbscript
```
```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
          CATIA.ActiveDocument.SaveAs(sFilePath)
```
```

```

```

```vbscript
```vbscript
```vbscript
         'Create a second new part document.
```cpp
          Dim oSecondNewPartDoc As Document
          Set oSecondNewPartDoc = CATIA.Documents.Add("Part")
         'Save the new document using the variable name defined for it.
```
```cpp
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
```
```

```

```

            "CAAInfWriteDocument2.CATPart")
```vbscript
```vbscript
```vbscript
'Save the new document using the variable name defined for it.
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
```
```

```

          oSecondNewPartDoc.SaveAs(sFilePath)
```vbscript
```vbscript
         'Open an existing document.
```cpp
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```

            "online/CAAScdInfUseCases/samples/CAAInfReadDocument.CATPart")
oSecondNewPartDoc.SaveAs(sFilePath)
```vbscript
```vbscript
'Open an existing document.
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

```vbscript
```vbscript
          Dim iThirdPartDoc As Document
```vbscript
```
```vbscript
```cpp
          Set iThirdPartDoc = CATIA.Documents.Open(sFilePath)
         'Save the new document by specifying its name.
```
```cpp
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _

```
```

```

```

              "CAAInfWriteDocument3.CATPart")
```vbscript
```vbscript
Dim iThirdPartDoc As Document
```vbscript
```
```vbscript
```cpp
Set iThirdPartDoc = CATIA.Documents.Open(sFilePath)
'Save the new document by specifying its name.
```
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
         CATIA.Documents.Item("CAAInfReadDocument.CATPart").SaveAs(sFilePath)

```
```

```

```

```vbscript
```vbscript
     End Sub

```
```
