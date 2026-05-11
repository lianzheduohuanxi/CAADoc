---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CAAStrCreationOfStructureObjects", "CAAStrModificationOfStructureObjects", "CAAStrCreateOfStructureObject", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAScdStrImg2", "CAAStrModificationOfStructureObjectsSource", "CAAStrCreationOfStructureObjectsSource", "CAAScdStrUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfStructureObjects.htm"
converted: "2026-05-11T11:06:32.527793"
---

## Structure Design
 
 
## []Modifying Structure Objects
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

[]This macro shows you how to modify structure
 objects.
 
 

This macro modifies some member and plate properties in the document
 created using the CAAStrCreateOfStructureObject  macro.
 

![](images/CAAScdStrImg2.jpg)
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAAStrModificationOfStructureObjects is launched in
 CATIA [[1]]. One document is needed.
 

You have to run the [CAAStrCreationOfStructureObjects]
 macro before running this macro.
 

[CAAStrModificationOfStructureObjects.CATScript]
 is located in the CAAScdStrUseCases module. [Execute
 macro] (windows only).
 

 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAAStrModificationOfStructureObjects includes four
 steps:
 

 
- [Prolog]
 
- [Retrieving  members]
 
- [Modifying members ]
 
- [Retrieving plates] 
 
- [Modifying plates]
 
 
####  
 
#### []Prolog
 
 
 
```
...
 
Dim
 doc 
As
 Document

 
Dim
 StrWorkbench 
As
 StrWorkbench
 
Dim
 strFactory 
As
 StrObjectFactory

 
Set
 doc = CATIA.ActiveDocument
 
Dim
 rootProduct 
As
 Product
 
Set
 rootProduct = doc.Product
 
 
Set
 strWorkbench = doc.GetWorkbench("StrWorkbench")
 ...
```

 
 
 
 

This step describes how to get the structure workbench.
 
#### []Retrieving members
 
 
 
```
...
 
Dim
 strMembers 
as
 StrMembers
 
Set
 strMembers = rootProduct.GetTechnologicalObject("StructureMembers")
```

 
```
Dim
 member 
as
 StrMember
 
Set
 member = strMembers.Item("Column_3")
 ...
```

 
 
 
 

This step describes how to get the collection of members and how to get
 one specific element in it.
 
#### []Modifying members
 
 
 
```
...
 member.Rotate(45.0)
 member.CurrentAnchorPointName = "catStrTopCenter"
 ...
```

 
 
 
 

We rotate the member and we change its current anchor point.
 
#### []Retrieving  plates
 
 
 
```
...
 
dim
 strPlates 
as
 StrPlates
 
Set
 strPlates = rootProduct.GetTechnologicalObject("StructurePlates")

 
dim
 plate 
as
 StrPlates
 
set
 plate = strPlates.Item("PlateType_11")
```

 
```
...
```

 
 
 
 

This step describes how to get the plate collection and how to get one
 specific element in it.
 
#### []Modifying plates
 
 
 
```
...
 plate.ReverseDirection
	
 plate.StandardThickness = 0.020

 rootProduct.Update
```

 
```
...
```

 
 
 
 

We reverse the material orientation of the plate and we change its
 thickness.
 

 
 
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to modify structure objects.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a macro]
 
 
 |[2]
 |[Creation of a
 structure object]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*