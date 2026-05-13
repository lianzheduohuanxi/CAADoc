---
title: "Untitled"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAScrBase", "CATIA", "CAAPstAddComponent", "CAAPstHull", "CAAPstFunnel"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddComponentSource.htmmd"
converted: "2026-05-11T11:27:02.580817"
---

Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2000

' *****************************************************************************
'   Purpose:       Create A Product Structure document containing
'                        two parts and multiply the instances of one of these parts,
'                        creating identical products differing only in their position.
'   Assumtions:   Looks for CAAPstHull.CATPart and
'                        CAAPstFunnel.CATPart in the CATDocView   
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
   
    'Create a new product document object by adding a document with the Product
    'type to the document collection of the CATIA application. 
```cpp
    Dim oProductDoc As Document
    Set oProductDoc = CATIA.Documents.Add("Product")

    'Retrieve the Titanic as the root product.
```
```vbscript
    Dim oTitanic As Product
    Set oTitanic = oProductDoc.Product

```

    'Declare the Titanic's part number and name.
    oTitanic.PartNumber = "Titanic"
    oTitanic.Name = "Steam_Ship_Titanic"
    
    'Retrieve the product's collection of the Titanic.
```vbscript
    Dim oTitanicProducts As Products
    Set oTitanicProducts = oTitanic.Products
 
    'Add the hull as a new component in the collection with its part number 
```
    'and name. 
```vbscript
    Dim oHull As Product
    Set  oHull = oTitanicProducts.AddNewProduct("Hull_Type")
    oHull.PartNumber = "Titanic's_Hull"
```
    oHull.Name = "Unsinkable_Hull"

    'Add a master shape representation to the hull using an existing part and
    'reframe the viewer.
    oHull.AddMasterShapeRepresentation sDocPath & "CAAPstHull.CATPart"
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
    
    'Add the first funnel to the Titanic's product collection, with part number
```
    'and name.
```vbscript
    Dim oFunnel1 As Product
    Set oFunnel1 = oTitanicProducts.AddNewProduct("Funnel_Type")
    oFunnel1.PartNumber = "Titanic's_Funnel"
```
    oFunnel1.Name = "Fore_Funnel"

    'Add a master shape representation to the funnel using an existing part
    oFunnel1.AddMasterShapeRepresentation sDocPath & "CAAPstFunnel.CATPart"
 
    'Define the initial positioning parameters for the Funnel1 instances.
```vbscript
    Dim iMatrix(11)
    iMatrix(0) = 1.0
```
    iMatrix(1) = 0.0
    iMatrix(2) = 0.0
    iMatrix(3) = 0.0
    iMatrix(4) = 1.0
    iMatrix(5) = 0.0
    iMatrix(6) = 0.0
    iMatrix(7) = 0.0
    iMatrix(8) = 1.0
    iMatrix(9) = 0.0
    iMatrix(10) = 0.0
    iMatrix(11) = 0.0    
    
    'Get the reference of the Funnel product
```vbscript
    Dim oFunnelRef As Product
    Set oFunnelRef = oFunnel1.ReferenceProduct

    'Add a second component using the existing Funnel product's reference.
```
```vbscript
    Dim oFunnel2 As Product
    Set oFunnel2 = oTitanicProducts.AddComponent(oFunnelRef)
    oFunnel2.Name = "Second_Funnel"
```
    'Associate the new product with a different position from its reference
    iMatrix(9) = -40.0
    oFunnel2.Move.Apply iMatrix

    'Add a third component using the existing Funnel product's reference.
```vbscript
    Dim oFunnel3 As Product
    Set oFunnel3 = oTitanicProducts.AddComponent(oFunnelRef)
    oFunnel3.Name = "Third_Funnel"
```
    'Associate the new product with a different position from its reference
    iMatrix(9) = -80.0
    oFunnel3.Move.Apply iMatrix

    'Add a fourth component using the existing Funnel product's reference.
```vbscript
    Dim oFunnel4 As Product
    Set oFunnel4 = oTitanicProducts.AddComponent(oFunnelRef)
    oFunnel4.Name = "Fourth_Funnel"
```
    'Associate the new product with a different position from its reference
    iMatrix(9) = -120.0
    oFunnel4.Move.Apply iMatrix
     
```vbscript
End Sub

