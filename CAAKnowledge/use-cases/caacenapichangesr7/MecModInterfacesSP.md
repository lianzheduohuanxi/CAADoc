---
```vbscript
title: "MecModInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIDimForwards", "CATIDimCst", "CATIBRepAccess", "CATIREdge"]
source_file: "Doc/online/CAACenAPIChangesR7/MecModInterfacesSP.htm"
converted: "2026-05-11T17:33:52.171535"
```

---
tags: ["CATIDimForwards", "CATIDimCst", "CATIBRepAccess", "CATIREdge"]
source_file: "Doc/online/CAACenAPIChangesR7/MecModInterfacesSP.htm"
converted: "2026-05-11T17:33:52.171535"
CAA API Modifications |  MecModInterfaces |   

* * *

** Entity | SP | Modification | To Do** | MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/IsValid | 3 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
---|---|---|---  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetValidity | 3 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/IsInfinite | 3 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/CreateBody | 3 | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetNamingReference | 1 | INDM | Check that you don't use it  
MecModInterfaces/Protected/CATIDimCst.h/CATIDimCst/IsHalf | 3 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIDimForwards.h | 1 | UHC | Usage Changed from U3 to U1 (Use As Is). Reimplement those interfaces is not supported by the software (does not work anyway)  
MecModInterfaces/Protected/CATIREdge.h/CATIREdge/IsAIntersectionREdge | 3 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact
