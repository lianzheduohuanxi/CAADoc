---
title: "MecModInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CATIDimForwards", "CATIDimCst", "CATIBRepAccess", "CATIREdge"]
source_file: "Doc/online/CAACenAPIChangesR8/MecModInterfaces.md"
converted: "2026-05-11T17:33:52.643644"
---

CAA C++ API Modifications |  MecModInterfaces |   
---|---|---  
  
* * *

** Entity | SP | Modification | To Do** | MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetMechanicalExtendedLabel | GA | MHBDM |    
---|---|---|---  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/IsValid | GA | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetValidity | GA | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/UnGroup | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetAncestors | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetBRepNodes | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetBReps | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetConnexity | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/IsInfinite | GA | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/IsSolvable | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetCells | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/ResolveFaces | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetGeometries | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/CreateBody | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/IsInScope | GA | MHBDM |    
MecModInterfaces/Protected/CATIBRepAccess.h/CATIBRepAccess/GetNamingReference | GA | INDM | Check that you don't use it  
MecModInterfaces/Protected/CATIDimCst.h/CATIDimCst/IsHalf | GA | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MecModInterfaces/Protected/CATIREdge.h/CATIREdge/IsSharp | GA | MHBDM |    
MecModInterfaces/Protected/CATIREdge.h/CATIREdge/IsAIntersectionREdge | GA | MRTHC |    
MecModInterfaces/Protected/CATIDimForwards.h | GA | UHC | Usage Changed from U3 to U1 (Use As Is). Reimplement those interfaces is not supported by the software (does not work anyway)  
MecModInterfaces/Protected/CATMathRGE.h | GA | UHC |  
