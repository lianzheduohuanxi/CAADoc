---
title: "CATSchPlatformInterfaces Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATISchAppComponent"]
source_file: "Doc/online/CAACenAPIChangesR15/CATSchPlatformInterfaces.htm"
converted: "2026-05-11T17:33:51.074000"
---
# CAA C++ API Modifications  
  
| 
##  CATSchPlatformInterfaces Framework Modifications in V5R15 

  
* * *

**Entity|  SP| Modification| To Do** | CATSchPlatformInterfaces/Public/CATSchEventServices.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Moved into CATSchPlatformModeler, IdentityCards & Imakefiles may have to be modified accordingly.  
---|---|---|---  
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppListGRRNames2  
**Prototype:**`virtual HRESULT AppListGRRNames2(CATListOfCATUnicodeString &oLGRRNames;)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited  
CATSchPlatformInterfaces/Public/CATISchAppComponent.h/CATISchAppComponent/AppGetDefaultGRRName2  
**Prototype:**`virtual HRESULT AppGetDefaultGRRName2(CATUnicodeString &oGRRDefaultName;)= 0;`| GA| [NPVM](CAACenAPIChangeDetail.htm#Abstract)| Implement it when entity is implemented or inherited
