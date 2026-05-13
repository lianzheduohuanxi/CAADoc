---
title: "New C++ Authorized APIs in CAA V5-6R2014 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: "["CATICGMPersistentOperator", "CATICGMAdvancedRemoveFaceOpe", "CATISpecObject", "CATIMmiMechanicalSet", "CATIOsmExtensionFactory", "CATIProviders", "CATISpecAttribute", "CATIWflUserExit", "CATIDescendants", "CATIReplace", "CATITPSSetGlobalCopy", "CATITPSOrientedLinearDimension", "CATIVpmLightNavigationServices", "CATIMmiViewServices", "CATIConnector", "CATIMfgLatheMultiTurSpiMachineMgt", "CATISpecUpdate", "CATIClientContainer", "CATISpecAttribute_var", "CATIUpdateProvider"]"
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R24GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.553018"
---
tags: ["CATICGMPersistentOperator", "CATICGMAdvancedRemoveFaceOpe", "CATISpecObject", "CATIMmiMechanicalSet", "CATIOsmExtensionFactory", "CATIProviders", "CATISpecAttribute", "CATIWflUserExit", "CATIDescendants", "CATIReplace", "CATITPSSetGlobalCopy", "CATITPSOrientedLinearDimension", "CATIVpmLightNavigationServices", "CATIMmiViewServices", "CATIConnector", "CATIMfgLatheMultiTurSpiMachineMgt", "CATISpecUpdate", "CATIClientContainer", "CATISpecAttribute_var", "CATIUpdateProvider"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R24GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.553018"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5-6R2014 GA

* * *

The following are the new CAA V5-6R2014 GA C++ Authorized APIs, compared with CAA V5-6R2013 at GA level.

  * ApplicationFrame framework
    * Class CATAfrAccessChangedNotification
    * Class CATCmdHeaderSensitivityMngt
    * Interface CATIHeaderSpecialize
  * BasicTopologicalOpe framework
```cpp
    * Global Function CATCreateTopGeodesicLineOperatorAngledTangentToWire
  * CATAnalysisInterfaces framework
```
    * Interface CATISamElementGroup
  * CATIAV4Interfaces framework
```cpp
    * Global Function CATV4iGetBaseObject
    * Global Function CATV4iGetDraft
    * Global Function CATV4iGetView
  * CATMecModExtendItf framework
```
    * Class CATMmrReplaceAdapter
    * Interface CATIMmiMechanicalSetServices
    * Interface CATIMmiMechanicalSet
    * Interface CATMmiExtendServicesFactory
  * CATMecModLiveUseItf framework
    * Interface CATIMmiViewServices
  * CATMecModUseItf framework
    * Interface CATMmiUseServicesFactory
  * CATTPSInterfaces framework
    * Interface CATITPSOrientedAngularDimension
    * Interface CATITPSOrientedLinearDimension
    * Interface CATITPSSetGlobalCopy
    * Interface CATITPSSetTransformIntoAssemblySet
  * DNBVNCInterfaces framework
    * Interface DNBIVncMillTurnMachineServices
  * Drafting2DLInterfaces framework
    * Enumeration CatInsureViewNamesUniquenessScope
  * FeatureModelerExt framework
    * Macro or #define E_FMOPERATIONNOTSUPPORTED
  * GMModelInterfaces framework
    * Class CATCGMDiagnosis
    * Enumeration CATFilletRadiusType
    * Enumeration CATFilletSectionType
    * Enumeration CATFilletType
  * GMOperatorsInterfaces framework
    * Macro or #define DOWNCAST
    * Enumeration CATDynExtrapolationMode
    * Enumeration CATDynSelectionMode
    * Enumeration CATFrFTopologicalSweepFill_Type
    * Enumeration CATFrFTopologicalSweepMF_Type
    * Enumeration CATHybConfusionDiagnostic
    * Enumeration CATHybEdgeStatus
    * Enumeration CATHybExtrapolReplaceMode
    * Enumeration CATHybExtrapolSelectionMode
    * Enumeration CATHybExtrapolationMode
    * Enumeration CATHybProjectionContext
    * Enumeration CATHybPropagateMode
    * Enumeration CATHybRelimitationMode
    * Enumeration CATHybSegmentationMode
    * Enumeration CATHybSelectionMode
    * Enumeration CATHybSimplifyMode
```cpp
    * Global Function CATCGMCreate2DBoxComputation
    * Global Function CATCGMCreateAdvancedRemoveFaceOpe
    * Global Function CATCGMCreateDynSplit
    * Global Function CATCGMCreatePowerFill
    * Global Function CATCGMCreateTopGeodesicLineOperatorAngledTangentToWire
    * Interface CATICGM2DBoxComputation
```
    * Interface CATICGMAdvancedRemoveFaceOpe
    * Interface CATICGMDRepOperator
    * Interface CATICGMPersistentOperator
    * Interface CATICGMPowerFill
    * Typedef CATHybEdges
    * Typedef CATHybEdgessIter
    * Typedef CATHybEdgess
    * Typedef CATHybFaces
    * Typedef CATHybFacessIter
    * Typedef CATHybFacess
    * Typedef CATHybVertexs
  * GeometricObjects framework
    * Macro or #define CATManifoldType
  * ManufacturingInterfaces framework
    * Interface CATIMfgActivityMultiSpindle
    * Interface CATIMfgLatheLocalPlaneElement
    * Interface CATIMfgLatheMultiTurSpiMachineMgt
    * Interface CATIMfgResourceFactory2
  * Mathematics framework
    * Class CATCGMInputError
  * MecModInterfaces framework
    * Class CATMmrGraphicPropertiesModes
  * NEOVPMWorkflowInterop framework
    * Class VPMWflUEDefault
    * Interface CATIWflUserExit
  * ObjectSpecsLegacy framework
    * Class CATBehaviorSpecs
    * Class CATLISTP(CATISpecObject)
    * Class CATLISTP(CATSpecPointing)
    * Class CATLISTP(IID)
    * Class CATLISTV(CATISpecAttrKey_var)
    * Class CATLISTV(CATISpecAttribute_var)
    * Class CATLISTV(CATISpecObject_var)
    * Class CATOsmCatalogAccessServices
    * Class CATOsmExtensionServices
    * Class CATOsmUpdateAdapter
    * Class CATSpecLifeCycleObjectExt
    * Class CATSpecPointing
    * Class CATSpecReplaceExt
    * Class ObjectCCP_SPEC
    * Macro or #define CATAttrKind
    * Macro or #define E_ATTRLINK
    * Macro or #define E_CANNOTLOAD
    * Macro or #define E_FACETNOTFOUND
    * Macro or #define E_KEYNOTFOUND
    * Macro or #define E_NOLOCALVALUE
    * Macro or #define E_NOTALIST
    * Macro or #define E_NOTLOADED
    * Macro or #define E_OUTOFBOUND
    * Macro or #define E_TYPEMISMATCH
    * Macro or #define S_NOSTATUS
    * Enumeration CATAttrAccess
    * Enumeration CATAttrInOut
    * Enumeration CATFlavorParam
    * Enumeration CATParentKind
```cpp
    * Global Function AccessCatalog
    * Global Function CATAddPublicAttributeToFile
    * Global Function CATCreatePublicSpecsInFile
    * Global Function SaveCatalog
    * Global Function SpecBindNativeFormat
    * Global Function UpgradeCatalog
    * Interface CATIAttrBehavior
```
    * Interface CATIBuild
    * Interface CATICatalog
    * Interface CATIClientContainer
    * Interface CATIConnectable
    * Interface CATIConnector
    * Interface CATIDescendants
    * Interface CATIOsmExtendable
    * Interface CATIOsmExtensionFactory
    * Interface CATIOsmExtension
    * Interface CATIOsmUpdate
    * Interface CATIOsmVolatileContainer
    * Interface CATIProviders
    * Interface CATIReplace
    * Interface CATISpecAttrAccess
    * Interface CATISpecAttrKey
    * Interface CATISpecAttribute
    * Interface CATISpecObject
    * Interface CATISpecUpdate
    * Interface CATIStructureAnalyse
    * Interface CATIUpdateProvider
    * Interface CATOsmSUHandler
    * Structure PublicSpec
    * Typedef CATOldTimeStamp
    * Typedef CATOldUpdateStamp
  * PSNInteroperability framework
```cpp
    * Global Function CATAddInstanceOfNotLoadedDocumentFromVPM
  * PartInterfaces framework
```
    * Enumeration CATPrtExtrapolationType
    * Enumeration CATPrtOffsetRegularisationType
    * Interface CATIPdgUseTechResTool
    * Interface CATIPdgUseTechnoRes
  * System framework
    * Macro or #define CATAddOMFactoryFunction
    * Macro or #define CATCreateAndAddOMFactoryFunctionWithSpecificKeyName
    * Macro or #define CATCreateAndAddOMFactoryFunction
    * Macro or #define CATRegisterCreationFunction
    * Enumeration CATTz
    * Typedef OMFactoryFunctionType
  * TopologicalOperators framework
    * Class CAT2DBoxComputation
```cpp
    * Global Function CATCreate2DBoxComputation
  * TopologicalOperatorsLight framework
```
    * Class CATRemoveFacesInShell
  * VPMDesktopObjects framework
    * Class ENOVLightQueryToFullObjectsServices
  * VPMInterfaces framework
    * Macro or #define CATLISTP_InsertAt
    * Macro or #define CATLIST_APPLY_DELETE_LIGHTEXPAND
    * Macro or #define LEX_MODE_42
    * Macro or #define LEX_MODE_ALL
    * Macro or #define LEX_MODE_DMU
    * Enumeration DocumentCriteria
    * Enumeration ENOVLQType
    * Enumeration LightExpandTreeType
    * Enumeration vpmOutOfSync
    * Enumeration vpmTypeNames
```cpp
    * Global Function schema
    * Interface CATIVpmLightExpandObject
```
    * Interface CATIVpmLightNavigationServices
    * Interface ENOVILightExpandable
    * Interface ENOVLightQueryResult

[Top]

* * *

History Version: **1** [Dec 2013] | Document created
---|---
[Top]

* * *

_Copyright © 1999-2013, Dassault Systèmes. All rights reserved._
```cpp
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)

```