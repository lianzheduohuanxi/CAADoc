---
title: "CATAnalysisBase Modifications"
category: "general"
module: "CAACenAPIChangesR7"
tags: ["CATICharacCollector"]
source_file: "Doc\online\CAACenAPIChangesR7\CATAnalysisBaseSP.htm"
converted: "2026-05-11T17:33:51.940436"
---

CAA API Modifications|  CATAnalysisBase  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | CATAnalysisBase/Protected/CATAnalysisCharacCollector.h/CATAnalysisCharacCollector/Stream| 3| INDM| Check that you don't use it  
---|---|---|---  
CATAnalysisBase/Protected/CATAnalysisCharacCollector.h/CATAnalysisCharacCollector/UnStream| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h/CATAnalysisExplicitCharac/Delete| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitChild.h/CATAnalysisExplicitChild/CheckValidity| 5| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/GetApplyTo| 3| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitListATo.h/CATAnalysisExplicitListATo/GetContents| 4| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitModel.h/CATAnalysisExplicitModel/FindData| 5| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitNode.h/CATAnalysisExplicitNode/GetCoordinates| 1| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitNode.h/CATAnalysisExplicitNode/CreateNode| 1| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/GetChildrenList| 5| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/AddChildren| 1| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/RemoveChildren| 1| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/GetPhysicalDescription| 4| MHBDM|   
CATAnalysisBase/Protected/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/GetNbNodes| 5| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/GetNbElements| 5| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATICharacCollector.h| 4| UHC| Now exposed with an adapter (CATECharachCollector). Derive your implementations from this adaptor.  
CATAnalysisBase/Protected/CATICharacCollector.h/CATICharacCollector/Update| 4| MHBDM|   
CATAnalysisBase/Protected/CATSamAxis.h/CATSamAxis/Stream| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATSamAxis.h/CATSamAxis/UnStream| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATSamCharacVersion.h/CATSamCharacVersion/Stream| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATSamCharacVersion.h/CATSamCharacVersion/UnStream| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/Stream| 3| INDM| Check that you don't use it  
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/UnStream| 3| INDM| Check that you don't use it
