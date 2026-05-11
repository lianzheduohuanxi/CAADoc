---
title: "CATAnalysisBase Modifications"
category: "general"
module: "CAACenAPIChangesR8"
tags: ["CATICharacCollector"]
source_file: "Doc\online\CAACenAPIChangesR8\CATAnalysisBase.htm"
converted: "2026-05-11T17:33:52.406794"
---

CAA C++ API Modifications|  CATAnalysisBase  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | CATAnalysisBase/Protected/CATAnalysisCharacCollector.h/CATAnalysisCharacCollector/Stream| GA| INDM| Internal use.   
---|---|---|---  
CATAnalysisBase/Protected/CATAnalysisCharacCollector.h/CATAnalysisCharacCollector/UnStream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h/CATAnalysisExplicitCharac/Delete| GA| INDM| No software change. Parent class delete is now called.  
CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h/CATAnalysisExplicitCharac/SetStatus| GA| MHBDM| No software change. Parent class delete is now called.  
CATAnalysisBase/Protected/CATAnalysisExplicitCharac.h/CATAnalysisExplicitCharac/CreateCharac| GA| MHBDM| No software change. New method.  
CATAnalysisBase/Protected/CATAnalysisExplicitChild.h/CATAnalysisExplicitChild/CheckValidity| GA| MHBDM| New optionnal argument with default value (No change)  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/GetApplyTo| GA| MHBDM| New optionnal argument with default value (No change)  
CATAnalysisBase/Protected/CATAnalysisExplicitEntity.h/CATAnalysisExplicitEntity/ApplyTo| GA| MHBDM| New optionnal argument with default value (No change)  
CATAnalysisBase/Protected/CATAnalysisExplicitListATo.h/CATAnalysisExplicitListATo/GetContents| GA| MHBDM| Use ExplicitList instead ExplicitPointerst  
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/GetChildrenList| GA| MHBDM| New optionnal argument with default value (No change)  
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/AddChildren| GA| INDM| Use ExplicitList instead ExplicitPointerst  
CATAnalysisBase/Protected/CATAnalysisExplicitParent.h/CATAnalysisExplicitParent/RemoveChildren| GA| INDM| Use ExplicitList instead ExplicitPointerst  
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/GetPhysicalDescription| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/ReadPhysicalTypeDescription| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATAnalysisExplicitRulesData.h/CATAnalysisExplicitRulesData/SavePhysicalTypeDescription| GA| MHBDM| Internal use.   
CATAnalysisBase/Protected/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/GetNbNodes| GA| INDM| New API.  
CATAnalysisBase/Protected/CATAnalysisExplicitTopology.h/CATAnalysisExplicitTopology/GetNbElements| GA| INDM| New API.  
CATAnalysisBase/Protected/CATICharacCollector.h/CATICharacCollector/Update| GA| MHBDM| New optionnal argument with default value (No change)  
CATAnalysisBase/Protected/CATICharacCollector.h| GA| UHC| Now exposed with an adapter (CATECharachCollector). Derive your implementations from this adaptor.  
CATAnalysisBase/Protected/CATSamAxis.h/CATSamAxis/Stream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATSamAxis.h/CATSamAxis/UnStream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATSamCharacVersion.h/CATSamCharacVersion/Stream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATSamCharacVersion.h/CATSamCharacVersion/UnStream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/Stream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATSamDimension.h/CATSamDimension/UnStream| GA| INDM| Internal use.   
CATAnalysisBase/Protected/CATAnalysisExplicitNode.h/CATAnalysisExplicitNode/GetCoordinates| GA| MHBDM| Default value for second parameter changed. Take Care!  
CATAnalysisBase/Protected/CATAnalysisExplicitNode.h/CATAnalysisExplicitNode/CreateNode| GA| MHBDM| One method removed.
