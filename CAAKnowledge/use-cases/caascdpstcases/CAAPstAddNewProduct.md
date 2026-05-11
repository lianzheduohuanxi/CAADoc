---
```vbscript
title: "Adding a New Product"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAPstPad1_2", "CAAPstAddNewProduct", "CATIA", "CAAScdPstUseCases", "CAAPstPad1_1"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddNewProduct.htm"
converted: "2026-05-11T17:31:52.326450"
```

---
|
## Product Structure

|
## Adding a New Product

* * *

  This macro shows you how to create a simple product structure containing two parts. It assumes that the CATDocView has been initialized so that it references the path leading to the two part documents, CAAPstPad1_1.CATPart and CAAPstPad1_2.CATPart The macro creates a new Product document and retrieves its root product. Next, it retrieves the product collection under the root product. A new product is then added to which is associated a new master shape representation from an existing external Part document. This same process is repeated for a second new product. Here is an image of the resulting product structure:
---

This macro shows you how to create a simple product structure containing two parts. It assumes that the CATDocView has been initialized so that it references the path leading to the two part documents, CAAPstPad1_1.CATPart and CAAPstPad1_2.CATPart The macro creates a new Product document and retrieves its root product. Next, it retrieves the product collection under the root product. A new product is then added to which is associated a new master shape representation from an existing external Part document. This same process is repeated for a second new product. Here is an image of the resulting product structure:
  CAAPstAddNewProduct is launched in CATIA [1]. No previously opened document is needed. [CAAPstAddNewProduct.CATScript ](CAAPstAddNewProductSource.md)is located in the CAAScdPstUseCases module. [Execute macro](macros/CAAPstAddNewProduct.CATScript) (Windows only).
  CAAPstAddNewProduct includes five steps:

  1. Prolog
  2. Adding a New Product
  3. Assigning a Master Shape Representation to the New Product
  4. Adding a Second New Product
  5. Assigning a Master Shape Representation to the Second New Product

#### Prolog

|

      ...
```vbscript
          'Create a new product document by adding a document with the Product type
```

```vbscript
```vbscript
```vbscript
'Create a new product document by adding a document with the Product type
          'to the document collection of the CATIA application.
```

```

```

```vbscript
          Dim oProductDoc As Document
```vbscript
          Set oProductDoc = CATIA.Documents.**Add**("Product")
```

```

```vbscript
```vbscript
```vbscript
          'Retrieve the root product.
          Dim oRootProduct As Product
          Set oRootProduct = oProductDoc.Product
          'Declare the root product's part number and name.
```

```

```

```vbscript
Dim oRootProduct As Product
```vbscript
```vbscript
Set oRootProduct = oProductDoc.Product
'Declare the root product's part number and name.
          oRootProduct.PartNumber = "Root"
          oRootProduct.Name = "The_Root_Product"
```

```

```

```vbscript
```vbscript
```vbscript
          'Retrieve the product's collection under the root product.
          Dim oRootChildren As Products
          Set oRootChildren = oRootProduct.Products
```

```

```

      ...

---

A new Product document is created using the `Add` method of the documents collection (_Documents_ object). Next, the root product of the document is retrieved using the `Product` property of the _ProductDocument_ object. A Part number and name are assigned to the root product.  Finally, the product's collection is retrieved using the `Products` property of the _Product_ object. New Products within this collection will later be added to construct the product structure.
#### Adding a New Product

      ...
A new Product document is created using the `Add` method of the documents collection (_Documents_ object). Next, the root product of the document is retrieved using the `Product` property of the _ProductDocument_ object. A Part number and name are assigned to the root product.  Finally, the product's collection is retrieved using the `Products` property of the _Product_ object. New Products within this collection will later be added to construct the product structure.
```vbscript
```vbscript
          'Add a new product to the collection. This adds both a product reference
          'and a product component.

```

```

```vbscript
          Dim oChildProduct1 As Product
```vbscript
```vbscript
          Set oChildProduct1 = oRootChildren.**AddNewProduct**("Child_1_Type")
          'Declare the part number and name for this product.
          oChildProduct1.PartNumber = "Child_001"
          oChildProduct1.Name = "1st_Child"
```

```

```

      ...

---

A new product is added to the collection using the `AddNewProduct` method of the _Products_ object. The new product is then assigned a part number and name which will allow its identification in the product structure tree.
#### Assigning a Master Shape Representation to the New Product

      ...
A new product is added to the collection using the `AddNewProduct` method of the _Products_ object. The new product is then assigned a part number and name which will allow its identification in the product structure tree.
```vbscript
```vbscript
        'Add a representation to this product using an existing part and reframe
        'the viewer to display the part completely.
```

```

        oChildProduct1.**AddMasterShapeRepresentation** sDocPath & "CAAPstPad1_1.CATPart"

```vbscript
        CATIA.ActiveWindow.ActiveViewer.**Reframe**
```

      ...

---

Using the `AddMasterShapeRepresentation` method of the _Product_ object, an existing Part from an external Part document is added to the product. The Part document is found in the documentation installation path which has already been stored in the `sDocPath` variable. In order to ensure that the visualization will be adequate, the viewer must be reframed.
#### Adding a Second New Product

      ...
Using the `AddMasterShapeRepresentation` method of the _Product_ object, an existing Part from an external Part document is added to the product. The Part document is found in the documentation installation path which has already been stored in the `sDocPath` variable. In order to ensure that the visualization will be adequate, the viewer must be reframed.
```vbscript
```vbscript
          'Add another product to the root product's collection.  This adds both
          'a product reference and a product component.

```

```

```vbscript
          Dim oChildProduct2 As Product
```vbscript
```vbscript
          Set oChildProduct2 = oRootChildren.AddNewProduct("Child_2_Type")

```

```

```

```vbscript
Dim oChildProduct2 As Product
```vbscript
```vbscript
Set oChildProduct2 = oRootChildren.AddNewProduct("Child_2_Type")
          'Declare the part number and name for this product.
          oChildProduct2.PartNumber = "Child_002"
          oChildProduct2.Name = "2nd_Child"
```

```

```

      ...

---

A second new product is added to the collection in the same way as the first. The new product is also assigned a part number and name which will allow its identification in the product structure tree.
#### Assigning a Master Shape Representation to the Second New Product

      ...
A second new product is added to the collection in the same way as the first. The new product is also assigned a part number and name which will allow its identification in the product structure tree.
```vbscript
```vbscript
        'Add a representation to this product using an existing part and reframe
        'the viewer to display the part completely.
```

```

        oChildProduct2.**AddMasterShapeRepresentation** sDocPath & "CAAPstPad1_2.CATPart"

```vbscript
        CATIA.ActiveWindow.ActiveViewer.**Reframe**()
```

      ...

---

Using the `AddMasterShapeRepresentation` method of the _Product_ object, another existing Part from a second external Part document is added to the product and the viewer is reframed.

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a simple product structure containing two parts. Specifically, it has illustrated using:

  * The `Add` method of the _Documents_ object to create a new Product document.
  * The `Product` property of the _ProductDocument_ object to retrieve the root product of the document.
  * The `Products` property of the _Product_ object to retrieve the product collection.
  * The `AddNewProduct` method of the _Products_ object to add a new product to the collection.
  * The `AddMasterShapeRepresentation` method of the _Product_ object to add a new part under an existing product.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
