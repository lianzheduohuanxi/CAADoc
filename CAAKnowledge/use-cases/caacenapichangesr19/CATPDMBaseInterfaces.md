---
```vbscript
title: "CATPDMBaseInterfaces Framework Modifications in V5R19"
category: "use-case"
module: "CAACenAPIChangesR19"
version: "V5R19"
tags: ["CATIPDMSaveInfo", "CATIPDMSaveAction", "CATIPDMUESaveProcess"]
source_file: "Doc/online/CAACenAPIChangesR19/CATPDMBaseInterfaces.htm"
converted: "2026-05-11T17:33:51.550298"
```

---
# CAA C++ API Modifications  

| 
##  CATPDMBaseInterfaces Framework Modifications in V5R19 

* * *

**Entity|  SP| Modification| To Do** | CATPDMBaseInterfaces/Public/CATIPDMSaveInfo.h/CATIPDMSaveInfo/GetModificationStatus  
**Prototype:**`virtual HRESULT GetModificationStatus(CATDocument* iDocToSave,ModifStatus& oStatus)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
---|---|---|---  
CATPDMBaseInterfaces/Public/CATIPDMUESaveProcess.h/CATIPDMUESaveProcess/BeforeCommit  
**Prototype:**`virtual HRESULT BeforeCommit(CATLISTP_CATDocument_* iDocsToSave,CATIPDMSaveInfo* ipInfo,CATIPDMSaveAction* ipAction)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
CATPDMBaseInterfaces/Public/CATIPDMUESaveProcess.h/CATIPDMUESaveProcess/BeforeRollback  
**Prototype:**`virtual HRESULT BeforeRollback(CATLISTP_CATDocument_* iDocsToSave,CATIPDMSaveInfo* ipInfo,CATIPDMSaveAction* ipAction)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited
