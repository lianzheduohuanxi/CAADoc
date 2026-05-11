---
title: "ENOVInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CATIEnovDDManager", "CATIEnovCMManager"]
source_file: "Doc/online/CAACenAPIChangesR8/ENOVInterfacesSP.htm"
converted: "2026-05-11T17:33:52.549807"
---

CAA C++ API Modifications|  ENOVInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | ENOVInterfaces/Protected/CATIEnovCMManager.h/CATIEnovCMManager/inEcoEffectivity| 1| MHBDM|   
---|---|---|---  
ENOVInterfaces/Protected/CATIEnovCMManager.h/CATIEnovCMManager/PropagateCMEffectivity| 3| INDM| Check that you don't use it  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforePropagateEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterPropagateEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeDeleteEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterDeleteEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeModifyEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterModifyEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeStatusEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeStatusEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeOwnerEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeOwnerEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAffectedObjectEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAffectedObjectEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAffectedObjectEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAffectedObjectEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAttachmentEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAttachmentEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAttachmentEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAttachmentEco| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeDeleteAction| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterDeleteAction| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeStatusAction| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeStatusAction| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeOwnerAction| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeOwnerAction| 1| MHBDM|   
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeDelete| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterDelete| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeStatus| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeStatus| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeOwner| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeOwner| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangePriority| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAffectedObject| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAffectedObject| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAffectedObject| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAffectedObject| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAttachment| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAttachment| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAttachment| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAttachment| 1| NPVM| Implement it when entity is implemented or inherited  
ENOVInterfaces/Protected/CATIEnovDDManager.h/CATIEnovDDManager/FindDocument| 1| MHBDM| 
