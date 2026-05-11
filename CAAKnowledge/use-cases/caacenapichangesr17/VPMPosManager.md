---
```vbscript
title: "VPMPosManager Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR17"
version: "V5R17"
tags: []
source_file: "Doc/online/CAACenAPIChangesR17/VPMPosManager.htm"
converted: "2026-05-11T17:33:51.395714"
```

---
| 
# CAA C++ API Modifications

| 
##  VPMPosManager Framework Modifications in V5R17 

* * *

**Entity|  SP| Modification| To Do** | VPMPosManager/Public/ENOVIPosEvent.h/ENOVIPosEvent/onLogon  
**Prototype:**`virtual HRESULT onLogon(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
---|---|---|---  
VPMPosManager/Public/ENOVIPosEvent.h/ENOVIPosEvent/onLogout  
**Prototype:**`virtual HRESULT onLogout(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited
