---
title: "Modifying Structure Objects"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAStrCreationOfStructureObjects", "CAAStrCreateOfStructureObject", "CAAStrModificationOfStructureObjects", "CAAScdStrUseCases", "CATIA"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfStructureObjects.md"
converted: "2026-05-11T17:31:50.901137"
---
## Structure Design

| 
## Modifying Structure Objects  
  
  
* * *

  This macro shows you how to modify structure objects. This macro modifies some member and plate properties in the document created using the CAAStrCreateOfStructureObject  macro. ![](images/CAAScdStrImg2.jpg)  
---|---  
  CAAStrModificationOfStructureObjects is launched in CATIA [1]. One document is needed. You have to run the [CAAStrCreationOfStructureObjects](CAAStrCreationOfStructureObjectsSource.md) macro before running this macro. [CAAStrModificationOfStructureObjects.CATScript](CAAStrModificationOfStructureObjectsSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrModificationOfStructureObjects.CATScript) (windows only).    
  CAAStrModificationOfStructureObjects includes four steps:

  1. Prolog
  2. Retrieving  members
  3. Modifying members 
  4. Retrieving plates 
  5. Modifying plates

####  
#### Prolog

| 
    
    
      ...
```vbscript
        Dim doc As Document
    
        Dim StrWorkbench As StrWorkbench
        Dim strFactory As StrObjectFactory
    
        Set doc = CATIA.ActiveDocument
        Dim rootProduct As Product
        Set rootProduct = doc.Product
       
        Set strWorkbench = doc.GetWorkbench("StrWorkbench")
      ...  
  
```

```

---  
  
This step describes how to get the structure workbench.
#### Retrieving members
    
    
      ...
```vbscript
       Dim strMembers as StrMembers
       Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
    
```

    
```vbscript
       Dim member as StrMember
       Set member = strMembers.Item("Column_3")
      ...  
  
```

```

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
```vbscript
        Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
    
```

        dim plate as StrPlates
        set plate = strPlates.Item("PlateType_11")
    
    
    ...
      
  
```

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

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[2] | [Creation of a structure object](CAAStrCreationOfStructureObjects.md)  
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
