---
title: "CAAPstAddExternalComponent.CATScript"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAPstHull", "CATIA", "CAAPstAddExternalComponent"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddExternalComponentSource.htm"
converted: "2026-05-11T17:31:52.321783"
---

    Option Explicit
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' *****************************************************************************
    '   Purpose:       Create A Product Structure document containing
    '                        an external component.
    '   Assumtions:   Opens CAAPstHull.CATPart in the CATDocView   
    '   Author: 
    '   Languages:   VBScript
    '   Locales:        English 
    '   CATIA Level:  V5R6 
    ' *****************************************************************************
    
```

    
```vbscript
    Sub CATMain()
        ' -----------------------------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed
```vbscript
         Dim sDocPath As String
         sDocPath=CATIA.SystemService.Environ("CATDocView")
         If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
           Err.Raise 9999,,"No Doc Path Defined"
         End If
```vbscript
        ' ------------------------------------------------------------------------------------------------ 
        'Create a new product document object by adding a document with the Product
        'type to the document collection of the CATIA application. 
        Dim oProductDoc As Document
        Set oProductDoc = CATIA.Documents.Add("Product") 
        'Retrieve the root product.
        Dim oRoot As Product
        Set oRoot = oProductDoc.Product
        'Retrieve the root product collection of products.
        Dim oRootCol As Products
        Set oRootCol = oRoot.Products
        'Open the Part Document
        Dim oPartDoc As Document
        Set oPartDoc = CATIA.Documents.Open(sDocPath & "CAAPstHull.CATPart")
        'Add a new component from the already opened part document.
        Dim oNewComponent As Product
        Set oNewComponent = oRootCol.AddExternalComponent(oPartDoc)
```

       
```

```vbscript
    End Sub
    
```

    

```