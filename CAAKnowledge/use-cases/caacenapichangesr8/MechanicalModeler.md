---
title: "MechanicalModeler Modifications"
category: "use-case"
module: "CAACenAPIChangesR8"
version: "V5R8"
tags: ["CATIMfBRep", "CATIMechanicalImport", "CATIMfPointOnEdge", "CATIMfRsur", "CATIMfScopeAccess", "CATIShapeFeatureBody", "CATIMfBRepFactory", "CATInterfaceObject"]
source_file: "Doc/online/CAACenAPIChangesR8/MechanicalModeler.md"
converted: "2026-05-11T17:33:52.629467"
---

CAA C++ API Modifications |  MechanicalModeler |   
---|---|---  
  
* * *

** Entity | SP | Modification | To Do** | MechanicalModeler/Protected/CATIMechanicalImport.h/CATIMechanicalImport/SynchronizeResult | GA | MHBDM |    
---|---|---|---  
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetCells | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsABRep | GA | MRTHC |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetGeometry | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsSolvable | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetConnexity | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetBRep | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetRSurs | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetFaces | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetEdges | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsASuperBRep | GA | MRTHC |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsAIntersectionBRep | GA | MRTHC |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsCompatibleWith | GA | MRTHC |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsSlaveContextuelle | GA | MRTHC |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetNamingReference | GA | INDM | Check that you don't use it  
MechanicalModeler/Protected/CATDimTempCst.h/CATDimTempCst/CATDimTempCst | GA | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MechanicalModeler/Protected/CATIMfBRepFactory.h | GA | UHC | Coorection in Usage, Before U1, Now U3  
Changed from U3 to U1 (Use As Is). Reimplement those interfaces is not supported by the software (does not work anyway)  | MechanicalModeler/Protected/CATIMfPointOnEdge.h/CATIMfPointOnEdge/GetNamingReference | GA | INDM | Check that you don't use it  
MechanicalModeler/Protected/CATIMfRsur.h/CATIMfRsur/GetSketchElement | GA | MHBDM |    
MechanicalModeler/Protected/CATIMfScopeAccess.h/CATIMfScopeAccess/CreateScopeAndNodesFromBRep | GA | INDM | Check that you don't use it  
MechanicalModeler/Protected/CATIShapeFeatureBody.h/CATIShapeFeatureBody/GetBodyOUT | GA | MRTHC | return type has changed from CATInterfaceObject to CATBaseUnknown.  
MechanicalModeler/Protected/CATIShapeFeatureBody.h/CATIShapeFeatureBody/GetShape | GA | MRTHC | return type has changed from CATInterfaceObject to CATBaseUnknown.  
MechanicalModeler/Protected/CATIShapeFeatureBody.h/CATIShapeFeatureBody/GetBodyIN | GA | MRTHC | return type has changed from CATInterfaceObject to CATBaseUnknown.
