---
```vbscript
title: "ObjectModelerBase Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIPersistent", "CATICatalogManager"]
source_file: "Doc/online/CAACenAPIChangesR7/ObjectModelerBase.htm"
converted: "2026-05-11T17:33:52.184516"
```

---
tags: ["CATIPersistent", "CATICatalogManager"]
source_file: "Doc/online/CAACenAPIChangesR7/ObjectModelerBase.htm"
converted: "2026-05-11T17:33:52.184516"
CAA API Modifications|  ObjectModelerBase  |

* * *

**Entity|  Modification| To Do** | ObjectModelerBase/Protected/CATDocumentServices.h/CATDocumentServices/Open| MHBDM| CATBoolean
---|---|---
ObjectModelerBase/Protected/CATDocumentServices.h/CATDocumentServices/Save| MHBDM| CATBoolean
ObjectModelerBase/Protected/CATDocumentServices.h/CATDocumentServices/SaveAs| MHBDM| CATBoolean
ObjectModelerBase/Protected/CATDocumentServices.h/CATDocumentServices/SaveAsNew| MHBDM| CATBoolean
ObjectModelerBase/Protected/CATDocumentsInSession.h/CATDocumentsInSession| CHBD| It's OK: not deleted.
ObjectModelerBase/Protected/CATICatalogManager.h/CATICatalogManager/IsAccessed| MRTHC| CATBoolean
ObjectModelerBase/Protected/CATICatalogManager.h/CATICatalogManager/IsLoaded| MRTHC| CATBoolean
ObjectModelerBase/Protected/CATIPersistent.h/CATIPersistent/Dirty| MRTHC| CATBoolean
ObjectModelerBase/Protected/CATIPersistent.h/CATIPersistent/SaveAs| NPVM| CATBoolean
ObjectModelerBase/Protected/CATIPersistent.h/CATIPersistent/SaveAs_B| NPVM| CATBoolean
ObjectModelerBase/Protected/CATIPersistent.h/CATIPersistent/Load| NPVM| CATBoolean
ObjectModelerBase/Protected/CATIPersistent.h/CATIPersistent/Load_B| NPVM| CATBoolean
ObjectModelerBase/Protected/CATSpecNotifications.h/CATModifNotification/~CATModifNotification| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATModifNotification/IsAKindOf| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATModifNotification/IsA| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATModifNotification/ClassName| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATModifNotification/GetObject| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoNotification/~CATCompoNotification| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoNotification/IsAKindOf| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoNotification/IsA| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoNotification/ClassName| INDM| The class is L1 in R7 but no methods are exposed.
ObjectModelerBase/Protected/CATSpecNotifications.h/CATCompoNotification/GetObject| INDM| The class is L1 in R7 but no methods are exposed.
