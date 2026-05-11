---
```vbscript
title: "TopologicalOperators Framework Modifications in V5R16"
category: "use-case"
module: "CAACenAPIChangesR16"
version: "V5R16"
tags: []
source_file: "Doc/online/CAACenAPIChangesR16/TopologicalOperators.htm"
converted: "2026-05-11T17:33:51.231124"
```

---
|
# CAA C++ API Modifications

|
##  TopologicalOperators Framework Modifications in V5R16

* * *

**Entity|  SP| Modification| To Do** | TopologicalOperators/Public/CATDynFilletRadius.h/CATDynFilletRadius/TestDirection
**Prototype:**`short TestDirection()const;`| GA| [INDM ](CAACenAPIChangeDetail.htm#Abstract)| Method never implemented, doesn't work. Check that you don't use it
---|---|---|---
TopologicalOperators/Public/CATDynFilletRadius.h/CATDynFilletRadius/Stream
**Prototype:**`void Stream(CATCGMStream& Str);`| GA| [INDM ](CAACenAPIChangeDetail.htm#Abstract)| Exposition error. Must not be used. Check that you don't use it
TopologicalOperators/Public/CATDynFilletRadius.h/CATDynFilletRadius/UnStream
**Prototype:**`static CATDynFilletRadius*UnStream(CATCGMStream & iStr);`| GA| [INDM ](CAACenAPIChangeDetail.htm#Abstract)| Exposition error. Must not be used. Check that you don't use it
