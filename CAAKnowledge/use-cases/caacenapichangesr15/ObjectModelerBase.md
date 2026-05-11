---
title: "ObjectModelerBase Framework Modifications in V5R15"
category: "general"
module: "CAACenAPIChangesR15"
tags: ["CATIConfigureDocLocator", "CATIDocLocator", "CATIDocDescriptor", "CATIDocId"]
source_file: "Doc\online\CAACenAPIChangesR15\ObjectModelerBase.htm"
converted: "2026-05-11T17:33:51.129396"
---

# CAA C++ API Modifications  
  
| 

##  ObjectModelerBase Framework Modifications in V5R15 

|   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | ObjectModelerBase/Public/CATDocId.h| GA| [FHBD](CAACenAPIChangeDetail.htm#Abstract)| Implementation that was used just to perform a QueryInterface on CATIDocId, breaking Object Modeler encapsulation principles. Now useless. Use CATOmbDocIdFinder to retrieve a CATIDocId.  
---|---|---|---  
ObjectModelerBase/Public/CATIConfigureDocLocator.h| GA| [FHBD ](CAACenAPIChangeDetail.htm#Abstract)| Deprecation error: cannot be used without CATIDocLocator, so was useless and has been removed.  
ObjectModelerBase/Public/CATIDocDescriptor.h| GA| [UHC ](CAACenAPIChangeDetail.htm#Abstract)| Deprecation error: cannot be reimplemented without CATIDocLocator, so keeping it U5 was useless and is now U3.
