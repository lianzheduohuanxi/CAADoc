---
```vbscript
title: "CATSchPlatformInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR12"
version: "V5R12"
tags: ["CATISchAppCompatible", "CATISchArrowDisplay", "CATISchCompatible", "CATISchCatalogComponent", "CATISchDisplay", "CATISchRoute", "CATISchCatalogRoute", "CATISchAppConnector", "CATISchAppComponent", "CATISchGRRZone", "CATISchGapDisplay", "CATISchAppRoute", "CATISchComponent", "CATISchSession"]
source_file: "Doc/online/CAACenAPIChangesR12/CATSchPlatformInterfaces.htm"
converted: "2026-05-11T17:33:50.537347"
```

---
tags: ["CATISchAppCompatible", "CATISchArrowDisplay", "CATISchCompatible", "CATISchCatalogComponent", "CATISchDisplay", "CATISchRoute", "CATISchCatalogRoute", "CATISchAppConnector", "CATISchAppComponent", "CATISchGRRZone", "CATISchGapDisplay", "CATISchAppRoute", "CATISchComponent", "CATISchSession"]
source_file: "Doc/online/CAACenAPIChangesR12/CATSchPlatformInterfaces.htm"
converted: "2026-05-11T17:33:50.537347"
CAA C++ API Modifications|  CATSchPlatformInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | CATSchPlatformInterfaces/Public/CATISchAppCompatible.h/CATISchAppCompatible/AppIsTargetOKForRouted| GA| MHBDM| Migration to CATBoolean.
---|---|---|---
CATSchPlatformInterfaces/Public/CATISchAppCompatible.h/CATISchAppCompatible/AppIsTargetOKForPlace| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppCompatible.h/CATISchAppCompatible/AppIsTargetOKForInsert| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToPlaceInSpace| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToSlide| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToFlipConnected| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToFlipOnLine| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToFlipVertical| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToFlipHorizontal| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToUninsert| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppOKToScale| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppConnector.h/CATISchAppConnector/AppOKToNoShowConnectedCntr| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppConnector.h/CATISchAppConnector/AppIsCntrConnected| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppRoute.h/CATISchAppRoute/AppOKToModifyPoints| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppRoute.h/CATISchAppRoute/AppOKToBreak| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppRoute.h/CATISchAppRoute/AppOKToConcatenate| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchAppRoute.h/CATISchAppRoute/AppOKToBranch| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchArrowDisplay.h/CATISchArrowDisplay/IsArrowShown| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchCatalogComponent.h/CATISchCatalogComponent/QueryDropAbility| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchCatalogComponent.h/CATISchCatalogComponent/QueryDropCompGroupAbility| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchCatalogRoute.h/CATISchCatalogRoute/QueryDropAbility| GA| MHBDMMigration to CATBoolean.|
CATSchPlatformInterfaces/Public/CATISchCompatible.h/CATISchCompatible/IsTargetOKForRoute| GA| MHBDMMigration to CATBoolean.|
CATSchPlatformInterfaces/Public/CATISchCompatible.h/CATISchCompatible/IsTargetOKForPlace| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchCompatible.h/CATISchCompatible/IsTargetOKForInsert| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchCompatible.h/CATISchCompatible/GetBestFitPlaceInfo| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchCompatible.h/CATISchCompatible/GetBestFitInsertInfo| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/IsInserted| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/IsAReference| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToSlide| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToPlaceInSpace| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToFlipConnected| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToFlipOnLine| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToFlipHorizontal| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToFlipVertical| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToUninsert| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchComponent.h/CATISchComponent/OKToScale| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchDisplay.h/CATISchDisplay/Highlight| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchDisplay.h/CATISchDisplay/Show| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchGRRZone.h/CATISchGRRZone/IsBoundaryValid| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchGapDisplay.h/CATISchGapDisplay/IsGapShown| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchRoute.h/CATISchRoute/OKToModifyPoints| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchRoute.h/CATISchRoute/OKToBreak| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchRoute.h/CATISchRoute/OKToConcatenate| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchRoute.h/CATISchRoute/OKToBranch| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATISchSession.h/CATISchSession/CreateDocument| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATSchListServices.h/CATSchListServices/IsSameImpl| GA| MRTHC| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATScuIndicationAgent.h/CATScuIndicationAgent/SetSnapMode| GA| MHBDM| Migration to CATBoolean.
CATSchPlatformInterfaces/Public/CATScuIndicationAgent.h/CATScuIndicationAgent/GetSnapMode| GA| MRTHC| Migration to CATBoolean.
