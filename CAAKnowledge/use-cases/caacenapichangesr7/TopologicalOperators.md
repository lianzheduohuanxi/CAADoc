---
title: "TopologicalOperators Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: []
source_file: "Doc/online/CAACenAPIChangesR7/TopologicalOperators.md"
converted: "2026-05-11T17:33:52.256969"
---

CAA API Modifications|  TopologicalOperators  |   
---|---|---  
  
* * *

**Entity|  Modification| To Do** | TopologicalOperators/Protected/CATDynDraftRibbon.h/CATDynDraftRibbon/CATDynDraftRibbon| MHBDM| Addition of a default argument -> BT compatible (recompile)  
---|---|---  
TopologicalOperators/Protected/CATDynDraftParam.h/CATDynDraftParam/CATDynDraftParam| MHBDM| The input arguments are now passed by reference -> modify your code if necessary  
TopologicalOperators/Protected/CATDynDraftParam.h/CATDynDraftParam/HasRatio| MHBDM| The input arguments of the constructor are now passed by reference, so that this method is useless -> suppress its call  
TopologicalOperators/Protected/CATDynDraftParam.h/CATDynDraftParam/HasAngle| MHBDM| The input arguments of the constructor are now passed by reference, so that this method is useless -> suppress its call
