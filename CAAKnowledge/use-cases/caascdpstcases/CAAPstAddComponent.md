---
```vbscript
title: "Adding Components"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAPstAddComponent", "CAAPstHull", "CATIA", "CAAScdPstUseCases", "CAAPstFunnel"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddComponent.htmmd"
converted: "2026-05-11T17:31:52.313802"
```

---
## Product Structure

|
## Adding Components

* * *

  This macro shows you how to create a product structure composed of four different instances of the same product, each having its own specific position. These four products are positioned so that they represent the funnels on the hull of the Titanic. The macro assumes that the CATDocView has been initialized so that it references the path leading to the two part documents, CAAPstHull.CATPart and CAAPstFunnel.CATPart. Here is an image of the resulting product structure and its representation:
---

This macro shows you how to create a product structure composed of four different instances of the same product, each having its own specific position. These four products are positioned so that they represent the funnels on the hull of the Titanic. The macro assumes that the CATDocView has been initialized so that it references the path leading to the two part documents, CAAPstHull.CATPart and CAAPstFunnel.CATPart. Here is an image of the resulting product structure and its representation:
  CAAPstAddComponent is launched in CATIA [1]. No previously opened document is needed. [CAAPstAddComponent.CATScript ](CAAPstAddComponentSource.md)is located in the CAAScdPstUseCases module. [Execute macro](macros/CAAPstAddComponent.CATScript) (Windows only).
  CAAPstAddComponent includes eight steps:

  1. Prolog
  2. Adding a New Product: the Hull
  3. Assigning a Master Shape Representation to the Hull
  4. Adding a Second New Product: the Funnel
  5. Assigning a Master Shape Representation to the Funnel
  6. Initializing the Position Matrix for the Instances of the Funnel
  7. Retrieving the Reference of the Funnel Product
  8. Adding and Positioning New Instances of the Funnel Product on the Hull

#### Prolog

|

      ...
```vbscript
          'Create a new product document object by adding a document with the Product
```

```vbscript
```vbscript
```vbscript
'Create a new product document object by adding a document with the Product
          'type to the document collection of the CATIA application.
```

```

```

```vbscript
```vbscript
          Dim oProductDoc As Document
```vbscript
```
```vbscript
          Set oProductDoc = CATIA.Documents.**Add**("Product")
```
```

```

```vbscript
```vbscript
```vbscript
          'Retrieve the Titanic as the root product.
```vbscript
          Dim oTitanic As Product
          Set oTitanic = oProductDoc.Product
          'Declare the Titanic's part number and name.
```
```

```

```

```vbscript
```vbscript
Dim oTitanic As Product
```vbscript
```
```vbscript
```vbscript
Set oTitanic = oProductDoc.Product
'Declare the Titanic's part number and name.
```
          oTitanic.PartNumber = "Titanic"
          oTitanic.Name = "Steam_Ship_Titanic"
```

```

```

```vbscript
```vbscript
```vbscript
          'Retrieve the product's collection of the Titanic.
```vbscript
          Dim oTitanicProducts As Products
          Set oTitanicProducts = oTitanic.Products
```
```

```

```

      ...

---

A new Product document is created using the `Add` method of the documents collection (_Documents_ object). Next, the root product of the document is retrieved using the `Product` property of the _ProductDocument_ object. A Part number and name are assigned to the root product.  Finally, the product's collection is retrieved using the `Products` property of the _Product_ object. New Products within this collection will later be added to construct the product structure.
#### Adding a New Product: the Hull

      ...
A new Product document is created using the `Add` method of the documents collection (_Documents_ object). Next, the root product of the document is retrieved using the `Product` property of the _ProductDocument_ object. A Part number and name are assigned to the root product.  Finally, the product's collection is retrieved using the `Products` property of the _Product_ object. New Products within this collection will later be added to construct the product structure.
```vbscript
```vbscript
          'Add the hull as a new component in the collection with its part number
          'and name.

```

```

```vbscript
```vbscript
          Dim oHull As Product
```vbscript
```
```vbscript
```vbscript
          Set  oHull = oTitanicProducts.**AddNewProduct**("Hull_Type")
          oHull.PartNumber = "Titanic's_Hull"
```
          oHull.Name = "Unsinkable_Hull"
```

```

```

      ...

---

A new product, the Hull,  is added to the collection using the `AddNewProduct` method of the _Products_ object. The new product is then assigned a part number and name which will allow its identification in the product structure tree.
#### Assigning a Master Shape Representation to the Hull

      ...
A new product, the Hull,  is added to the collection using the `AddNewProduct` method of the _Products_ object. The new product is then assigned a part number and name which will allow its identification in the product structure tree.
```vbscript
```vbscript
          'Add a master shape representation to the hull using an existing part and
          'reframe the viewer.
```

```

          oHull.**AddMasterShapeRepresentation** sDocPath & "CAAPstHull.CATPart"

```vbscript
```vbscript
          CATIA.ActiveWindow.ActiveViewer.**Reframe**
```
```

      ...

---

Using the `AddMasterShapeRepresentation` method of the _Product_ object, an existing Part from an external Part document is added to the product. The Part document is found in the documentation installation path which has already been stored in the `sDocPath` variable. In order to ensure that the visualization will be adequate, the viewer must be reframed.
#### Adding a Second New Product: the Funnel

      ...
Using the `AddMasterShapeRepresentation` method of the _Product_ object, an existing Part from an external Part document is added to the product. The Part document is found in the documentation installation path which has already been stored in the `sDocPath` variable. In order to ensure that the visualization will be adequate, the viewer must be reframed.
```vbscript
```vbscript
        'Add the first funnel to the Titanic's product collection, with part number
        'and name.

