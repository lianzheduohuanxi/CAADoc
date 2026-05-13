---
```vbscript
title: "Mathematics Framework Modifications in V5R21"
category: use-case
module: "CAACenAPIChangesR21"
version: "V5R21"
tags: []
source_file: "Doc/online/CAACenAPIChangesR21/Mathematics.htmmd"
converted: "2026-05-11T17:33:51.685249"
```

---
# CAA C++ API Modifications

|
##  Mathematics Framework Modifications in V5R21

* * *

**Entity|  SP| Modification| To Do** | Mathematics/Public/CATMathDirectionf.h/CATMathDirectionf/CATMathDirectionf
**Prototype:**`CATMathDirectionf(const float iFirstCoord = 1.,const float iSecondCoord = 0.,const float iThirdCoord = 0.)`| GA| [ADVHC](CAACenAPIChangeDetail.htm#Abstract)| Constructor with default values becomes two constructors: one without any arguments and one with three arguments, making result more predictable.
---|---|---|---
