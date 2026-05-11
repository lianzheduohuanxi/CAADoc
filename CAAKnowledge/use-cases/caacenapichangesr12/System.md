---
title: "System Modifications"
category: "use-case"
module: "CAACenAPIChangesR12"
version: "V5R12"
tags: ["CATISysSettingControler", "CATIIniSettingManagement"]
source_file: "Doc/online/CAACenAPIChangesR12/System.htm"
converted: "2026-05-11T17:33:50.591299"
---

CAA C++ API Modifications|  System  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | System/Public/CATIIniSettingManagement.h| GA| FHBD| Has been renamed into CATISysSettingControler.h, was anyway useless in V5R11.  
---|---|---|---  
System/Public/CATSettingRepository.h/CATSettingRepository/GetRepository| GA| MHBDM| Argument type has changed to accomodate the rename of CATIIniSettingManagement into CATISysSettingControler.
