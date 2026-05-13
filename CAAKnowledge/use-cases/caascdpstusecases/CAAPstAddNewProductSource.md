---
title: "Untitled"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAScrBase", "CAAPstPad1_1", "CAAPstPad1_2", "CATIA", "CAAScdPstUseCases", "CAAPstAddNewProduct"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddNewProductSource.htmmd"
converted: "2026-05-11T11:27:02.575384"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2000

' *****************************************************************************
'   Purpose:       Create A Product Structure document containing
'                        two parts.
'   Assumtions:   Looks for CAAPstPad1_1.CATPart and
'                        CAAPstPad1_2.CATPart in the CATDocView   
'   Author: 
'   Languages:   VBScript
'   Locales:        English 
'   CATIA Level:  V5R6 
' *****************************************************************************

```cpp
Sub CATMain(#)

    ' -----------------------------------------------------------------------------------------------
```
    ' Optional: allows to find the sample wherever it's installed
```cpp
    Dim sDocPath As String
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
    ' ------------------------------------------------------------------------------------------------ 
   
    'Create a new product document by adding a document with the Product type
    'to the document collection of the CATIA application. 
```cpp
    Dim oProductDoc As Document
    Set oProductDoc = CATIA.Documents.Add("Product")

    'Retrieve the root product.
```
```vbscript
    Dim oRootProduct As Product
    Set oRootProduct = oProductDoc.Product

```

    'Declare the root product's part number and name.
    oRootProduct.PartNumber = "Root"
    oRootProduct.Name = "The_Root_Product"

    'Retrieve the product's collection under the root product.
```vbscript
    Dim oRootChildren As Products
    Set oRootChildren = oRootProduct.Products

    'Add a new product to the collection. This adds both a product reference
```
    'and a product component.
```vbscript
    Dim oChildProduct1 As Product
    Set oChildProduct1 = oRootChildren.AddNewProduct("Child_1_Type")

```

    'Declare the part number and name for this product.
    oChildProduct1.PartNumber = "Child_001"
    oChildProduct1.Name = "1st_Child"

    'Add a representation to this product using an existing part and reframe
    'the viewer to display the part completely.
    oChildProduct1.AddMasterShapeRepresentation sDocPath & "CAAPstPad1_1.CATPart"
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe

    'Add another product to the root product's collection.  This adds both
```
    'a product reference and a product component.
```vbscript
    Dim oChildProduct2 As Product
    Set oChildProduct2 = oRootChildren.AddNewProduct("Child_2_Type")

```

    'Declare the part number and name for this product.
    oChildProduct2.PartNumber = "Child_002"
    oChildProduct2.Name = "2nd_Child"

    'Add a representation to this product using an existing part and reframe
    'the viewer to display the part completely.
    oChildProduct2.AddMasterShapeRepresentation sDocPath & _
       "/online/CAAScdPstUseCases/samples/CAAPstPad1_2.CATPart"
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe(#)
     
End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2000

' *****************************************************************************
'   Purpose:       Create A Product Structure document containing
'                        two parts.
'   Assumtions:   Looks for CAAPstPad1_1.CATPart and
'                        CAAPstPad1_2.CATPart in the CATDocView   
'   Author: 
'   Languages:   VBScript
'   Locales:        English 
'   CATIA Level:  V5R6 
' *****************************************************************************

```cpp
Sub CATMain(#)

    ' -----------------------------------------------------------------------------------------------
```
    ' Optional: allows to find the sample wherever it's installed
```cpp
    Dim sDocPath As String
    sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
    ' ------------------------------------------------------------------------------------------------ 
   
    'Create a new product document by adding a document with the Product type
    'to the document collection of the CATIA application. 
```cpp
    Dim oProductDoc As Document
    Set oProductDoc = CATIA.Documents.Add(&quot;Product&quot;)

    'Retrieve the root product.
```
```vbscript
    Dim oRootProduct As Product
    Set oRootProduct = oProductDoc.Product

```

    'Declare the root product's part number and name.
    oRootProduct.PartNumber = &quot;Root&quot;
    oRootProduct.Name = &quot;The_Root_Product&quot;

    'Retrieve the product's collection under the root product.
```vbscript
    Dim oRootChildren As Products
    Set oRootChildren = oRootProduct.Products

    'Add a new product to the collection. This adds both a product reference
```
    'and a product component.
```vbscript
    Dim oChildProduct1 As Product
    Set oChildProduct1 = oRootChildren.AddNewProduct(&quot;Child_1_Type&quot;)

```

    'Declare the part number and name for this product.
    oChildProduct1.PartNumber = &quot;Child_001&quot;
    oChildProduct1.Name = &quot;1st_Child&quot;

    'Add a representation to this product using an existing part and reframe
    'the viewer to display the part completely.
    oChildProduct1.AddMasterShapeRepresentation sDocPath &amp; &quot;CAAPstPad1_1.CATPart&quot;
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe

    'Add another product to the root product's collection.  This adds both
```
    'a product reference and a product component.
```vbscript
    Dim oChildProduct2 As Product
    Set oChildProduct2 = oRootChildren.AddNewProduct(&quot;Child_2_Type&quot;)

```

    'Declare the part number and name for this product.
    oChildProduct2.PartNumber = &quot;Child_002&quot;
    oChildProduct2.Name = &quot;2nd_Child&quot;

    'Add a representation to this product using an existing part and reframe
    'the viewer to display the part completely.
    oChildProduct2.AddMasterShapeRepresentation sDocPath &amp; _
       &quot;/online/CAAScdPstUseCases/samples/CAAPstPad1_2.CATPart&quot;
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe(#)
     
End Sub
```
```