```

```cpp
Option Explicit
' COPYRIGHT DASSAULT SYSTEMES 2000

' *****************************************************************************
'   Purpose:       Create A Product Structure document containing
'                        two parts and multiply the instances of one of these parts,
'                        creating identical products differing only in their position.
'   Assumtions:   Looks for CAAPstHull.CATPart and
'                        CAAPstFunnel.CATPart in the CATDocView   
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
   
    'Create a new product document object by adding a document with the Product
    'type to the document collection of the CATIA application. 
```cpp
    Dim oProductDoc As Document
    Set oProductDoc = CATIA.Documents.Add("Product")

    'Retrieve the Titanic as the root product.
```
```vbscript
    Dim oTitanic As Product
    Set oTitanic = oProductDoc.Product

```

    'Declare the Titanic's part number and name.
    oTitanic.PartNumber = "Titanic"
    oTitanic.Name = "Steam_Ship_Titanic"
    
    'Retrieve the product's collection of the Titanic.
```vbscript
    Dim oTitanicProducts As Products
    Set oTitanicProducts = oTitanic.Products
 
    'Add the hull as a new component in the collection with its part number 
```
    'and name. 
```vbscript
    Dim oHull As Product
    Set  oHull = oTitanicProducts.AddNewProduct("Hull_Type")
    oHull.PartNumber = "Titanic's_Hull"
```
    oHull.Name = "Unsinkable_Hull"

    'Add a master shape representation to the hull using an existing part and
    'reframe the viewer.
    oHull.AddMasterShapeRepresentation sDocPath & "CAAPstHull.CATPart"
```cpp
    CATIA.ActiveWindow.ActiveViewer.Reframe
    
    'Add the first funnel to the Titanic's product collection, with part number
```
    'and name.
```vbscript
    Dim oFunnel1 As Product
    Set oFunnel1 = oTitanicProducts.AddNewProduct("Funnel_Type")
    oFunnel1.PartNumber = "Titanic's_Funnel"
```
    oFunnel1.Name = "Fore_Funnel"

    'Add a master shape representation to the funnel using an existing part
    oFunnel1.AddMasterShapeRepresentation sDocPath & "CAAPstFunnel.CATPart"
 
    'Define the initial positioning parameters for the Funnel1 instances.
```vbscript
    Dim iMatrix(11)
    iMatrix(0) = 1.0
```
    iMatrix(1) = 0.0
    iMatrix(2) = 0.0
    iMatrix(3) = 0.0
    iMatrix(4) = 1.0
    iMatrix(5) = 0.0
    iMatrix(6) = 0.0
    iMatrix(7) = 0.0
    iMatrix(8) = 1.0
    iMatrix(9) = 0.0
    iMatrix(10) = 0.0
    iMatrix(11) = 0.0    
    
    'Get the reference of the Funnel product
```vbscript
    Dim oFunnelRef As Product
    Set oFunnelRef = oFunnel1.ReferenceProduct

    'Add a second component using the existing Funnel product's reference.
```
```vbscript
    Dim oFunnel2 As Product
    Set oFunnel2 = oTitanicProducts.AddComponent(oFunnelRef)
    oFunnel2.Name = "Second_Funnel"
```
    'Associate the new product with a different position from its reference
    iMatrix(9) = -40.0
    oFunnel2.Move.Apply iMatrix

    'Add a third component using the existing Funnel product's reference.
```vbscript
    Dim oFunnel3 As Product
    Set oFunnel3 = oTitanicProducts.AddComponent(oFunnelRef)
    oFunnel3.Name = "Third_Funnel"
```
    'Associate the new product with a different position from its reference
    iMatrix(9) = -80.0
    oFunnel3.Move.Apply iMatrix

    'Add a fourth component using the existing Funnel product's reference.
```vbscript
    Dim oFunnel4 As Product
    Set oFunnel4 = oTitanicProducts.AddComponent(oFunnelRef)
    oFunnel4.Name = "Fourth_Funnel"
```
    'Associate the new product with a different position from its reference
    iMatrix(9) = -120.0
    oFunnel4.Move.Apply iMatrix
     
```vbscript
End Sub
```
```