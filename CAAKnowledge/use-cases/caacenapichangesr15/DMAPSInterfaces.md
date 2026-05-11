---
```vbscript
title: "DMAPSInterfaces Framework Modifications in V5R15"
category: "use-case"
module: "CAACenAPIChangesR15"
version: "V5R15"
tags: ["CATISPPItemMgt"]
source_file: "Doc/online/CAACenAPIChangesR15/DMAPSInterfaces.htm"
converted: "2026-05-11T17:33:51.084972"
```

---
|
# CAA C++ API Modifications

|
##  DMAPSInterfaces Framework Modifications in V5R15

* * *

**Entity|  SP| Modification| To Do** | DMAPSInterfaces/Public/CATISPPItemMgt.h/CATISPPItemMgt/RemoveItem/Arg_2| GA| [ADVHC](CAACenAPIChangeDetail.htm#Abstract)| This argument was not used but is now used since V5R15. Current default status (all_item_kinds) reflects pre-V5R15 behaviour. Behaviour of client code will change only if a (previously useless) value had been provided for this argument.
---|---|---|---