```

```

```vbscript
```vbscript
        Dim oFunnel1 As Product
```vbscript
```
```vbscript
```vbscript
        Set oFunnel1 = oTitanicProducts.**AddNewProduct**("Funnel_Type")
        oFunnel1.PartNumber = "Titanic's_Funnel"
```
        oFunnel1.Name = "Fore_Funnel"
```

```

```

      ...

---

A second new product, the Funnel,  is added to the collection using the `AddNewProduct` method of __ the _Products_ object. The new product is then assigned a part number and name which will allow its identification in the product structure tree.
#### Assigning a Master Shape Representation to the Funnel

      ...
A second new product, the Funnel,  is added to the collection using the `AddNewProduct` method of __ the _Products_ object. The new product is then assigned a part number and name which will allow its identification in the product structure tree.
```vbscript
          'Add a master shape representation to the funnel using an existing part
```

          oFunnel1.**AddMasterShapeRepresentation** sDocPath & "CAAPstFunnel.CATPart"

      ...

---

Using the `AddMasterShapeRepresentation` method of the _Product_ object, an existing Part from an external Part document is added to the product. The Part document is found in the documentation installation path which has already been stored in the `sDocPath` variable.
#### Initializing the Position Matrix for the Instances of the Funnel

      ...
Using the `AddMasterShapeRepresentation` method of the _Product_ object, an existing Part from an external Part document is added to the product. The Part document is found in the documentation installation path which has already been stored in the `sDocPath` variable.
```vbscript
```vbscript
          'Define the initial positioning parameters for the Funnel1 instances.

```

```

```vbscript
```vbscript
          Dim iMatrix(11)
```vbscript
```
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
```

```

      ...

---

Remember that arrays are initialized to 1 less than the maximum number of items in the array.
#### Retrieving the Reference of the Funnel Product

      ...
Remember that arrays are initialized to 1 less than the maximum number of items in the array.
```vbscript
```vbscript
          'Get the reference of the Funnel product

```

```

```vbscript
```vbscript
          Dim oFunnelRef As Product
```vbscript
```
```vbscript
          Set oFunnelRef = oFunnel1.ReferenceProduct
```
```

```

      ...

---

In order to create new instances of a product, it is first necessary to retrieve the actual reference of the product from which the new instances will be created. This is done using the `ReferenceProduct` property of __ the _Product_ object on the Funnel product created above.
#### Adding and Positioning New Instances of the Funnel Product on the Hull

      ...
In order to create new instances of a product, it is first necessary to retrieve the actual reference of the product from which the new instances will be created. This is done using the `ReferenceProduct` property of __ the _Product_ object on the Funnel product created above.
```vbscript
```vbscript
          'Add a second component using the existing Funnel product's reference.

```

```

```vbscript
```vbscript
          Dim oFunnel2 As Product
```vbscript
```
```vbscript
```vbscript
          Set oFunnel2 = oTitanicProducts.**AddComponent**(oFunnelRef)
          oFunnel2.Name = "Second_Funnel"
```
          'Associate the new product with a different position from its reference
```

          iMatrix(9) = -40.0
```

          oFunnel2.Move.**Apply** iMatrix
```

```vbscript
```vbscript
```vbscript
          'Add a third component using the existing Funnel product's reference.
```vbscript
          Dim oFunnel3 As Product
          Set oFunnel3 = oTitanicProducts.**AddComponent**(oFunnelRef)
```
```

```

```

```vbscript
```vbscript
```vbscript
'Add a third component using the existing Funnel product's reference.
```vbscript
Dim oFunnel3 As Product
Set oFunnel3 = oTitanicProducts.**AddComponent**(oFunnelRef)
          oFunnel3.Name = "Third_Funnel"
```
          'Associate the new product with a different position from its reference
```

          iMatrix(9) = -80.0
```

          oFunnel3.Move.**Apply** iMatrix
```

```vbscript
```vbscript
```vbscript
          'Add a fourth component using the existing Funnel product's reference.
```vbscript
          Dim oFunnel4 As Product
          Set oFunnel4 = oTitanicProducts.**AddComponent**(oFunnelRef)
```
```

```

```

```vbscript
```vbscript
```vbscript
'Add a fourth component using the existing Funnel product's reference.
```vbscript
Dim oFunnel4 As Product
Set oFunnel4 = oTitanicProducts.**AddComponent**(oFunnelRef)
          oFunnel4.Name = "Fourth_Funnel"
```
          'Associate the new product with a different position from its reference
```

          iMatrix(9) = -120.0
```

          oFunnel4.Move.**Apply** iMatrix
```

      ...

---

A new instance of a product is created using the `AddComponent` method of the _Products_ object. A specific name is assigned to the new product instance.  The new product instance, the Funnel, is then positioned on the Hull in relation to the initial reference product's position. This is done using by acquiring a movable object using the `Move` property of __ the _Product_ object and then using the `Apply` method of the _Move_ object. The same procedure is repeated for the last two Funnels.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a product structure composed of four different instances of the same product, each having its own specific position. Specifically, it has illustrated using:

  * The `Add` method of the _Documents_ object to create a new Product document.
  * The `Product` property of the _ProductDocument_ object to retrieve the root product of the document.
  * The `Products` property of the _Product_ object to retrieve the product collection.
  * The `AddNewProduct` method of the _Products_ object to add a new product to the collection.
  * The `AddMasterShapeRepresentation` method of the _Product_ object to add a new part under an existing product.
  * The `AddComponent` method of the _Products_ object to create a new instance of an existing product.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
