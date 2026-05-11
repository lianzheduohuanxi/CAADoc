---
title: "Untitled"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAPstHull", "CAAScrBase", "CAAInfLauchMacro", "CAAPstAddComponent", "CAAScdInfUseCases", "CAAPstAddComponentSource", "CAAScdPstUseCases", "CAAPstFunnel", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddComponent.htm"
converted: "2026-05-11T11:06:32.486305"
---

## Product Structure
 
 
## []Adding Components
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create a product
 structure composed of four different instances of the same product, each
 having its own specific position. These four products are positioned so
 that they represent the funnels on the hull of the Titanic. The macro
 assumes that the CATDocView has been initialized so that it references the
 path leading to the two part documents, CAAPstHull.CATPart and
 CAAPstFunnel.CATPart.
 
 

Here is an image of the resulting product structure and its
 representation:
 
 
 |![](image/CAAPstAddComponent.jpg)
 
 
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAPstAddComponent is launched in CATIA [[1]].
 No previously opened document is needed.
 

[CAAPstAddComponent.CATScript
 ]is located in the CAAScdPstUseCases module. [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAPstAddComponent includes eight steps:
 

 
- [Prolog]
 
- [Adding a New Product: the Hull]
 
- [Assigning a Master Shape
 Representation to the Hull]
 
- [Adding a Second New Product: the Funnel]
 
- [Assigning a Master Shape
 Representation to the Funnel]
 
- [Initializing the Position Matrix for the
 Instances of the Funnel]
 
- [Retrieving the Reference of the Funnel
 Product]
 
- [Adding and Positioning New Instances
 of the Funnel Product on the Hull]
 
 
#### []Prolog
 
 
 ****
```
...
 
'Create a new product document object by adding a document with the Product
 'type to the document collection of the CATIA application. 
 
Dim
 oProductDoc 
As
 Document
 
Set
 oProductDoc = CATIA.Documents.
Add
("Product")

 'Retrieve the Titanic as the root product.
 
Dim
 oTitanic 
As
 Product
 
Set
 oTitanic = oProductDoc.Product

 'Declare the Titanic's part number and name.
 
oTitanic.PartNumber = "Titanic"
 oTitanic.Name = "Steam_Ship_Titanic"

 
 'Retrieve the product's collection of the Titanic.
 
Dim
 oTitanicProducts 
As
 Products
 
Set
 oTitanicProducts = oTitanic.Products
 ...
```

 
 
 
 

A new Product document is created using the `Add` method of
 the documents collection (*Documents *object). Next, the root product
 of the document is retrieved using the `Product` property of
 the *ProductDocument *object. A Part number and name are assigned to
 the root product.  Finally, the product's collection is retrieved
 using the `Products` property of the *Product *object. New
 Products within this collection will later be added to construct the
 product structure. 
 
#### []Adding a New Product: the Hull
 
 
 ****
```
...
 
'Add the hull as a new component in the collection with its part number 
 'and name. 
 
Dim
 oHull 
As
 Product
 
Set
 oHull = oTitanicProducts.
AddNewProduct
("Hull_Type")
 oHull.PartNumber = "Titanic's_Hull"
 oHull.Name = "Unsinkable_Hull"
 ...
```

 
 
 
 

A new product, the Hull,  is added to the collection using the `AddNewProduct`
 method of the* Products *object. The new product is then assigned a
 part number and name which will allow its identification in the product
 structure tree.
 
#### []Assigning a Master Shape
 Representation to the Hull
 
 
 ********
```
...
 
'Add a master shape representation to the hull using an existing part and
 'reframe the viewer.
 
oHull.
AddMasterShapeRepresentation
 sDocPath & "CAAPstHull.CATPart"
 CATIA.ActiveWindow.ActiveViewer.
Reframe

 ...
```

 
 
 
 

Using the `AddMasterShapeRepresentation` method of the *Product
 *object, an existing Part from an external Part document is added to
 the product. The Part document is found in the documentation installation
 path which has already been stored in the `sDocPath` variable.
 In order to ensure that the visualization will be adequate, the viewer
 must be reframed.
 
#### []Adding a Second New Product: the Funnel
 
 
 ****
```
...
 
'Add the first funnel to the Titanic's product collection, with part number
 'and name.
 
Dim
 oFunnel1 
As
 Product
 
Set
 oFunnel1 = oTitanicProducts.
AddNewProduct
("Funnel_Type")
 oFunnel1.PartNumber = "Titanic's_Funnel"
 oFunnel1.Name = "Fore_Funnel"
 ...
```

 
 
 
 

A second new product, the Funnel,  is added to the collection
 using the `AddNewProduct` method of * *the*
 Products *object. The new product is then assigned a part number and
 name which will allow its identification in the product structure tree.
 
#### []Assigning a Master Shape
 Representation to the Funnel
 
 
 ****
```
...
 
'Add a master shape representation to the funnel using an existing part
 
oFunnel1.
AddMasterShapeRepresentation
 sDocPath & "CAAPstFunnel.CATPart"
 ...
```

 
 
 
 

Using the `AddMasterShapeRepresentation` method of the *Product
 *object, an existing Part from an external Part document is added to
 the product. The Part document is found in the documentation installation
 path which has already been stored in the `sDocPath` variable.
 
#### []Initializing the Position Matrix for the
 Instances of the Funnel
 
 
 
```
...
 
'Define the initial positioning parameters for the Funnel1 instances.
 Dim iMatrix(11)
 iMatrix(0) = 1.0
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

 ...
```

 
 
 
 

Remember that arrays are initialized to 1 less than the maximum number
 of items in the array.
 
#### []Retrieving the Reference of the
 Funnel Product
 
 
 
```
...
 
'Get the reference of the Funnel product
 
Dim
 oFunnelRef 
As
 Product
 
Set
 oFunnelRef = oFunnel1.ReferenceProduct
 ...
```

 
 
 
 

In order to create new instances of a product, it is first necessary to
 retrieve the actual reference of the product from which the new instances
 will be created. This is done using the `ReferenceProduct`
 property of * *the* Product *object on the Funnel product
 created above.
 
#### []Adding and Positioning New Instances
 of the Funnel Product on the Hull
 
 
 ************************
```
...
 
'Add a second component using the existing Funnel product's reference.
 
Dim
 oFunnel2 
As
 Product
 
Set
 oFunnel2 = oTitanicProducts.
AddComponent
(oFunnelRef)
 oFunnel2.Name = "Second_Funnel"

 'Associate the new product with a different position from its reference
 
iMatrix(9) = -40.0
 oFunnel2.Move.
Apply
 iMatrix

 'Add a third component using the existing Funnel product's reference.
 
Dim
 oFunnel3 
As
 Product
 
Set
 oFunnel3 = oTitanicProducts.
AddComponent
(oFunnelRef)
 oFunnel3.Name = "Third_Funnel"

 'Associate the new product with a different position from its reference
 
iMatrix(9) = -80.0
 oFunnel3.Move.
Apply
 iMatrix

 'Add a fourth component using the existing Funnel product's reference.
 
Dim
 oFunnel4 
As
 Product
 
Set
 oFunnel4 = oTitanicProducts.
AddComponent
(oFunnelRef)
 oFunnel4.Name = "Fourth_Funnel"

 'Associate the new product with a different position from its reference
 
iMatrix(9) = -120.0
 oFunnel4.Move.
Apply
 iMatrix
 ...
```

 
 
 
 

A new instance of a product is created using the `AddComponent`
 method of the *Products *object. A specific name is assigned to the
 new product instance.  The new product instance, the Funnel, is then
 positioned on the Hull in relation to the initial reference product's
 position. This is done using by acquiring a movable object using the `Move`
 property of * *the* Product *object and then using the `Apply`
 method of the *Move *object. The same procedure is repeated for the
 last two Funnels.
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create a product structure composed of four
different instances of the same product, each having its own specific position.
Specifically, it has illustrated using:

 
- The `Add` method of the *Documents* object to create a new
 Product document.
 
- The `Product` property of the *ProductDocument *object to
 retrieve the root product of the document.
 
- The `Products` property of the *Product* object to
 retrieve the product collection.
 
- The `AddNewProduct` method of the *Products* object to add
 a new product to the collection.
 
- The `AddMasterShapeRepresentation` method of the *Product*
 object to add a new part under an existing product.
 
- The `AddComponent` method of the *Products* object to
 create a new instance of an existing product.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a macro]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*