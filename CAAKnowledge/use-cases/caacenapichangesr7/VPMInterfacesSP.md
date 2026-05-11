---
```vbscript
title: "VPMInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIConfigurable", "CATIAVPMBusinessObject", "CATICfgManager", "CATIABase", "CATIAVPMBOProductInstance", "CATIConfigHandler", "CATIVpmAFLAffectedObject", "CATICfgModification", "CATICfgNormalValue", "CATIVpmFactoryObject", "CATICfgEffectivity", "CATICfgFilter", "CATIAVPMBOProductComponent", "CATICfgSpecCategory", "CATIVpmAFLAction", "CATICfgSimpleSpecification", "CATIConfigurableObject", "CATIVpmLoginSession", "CATICfgORExpression", "CATIAVPMBOPartReference"]
source_file: "Doc/online/CAACenAPIChangesR7/VPMInterfacesSP.htm"
converted: "2026-05-11T17:33:52.330246"
```

---
tags: ["CATIConfigurable", "CATIAVPMBusinessObject", "CATICfgManager", "CATIABase", "CATIAVPMBOProductInstance", "CATIConfigHandler", "CATIVpmAFLAffectedObject", "CATICfgModification", "CATICfgNormalValue", "CATIVpmFactoryObject", "CATICfgEffectivity", "CATICfgFilter", "CATIAVPMBOProductComponent", "CATICfgSpecCategory", "CATIVpmAFLAction", "CATICfgSimpleSpecification", "CATIConfigurableObject", "CATIVpmLoginSession", "CATICfgORExpression", "CATIAVPMBOPartReference"]
source_file: "Doc/online/CAACenAPIChangesR7/VPMInterfacesSP.htm"
converted: "2026-05-11T17:33:52.330246"
CAA API Modifications|  VPMInterfaces  |

* * *

