---
```vbscript
title: "ObjectModelerBase Modifications"
category: "use-case"
module: "CAACenAPIChangesR9"
version: "V5R9"
tags: ["CATICatalogManager"]
source_file: "Doc/online/CAACenAPIChangesR9/ObjectModelerBase.htmmd"
converted: "2026-05-11T17:33:52.954496"
```

---
tags: ["CATICatalogManager"]
source_file: "Doc/online/CAACenAPIChangesR9/ObjectModelerBase.htmmd"
converted: "2026-05-11T17:33:52.954496"
CAA C++ API Modifications|  ObjectModelerBase  |

* * *

**Entity|  SP| Modification| To Do** | ObjectModelerBase/Protected/CATDocument.h/CATDocument/CATDocument| GA| MHBDM|
---|---|---|---
ObjectModelerBase/Protected/CATICatalogManager.h/CATICatalogManager/OpenCatalog| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATICatalogManager.h/CATICatalogManager/ListCatalog| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATICatalogManager.h/CATICatalogManager/IsAccessed| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATICatalogManager.h/CATICatalogManager/ListCatalogAt| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATNavigController.h/CATNavigController/WakeMeOnRepMulti| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATSpecNotification/CATSpecNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCreationNotification/CATCreationNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATDeleteNotification/CATDeleteNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoValNotification/CATCompoValNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructNotification/IsAKindOf| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructNotification/IsA| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructNotification/ClassName| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructAddNotification/IsAKindOf| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructAddNotification/IsA| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructAddNotification/ClassName| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructRemoveNotification/IsAKindOf| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructRemoveNotification/IsA| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoStructRemoveNotification/ClassName| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrNotification/CATAttrNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrValNotification/CATAttrValNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructNotification/CATAttrStructNotification| GA| INDM| Check that you don't use it
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructAddNotification/IsAKindOf| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructAddNotification/IsA| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructAddNotification/ClassName| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructRemoveNotification/IsAKindOf| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructRemoveNotification/IsA| GA| MHBDM|
ObjectModelerBase/Protected/CATSpecNotifications.h/CATAttrStructRemoveNotification/ClassName| GA| MHBDM|
ObjectModelerBase/Protected/CATLISTV_CATBaseUnknown.h| GA| FHBDMoved into System/ProtectedInterfaces: no Impact (mandatory module).|
