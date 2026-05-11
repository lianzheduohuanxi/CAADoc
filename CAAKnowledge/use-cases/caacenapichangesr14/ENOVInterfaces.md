---
title: "ENOVInterfaces Framework Modifications in V5R14"
category: "use-case"
module: "CAACenAPIChangesR14"
version: "V5R14"
tags: []
source_file: "Doc/online/CAACenAPIChangesR14/ENOVInterfaces.md"
converted: "2026-05-11T17:33:50.911535"
---

CAA C++ API Modifications|  ENOVInterfaces Framework Modifications in V5R14 |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | ENOVInterfaces/Public/ENOVICWEvents.h/ENOVICWEvents/onBeforeRemoveLinkRelatedEco  
**Prototype:**`virtual HRESULT onBeforeRemoveLinkRelatedEco(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
---|---|---|---  
ENOVInterfaces/Public/ENOVICWEvents.h/ENOVICWEvents/onAfterRemoveLinkRelatedEco  
**Prototype:**`virtual HRESULT onAfterRemoveLinkRelatedEco(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
ENOVInterfaces/Public/ENOVICWEvents.h/ENOVICWEvents/onBeforeActModify  
**Prototype:**`virtual HRESULT onBeforeActModify(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
ENOVInterfaces/Public/ENOVICWEvents.h/ENOVICWEvents/onAfterActModify  
**Prototype:**`virtual HRESULT onAfterActModify(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
ENOVInterfaces/Public/ENOVICWEvents.h/ENOVICWEvents/onBeforeAffObjModify  
**Prototype:**`virtual HRESULT onBeforeAffObjModify(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
ENOVInterfaces/Public/ENOVICWEvents.h/ENOVICWEvents/onAfterAffObjModify  
**Prototype:**`virtual HRESULT onAfterAffObjModify(const ENOVIEvent_var& iRaisedEvent,HRESULT& ioNotifyReturnCode)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited
