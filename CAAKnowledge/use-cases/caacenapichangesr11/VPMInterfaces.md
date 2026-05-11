---
title: "VPMInterfaces Modifications"
category: "general"
module: "CAACenAPIChangesR11"
tags: ["CATIVpmAFLAffectedObject", "CATIVpmFactoryManager", "CATIVpmAFLAction", "CATIVpmLoginSession"]
source_file: "Doc\online\CAACenAPIChangesR11\VPMInterfaces.htm"
converted: "2026-05-11T17:33:50.482134"
---

CAA C++ API Modifications|  VPMInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/GetGraphManager| GA| NPVM| Second argument of GetGraphManager is now of type _CATBaseUnknown_var &_  
---|---|---|---  
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/GetLogicalUser| GA| NPVM| Implement it when entity is implemented or inherited  
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/Register| GA| MHBDM|   
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/PromoteConfiguration| GA| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/Modify| GA| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/SetValue| GA| MHBDM|   
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/GetValue| GA| MHBDM|   
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/SetId| GA| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/SetValue| GA| MHBDM|   
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/GetValue| GA| MHBDM|   
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/GetDocType| GA| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/SetDocType| GA| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/SetName| GA| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIEventDefinition.h/ENOVIEventDefinition/HasAssociatedData| GA| MRTHC| Return value has changed from boolean to CATBoolean. No impact but please check for correct typing of the receiving variable (should be CATBoolean).  
VPMInterfaces/Protected/ENOVIEventDefinition.h/ENOVIEventDefinition/IsPersistentEvent| GA| MRTHC| Same as above.  
VPMInterfaces/Protected/ENOVIEventDefinition.h/ENOVIEventDefinition/IsBeforeAfterMode| GA| MRTHC| Same as above.  
VPMInterfaces/Protected/ENOVIEventDefinition.h/ENOVIEventDefinition/IsVetoAble| GA| MRTHC| Same as above.