**Entity|  SP| Modification| To Do** | VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsRoot| 1| MHBDM|
---|---|---|---
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsLeaf| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsNode| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsOrphan| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/ModifyReference| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/UpdateFromReference| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/UpdateVersion| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsUptodateFromReference| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsVersionUptodate| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsUptodate| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/Substitute| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/IsSubstitute| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOPartReference.h/CATIAVPMBOPartReference/Alternate| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOProductComponent.h/CATIAVPMBOProductComponent/IsRoot| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOProductComponent.h/CATIAVPMBOProductComponent/IsLeaf| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOProductComponent.h/CATIAVPMBOProductComponent/IsNode| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOProductComponent.h/CATIAVPMBOProductComponent/IsOrphan| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBOProductInstance.h/CATIAVPMBOProductInstance/Substitute| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBOProductInstance.h/CATIAVPMBOProductInstance/IsSubstitute| 1| MHBDM|
VPMInterfaces/Protected/CATIAVPMBusinessObject.h/CATIAVPMBusinessObject/Describe| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBusinessObject.h/CATIAVPMBusinessObject/DescribeCount| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMBusinessObject.h/CATIAVPMBusinessObject/DuplicateMe| 3| MHBDM|
VPMInterfaces/Protected/CATIAVPMBusinessObject.h/CATIAVPMBusinessObject/Promote| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_DomainName| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgBasicEffectivity.h/CATICfgBasicEffectivity/SetStartValue| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgBasicEffectivity.h/CATICfgBasicEffectivity/SetEndValue| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgEffectivity.h/CATICfgEffectivity/GetListOfSimpleSpecs| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/SetModRestriction| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/GetModRestriction| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/AddCondition| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/RemoveCondition| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/AllFilteredObjects| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/GetSize| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/Filter| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/GetListOfFilters| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/GetIdentifier| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/Copy| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/Dump| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/Clean| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/Freeze| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgFilter.h/CATICfgFilter/GetNonCompliantObjects| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffValByObject| 3| MHBDM|
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffValByCV| 3| MHBDM|
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/SetProposedEffectivity| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetProposedEffectivity| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/Validated| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/Validate| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/ValidatedInto| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetSign| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/SetX_Status| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetX_Status| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/Attach| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/Dump| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetIdentifier| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/IsTrue| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/AttachMoins| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgModification.h/CATICfgModification/GetAttachedObjectsMoins| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetValues| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/Substract| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/ComputeAND| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetEndMileStoneName| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetStartMileStoneName| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/SetEndMileStoneName| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/SetStartMileStoneName| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetMileStoneValue| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetListOfModifications| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/AddModification| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/RemoveModification| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/Inverse| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetSign| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/SetSign| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/CopyMe| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/IsTrue| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/Dump| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetAsString| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/Delete| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgNormalValue.h/CATICfgNormalValue/GetSpec| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgORExpression.h/CATICfgORExpression/IsFullyIncludedIn| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/SetMutuallyExclusive| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/UnsetMutuallyExclusive| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/GetMutuallyExclusive| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/GetOwnedSpec| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/Attach| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/Detach| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/IsMandatoryForUID| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/UnsetMandatory| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/SetMandatory| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/GetUIDList| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/CreateSpecification| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/RemoveSpecification| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/SetDescription| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/GetLinkForUID| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSpecCategory.h/CATICfgSpecCategory/Delete| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/SetPackage| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/UnsetPackage| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/IsPackage| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/DefinePackage| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/GetPackage| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/AddWhereUsed| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/SetName| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/GetAlias| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/SetAlias| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATICfgSimpleSpecification.h/CATICfgSimpleSpecification/GetAsXmlSpecObject| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetIdentifier| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/SetName| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetConfigurableObject| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/SetFilter| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetFilter| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetStatus| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/SetOwner| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetOwner| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/AddChild| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/RemoveChild| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetChildren| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/AddBrother| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/RemoveBrother| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetBrothers| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/IsBrother| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/GetDescription| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/SetDescription| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigHandler.h/CATIConfigHandler/CleanMe| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetAllowedType| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/SetAllowedType| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/CreateComponent| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/ImportComponent| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/Unimport| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfImportedComponents| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfSpecUsages| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/QueryInheritedSpecsByPath| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfComponents| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfAuthorizedComponents| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/SetListOfAuthorizedComponents| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/CreateProductType| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetImportedCategoriesFrom| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/Detach| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfImportedSpecsForCO| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/ImportSpecs| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfImportingCO| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/ImportCO| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/GetListOfImportedCO| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/InheritRBFrom| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurable.h/CATIConfigurable/IsHeir| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/CreateModificationEffectivity| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/GetValidatedEffectivityList| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/Restructure| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/CopyConfigHandler| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/CopyMe| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/CopyModification| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/GetValueForUID| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/ConfigAnalysis| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/QueryEffValByObject| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/QueryEffValByListOfObject| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/IsSessionEffectivityEmpty| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/GetActionSE| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/ValidateAssociatedSessionEffectivity| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/GetAssociatedSessionEffectivity| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/SplitEffectivity| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIConfigurableObject.h/CATIConfigurableObject/GetConfigMatrix| 4| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/GetAllAffObj| 3| MHBDM|
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/GetAllObjOfType| 3| MHBDM|
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/RemoveProductView| 3| MHBDM|
VPMInterfaces/Protected/CATIVpmAFLAffectedObject.h/CATIVpmAFLAffectedObject/AddObject| 4| MHBDM|
VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/GetCurrentEnvironment| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/GetVpmObjectAttributeNames| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/GetVpmObjectAttributeName| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/GetPropertiesManager| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/GetCurrentPropertiesManagerName| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryManager.h/CATIVpmFactoryManager/Register| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryObject.h/CATIVpmFactoryObject/GetAssociatedNod| 5| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmFactoryObject.h/CATIVpmFactoryObject/SetAssociatedNod| 3| NPVM| Implement it when entity is implemented or inherited
VPMInterfaces/Protected/CATIVpmFactoryObject.h/CATIVpmFactoryObject/SetNull| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/get_ENOVEventManager| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/get_LongTransactionId| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/get_CommandTransactionId| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/Register| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/Unregister| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/SetSaveActivation| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/GetSaveActivation| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/UndoCommand| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/AbortCommand| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/FireBeforeExecuteCommand| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/FireAfterExecuteCommand| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/CATIVpmLoginSession.h/CATIVpmLoginSession/get_Log| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIAUEName.h| 3| UHC| This is a **deprecated** interface. Starting from V5R10 release. CATIABase has to be used instead.
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getName| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getSupType| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getEntityName| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getGenesisSchema| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getGenesisDomain| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/newInstanceWithIdentifier| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/newInstance| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/bindInstance| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/bindInstanceP| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/bindInstanceList| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/get_Instance| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/IsAKindOf| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getPackageInfo| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/PropertyInfoCount| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getPropertyInfo| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getAggregatingPropertyInfo| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/GetIdentifier| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/GetDicElement| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIObjectInfo.h/ENOVIObjectInfo/getMethodInfo| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/add_PointedObject| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/get_PointedObjects| 3| MHBDM|
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/DetachPointedObject| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/add_PointingObject| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/get_PointingObjects| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/get_PointingObjectsCount| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/DetachPointingObject| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/ENOVIRelationship.h/ENOVIRelationship/get_AllObjects| 1| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/Save| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/Abort| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/BeginModifications| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateProject| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveProject| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateHost| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetListOfHosts| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetHost| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveHost| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateDataServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveDataServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateAppServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetListOfAppServers| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetAppServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveAppServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateVaultServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetListOfVaultServers| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetVaultServer| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveVaultServers| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateDataDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetDataDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveDataDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateDataRDB| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateDataFile| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/CreateBusinessDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/RemoveBusinessDomain| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetListOfRelatedBusinessDomains| 3| INDM| Check that you don't use it
VPMInterfaces/Protected/VPMIAdmin.h/VPMIAdmin/GetMasterBusinessDomain| 3| INDM| Check that you don't use it
