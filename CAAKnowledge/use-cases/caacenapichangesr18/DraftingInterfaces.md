---
```vbscript
title: "DraftingInterfaces Framework Modifications in V5R18"
category: use-case
module: "CAACenAPIChangesR18"
version: "V5R18"
tags: ["CATIDrwThread", "CATIDrwAnnotationFactory", "CATIDrwThread_var"]
source_file: "Doc/online/CAACenAPIChangesR18/DraftingInterfaces.htmmd"
converted: "2026-05-11T17:33:51.472913"
```

---
# CAA C++ API Modifications

|
##  DraftingInterfaces Framework Modifications in V5R18

* * *

**Entity|  SP| Modification| To Do** | DraftingInterfaces/Public/CATIDrwAnnotationFactory.h/CATIDrwAnnotationFactory/CreateDrwThread
**Prototype:**`virtual CATIDrwThread_var CreateDrwThread(CATBaseUnknown_var iReference,CATBaseUnknown_var iDirection = NULL_var,int iQuadrant = 1,ThreadType iType = Taped)=0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Because of naming conflict, enum ThreadType has been renamed into CATDftThreadTypeEnum.
---|---|---|---
DraftingInterfaces/Public/CATIDrwThread.h/CATIDrwThread/SetThreadType
**Prototype:**`virtual void SetThreadType(const int iQuadrant=0,ThreadType iType=Taped)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Because of naming conflict, enum ThreadType has been renamed into CATDftThreadTypeEnum.
DraftingInterfaces/Public/CATIDrwThread.h/CATIDrwThread/GetThreadInfo
**Prototype:**`virtual HRESULT GetThreadInfo(CATMathCircleArc2D*oCircleArc,int*oQuad,ThreadType*oType,int*oShowMode)=0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Because of naming conflict, enum ThreadType has been renamed into CATDftThreadTypeEnum.
