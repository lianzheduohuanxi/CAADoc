---
title: "CATIArrNomenclature, CATIArrNomenclatures, CATIArrNomenclatureTrees 
 Interfaces Use Case"
category: "general"
module: "CAAScdArrUseCases"
tags: ["CAAPslNomenAccessFeat", "CATIA", "CATIArrNomenclatures", "CATIArrNomenclature", "CATIAArrNomenclatureTrees", "CATIArrNomenclatureTrees"]
source_file: "Doc\online\CAAScdArrUseCases\CAAPslNomenAccessFeat.htm"
converted: "2026-05-11T17:31:51.577544"
---

## Arrangement  
  
| 

## CATIArrNomenclature, CATIArrNomenclatures, CATIArrNomenclatureTrees Interfaces Use Case  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) | This example shows how to extract Bendable Data from BendableString objects (Pipe with bends, Tube with bends). Help is taken of a macro. This macro has a reference to CATIArrNomenclature , CATIArrNomenclatures and CATIAArrNomenclatureTrees Interfaces (referred to as ArrNomenclature, ArrNomenclatures and ArrNomenclatureTree in reference Visual Basic document).This macro opens an existing Product document and retrieves the BaseNomenclatures from ArrNomenclatureTree. Then it obtains the ArrNomanclatures and ArrNomenclature recursively.  
---|---  
![](../CAAScrBase/images/ainfo.gif) | PSLNomenAccessFeat is launched after CATIA is up and the reference document is opened.PslNomenFeatAccess.CATScript is located in the runtime directory Operating System (say intel_a)\code\command  
![](../CAAScrBase/images/ascenari.gif) | CAAPslNomenAccessFeat includes the following steps:

  1. Prolog
  2. Obtain the ArrNomenclatures object.
  3. Start to get the information about ArrNomenclature object from ArrNomenclatures object recursively.
  4. Epilog



#### Prolog

| 
    
    
      ...
      a) Open the Input Document
      b) Run the macro
      ...  
  
---  
  
Once the Product has been loaded, the macro is designed to read the relevant objects from the model.

#### Obtain the ArrNomenclatures object
    
    
    ...
       '//---------- Get Arrworkbench from current document
       Dim objDocument0 As Object
       Set objDocument0 = CATIA.ActiveDocument  
       Dim objArrWorkbench1 As Workbench
       Set objArrWorkbench1 = objDocument0.GetWorkbench  ( "ArrWorkbench" )
       '//---------- Get ArrNomenclatureTree from ArrWorkbench
       Dim objArrNomTree1 As ArrNomenclatureTree
       Set objArrNomTree1 = objArrWorkbench1.ArrNomenclatureTree

'//---------- Get ArrNomenclatures from ArrNomenclatureTree and get a count of the Nomenclatures Dim objArrNomTopNode As ArrNomenclatures Set objArrNomTopNode = objArrNomTree1.BaseNomenclatures Dim intNBOfNom intNBOfNom = objArrNomTopNode.Count ...  
  

---  
  
#### Start to get the information about ArrNomenclature object from ArrNomenclatures object recursively
    
    
    ...
       Dim intK
       Dim objKArrNom As ArrNomenclature
       Dim strIntSysClassName
       Dim strNLSInstanceName
       Dim strIconName
      '// -------- Recursively loop Through each Nomenclature and do the following
       Set objKArrNom = objArrNomTopNode.Item(intK)
       strIntSysClassName = objKArrNom.IntSysClassName
       strNLSInstanceName = objKArrNom.NLSInstanceName
       strIconName = objKArrNom.IconName
       '// ArrNomenclature can contain various subtypes
       Dim objArrSubTypes As ArrNomenclatures
       Set objArrSubTypes = iobjArrNomen.SubTypes
       intNBOfNom = objArrSubtypes.Count
       Dim objJArrNom As ArrNomenclature
       For intJ=1 to intNBOfNom  
       Set objJArrNom = objArrSubTypes.Item(intJ) 
       strNLSInstanceName = objJArrNom.NLSInstanceName
       strIntSysClassName = objJArrNom.IntSysClassName
       strIconName = objJArrNom.IconName
       ' Call recursive function again on objJArrNom
      ...  
  
---  
  
#### Epilog

Thus we saw how to read a CATProduct document, retrieve the objects we are interested in and get more information about the objects
    
    
    ...
    End Sub  
  
---  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

Thus we saw how to read a CATProduct document, retrieve the objects we are interested in and get more information about the objects

[Top]

* * *

#### References

[1] | Replaying a macro  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
