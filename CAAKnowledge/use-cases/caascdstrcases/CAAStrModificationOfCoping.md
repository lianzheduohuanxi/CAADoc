---
title: "Modifying Copings"
category: "general"
module: "CAAScdStrUseCases"
tags: ["CATIA", "CAAStrEditCoping", "CAAScdStrUseCases"]
source_file: "Doc\online\CAAScdStrUseCases\CAAStrModificationOfCoping.htm"
converted: "2026-05-11T17:31:50.892078"
---

| 

## Structure Design

| 

## Modifying Copings  
  
---|---  
  
* * *

![Target Icon](../CAAScrBase/images/atarget.gif) |  This macro shows you how to Edit existing coping between structure objects. This macro modifies SubType of Existing Coping created using CreateCoping Macro. ![Starting Product](images/CAAScdStrCoping02.png)  
---|---  
![Information Icon](../CAAScrBase/images/ainfo.gif) |  CAAStrEditCoping is launched in CATIA [1]. Some documents are needed.

  * [CAAStrEditCoping.CATScript](CAAStrModificationOfCopingSource.htm) is located in the CAAScdStrUseCases module. [Execute macro](macros/CAAStrEditCoping.CATScript) (Windows only).
  * The document Product1.CATProduct is located in the CAAScdStrUseCases module in the samples directory. Part1.CATPart is linked to the previous document and it contains the grid used by the macro.

  
![Scenario Icon](../CAAScrBase/images/ascenari.gif) |  CAAStrEditCoping includes two steps:

  1. Prolog
  2. Retrieving Existing Coping and Modifying its SubType



#### Prolog
    
    
    Sub CATMain()
    
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

#### Retrieving Existing Coping and Modifying its SubType

The Existing coping can be searched by using the search method on selection.”Coping.1” is searched for in the entire product. The subtype of 1st coping feature is modifed to "CurrCurr".
    
    
      Dim selection1 As Selection
      Set selection1 = doc.Selection
    
      selection1.Search "Name='Coping.1',all"
    
      Dim NibblingToEdit As StrNibblingFeature
      Set NibblingToEdit = selection1.Item(1).Value
    
      Dim SubTypeOfNibbling As String
      SubTypeOfNibbling = NibblingToEdit.SubType
    
      NibblingToEdit.SubType = "CurrCurr"
    
    End Sub  
  
![End Task Icon](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to edit coping between structure objects.

[Top]

* * *

#### References

[1] | [Replaying a macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[Top]  
  
* * *

_Copyright 1999-2010, Dassault Systmes. All rights reserved._
