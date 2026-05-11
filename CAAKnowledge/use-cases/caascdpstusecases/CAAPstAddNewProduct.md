---
title: "Untitled"
category: "use-case"
module: "CAAScdPstUseCases"
tags: ["CAAScrBase", "CAAPstPad1_1", "CAAPstPad1_2", "CATIA", "CAAScrJavaScript", "CAAScdPstUseCases", "CAAScdInfUseCases", "CAAPstAddNewProduct", "CAAPstAddNewProductSource", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdPstUseCases/CAAPstAddNewProduct.htm"
converted: "2026-05-11T11:27:02.578575"
---

---

      

 
    
  
  
    ![](../CAAScrBase/images/ainfo.gif)
    
      

CAAPstAddNewProduct is launched in CATIA [1].
      No previously opened document is needed.
      

[CAAPstAddNewProduct.CATScript
      ](CAAPstAddNewProductSource.htm)is located in the CAAScdPstUseCases module. [Execute
      macro](macros/CAAPstAddNewProduct.CATScript) (Windows only).
      

 
    
  
  
    ![](../CAAScrBase/images/ascenari.gif)
    
      

CAAPstAddNewProduct includes five steps:
      

        
- Prolog
        
- Adding a New Product
        
- Assigning a Master Shape Representation
          to the New Product
        
- Adding a Second New Product
        
- Assigning a Master Shape Representation
          to the Second New Product
      
      

#### Prolog
      
      

A new Product document is created using the `Add` method of
      the documents collection (*Documents *object). Next, the root product
      of the document is retrieved using the `Product` property of
      the *ProductDocument *object. A Part number and name are assigned to
      the root product.  Finally, the product's collection is retrieved
      using the `Products` property of the *Product *object. New
      Products within this collection will later be added to construct the
      product structure. 
      

#### Adding a New Product 
      
      

A new product is added to the collection using the `AddNewProduct`
      method of the *Products *object. The new product is then assigned a
      part number and name which will allow its identification in the product
      structure tree.
      

#### Assigning a Master Shape Representation
      to the New Product
      
      

Using the `AddMasterShapeRepresentation` method of the *Product
      *object, an existing Part from an external Part document is added to
      the product. The Part document is found in the documentation installation
      path which has already been stored in the `sDocPath` variable.
      In order to ensure that the visualization will be adequate, the viewer
      must be reframed. 
      

#### Adding a Second New Product 
      
      

A second new product is added to the collection in the same way as the
      first. The new product is also assigned a part number and name which will
      allow its identification in the product structure tree.
      

#### Assigning a Master Shape
      Representation to the Second New Product
      
      

Using the `AddMasterShapeRepresentation` method of the *Product
      *object, another existing Part from a second external Part document is
      added to the product and the viewer is reframed.
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create a simple product structure containing
two parts. Specifically, it has illustrated using:

  
- The `Add` method of the *Documents *object
    to create a new Product document.
  
- The `Product` property of the *ProductDocument *object to
    retrieve the root product of the document.
  
- The `Products` property of the *Product* object to
    retrieve the product collection.
  
- The `AddNewProduct` method of the *Products*
    object to add a new product to the collection.
  
- The `AddMasterShapeRepresentation` method of the
    *Product* object to add a new part under an existing product.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
...
      'Create a new product document by adding a document with the Product type
      'to the document collection of the CATIA application. 
      Dim oProductDoc As Document
      Set oProductDoc = CATIA.Documents.Add(&quot;Product&quot;)

      'Retrieve the root product.
      Dim oRootProduct As Product
      Set oRootProduct = oProductDoc.Product

      'Declare the root product's part number and name.
      oRootProduct.PartNumber = &quot;Root&quot;
      oRootProduct.Name = &quot;The_Root_Product&quot;

      'Retrieve the product's collection under the root product.
      Dim oRootChildren As Products
      Set oRootChildren = oRootProduct.Products 
  ...
```

```vbscript
...
      'Add a new product to the collection. This adds both a product reference
      'and a product component.
      Dim oChildProduct1 As Product
      Set oChildProduct1 = oRootChildren.AddNewProduct(&quot;Child_1_Type&quot;)

      'Declare the part number and name for this product.
      oChildProduct1.PartNumber = &quot;Child_001&quot;
      oChildProduct1.Name = &quot;1st_Child&quot;
  ...
```

```vbscript
...
    'Add a representation to this product using an existing part and reframe
    'the viewer to display the part completely.
    oChildProduct1.AddMasterShapeRepresentation sDocPath &amp; &quot;CAAPstPad1_1.CATPart&quot;
    CATIA.ActiveWindow.ActiveViewer.Reframe
  ...
```

```vbscript
...
      'Add another product to the root product's collection.  This adds both
      'a product reference and a product component.
      Dim oChildProduct2 As Product
      Set oChildProduct2 = oRootChildren.AddNewProduct(&quot;Child_2_Type&quot;)


      'Declare the part number and name for this product.
      oChildProduct2.PartNumber = &quot;Child_002&quot;
      oChildProduct2.Name = &quot;2nd_Child&quot;
  ...
```

```vbscript
...
    'Add a representation to this product using an existing part and reframe
    'the viewer to display the part completely.
    oChildProduct2.AddMasterShapeRepresentation sDocPath &amp; &quot;CAAPstPad1_2.CATPart&quot;
    CATIA.ActiveWindow.ActiveViewer.Reframe()
  ...
```