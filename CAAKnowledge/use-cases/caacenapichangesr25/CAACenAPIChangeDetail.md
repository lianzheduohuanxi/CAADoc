---
title: "Detail Of C++ API Changes"
category: "use-case"
module: "CAACenAPIChangesR25"
tags: "["CATICfgInterval", "CATIConfigurable", "CAA2Usage", "CATICfgFilter", "CATICfgManager", "CATIVpmAttribute", "CAA2Level", "CATICfgAttachable", "CATIVpmAFLManager", "CATICfgSimpleSpecification", "CATICfgUEValidateEff", "CATIVpmFactoryObject", "CATIEnovCMManager"]"
source_file: "Doc/online/CAACenAPIChangesR25/CAACenAPIChangeDetail.htm"
converted: "2026-05-11T17:33:51.832518"
---
#

|
##

|
### Detail Of V5-6R2015 C++ API Changes _What changes in the API compared with CAA V5-6R2014_
---|---|---
Technical Article

* * *

Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5-6R2015 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
| Classification | Meaning
---|---
Abstract This article presents by frameworks the detail of CAA C++ resources modified in V5-6R2015 and how to modify your code accordingly. Each modification is listed for a resource (file, class, method) with a classification. They will generally be detected by a recompilation of the code. Most of the time, signature modifications are obvious. Check in the framework detail how to replace deleted entities. Possibly impacting modifications are highlighted in red.
LHC | @CAA2Level Has Changed: a L1 file is no more L1.
UHC | @CAA2Usage Has Changed: usage has changed for a more restricted usage. For example a class tagged as derivable is not derivable anymore.
CHBD | Class Has Been Deleted
FHBD | File Has Been Deleted
ADVHC | Argument Default Value Has Changed
MHBDM | Method Has Been Deleted or Modified
MRTHC | Method Returned Type Has Changed
NPVM | New Pure Virtual Method. A new pure virtual method has been added on a derivable class or on an interface to be implemented without an adapter.
INDM | Method is no more documented. It does not break your code in any way but means that you are not supposed to use it anymore. Check that you don't use it or look for replacement informations.
MINMV | Method is no more virtual. If occurs on a U1 class, may require modifications in Imakefile.mk of client code. If occurs on a U2 class, see details on the documentation of the concerned resource modification.

* * *

MINMV | Method is no more virtual. If occurs on a U1 class, may require modifications in Imakefile.mk of client code. If occurs on a U2 class, see details on the documentation of the concerned resource modification.
File | Class | Method | Modification | To Do

ObjectModelerSystem/PublicInterfaces/sequence_CORBAAny.h |  |  | FHBD | File has been moved into the ObjectModelerCollection framework. Update you application IdentityCard.h and Imakefile.mk files accordingly.
ObjectModelerSystem/PublicInterfaces/sequence.h
ObjectModelerSystem/PublicInterfaces/sequence_octet.h
Mathematics/PublicInterfaces/CATTolerance.h | CATTolerance | ~CATTolerance | INDM | CATTolerance objects are not meant to not de bestroyed by applications. Check that you don't use it
CATPDMReconcile/PublicInterfaces/CATScmPDMObject.h | CATScmPDMObject | CATScmPDMObject | INDM | Check that you don't use it
CATPDMReconcile/PublicInterfaces/CATScmPDMObject.h | CATScmPDMObject | GetDescriptor | INDM | Check that you don't use it
CATPDMReconcile/PublicInterfaces/CATScmPDMObject.h | CATScmPDMObject | SetDescriptor | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/CATIEnovCMManager.h | CATIEnovCMManager | GetCOPSpecRelationships | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/ENOVICfgUESolver.h | ENOVICfgUESolver | Solve | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/ENOVIInitSpecsUE.h | ENOVIInitSpecsUE | getListOfSpecs | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/ENOVIOrderCategoriesUE.h | ENOVIOrderCategoriesUE | OrderCategories | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/VPMIWflParticipant.h | VPMIWflParticipant | Resolve | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/VPMIWflProcess.h | VPMIWflProcess | GetRealResponsible | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/VPMIWflQuery.h | VPMIWflQuery | GetWflDefaultCalendar | INDM | Check that you don't use it
ENOVInterfaces/PublicInterfaces/VPMIWflRegularActivity.h | VPMIWflRegularActivity | GetRealPerformer | INDM | Check that you don't use it
SDMRuntime/PublicInterfaces/SdaiEntity.h | SdaiEntity | SDAIAGGRH | INDM | Check that you don't use it
SDMRuntime/PublicInterfaces/SdaiModel.h | SdaiModel | SDAIAGGRH | INDM | Check that you don't use it
SDMRuntime/PublicInterfaces/SdaiSchema.h | SdaiSchema | SDAIAGGRH | INDM | Check that you don't use it
VPMDesktopObjects/PublicInterfaces/ENOVCustoCommandUtils.h | ENOVCustoCommandUtils | ENOVCustoCommandUtils | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgAttachable.h | CATICfgAttachable | QueryAttachedObject | INDM | Check that you don't use it

