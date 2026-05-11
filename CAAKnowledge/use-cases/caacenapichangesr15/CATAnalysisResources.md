---
title: "CATAnalysisResources Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: []
source_file: "Doc/online/CAACenAPIChangesR15/CATAnalysisResources.md"
converted: "2026-05-11T17:33:51.062657"
---
# CAA C++ API Modifications  
  
| 
##  CATAnalysisResources Framework Modifications in V5R15 

  
* * *

**Entity|  SP| Modification| To Do** | CATAnalysisResources/Public/CATEAnalysisVisibility.h/CATEAnalysisVisibility/SetShowStatus  
**Prototype:**`virtual void SetShowStatus(CATBoolean iStatus);`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Had never been implemented, so was useless.  
---|---|---|---  
CATAnalysisResources/Public/CATEAnalysisVisibility.h/CATEAnalysisVisibility/IsNoShow  
**Prototype:**`virtual CATBoolean IsNoShow();`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Had never been implemented, so was useless.
