---
title: "CATTPSInterfaces Modifications"
category: "general"
module: "CAACenAPIChangesR8"
tags: ["CATITPSDimensionLimits", "CATITPSTTRSServices", "CATITPSServices", "CATITPSDocument"]
source_file: "Doc\online\CAACenAPIChangesR8\CATTPSInterfaces.htm"
converted: "2026-05-11T17:33:52.446204"
---

CAA C++ API Modifications|  CATTPSInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/RunAnnotPlaneOperator| GA| MHBDM|   
---|---|---|---  
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/RetrieveOrCreateTTRSCont| GA| MHBDM|   
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/RetrieveOrCreateCurrentTPSSet| GA| MHBDM|   
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/GetTTRSFactoryFromTPSSet| GA| MHBDM|   
CATTPSInterfaces/Protected/CATITPSServices.h/CATITPSServices/StoreText| GA| MHBDM|   
CATTPSInterfaces/Protected/CATITPSTTRSServices.h/CATITPSTTRSServices/RetrieveParentTTRS| GA| MHBDM|   
CATTPSInterfaces/Protected/CATTPSServicesEnum.h| GA| FHBD| Has been splited into individual file for each enum to conform to CAA rules. Remove the include of this file and include files that has the same name as the enums you are actually using.  
CATTPSInterfaces/Protected/CATTPSTTRSServicesEnum.h| GA| FHBD|   
CATTPSInterfaces/Protected/CATITPSDocument.h/CATITPSDocument/GetSets| GA| MHBDM|   
CATTPSInterfaces/Protected/CATITPSDocument.h/CATITPSDocument/GetCurrentSet| GA| INDM| Check that you don't use it  
CATTPSInterfaces/Protected/CATITPSDimensionLimits.h/CATITPSDimensionLimits/GetLimits| GA| MRTHC| 
