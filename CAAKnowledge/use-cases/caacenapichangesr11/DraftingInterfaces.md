---
```vbscript
title: "DraftingInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR11"
version: "V5R11"
tags: ["CATIDrwDressUp", "CATIGenerSpec"]
source_file: "Doc/online/CAACenAPIChangesR11/DraftingInterfaces.htm"
converted: "2026-05-11T17:33:50.364212"
```

---
tags: ["CATIDrwDressUp", "CATIGenerSpec"]
source_file: "Doc/online/CAACenAPIChangesR11/DraftingInterfaces.htm"
converted: "2026-05-11T17:33:50.364212"
CAA C++ API Modifications|  DraftingInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | DraftingInterfaces/Protected/CATIGenerSpec.h/CATIGenerSpec/GetSection| GA| MHBDM| Argument 2, whose type was _CATMathPoint *_ is now of type _CATMathPoint * **&**_. The previous signature did'nt work: the output value of the pointer was never retrieved by the caller. No compilation impact.
---|---|---|---
DraftingInterfaces/Protected/CATIDrwDressUp.h/CATIDrwDressUp/GetComponents| GA| MRTHC|
DraftingInterfaces/Protected/CATIDrwDressUp.h/CATIDrwDressUp/ListDimensions| GA| MRTHC|
