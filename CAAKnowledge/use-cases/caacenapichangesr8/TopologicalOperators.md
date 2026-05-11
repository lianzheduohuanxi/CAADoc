---
title: "TopologicalOperators Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: []
source_file: "Doc/online/CAACenAPIChangesR8/TopologicalOperators.md"
converted: "2026-05-11T17:33:52.710407"
---

CAA C++ API Modifications|  TopologicalOperators  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/CATDynFilletRibbon| GA| INDM| Check that you don't use it  
---|---|---|---  
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/GetSegmentationMode| GA| MHBDM|   
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/SetSegmentationMode| GA| MHBDM|   
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/GetRelimitationMode| GA| MHBDM|   
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/SetRelimitationMode| GA| MHBDM|   
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/GetMaxOption| GA| MHBDM|   
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynFilletRibbon/SetMaxOption| GA| MHBDM|   
TopologicalOperators/Protected/CATDynFilletRibbon.h/CATDynEdgeFilletRibbon/SetFilletTool| GA| MHBDM|   
TopologicalOperators/Protected/CATBodyFreezeMode.h| GA| FHBD| Moved in NewTopologicalObjects to allow a widest use. It's now included in CATTopOperator.h. No impact (if you use this header, the new framework is already in your IC prerequisites).  
TopologicalOperators/Protected/CATDynDraftDomain.h/CATDynDraftDomain/GetPullingDirection| GA| MRTHC|   
TopologicalOperators/Protected/CATGeoToTopOperator.h/CATGeoToTopOperator/SetFreezeMode| GA| MHBDM|   
TopologicalOperators/Protected/CATGeoToTopOperator.h/CATGeoToTopOperator/GetFreezeMode| GA| MHBDM|   
TopologicalOperators/Protected/CATGeoToTopOperator.h/CATGeoToTopOperator/GetResult| GA| MHBDM|   
TopologicalOperators/Protected/CATDynDraft.h/CATDynDraft/GetFreezeMode| GA| MHBDM|   
TopologicalOperators/Protected/CATDynDraft.h/CATDynDraft/SetFreezeMode| GA| MHBDM|   
TopologicalOperators/Protected/CATDynOperator.h/CATDynOperator/GetResult| GA| MHBDM|   
TopologicalOperators/Protected/CATDynOperator.h/CATDynOperator/GetJournal| GA| MHBDM| 
