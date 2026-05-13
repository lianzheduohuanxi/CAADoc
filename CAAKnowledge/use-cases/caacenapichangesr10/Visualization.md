---
title: "Visualization Modifications"
category: "use-case"
module: "CAACenAPIChangesR10"
tags: "["CATIVisu"]"
source_file: "Doc/online/CAACenAPIChangesR10/Visualization.htm"
converted: "2026-05-11T17:33:50.275018"
---
tags: ["CATIVisu"]
source_file: "Doc/online/CAACenAPIChangesR10/Visualization.htmmd"
converted: "2026-05-11T17:33:50.275018"
CAA C++ API Modifications |  Visualization |

* * *

** Entity | SP | Modification | To Do** | Visualization/Protected/CAT3DArrowGP.h | GA | FHBD | [Split Visualization/VisualizationBase (forgotten in R9).](../CAACenQuickRefs/CAACenWhatsNew.htm#VisuSplit)
---|---|---|---
Visualization/Protected/CATExtIVisu.h/CATExtIVisu/GetRep | GA | INDM | Check that you don't use it
Visualization/Protected/CATIVisu.h/CATIVisu/GetRep | GA | INDM | Check that you don't use it
Visualization/Protected/CATPathElement.h/CATPathElement/GetFlag | GA | INDM | Check that you don't use it
Visualization/Protected/CATPathElement.h/CATPathElement/SetFlag | GA | INDM | Check that you don't use it
Visualization/Protected/CATModifyAttribut.h | GA | LHC | Deprecated since V5R8. Use CATModifyVisProperties instead.
