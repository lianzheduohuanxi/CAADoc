---
title: "CATInstantCollabDesignCAAItf Framework Modifications in V5R17"
category: "use-case"
module: "CAACenAPIChangesR21"
tags: "["CATIColMergeItem", "CATIColIdManager", "CATIColMergeBriefcase", "CATICollabServices", "CATInstantCollabDesignCAAItf"]"
source_file: "Doc/online/CAACenAPIChangesR21/CATInstantCollabDesignCAAItf.htm"
converted: "2026-05-11T17:33:51.660575"
---
# CAA C++ API Modifications

|
##  CATInstantCollabDesignCAAItf Framework Modifications in V5R17

* * *

**Entity|  SP| Modification| To Do** | CATInstantCollabDesignCAAItf/Public/CATICollabServices.h/CATICollabServices/GetCollabIdManager
**Prototype:**`virtual HRESULT GetCollabIdManager(CATIColIdManager**oManager, const CATBaseUnknown* iReferenceObj=NULL)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Method was using a non exposed type, was so useless, and has been remoned from CAA exposition.
---|---|---|---
CATInstantCollabDesignCAAItf/Public/CATIColMergeItem.h/CATIColMergeItem/GetReferenceBriefcase
**Prototype:**`virtual HRESULT GetReferenceBriefcase(CATIColMergeBriefcase**oBriefcase)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Method was using a non exposed type, was so useless, and has been remoned from CAA exposition.
