---
```vbscript
title: "VPMInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR9"
version: "V5R9"
tags: ["CATIConfigurable", "CATIVpmObjectRules", "CATIVpmGraphPredicat", "CATIVpmAttribute", "CATICfgManager", "CATIVpmAggrAttribute", "CATIVpmServices", "CATIVpmAFLLink", "CATIVpmAFLAffectedObject", "CATIVpmAFLAttachement", "CATICfgModification", "CATIVpmAFLAction", "CATIVpmGraphAdministrator", "CATIVpmGraphStatus", "CATIVpmGraphMng", "CATIVpmAFLResp"]
source_file: "Doc/online/CAACenAPIChangesR9/VPMInterfaces.htmmd"
converted: "2026-05-11T17:33:53.009876"
```

---
tags: ["CATIConfigurable", "CATIVpmObjectRules", "CATIVpmGraphPredicat", "CATIVpmAttribute", "CATICfgManager", "CATIVpmAggrAttribute", "CATIVpmServices", "CATIVpmAFLLink", "CATIVpmAFLAffectedObject", "CATIVpmAFLAttachement", "CATICfgModification", "CATIVpmAFLAction", "CATIVpmGraphAdministrator", "CATIVpmGraphStatus", "CATIVpmGraphMng", "CATIVpmAFLResp"]
source_file: "Doc/online/CAACenAPIChangesR9/VPMInterfaces.htmmd"
converted: "2026-05-11T17:33:53.009876"
CAA C++ API Modifications|  VPMInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/CreateXEff| GA| INDM| Check that you don't use it
---|---|---|---
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/CreateSessionEffectivity| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/GetSessionEffectivityByCV| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/CreateSpecInclusion| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySpecInclusion| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/CreateSpecExpression| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySpecExpression| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/GetFolder| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetModState| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/AttachPlus| GA| MHBDM|
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/AttachMinus| GA| MHBDM|
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/AttachExtension| GA| MHBDM|
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/Modify| GA| MHBDM|
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetX_Effectivity| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetX_EffectivityList| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/SetX_EffectivityList| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfProductType| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/CountValues| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/GetValue| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/Prepend| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/Append| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/AddValue| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/RemoveValue| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAggrAttribute.h/CATIVpmAggrAttribute/RemoveValue| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAttribute.h/CATIVpmAttribute/GetValue| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmAttribute.h/CATIVpmAttribute/SetValue| GA| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmObjectRules.h/CATIVpmObjectRules/GetChildLinkToAExternalNetwork| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmServices.h/CATIVpmServices/SeekEnv| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIHistoricalConnexion.h/ENOVIHistoricalConnexion/CheckConnexionState| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateReplPackageDefinition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateExternSite| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetExternSite| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateReplSubscribingTarget| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetReplSubscribingTarget| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GenerateSubscription| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/Subscribe| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateReplSubscription| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveAllInstances| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetLocalSite| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetReplApplyStatus| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetReplCaptureStatus| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetReplMedia| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetReplPackageDefinition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetReplSubscription| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateLocalSite| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateReplApplyStatus| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateReplCaptureStatus| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateReplMedia| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/AddExternSite| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/AddReplPackageDefinition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/AddReplSubscribingTarget| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/AddReplSubscription| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/SetLocalSite| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/GetOwner| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/GetOrganization| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/ChangeOwner| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/ChangeOwnerWithDesc| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/FindAffObject| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/GetResponsabilitiesByRole| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/GetOwner| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/GetOrganization| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/ChangeOwner| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAttachement.h/CATIVpmAFLAttachement/GetCreator| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLLink.h/CATIVpmAFLLink/GetOwner| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLLink.h/CATIVpmAFLLink/GetOrganization| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLResp.h/CATIVpmAFLResp/GetUser| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLResp.h/CATIVpmAFLResp/GetRole| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIConnectable.h/ENOVIConnectable/CreateDependenceConnexion| GA| MHBDM|
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/GetGraphFolder| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/CreateGraphInstance| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/RemoveGraphInstance| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/CreateTransition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/CreateOperation| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/CreateCondition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/CreateCommand| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphAdministrator.h/CATIVpmGraphAdministrator/CreateEnumPredicat| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphMng.h/CATIVpmGraphMng/GetTransitionDefinition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphMng.h/CATIVpmGraphMng/GetCondition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphMng.h/CATIVpmGraphMng/GetCommandDefinition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphPredicat.h/CATIVpmGraphPredicat/GetEnumPredicat| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphStatus.h/CATIVpmGraphStatus/AddTransition| GA| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmGraphStatus.h/CATIVpmGraphStatus/RemoveTransition| GA| INDM| Check that you don't use it
