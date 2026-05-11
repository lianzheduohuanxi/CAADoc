---
```vbscript
title: "Adding an External Component"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAPstAddExternalComponent", "CAAScdPstUseCases", "CATIA", "CAAPstHull"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddExternalComponent.htm"
converted: "2026-05-11T17:31:52.319791"
```

---
|
## Product Structure

|
## Adding an External Component

* * *

  This macro shows you how to create a simple product structure that imports an existing Part from an external Part document. It assumes that the CATDocView has been initialized so that it references the path leading to the part document, CAAPstHull.CATPart.  Here is an image of the resulting product structure:
---

This macro shows you how to create a simple product structure that imports an existing Part from an external Part document. It assumes that the CATDocView has been initialized so that it references the path leading to the part document, CAAPstHull.CATPart.  Here is an image of the resulting product structure:
  CAAPstAddExternalComponent is launched in CATIA [1]. No previously opened document is needed. [CAAPstAddExternalComponent.CATScript ](CAAPstAddExternalComponentSource.md)is located in the CAAScdPstUseCases module. [Execute macro](macros/CAAPstAddExternalComponent.CATScript) (Windows only).
  CAAPstAddExternalComponent includes three steps:

  1. Prolog
  2. Open the Part Document
  3. Import the Part Document as a Product in the Collection of Products

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
          Dim oProductDoc As Document
```vbscript
          Set oProductDoc = CATIA.Documents.**Add**("Product")
```

```

```vbscript
```vbscript
```vbscript
          'Retrieve the root product.
          Dim oRoot As Product
          Set oRoot = oProductDoc.Product
          'Retrieve the root product collection of products.
          Dim oRootCol As Products
          Set oRootCol = oRoot.Products
```

```

```

      ...

---

A new Product document is created using the `Add` method of the documents collection (_Documents o_ bject). Next, the root product of the document is retrieved using the `Product` property of the _ProductDocument_ object.  Finally, the product's collection is retrieved using the `Products` property of the _Product_ object.
#### Open the Part Document

      ...
A new Product document is created using the `Add` method of the documents collection (_Documents o_ bject). Next, the root product of the document is retrieved using the `Product` property of the _ProductDocument_ object.  Finally, the product's collection is retrieved using the `Products` property of the _Product_ object.
```vbscript
```vbscript
          'Open the Part Document

```

```

```vbscript
          Dim oPartDoc As Document
```vbscript
          Set oPartDoc = CATIA.Documents.**Open**(sDocPath & "CAAPstHull.CATPart")
```

```

      ...

---

The Part document to be imported is opened using the `Open` method of the _Documents_ object.
#### Import the Part Document as a Product in the Collection of Products

      ...
The Part document to be imported is opened using the `Open` method of the _Documents_ object.
```vbscript
```vbscript
          'Add a new component from the already opened part document.

```

```

```vbscript
          Dim oNewComponent As Product
```vbscript
          Set oNewComponent = oRootCol.**AddExternalComponent**(oPartDoc)
```

```

      ...

---

A new part is imported under the product collection using the `AddExternalComponent` method of the _Products_ object.

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a simple product structure that imports an existing Part from an external Part document. Specifically, it has illustrated using:

  * The `Add` method the _Documents_ object to create a new Product document.
  * The `Product` property of the _ProductDocument_ object to retrieve the root product of the document.
  * The `Products` property of the _Product_ object to retrieve the product collection.
  * The `Open` method of the _Documents_ object to open an existing external Part document.
  * The `AddExternalComponent` method of the _Products_ object to import the part as a product under the product collection.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
