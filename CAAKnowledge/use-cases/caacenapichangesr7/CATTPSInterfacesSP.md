---
title: "CATTPSInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATITPSDimensionLimits", "CATITPSTTRSServices", "CATITPSServices", "CATITPSDocument"]
source_file: "Doc/online/CAACenAPIChangesR7/CATTPSInterfacesSP.md"
converted: "2026-05-11T17:33:51.976108"
---

CAA API Modifications|  CATTPSInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | CATTPSInterfaces/Protected/CATITPSDimensionLimits.h/CATITPSDimensionLimits/GetLimits| 1| MRTHC|   
---|---|---|---  
CATTPSInterfaces/Protected/CATITPSDocument.h/CATITPSDocument/GetSets| 5| MHBDM|   
CATTPSInterfaces/Protected/CATITPSDocument.h/CATITPSDocument/GetCurrentSet| 5| INDM| Check that you don't use it  
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/RunAnnotPlaneOperator| 4| MHBDM|   
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/RetrieveOrCreateTTRSCont| 4| MHBDM|   
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/RetrieveOrCreateCurrentTPSSet| 4| MHBDM|   
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/GetTTRSFactoryFromTPSSet| 4| MHBDM|   
CATTPSInterfaces/Protected/CATITPSTTRSServices.h/CATITPSTTRSServices/RetrieveParentTTRS| 4| MHBDM|   
CATTPSInterfaces/Protected/CATTPSServicesEnum.h| 4| FHBD| Has been splited into individual file for each enum to conform to CAA rules. Remove the include of this file and include files that has the same name as the enums you are actually using.  
CATTPSInterfaces/Protected/CATTPSTTRSServicesEnum.h| 4| FHBD| 
