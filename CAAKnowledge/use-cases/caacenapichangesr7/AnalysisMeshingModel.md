---
```vbscript
title: "AnalysisMeshingModel Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIMSHMeshPart", "CATIMSHMesh", "CATIMSHMesher"]
source_file: "Doc/online/CAACenAPIChangesR7/AnalysisMeshingModel.htmmd"
converted: "2026-05-11T17:33:51.887410"
```

---
tags: ["CATIMSHMeshPart", "CATIMSHMesh", "CATIMSHMesher"]
source_file: "Doc/online/CAACenAPIChangesR7/AnalysisMeshingModel.htmmd"
converted: "2026-05-11T17:33:51.887410"
CAA API Modifications|  AnalysisMeshingModel  |

* * *

**Entity|  Modification| To Do** | AnalysisMeshingModel/Protected/CATIMSHMesh.h/CATIMSHMesh/CloseMeshDomain| INDM| Not Exposed because done automatically by the MeshPart Object. Check that you don't use it
---|---|---
AnalysisMeshingModel/Protected/CATIMSHMeshPart.h/CATIMSHMeshPart/GetDomains| INDM| Replace by CATIMSHMeshPart:: GetElements. Check that you don't use it
AnalysisMeshingModel/Protected/CATIMSHMesher.h/CATIMSHMesher/Mesh| MHBDM| 2 arguments removed, use CATIMSHMeshPart for this.
