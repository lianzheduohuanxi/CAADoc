---
```vbscript
title: "TopologicalOperators Framework Modifications in V5R14"
category: "use-case"
module: "CAACenAPIChangesR14"
version: "V5R14"
tags: []
source_file: "Doc/online/CAACenAPIChangesR14/TopologicalOperators.htmmd"
converted: "2026-05-11T17:33:50.979971"
```

---
tags: []
source_file: "Doc/online/CAACenAPIChangesR14/TopologicalOperators.htmmd"
converted: "2026-05-11T17:33:50.979971"
CAA C++ API Modifications|  TopologicalOperators Framework Modifications in V5R14 |

* * *

**Entity|  SP| Modification| To Do** | TopologicalOperators/Public/CATTopCorner.h/CATTopCorner/GetCurBeginOfCorner
**Prototype:**`virtual void GetCurBeginOfCorner(int & oNumWire)=0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of a wrong 'nodoc' tag. Documentation was clear: this method must not be used.
---|---|---|---
TopologicalOperators/Public/CATTopCorner.h/CATTopCorner/SetBeginOfCorner
**Prototype:**`virtual void SetBeginOfCorner(int iNumWire)=0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of a wrong 'nodoc' tag. Documentation was clear: this method must not be used.
TopologicalOperators/Public/CATTopCorner.h/CATTopCorner/GetBeginOfCorner
**Prototype:**`virtual void GetBeginOfCorner(int & oNumWire)=0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Correction of a wrong 'nodoc' tag. Documentation was clear: this method must not be used.