| CATICfgFilter | Filter | INDM | Check that you don't use it
SDMRuntime/PublicInterfaces/SdaiModel.h | SdaiModel | SDAIAGGRH | INDM | Check that you don't use it
SDMRuntime/PublicInterfaces/SdaiSchema.h | SdaiSchema | SDAIAGGRH | INDM | Check that you don't use it
VPMDesktopObjects/PublicInterfaces/ENOVCustoCommandUtils.h | ENOVCustoCommandUtils | ENOVCustoCommandUtils | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgAttachable.h | CATICfgAttachable | QueryAttachedObject | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgInterval.h | CATICfgInterval | GetValues | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | CreateBasicEffectivity | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | CreateInterval | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | CreateModContainer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | GetContributingObjectList | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | QueryEffValByObject | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | QueryModContainerByDescription | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | QueryProductType | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgManager.h | CATICfgManager | QuerySpecCategories | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgSimpleSpecification.h | CATICfgSimpleSpecification | Attach | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgSimpleSpecification.h | CATICfgSimpleSpecification | GetLinkForUID | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATICfgUEValidateEff.h | CATICfgUEValidateEff | ValidateEffectivity | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIConfigurable.h | CATIConfigurable | GetListOfMileStoneValue | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIConfigurable.h | CATIConfigurable | GetSpecification | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIConfigurable.h | CATIConfigurable | GetSpecLnkType | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIConfigurable.h | CATIConfigurable | GetTypeDefiningCategories | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIConfigurable.h | CATIConfigurable | QueryMileStoneValueByMileStone | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIConfigurable.h | CATIConfigurable | SetSpecLnkType | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAFLManager.h | CATIVpmAFLManager | CreateAflBinPredicate | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAFLManager.h | CATIVpmAFLManager | CreateAflPredicate | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAFLManager.h | CATIVpmAFLManager | GetVpmObjectAttributeNames | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAttribute.h | CATIVpmAttribute | CheckAttribute | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAttribute.h | CATIVpmAttribute | CloneMe | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAttribute.h | CATIVpmAttribute | GetAttributeName | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmAttribute.h | CATIVpmAttribute | GetAttributeNames | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmFactoryObject.h | CATIVpmFactoryObject | GetFactoryObject | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmFactoryObject.h | CATIVpmFactoryObject | GetRealObject | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmFactoryObject.h | CATIVpmFactoryObject | SetFactoryObject | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/CATIVpmFactoryObject.h | CATIVpmFactoryObject | SetRealObject | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddBusinessDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddDataDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddExternSite | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddHost | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddReplPackageDefinition | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddReplSubscribingTarget | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddReplSubscription | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | AddServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateBusinessDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateDataRDB | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateDataServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateExternSite | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateHost | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateLocalSite | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateReplApplyStatus | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateReplCaptureStatus | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateReplMedia | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateReplPackageDefinition | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateReplSubscribingTarget | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateReplSubscription | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | CreateServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GenerateSubscription | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetAppServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetBusinessDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetDataDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetDataServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetExternSite | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetHost | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetLocalSite | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetMasterBusinessDomain | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetReplApplyStatus | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetReplCaptureStatus | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetReplMedia | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetReplPackageDefinition | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetReplSubscribingTarget | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetReplSubscription | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | GetVaultServer | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | SetLocalSite | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMIAdmin.h | VPMIAdmin | Subscribe | INDM | Check that you don't use it
VPMInterfaces/PublicInterfaces/VPMSession.h | VPMSession | GetPubSubManager | INDM | Check that you don't use it
VPMXBom/PublicInterfaces/ENOVIAttributeDefinitions.h | ENOVIAttributeDefinitions | get_Enum | INDM | Check that you don't use it
References

* * *

VPMXBom/PublicInterfaces/ENOVIAttributeDefinitions.h | ENOVIAttributeDefinitions | get_Enum | INDM | Check that you don't use it
References
History Version: **1** [Jan 2015] | Document created

[Top]

* * *

_Copyright 2014, Dassault Systmes. All rights reserved._
