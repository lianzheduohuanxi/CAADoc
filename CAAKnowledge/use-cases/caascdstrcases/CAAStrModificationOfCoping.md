---
title: "Modifying Copings"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrEditCoping", "CAAScdStrUseCases"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrModificationOfCoping.htm"
converted: "2026-05-11T17:31:50.892078"
---

| 
## Structure Design

| 
## Modifying Copings  
  
  
* * *

  This macro shows you how to Edit existing coping between structure objects. This macro modifies SubType of Existing Coping created using CreateCoping Macro. ![Starting Product](images/CAAScdStrCoping02.png)  
---|---  
  CAAStrEditCoping is launched in CATIA [1]. Some documents are needed.

  * [CAAStrEditCoping.CATScript](CAAStrModificationOfCopingSource.md) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrEditCoping.CATScript) (Windows only).
  * The document Product1.CATProduct is located in the CAAScdStrUseCases module in the samples directory. Part1.CATPart is linked to the previous document and it contains the grid used by the macro.

  
  CAAStrEditCoping includes two steps:

  1. Prolog
  2. Retrieving Existing Coping and Modifying its SubType

#### Prolog
    
    
```vbscript
    Sub CATMain()
    
```vbscript
      Dim StrWorkbench As StrWorkbench
      Dim strFactory As StrObjectFactory
    
      Set doc = CATIA.ActiveDocument
      Dim rootProduct As Product
      Set rootProduct = doc.Product
    
      Set StrWorkbench = doc.GetWorkbench("StrWorkbench")
        
      Dim strPlates As strPlates
      Set strPlates = rootProduct.GetTechnologicalObject("StructurePlates")
       
      Dim strMembers As strMembers
      Set strMembers = rootProduct.GetTechnologicalObject("StructureMembers")

```
#### Retrieving Existing Coping and Modifying its SubType

The Existing coping can be searched by using the search method on selection.”Coping.1” is searched for in the entire product. The subtype of 1st coping feature is modifed to "CurrCurr".
    
    
```vbscript
      Dim selection1 As Selection
      Set selection1 = doc.Selection
    
```

      selection1.Search "Name='Coping.1',all"
    
```vbscript
      Dim NibblingToEdit As StrNibblingFeature
      Set NibblingToEdit = selection1.Item(1).Value
    
      Dim SubTypeOfNibbling As String
      SubTypeOfNibbling = NibblingToEdit.SubType
    
```

      NibblingToEdit.SubType = "CurrCurr"
    
```vbscript
    End Sub  
  
```

![End Task Icon](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to edit coping between structure objects.

[Top]

* * *
#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
```

[Top]  
  
* * *

_Copyright 1999-2010, Dassault Systmes. All rights reserved._
