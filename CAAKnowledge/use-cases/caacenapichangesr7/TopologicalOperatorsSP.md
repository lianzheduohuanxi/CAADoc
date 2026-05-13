---
title: "TopologicalOperators Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
tags: "[]"
source_file: "Doc/online/CAACenAPIChangesR7/TopologicalOperatorsSP.htm"
converted: "2026-05-11T17:33:52.263561"
---
tags: []
source_file: "Doc/online/CAACenAPIChangesR7/TopologicalOperatorsSP.htmmd"
converted: "2026-05-11T17:33:52.263561"
CAA API Modifications|  TopologicalOperators  |

* * *

**Entity|  SP| Modification| To Do** | TopologicalOperators/Protected/CATBodyFreezeMode.h| 3| FHBD| Moved in NewTopologicalObjects to allow a widest use. It's now included in CATTopOperator.h. No impact (if you use this header, the new framework is already in your IC prerequisites).
---|---|---|---
TopologicalOperators/Protected/CATDynDraftDomain.h/CATDynDraftDomain/GetPullingDirection| 1| MRTHC|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/CATDynFilletRibbon| 3| INDM| Check that you don't use it
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/GetSegmentationMode| 3| MHBDM|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/SetSegmentationMode| 3| MHBDM|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/GetRelimitationMode| 1| MHBDM|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/SetRelimitationMode| 1| MHBDM|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/GetMaxOption| 1| MHBDM|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/SetMaxOption| 1| MHBDM|
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynEdgeFilletRibbon/SetFilletTool| 5| MHBDM|
TopologicalOperators/Protected/CATGeoToTopOperator.h/CATGeoToTopOperator/SetFreezeMode| 1| MHBDM|
TopologicalOperators/Protected/CATGeoToTopOperator.h/CATGeoToTopOperator/GetFreezeMode| 1| MHBDM|
TopologicalOperators/Protected/CATGeoToTopOperator.h/CATGeoToTopOperator/GetResult| 1| MHBDM|
