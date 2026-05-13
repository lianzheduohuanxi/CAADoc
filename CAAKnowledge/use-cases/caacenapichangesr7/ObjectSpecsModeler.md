---
```vbscript
title: "ObjectSpecsModeler Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATISpecObject", "CATISpecAttribute", "CATISpecUpdate", "CATIAttrBehavior", "CATISpecAttrAccess"]
source_file: "Doc/online/CAACenAPIChangesR7/ObjectSpecsModeler.htmmd"
converted: "2026-05-11T17:33:52.197265"
```

---
tags: ["CATISpecObject", "CATISpecAttribute", "CATISpecUpdate", "CATIAttrBehavior", "CATISpecAttrAccess"]
source_file: "Doc/online/CAACenAPIChangesR7/ObjectSpecsModeler.htmmd"
converted: "2026-05-11T17:33:52.197265"
CAA API Modifications|  ObjectSpecsModeler  |

* * *

**Entity|  Modification| To Do** | ObjectSpecsModeler/Protected/CATIAttrBehavior.h/CATIAttrBehavior/GetRequestedBehavior| MHBDM|
---|---|---
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/TestAttrName| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/TestAttrKey| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/TestAttributeValue| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/SetBoolean| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/SetSpecObject| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/SetExternalObject| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/GetBoolean| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttrAccess.h/CATISpecAttrAccess/TestFinalAttributeValue| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/IsUpToDate| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/SetUpToDate| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/TestAttributeValue| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/SetBoolean| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/SetSpecObject| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/SetExternalObject| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/GetBoolean| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/TestFinalAttributeValue| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecAttribute.h/CATISpecAttribute/EventsAreSent| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecObject.h/CATISpecObject/Instanciate| MHBDM| CATBoolean
ObjectSpecsModeler/Protected/CATISpecObject.h/CATISpecObject/IsSubTypeOf| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecObject.h/CATISpecObject/IsSynchronized| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecObject.h/CATISpecObject/CanGetReference| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecUpdate.h/CATISpecUpdate/IsUpToDate| MRTHC| CATBoolean
ObjectSpecsModeler/Protected/CATISpecUpdate.h/CATISpecUpdate/SetUpToDate| NPVM| CATBoolean
