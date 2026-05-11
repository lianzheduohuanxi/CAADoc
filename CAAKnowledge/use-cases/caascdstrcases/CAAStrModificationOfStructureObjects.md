---
title: "Modifying Structure Objects"
category: "general"
module: "CAAScdStrUseCases"
tags: ["CAAStrCreationOfStructureObjects", "CAAStrCreateOfStructureObject", "CAAStrModificationOfStructureObjects", "CAAScdStrUseCases", "CATIA"]
source_file: "Doc\online\CAAScdStrUseCases\CAAStrModificationOfStructureObjects.htm"
converted: "2026-05-11T17:31:50.901137"
---

## Structure Design

| 

## Modifying Structure Objects  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This macro shows you how to modify structure objects. This macro modifies some member and plate properties in the document created using the CAAStrCreateOfStructureObject  macro. ![](images/CAAScdStrImg2.jpg)  
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAStrModificationOfStructureObjects is launched in CATIA [1]. One document is needed. You have to run the [CAAStrCreationOfStructureObjects](CAAStrCreationOfStructureObjectsSource.htm) macro before running this macro. [CAAStrModificationOfStructureObjects.CATScript](CAAStrModificationOfStructureObjectsSource.htm) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrModificationOfStructureObjects.CATScript) (windows only).    
![](../CAAScrBase/images/ascenari.gif) |  CAAStrModificationOfStructureObjects includes four steps:

  1. Prolog
  2. Retrieving  members
  3. Modifying members 
  4. Retrieving plates 
  5. Modifying plates



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
       
        Set strWorkbench = doc.GetWorkbench("StrWorkbench")
      ...  
  
---  
  
This step describes how to get the structure workbench.

#### Retrieving members
    
    
      ...
       Dim strMembers as StrMembers
       Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
    
    
       Dim member as StrMember
       Set member = strMembers.Item("Column_3")
      ...  
  
---  
  
This step describes how to get the collection of members and how to get one specific element in it.

#### Modifying members
    
    
    ...
       member.Rotate(45.0)
       member.CurrentAnchorPointName = "catStrTopCenter"
      ...  
  
---  
  
We rotate the member and we change its current anchor point.

#### Retrieving  plates
    
    
    ...
        dim strPlates as StrPlates
        Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
    
        dim plate as StrPlates
        set plate = strPlates.Item("PlateType_11")
    
    
    ...
      
  
---  
  
This step describes how to get the plate collection and how to get one specific element in it.

#### Modifying plates
    
    
    ...
      plate.ReverseDirection
    	
      plate.StandardThickness = 0.020
    
      rootProduct.Update
    
    
    ...
      
  
---  
  
We reverse the material orientation of the plate and we change its thickness.

   
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to modify structure objects.

[Top]

* * *

#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[2] | [Creation of a structure object](CAAStrCreationOfStructureObjects.htm)  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
