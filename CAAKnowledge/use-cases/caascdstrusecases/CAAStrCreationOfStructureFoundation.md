---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CAAStrCreationOfStructureFoundation", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAStrCreationOfStructureFoundationSource", "CAAScdStrUseCases", "CAAInfLauchMacro", "CAAStrCreationOfStructureObjects"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfStructureFoundation.htm"
converted: "2026-05-11T11:27:02.593399"
---

---

      

This step describes how to get the structure object factory.
      

#### Creating structure foundation 
      
      

The foundation is created by extending the product with structure data.
      

 
      

#### Retreiving the created Foundation in the assembly
      
      

The foundation is retreived thanks to the collection of foundations.
      

 
      

 
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create structure objects

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
...
    Dim doc As Document

    Dim StrWorkbench As StrWorkbench
    Dim strFactory As StrObjectFactory

    Set doc = CATIA.ActiveDocument
    Dim rootProduct As Product
    Set rootProduct = doc.Product

    Dim products As Products
    Set products = rootProduct.Products

    Dim component As Product
    Set component = products.AddNewProduct(&quot;Foundation&quot;)

    Set strFactory = component.GetTechnologicalObject(&quot;StructureObjectFactory&quot;)

  ...
```

```vbscript
...
    Dim foundation As StrFoundation 
    Set foundation = strFactory.ExtendProductAsFoundation(&quot;&quot;)
  ...
```

```vbscript
...
    Dim foundations As StrFoundations
    Set foundations = rootProduct.GetTechnologicalObject(&quot;StructureFoundations&quot;)		
	
    Set foundation = foundations.Item(1)

  ...
```