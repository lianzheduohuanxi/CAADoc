---
title: "Creating Structure Foundations"
category: "general"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrCreationOfStructureFoundation", "CAAScdStrUseCases"]
source_file: "Doc\online\CAAScdStrUseCases\CAAStrCreationOfStructureFoundation.htm"
converted: "2026-05-11T17:31:50.877607"
---

## Structure Design

| 

## Creating Structure Foundations  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This macro shows you how to create structure foundation. It extends a root product in a product document    
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAStrCreationOfStructureFoundation is launched in CATIA [1]. Some documents are needed.

  * [CAAStrCreationOfStructureFoundation.CATScript](CAAStrCreationOfStructureFoundationSource.htm) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrCreationOfStructureObjects.CATScript) (windows only).
  * You need to create first a new empty Product Document

   
![](../CAAScrBase/images/ascenari.gif) |  CAAStrCreationOfStructureFoundation includes five steps:

  1. Prolog
  2. Creating Foundation
  3. Retreiving the created Foundation in the assembly



####  

#### Prolog

| 
    
    
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
        Set component = products.AddNewProduct("Foundation")
    
        Set strFactory = component.GetTechnologicalObject("StructureObjectFactory")
    
      ...  
  
---  
  
This step describes how to get the structure object factory.

#### Creating structure foundation 
    
    
      ...
        Dim foundation As StrFoundation 
        Set foundation = strFactory.ExtendProductAsFoundation("")
      ...  
  
---  
  
The foundation is created by extending the product with structure data.

 

#### Retreiving the created Foundation in the assembly
    
    
      ...
        Dim foundations As StrFoundations
        Set foundations = rootProduct.GetTechnologicalObject("StructureFoundations")		
    	
        Set foundation = foundations.Item(1)
    
      ...  
  
---  
  
The foundation is retreived thanks to the collection of foundations.

 

   
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to create structure objects

[Top]

* * *

#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
