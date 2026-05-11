---
title: "AnalysisMeshingModel Modifications"
category: "general"
module: "CAACenAPIChangesR8"
tags: ["CATIMSHMeshPart", "CATIMSHMeshDomain"]
source_file: "Doc\online\CAACenAPIChangesR8\AnalysisMeshingModel.htm"
converted: "2026-05-11T17:33:52.356915"
---

CAA C++ API Modifications|  AnalysisMeshingModel  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | AnalysisMeshingModel/Protected/CATIMSHMeshDomain.h/CATIMSHMeshDomain/GetMesh| GA| MHBDM|  Check that you don't use it. Domain internal data must be manipulated throught CATIMSHMeshPart interface.  
---|---|---|---  
AnalysisMeshingModel/Protected/CATIMSHMeshDomain.h/CATIMSHMeshDomain/GetNumberOfElements| GA| MHBDM|  Replace by CATIMSHMeshPart:: GetElements. Check that you don't use it  
AnalysisMeshingModel/Protected/CATIMSHMeshDomain.h/CATIMSHMeshDomain/GetElements| GA| MHBDM|  Replace by CATIMSHMeshPart:: GetElements. Check that you don't use it
