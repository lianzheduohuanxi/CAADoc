---
```vbscript
title: "DraftingInterfaces Framework Modifications in V5R14"
category: "use-case"
module: "CAACenAPIChangesR14"
version: "V5R14"
tags: ["CATISketch_var", "CATIDrwGenDrawShape", "CATIDftPattern", "CATIGenerSpec", "CATIProduct_var", "CATILinkableObject_var", "CATISpecObject_var"]
source_file: "Doc/online/CAACenAPIChangesR14/DraftingInterfaces.htmmd"
converted: "2026-05-11T17:33:50.891917"
```

---
| CAA C++ API Modifications|  DraftingInterfaces Framework Modifications in V5R14 |
---|---|---

* * *

**Entity|  SP| Modification| To Do** | DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetBody
**Prototype:**`virtual CATILinkableObject_var GetBody(#)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
---|---|---|---
DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetProduct
**Prototype:**`virtual CATIProduct_var GetProduct(#)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetProduct
DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetPattern

**Prototype:**`virtual CATIDftPattern* GetPattern(#)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetProduct
DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetPattern
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetDetailSketch

**Prototype:**`virtual CATISketch_var GetDetailSketch(#)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIDrwGenDrawShape.h/CATIDrwGenDrawShape/GetPattern
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetDetailSketch
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetDetailCallout

**Prototype:**`virtual CATISpecObject_var GetDetailCallout(#)const = 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetDetailSketch
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetDetailCallout
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetSectionCallout

**Prototype:**`virtual CATISpecObject_var GetSectionCallout(#)const = 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetDetailCallout
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetSectionCallout
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetProjectionProfil

**Prototype:**`virtual CATISpecObject_var GetProjectionProfil(CATMathPoint oProfil[2],CATMathDirection &oVecpro;)const = 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetSectionCallout
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetProjectionProfil
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetProjectionCallout

**Prototype:**`virtual CATISpecObject_var GetProjectionCallout(#)const = 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetProjectionProfil
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetProjectionCallout
DraftingInterfaces/Public/CATIGenerSpec.h/CATIGenerSpec/GetBreakCallout

**Prototype:**`virtual CATISpecObject_var GetBreakCallout(#)const = 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| Useless: was not implemented.
