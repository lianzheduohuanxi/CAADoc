---
```vbscript
title: "CATAnalysisInterfaces Framework Modifications in CXR14"
category: "use-case"
module: "CAACenAPIChangesR14"
version: "V5R14"
tags: ["CATISamAnalysisManager", "CATISamAnalysisSet", "CATISamAnalysisModel", "CATISamAnalysisContext"]
source_file: "Doc/online/CAACenAPIChangesR14/CATAnalysisInterfaces.htmmd"
converted: "2026-05-11T17:33:50.847843"
```

---
tags: ["CATISamAnalysisManager", "CATISamAnalysisSet", "CATISamAnalysisModel", "CATISamAnalysisContext"]
source_file: "Doc/online/CAACenAPIChangesR14/CATAnalysisInterfaces.htmmd"
converted: "2026-05-11T17:33:50.847843"
CAA C++ API Modifications|  CATAnalysisInterfaces |

* * *

**Entity|  SP| Modification| To Do** | CATAnalysisInterfaces/Public/CATISamAnalysisContext.h| GA| [UHC](CAACenAPIChangeDetail.htm#Abstract)| Must not be derived anymore. Use the newly added methods to set options instead.
---|---|---|---
CATAnalysisInterfaces/Public/CATISamAnalysisManager.h/CATISamAnalysisManager/AddAnalysisModel
**Prototype:**`virtual HRESULT AddAnalysisModel(const CATISamAnalysisModel* ipiAnalysisModel)= 0;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| Has always crashed. Check that you don't use it
CATAnalysisInterfaces/Public/CATISamAnalysisManager.h/CATISamAnalysisManager/AddAnalysisModel
CATAnalysisInterfaces/Public/CATISamAnalysisSet.h/CATISamAnalysisSet/GetConnected

**Prototype:**`virtual HRESULT GetConnected(CATLISTV_CATISamAnalysisSet_var_ & oLinks,CATLONG32 iLevel =-1)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| long Changed into int for performance purpose, no impact, prepares 64 bits migration.
CATAnalysisInterfaces/Public/CATISamAnalysisManager.h/CATISamAnalysisManager/AddAnalysisModel
CATAnalysisInterfaces/Public/CATISamAnalysisSet.h/CATISamAnalysisSet/GetConnected
CATAnalysisInterfaces/Public/CATISamAnalysisSet.h/CATISamAnalysisSet/GetSons

**Prototype:**`virtual HRESULT GetSons(CATLISTV_CATISamAnalysisSet_var_ & oSons,CATLONG32 iLevel =-1)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| long Changed into int for performance purpose, no impact, prepares 64 bits migration.
CATAnalysisInterfaces/Public/CATISamAnalysisSet.h/CATISamAnalysisSet/GetConnected
CATAnalysisInterfaces/Public/CATISamAnalysisSet.h/CATISamAnalysisSet/GetSons
CATAnalysisInterfaces/Public/CATISamAnalysisSet.h/CATISamAnalysisSet/Scan

**Prototype:**`virtual HRESULT Scan(CATLISTV_CATISamAnalysisSet_var_ & oLinks,SAM_ScanCriterium iCriterium,const CATUnicodeString& iName,const CATUnicodeString& iType,CATLONG32 iDirection = 0,CATLONG32 iPartial = 0,CATLONG32 iLevel =-1)= 0;`| GA| [MHBDM](CAACenAPIChangeDetail.htm#Abstract)| long Changed into int for performance purpose, no impact, prepares 64 bits migration.
