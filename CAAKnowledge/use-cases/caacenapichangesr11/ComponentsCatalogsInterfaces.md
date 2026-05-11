---
title: "ComponentsCatalogsInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR11"
version: "V5R11"
tags: ["CATICatalogPersistentQuery"]
source_file: "Doc/online/CAACenAPIChangesR11/ComponentsCatalogsInterfaces.md"
converted: "2026-05-11T17:33:50.347204"
---

CAA C++ API Modifications|  ComponentsCatalogsInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | ComponentsCatalogsInterfaces/Protected/CATICatalogPersistentQuery.h/CATICatalogPersistentQuery/SetResolutionDate| GA| MHBDM| CATTime argument is now passed by reference for performance purpose. As the value is not modified by the method, there is no impact.  
---|---|---|---
