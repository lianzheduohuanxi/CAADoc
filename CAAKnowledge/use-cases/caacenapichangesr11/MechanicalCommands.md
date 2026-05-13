---
title: "MechanicalCommands Modifications"
category: "use-case"
module: "CAACenAPIChangesR11"
tags: "["CATICCPable", "CATInteractiveInterfaces"]"
source_file: "Doc/online/CAACenAPIChangesR11/MechanicalCommands.htm"
converted: "2026-05-11T17:33:50.434681"
---
| CAA C++ API Modifications|  MechanicalCommands  |
---|---|---

* * *

**Entity|  SP| Modification| To Do** | MechanicalCommands/Protected/CATICCPable.h| GA| FHBD| Modules using the moved resources should have the CATInteractiveInterfaces module added to their LINK_WITH statement of their Imakefile.mk file and add the InteractiveInterfaces framework as a prerequisite in the IdentityCard of their frameworks.
---|---|---|---
