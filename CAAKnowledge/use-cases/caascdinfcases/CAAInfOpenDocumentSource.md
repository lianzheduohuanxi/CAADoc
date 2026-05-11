---
title: "CAAInfOpenDocument.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAScdInfUseCases", "CAAInfOpenDocument", "CATIA", "CAAInfReadDocument"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfOpenDocumentSource.md"
converted: "2026-05-11T17:31:52.383997"
---

Option Explicit
```vbscript
     ' COPYRIGHT DASSAULT SYSTEMES 2001
     ' *****************************************************************************
     '   Purpose:       Open an Existing Document.
     '   Assumtions:   Looks for CAAInfReadDocument.CATPart
     '                         in the CATDocView   
     '   Author: 
     '   Languages:   VBScript
     '   Locales:        English 
     '   CATIA Level:  V5R7 
     ' *****************************************************************************
     
```

     
```vbscript
     Sub CATMain()
         ' -----------------------------------------------------------------------------------------------
         ' Optional: allows to find the sample wherever it may be installed
```vbscript
         Dim sDocPath As String
         sDocPath=CATIA.SystemService.Environ("CATDocView")
         If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
           Err.Raise 9999,,"No Doc Path Defined"
         End If
```vbscript
         ' ------------------------------------------------------------------------------------------------ 
         'Open the document and add it as the last item of the collection of documents.
         'Create and display a new window for the document.
         'Activate the document and its window.
         Dim sFilePath
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

            "online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
         Dim iPartDoc As Document
         Set iPartDoc = CATIA.Documents.Open(sFilePath)
        
```

```vbscript
     End Sub
     
```

     

```