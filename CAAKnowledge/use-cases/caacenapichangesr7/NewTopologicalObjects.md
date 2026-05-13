---
```vbscript
title: "NewTopologicalObjects Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: []
source_file: "Doc/online/CAACenAPIChangesR7/NewTopologicalObjects.htmmd"
converted: "2026-05-11T17:33:52.177019"
```

---
tags: []
source_file: "Doc/online/CAACenAPIChangesR7/NewTopologicalObjects.htmmd"
converted: "2026-05-11T17:33:52.177019"
CAA API Modifications|  NewTopologicalObjects  |

* * *

**Entity|  Modification| To Do** | NewTopologicalObjects/Protected/CATBody.h/CATBody/GetNbDomains| MHBDM| The method is now on the parent class CATTopObject-> BT compatible (recompile)
---|---|---
NewTopologicalObjects/Protected/CATBody.h/CATBody/GetDomain| MHBDM| The method is now on the parent class CATTopObject-> BT compatible (recompile)
NewTopologicalObjects/Protected/CATBody.h/CATBody/RemoveDomain| MHBDM| The method is now on the parent class CATTopObject-> BT compatible (recompile)
NewTopologicalObjects/Protected/CATCell.h/CATCell/GetNbDomains| MHBDM| The method is now on the parent class CATTopObject-> BT compatible (recompile)
NewTopologicalObjects/Protected/CATCell.h/CATCell/GetDomain| MHBDM| The method is now on the parent class CATTopObject-> BT compatible (recompile)
NewTopologicalObjects/Protected/CATCell.h/CATCell/RemoveDomain| MHBDM| The method is now on the parent class CATTopObject-> BT compatible (recompile)
NewTopologicalObjects/Protected/CATEdge.h/CATEdge/EvalGlobalSharpness| MHBDM| Addition of a default argument -> BT compatible (recompile)
NewTopologicalObjects/Protected/CATLoop.h/CATLoop/InsertEdge| MHBDM| The method is now on the parent class CATEdgeDomain-> BT compatible (recompile)
NewTopologicalObjects/Protected/CATTopology.h/CATTopology/IsInside| MHBDM| Addition of a default argument -> BT compatible (recompile)
NewTopologicalObjects/Protected/CATWire.h/CATWire/InsertEdge| MHBDM| The method is now on the parent class CATEdgeDomain-> BT compatible (recompile)
