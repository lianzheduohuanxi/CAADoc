---
```vbscript
title: "CATAnalysisInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CATISamAnalysisEntity", "CATISamAnalysisConnector", "CATISamAnalysisManager", "CATISamAnalysisModel", "CATISamAnalysisModelFactory"]
source_file: "Doc/online/CAACenAPIChangesR8/CATAnalysisInterfaces.htmmd"
converted: "2026-05-11T17:33:52.421759"
```

---
tags: ["CATISamAnalysisEntity", "CATISamAnalysisConnector", "CATISamAnalysisManager", "CATISamAnalysisModel", "CATISamAnalysisModelFactory"]
source_file: "Doc/online/CAACenAPIChangesR8/CATAnalysisInterfaces.htmmd"
converted: "2026-05-11T17:33:52.421759"
CAA C++ API Modifications|  CATAnalysisInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | CATAnalysisInterfaces/Protected/CATISamAnalysisConnector.h/CATISamAnalysisConnector/AddImpactingObject| GA| MHBDM| Never Implemented.
---|---|---|---
CATAnalysisInterfaces/Protected/CATISamAnalysisConnector.h/CATISamAnalysisConnector/GetImpactingObjects| GA| MHBDM| Never Implemented.
CATAnalysisInterfaces/Protected/CATISamAnalysisConnector.h/CATISamAnalysisConnector/GetStrategy| GA| MHBDM| Never Implemented.
```vbscript
CATAnalysisInterfaces/Protected/CATISamAnalysisConnector.h/CATISamAnalysisConnector/GetObjects| GA| MHBDM| Never Implemented.
CATAnalysisInterfaces/Protected/CATISamAnalysisManager.h/CATISamAnalysisManager/AddCase| GA| MHBDM| Never Implemented. Use same methods on CATISamAnalysisModel.
```
CATAnalysisInterfaces/Protected/CATISamAnalysisManager.h/CATISamAnalysisManager/GetNamedCase| GA| MHBDM| Never Implemented. Use same methods on CATISamAnalysisModel.
CATAnalysisInterfaces/Protected/CATISamAnalysisManager.h/CATISamAnalysisManager/GetAllCases| GA| MHBDM| Never Implemented. Use same methods on CATISamAnalysisModel.
CATAnalysisInterfaces/Protected/CATISamAnalysisModelFactory.h/CATISamAnalysisModelFactory/CreateAnalysisSupport| GA| MHBDM| Never Implemented.
CATAnalysisInterfaces/Protected/CATISamAnalysisModelFactory.h/CATISamAnalysisModelFactory/CreateConnector| GA| MHBDM| NoChange!
CATAnalysisInterfaces/Protected/CATISamAnalysisEntity.h/CATISamAnalysisEntity/AddBasicComponent| GA| MHBDM| New capability.
