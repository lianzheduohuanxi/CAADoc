---
title: "DraftingInterfaces Modifications"
category: "general"
module: "CAACenAPIChangesR7"
tags: ["CATISpecObject", "CATIGenerSpec", "CATIDrwSubString", "CATIDrwText", "CATIDrwAnnotationFactory", "CATIDrwLeader"]
source_file: "Doc\online\CAACenAPIChangesR7\DraftingInterfaces.htm"
converted: "2026-05-11T17:33:52.011735"
---

CAA API Modifications|  DraftingInterfaces  |   
---|---|---  
  
* * *

**Entity|  Modification| To Do** | DraftingInterfaces/Protected/CATIDrwAnnotationFactory.h/CATIDrwAnnotationFactory/CreateDimension| INDM| Dimension API  for CSC is nodoc (No impact). CreateDimension API has a new initialize argument  New method to create arrow   
---|---|---  
DraftingInterfaces/Protected/CATIDrwLeader.h/CATIDrwLeader/SetSymbolType| MHBDM| New nodoc method:  SetAttachElem   
DraftingInterfaces/Protected/CATIDrwSubString.h/CATIDrwSubString/InsertVariable| MHBDM| InsertVariable method takes CATBaseUnknow instead of CATISpecObject.  
DraftingInterfaces/Protected/CATIDrwSubString.h/CATIDrwSubString/GetVariablePositions| MHBDM| GetListOfVariables method is deprecated ==> Use new GetListOfVariables method with CATListValCATBaseUnknown  
DraftingInterfaces/Protected/CATIDrwText.h/CATIDrwText/InsertVariable| MHBDM| InsertVariable method takes CATBaseUnknow instead of CATISpecObject  
DraftingInterfaces/Protected/CATIDrwText.h/CATIDrwText/GetVariablePositions| MHBDM| New GetListOfVariables  with CATListValCATBaseUnknown in Input.  
DraftingInterfaces/Protected/CATIDrwText.h/CATIDrwText/Isolate| MHBDM| Isolate method takes CATBaseUnknow instead of CATISpecObject  
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/GetUseCutUncutInfo| MHBDM| GetUseCutUnCutInfo has been replaced by  GetUse3DSpec with Deprecated step.   
DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/SetUseCutUncutInfo| MHBDM| SetUseCutUnCutInfo has been replaced by  SetUse3DSpec with Deprecated step.   
