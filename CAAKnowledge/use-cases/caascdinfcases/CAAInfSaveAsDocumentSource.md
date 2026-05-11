---
title: "CAAInfSaveAsDocument.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAInfSaveAsDocument", "CAAScdInfUseCases", "CAAInfReadDocument", "CATIA", "CAAInfWriteDocument3", "CAAInfWriteDocument2", "CAAInfWriteDocument1"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveAsDocumentSource.md"
converted: "2026-05-11T17:31:52.390982"
---

Option Explicit
```vbscript
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
         ' -----------------------------------------------------------------------------------------------
         ' Optional: allows to specify where document should be saved
         Dim sTmpPath As String
         sTmpPath=CATIA.SystemService.Environ("CATTemp")
         If (Not CATIA.FileSystem.FolderExists(sTmpPath)) Then
           Err.Raise 9999,,"No Tmp Path Defined"
         End If
         ' ------------------------------------------------------------------------------------------------ 
         'Create a new part document.
         'Add the new document to the end of the collection of documents.
         'Create and display a new window for the new document.
         'Activate the new document and the window.
         Dim oFirstNewPartDoc As Document
         Set oFirstNewPartDoc = CATIA.Documents.Add("Part")
         'The document just created is the active one.
         'Save the new document.
         Dim sFilePath
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
```

            "CAAInfWriteDocument1.CATPart")
          CATIA.ActiveDocument.SaveAs(sFilePath)
```vbscript
         'Create a second new part document.
          Dim oSecondNewPartDoc As Document
          Set oSecondNewPartDoc = CATIA.Documents.Add("Part")
         'Save the new document using the variable name defined for it.
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
```

            "CAAInfWriteDocument2.CATPart")
          oSecondNewPartDoc.SaveAs(sFilePath)
         'Open an existing document.
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
          Dim iThirdPartDoc As Document
          Set iThirdPartDoc = CATIA.Documents.Open(sFilePath)
         'Save the new document by specifying its name.
         sFilePath = CATIA.FileSystem.ConcatenatePaths(sTmpPath, _
              "CAAInfWriteDocument3.CATPart")
         CATIA.Documents.Item("CAAInfReadDocument.CATPart").SaveAs(sFilePath)
       
```

```vbscript
     End Sub
     
```

     

```