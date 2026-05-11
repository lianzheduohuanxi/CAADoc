---
title: "Untitled"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAPstHull", "CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAScdPstUseCases", "CAAPstAddExternalComponent", "CAAPstAddExternalComponentSource", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddExternalComponent.htm"
converted: "2026-05-11T11:06:32.492923"
---

## Product Structure
 
 
## []Adding an External Component
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to create a simple product
 structure that imports an existing Part from an external Part document. It
 assumes that the CATDocView has been initialized so that it references the
 path leading to the part document, CAAPstHull.CATPart. 
 
 

Here is an image of the resulting product structure:
 
 
 |![](image/CAAPstAddExternalComponent.jpg)
 
 
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAPstAddExternalComponent is launched in CATIA [[1]].
 No previously opened document is needed.
 

[CAAPstAddExternalComponent.CATScript
 ]is located in the CAAScdPstUseCases module. [Execute
 macro] (Windows only).
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAPstAddExternalComponent includes three steps:
 

 
- [Prolog]
 
- [Open the Part Document]
 
- [Import the Part Document as a Product in
 the Collection of Products]
 
 
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
 

 'Retrieve the root product.
 
Dim
 oRoot 
As
 Product
 
Set
 oRoot = oProductDoc.Product

 'Retrieve the root product collection of products.
 
Dim
 oRootCol 
As
 Products
 
Set
 oRootCol = oRoot.Products
 

 ...
```

 
 
 
 

A new Product document is created using the `Add` method of
 the documents collection (*Documents o*bject). Next, the root product
 of the document is retrieved using the `Product` property of
 the *ProductDocument *object.  Finally, the product's collection
 is retrieved using the `Products` property of the *Product *object.
 
#### []Open the Part Document
 
 
 ****
```
...
 
'Open the Part Document
 
Dim
 oPartDoc 
As
 Document
 
Set
 oPartDoc = CATIA.Documents.
Open
(sDocPath & "CAAPstHull.CATPart")

 ...
```

 
 
 
 

The Part document to be imported is opened using the `Open`
 method of the* Documents *object.
 
#### []Import the Part Document as a Product in
 the Collection of Products
 
 
 ****
```
...
 
'Add a new component from the already opened part document.
 
Dim
 oNewComponent 
As
 Product
 
Set
 oNewComponent = oRootCol.
AddExternalComponent
(oPartDoc)
 ...
```

 
 
 
 

A new part is imported under the product collection using the `AddExternalComponent`
 method of the *Products *object.
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create a simple product structure that imports
an existing Part from an external Part document. Specifically, it has
illustrated using:

 
- The `Add` method the *Documents *object to create a new
 Product document.
 
- The `Product` property of the *ProductDocument *object to
 retrieve the root product of the document.
 
- The `Products` property of the *Product *object to
 retrieve the product collection.
 
- The `Open` method of the *Documents* object to open an
 existing external Part document.
 
- The `AddExternalComponent` method of the *Products *object
 to import the part as a product under the product collection.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a macro]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*