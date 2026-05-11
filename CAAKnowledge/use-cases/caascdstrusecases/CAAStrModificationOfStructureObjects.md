---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CAAStrCreationOfStructureObjectsSource", "CATIA", "CAAScrJavaScript", "CAAStrModificationOfStructureObjects", "CAAScdInfUseCases", "CAAScdStrImg2", "CAAScdStrUseCases", "CAAStrCreationOfStructureObjects", "CAAInfLauchMacro", "CAAStrModificationOfStructureObjectsSource", "CAAStrCreateOfStructureObject"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfStructureObjects.htm"
converted: "2026-05-11T11:27:02.595137"
---

---

      

This step describes how to get the structure workbench.
      

#### Retrieving members
      
      

This step describes how to get the collection of members and how to get
      one specific element in it.
      

#### Modifying members
      
      

We rotate the member and we change its current anchor point.
      

#### Retrieving  plates
      
      

This step describes how to get the plate collection and how to get one
      specific element in it.
      

#### Modifying plates
      
      

We reverse the material orientation of the plate and we change its
      thickness.
      

 
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to modify structure objects.

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
   
    Set strWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
  ...
```

```vbscript
...
   Dim strMembers as StrMembers
   Set strMembers = rootProduct.GetTechnologicalObject(&quot;StructureMembers&quot;)
```

```vbscript
Dim member as StrMember
   Set member = strMembers.Item(&quot;Column_3&quot;)
  ...
```

```vbscript
...
   member.Rotate(45.0)
   member.CurrentAnchorPointName = &quot;catStrTopCenter&quot;
  ...
```

```vbscript
...
    dim strPlates as StrPlates
    Set strPlates = rootProduct.GetTechnologicalObject(&quot;StructurePlates&quot;)

    dim plate as StrPlates
    set plate = strPlates.Item(&quot;PlateType_11&quot;)
```

```vbscript
...
```

```vbscript
...
  plate.ReverseDirection
	
  plate.StandardThickness = 0.020

  rootProduct.Update
```

```vbscript
...
```