---
```vbscript
title: "DNBManufacturingLayoutItf Framework Modifications in V5R19"
category: use-case
module: "CAACenAPIChangesR19"
version: "V5R19"
tags: ["CATIArrIgpAttachment", "CATIArrAttachmentFactory", "CATISpecObject"]
source_file: "Doc/online/CAACenAPIChangesR19/DNBManufacturingLayoutItf.htmmd"
converted: "2026-05-11T17:33:51.555782"
```

---
# CAA C++ API Modifications

|
##  DNBManufacturingLayoutItf Framework Modifications in V5R19

* * *

**Entity|  SP| Modification| To Do** | DNBManufacturingLayoutItf/Public/CATIArrAttachmentFactory.h/CATIArrAttachmentFactory/AttachMA
**Prototype:**`virtual HRESULT AttachMA(CATISpecObject* iParent,CATISpecObject* iChild,CATIArrIgpAttachment**oAttach)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited
---|---|---|---
DNBManufacturingLayoutItf/Public/CATIArrAttachmentFactory.h/CATIArrAttachmentFactory/Remove
**Prototype:**`virtual HRESULT Remove(CATIArrIgpAttachment*iAttach)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited
