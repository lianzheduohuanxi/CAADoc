---
title: "CAAPstAddExternalComponent.CATScript"
category: "use-case"
module: "CAAScdPstUseCases"
tags: "["CAAPstHull", "CATIA", "CAAPstAddExternalComponent"]"
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddExternalComponentSource.htm"
converted: "2026-05-11T17:31:52.321783"
---
tags: ["CAAPstHull", "CATIA", "CAAPstAddExternalComponent"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddExternalComponentSource.htmmd"
converted: "2026-05-11T17:31:52.321783"
    Option Explicit

```vbscript
```vbscript
```cpp
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

```

```

```cpp
    Sub CATMain(#)
```vbscript
```
```vbscript
        ' -----------------------------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it's installed

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
```cpp
        ' ------------------------------------------------------------------------------------------------
        'Create a new product document object by adding a document with the Product
        'type to the document collection of the CATIA application.
```cpp
        Dim oProductDoc As Document
        Set oProductDoc = CATIA.Documents.Add("Product")
        'Retrieve the root product.
```
```vbscript
        Dim oRoot As Product
        Set oRoot = oProductDoc.Product
        'Retrieve the root product collection of products.
```
```vbscript
        Dim oRootCol As Products
        Set oRootCol = oRoot.Products
        'Open the Part Document
```
```cpp
        Dim oPartDoc As Document
        Set oPartDoc = CATIA.Documents.Open(sDocPath & "CAAPstHull.CATPart")
        'Add a new component from the already opened part document.
```
```vbscript
        Dim oNewComponent As Product
        Set oNewComponent = oRootCol.AddExternalComponent(oPartDoc)
```
```

```

```

```vbscript
```vbscript
    End Sub

```
```
