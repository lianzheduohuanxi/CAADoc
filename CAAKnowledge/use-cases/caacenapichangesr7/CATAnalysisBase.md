---
title: "CATAnalysisBase Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATICharacCollector"]
source_file: "Doc/online/CAACenAPIChangesR7/CATAnalysisBase.htm"
converted: "2026-05-11T17:33:51.932448"
---

CAA API Modifications|  CATAnalysisBase  |   
---|---|---  
  
* * *

**Entity|  Modification| To Do** | CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h| UHC| U1 to U2. Should not be derived (useless).  
---|---|---  
CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h/CATAnalysisExplicitCharac/Reset| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h/CATAnalysisExplicitCharac/Init| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h| UHC| U1 to U2. Should not be derived (useless).  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/Reset| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/Init| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/Stream| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/UnStream| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitList.h/CATAnalysisExplicitList/Reset| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitList.h/CATAnalysisExplicitList/ResetLocation| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitList.h/CATAnalysisExplicitList/ResetCurrent| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitList.h/CATAnalysisExplicitList/Init| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitList.h/CATAnalysisExplicitList/GetLength| MHBDM| Boolean Argument added with compatible default value  
CATAnalysisBase/Protected/CATAnalysisExplicitListUsr.h/CATAnalysisExplicitListUsr/Remove| MHBDM| CATBoolean  
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/GetChildren| MHBDM| Use GetChildreList instead.  
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/GetPhysicalTypeDofs| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/SetPhysicalDescription| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/SetNumberOfPhysicalTypes| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitSet.h| UHC| U1 to U2. Should not be derived (useless).  
CATAnalysisBase/Protected/CATAnalysisExplicitSet.h/CATAnalysisExplicitSet/Reset| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitSet.h/CATAnalysisExplicitSet/Init| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitSet.h/CATAnalysisExplicitSet/Stream| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitSet.h/CATAnalysisExplicitSet/UnStream| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATICharacCollector.h/CATICharacCollector/GetCharacCollectorsForOccurrences| NPVM| Implement it when entity is implemented or inherited  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/ValuesAddress| MHBDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitElement.h/CATAnalysisExplicitElement/GetCriterionEngine| INDM| Internal methods. No use detected  
CATAnalysisBase/Protected/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/SetUpToDate| INDM| Internal methods. No use detected
