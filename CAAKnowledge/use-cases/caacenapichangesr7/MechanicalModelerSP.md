---
title: "MechanicalModeler Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIMfBRep", "CATIMechanicalImport", "CATIMfPointOnEdge", "CATIMfRsur", "CATIMfScopeAccess", "CATIShapeFeatureBody", "CATIMfBRepFactory", "CATInterfaceObject"]
source_file: "Doc/online/CAACenAPIChangesR7/MechanicalModelerSP.md"
converted: "2026-05-11T17:33:52.156957"
---

CAA API Modifications |  MechanicalModeler |   
---|---|---  
  
* * *

** Entity | SP | Modification | To Do** | MechanicalModeler/Protected/CATDimTempCst.h/CATDimTempCst/CATDimTempCst | 1 | MHBDM | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
---|---|---|---  
MechanicalModeler/Protected/CATIMechanicalImport.h/CATIMechanicalImport/SynchronizeResult | 5 | MHBDM |    
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsABRep | 1 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsASuperBRep | 1 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsAIntersectionBRep | 1 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsCompatibleWith | 1 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/IsSlaveContextuelle | 1 | MRTHC | [CATBoolean Migration](../CAACenQuickRefs/CAACenWhatsNew.htm#CATBoolean).No Impact  
MechanicalModeler/Protected/CATIMfBRep.h/CATIMfBRep/GetNamingReference | 1 | INDM | Check that you don't use it  
MechanicalModeler/Protected/CATIMfBRepFactory.h | 1 | UHC | Usage Changed from U3 to U1 (Use As Is). Reimplement those interfaces is not supported by the software (does not work anyway)  
MechanicalModeler/Protected/CATIMfPointOnEdge.h/CATIMfPointOnEdge/GetNamingReference | 1 | INDM | Check that you don't use it  
MechanicalModeler/Protected/CATIMfRsur.h/CATIMfRsur/GetSketchElement | 1 | MHBDM |    
MechanicalModeler/Protected/CATIMfScopeAccess.h/CATIMfScopeAccess/CreateScopeAndNodesFromBRep | 1 | INDM | Check that you don't use it  
MechanicalModeler/Protected/CATIShapeFeatureBody.h/CATIShapeFeatureBody/GetBodyOUT | 1 | MRTHC | return type has changed from CATInterfaceObject to CATBaseUnknown.  
MechanicalModeler/Protected/CATIShapeFeatureBody.h/CATIShapeFeatureBody/GetShape | 1 | MRTHC | return type has changed from CATInterfaceObject to CATBaseUnknown.  
MechanicalModeler/Protected/CATIShapeFeatureBody.h/CATIShapeFeatureBody/GetBodyIN | 1 | MRTHC | return type has changed from CATInterfaceObject to CATBaseUnknown.
