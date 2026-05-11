---
title: "CATAnalysisResources Modifications"
category: "general"
module: "CAACenAPIChangesR8"
tags: []
source_file: "Doc\online\CAACenAPIChangesR8\CATAnalysisResources.htm"
converted: "2026-05-11T17:33:52.432237"
---

CAA C++ API Modifications|  CATAnalysisResources  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | CATAnalysisResources/Protected/CATECharacCollector.h/CATECharacCollector/Update| GA| MHBDM|  New optionnal argument with compatible default value (No Change)  
---|---|---|---  
CATAnalysisResources/Protected/CATECharacCollector.h| GA| UHC| Usage changed from U5 to U2 because of a tagging error: this class is an adaptor and so at the same time concrete and intended to be derived.
