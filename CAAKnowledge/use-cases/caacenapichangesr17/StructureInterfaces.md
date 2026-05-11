---
title: "StructureInterfaces Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR17"
version: "V5R17"
tags: ["CATIStructureMember"]
source_file: "Doc/online/CAACenAPIChangesR17/StructureInterfaces.md"
converted: "2026-05-11T17:33:51.371929"
---
# CAA C++ API Modifications  
  
| 
##  StructureInterfaces Framework Modifications in V5R17 

  
* * *

**Entity|  SP| Modification| To Do** | StructureInterfaces/Public/CATIStructureMember.h/CATIStructureMember/GetSection  
**Prototype:**`virtual HRESULT GetSection(CATDocument*oSectionDoc)=0;`| GA| [MHBDM ](CAACenAPIChangeDetail.htm#Abstract)| The previous signature in CATDocument* did'nt allow to return the expected value, it so has been changed into CATDocument*&. No impact on existing client code.   
---|---|---|---
