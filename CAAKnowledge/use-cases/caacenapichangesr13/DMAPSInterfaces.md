---
```vbscript
title: "DMAPSInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR13"
version: "V5R13"
tags: ["CATISPPChildManagement"]
source_file: "Doc/online/CAACenAPIChangesR13/DMAPSInterfaces.htm"
converted: "2026-05-11T17:33:50.687409"
```

---
| CAA C++ API Modifications|  DMAPSInterfaces  |
---|---|---

* * *

**Entity|  SP| Modification| To Do** | DMAPSInterfaces/Public/CATISPPChildManagement.h/CATISPPChildManagement/GetNumberOfChild/Arg_1| GA| ADVHC| Default value has changed from "Activity" to "". No impact today because the default value is managed internally but is meant to prepare a tigher IPD integration. Pleaser check that you don't call it like this:
      * `GetNumberOfChild("Activity");` but like that:
      * `GetNumberOfChlid("");`
---|---|---|---
DMAPSInterfaces/Public/CATISPPChildManagement.h/CATISPPChildManagement/GetChild/Arg_1| GA| ADVHC
