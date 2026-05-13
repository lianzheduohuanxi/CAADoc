---
title: "ENOVInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR9"
tags: "["CATIEnovDDManager", "CATIEnovCMManager"]"
source_file: "Doc/online/CAACenAPIChangesR9/ENOVInterfaces.htm"
converted: "2026-05-11T17:33:52.893327"
---
tags: ["CATIEnovDDManager", "CATIEnovCMManager"]
source_file: "Doc/online/CAACenAPIChangesR9/ENOVInterfaces.htmmd"
converted: "2026-05-11T17:33:52.893327"
CAA C++ API Modifications|  ENOVInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | ENOVInterfaces/Protected/CATIEnovCMManager.h/CATIEnovCMManager/inEcoEffectivity| GA| MHBDM|
---|---|---|---
ENOVInterfaces/Protected/CATIEnovCMManager.h/CATIEnovCMManager/PropagateCMEffectivity| GA| INDM| Check that you don't use it
ENOVInterfaces/Protected/CATIEnovDDManager.h/CATIEnovDDManager/FindDocument| GA| MHBDM|
ENOVInterfaces/Protected/CATIEnovDDManager.h/CATIEnovDDManager/set_ViewerAttributes| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforePropagateEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterPropagateEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeDeleteEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterDeleteEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeModifyEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterModifyEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeStatusEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeStatusEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeOwnerEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeOwnerEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAffectedObjectEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAffectedObjectEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAffectedObjectEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAffectedObjectEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAttachmentEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAttachmentEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAttachmentEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAttachmentEco| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeDeleteAction| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterDeleteAction| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeStatusAction| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeStatusAction| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeOwnerAction| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeOwnerAction| GA| MHBDM|
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeDelete| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterDelete| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeStatus| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeStatus| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeChangeOwner| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangeOwner| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterChangePriority| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAffectedObject| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAffectedObject| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAffectedObject| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAffectedObject| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeAddAttachment| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterAddAttachment| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveAttachment| GA| NPVM| Implement it when entity is implemented or inherited
ENOVInterfaces/Protected/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveAttachment| GA| NPVM| Implement it when entity is implemented or inherited
