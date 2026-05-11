---
title: "VPMInterfaces Modifications"
category: "use-case"
module: "CAACenAPIChangesR7"
version: "V5R7"
tags: ["CATIAVPMItemInstance", "CATIAVPMObject", "CATICfgSignedSpec", "CATIAVPMDocumentVersion", "CATIAVPMTPConfigurable", "CATICfgManager", "CATIAVPMTPRootDesktop", "CATIAVPMPartVersion", "CATIAVPMBOPartInstance", "CATIAVPMObjectVersion", "CATIAVPMProductRootClass", "CATIAVPMRootDesktop", "CATIVpmAFLAction", "CATIAVPMObjectMaster", "CATICfgSpecANDExpression", "CATIAVPMBOVersionMaster", "CATIAVPMProductClass"]
source_file: "Doc/online/CAACenAPIChangesR7/VPMInterfaces.md"
converted: "2026-05-11T17:33:52.306203"
---

CAA API Modifications|  VPMInterfaces  |   
---|---|---  
  
* * *

**Entity|  Modification| To Do** | VPMInterfaces/Protected/CATIAVPMBOPartInstance.h/CATIAVPMBOPartInstance/NewVersion| MHBDM|   
---|---|---  
VPMInterfaces/Protected/CATIAVPMBOVersionMaster.h/CATIAVPMBOVersionMaster/NewVersion| MHBDM|   
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/get_DocType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/get_DocPersistency| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/AggregateData| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/AggregateDataStream| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/DeleteData| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/get_Data| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMDocumentVersion.h/CATIAVPMDocumentVersion/get_DataStream| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/IsRoot| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/IsLeaf| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/IsNode| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/IsOrphan| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ParentProductRootClass| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/put_PartVersion| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ProductSpecification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/put_ProductSpecification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/AggregateTechInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_TechInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_TechInstanceCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ItemInstanceCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/put_ItemInstanceFromPV| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/put_ItemInstanceFromPS| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ParentItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/put_ProductComponent| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/RemoveProductComponent| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ProductComponentCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ProductComponent| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/AggregateSubstituteItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_Substitute| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_SubstituteCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/Substitute| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/IsSubstitute| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_SubstituteBase| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/CreateSymetricalItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/AggregateRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_Relation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_RelationCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/DeleteRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_AttachedRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_AttachedRelationCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/DeleteAttachedRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/put_Matrix| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_Matrix| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_NearItemInstances| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_AssemblyRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_Reference| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ParentTechRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMItemInstance.h/CATIAVPMItemInstance/get_ParentTechRelationCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/put_IND| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/Remove| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/get_HexaUuid| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/get_Uuid| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/put_Document| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/RemoveDocumentValue| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/get_Document| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/get_DocumentCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/get_AllDocument| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/get_AllDocumentCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObject.h/CATIAVPMObject/Print| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/AggregateObjectVersion| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/get_PreferedVersion| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/get_FirstVersion| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/CreateMaster| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/AggregateObjectFamily| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/get_ObjectFamilyCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/get_ObjectFamily| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectMaster.h/CATIAVPMObjectMaster/get_PreferedObjectFamily| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectVersion.h/CATIAVPMObjectVersion/Init| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectVersion.h/CATIAVPMObjectVersion/get_ParentObjectFamily| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMObjectVersion.h/CATIAVPMObjectVersion/IsPreferredVersion| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/AggregateTechInterface| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/get_TechInterface| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/get_TechInterfaceCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/get_ParentItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/get_ParentItemInstanceCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/AggregateAssemblyRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMPartVersion.h/CATIAVPMPartVersion/get_AssemblyRelation| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductClass.h| LHC| Useless for customer scenarii.  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ParentProductClass| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateProductComponent| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ProductComponentCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ProductComponent| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateZone| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ZoneCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_Zone| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateItemInstanceFromPV| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateItemInstanceFromPS| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateItemInstanceFromReference| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ItemInstanceCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ItemInstance| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/AggregateProductSpecification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ProductSpecification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMProductRootClass.h/CATIAVPMProductRootClass/get_ProductSpecificationCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMRootDesktop.h| LHC| Useless for customer scenarii.  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/AggregateConfigurableObject| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/DeleteConfigurableObject| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/Is_Configurable| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/put_CurrentCfgModification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/get_CurrentCfgModification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/ResetCurrentCfgModification| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/put_CurrentModificationTag| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/get_CurrentModificationTag| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPConfigurable.h/CATIAVPMTPConfigurable/ResetCurrentModificationTag| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_Object| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/GetVpmObjectAttributeNames| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_CurrentSubType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/put_CurrentSubType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_SubTypeCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_SubType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_SupType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/put_Buffer| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_BufferedAttributeCount| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_BufferedObjectType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_BufferedAttribute| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/ResetBuffer| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/SaveBuffer| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/RestoreBuffer| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/SaveFolder| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/Create| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/put_CustomizedType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/get_CustomizedType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/RemoveCustomizedType| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/put_DomainName| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATIAVPMTPRootDesktop.h/CATIAVPMTPRootDesktop/IsFileMode| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffValByObject| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffValByCV| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffectivities| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffectivitiesByCO| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryAllConfigurableObject| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryConfigurableObjectByName| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryConfigurableObjectByObject| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryConfigurableObject| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySpecCategories| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySimpleSpec| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySimpleSpecForCategory| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySpecInclusion| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QuerySpecExpression| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryConfigHandler| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryConfigHandlerForCO| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryAllConfigurable| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/AllowApplicability| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryNormalValuesByMileStoneName| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryModHistoryByObject| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryAllModHistory| MHBDM|   
VPMInterfaces/Protected/CATICfgManager.h/CATICfgManager/QueryEffectivitiesByName| MHBDM|   
VPMInterfaces/Protected/CATIVpmAFLAction.h/CATIVpmAFLAction/RemoveProductView| MHBDM|   
VPMInterfaces/Protected/CATListOfCATIAVPMObject.h| LHC| Useless for customer scenarii.  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/ActivateBoundingVolumeComputing| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/DeactivateBoundingVolumeComputing| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/IsBoundingVolumeComputingActivated| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/RemoveBoundingVolumeComputing| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/ComputeBoundingVolume| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/PropagateBoundingVolume| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/NotifyVolumeModification| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/SaveSpaceMap| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/get_SpaceMap| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/ComputeSpaceMap| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/DeleteSpaceMap| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIAVolumeManager.h/ENOVIAVolumeManager/CheckClearence| INDM| Check that you don't use it  
VPMInterfaces/Protected/ENOVIExpandable.h/ENOVIExpandable/get_ExpandTypes| INDM| Check that you don't use it  
VPMInterfaces/Protected/CATICfgSignedSpec.h/CATICfgSignedSpec/GetEncodedString| MHBDM|   
VPMInterfaces/Protected/CATICfgSignedSpec.h/CATICfgSignedSpec/GetAsXmlString| MHBDM|   
VPMInterfaces/Protected/CATICfgSpecANDExpression.h/CATICfgSpecANDExpression/IsIncludedIn| MHBDM|   
VPMInterfaces/Protected/CATICfgSpecANDExpression.h/CATICfgSpecANDExpression/GetAsXmlString| MHBDM| 
