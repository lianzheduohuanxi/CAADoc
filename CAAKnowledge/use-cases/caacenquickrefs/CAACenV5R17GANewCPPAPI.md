---
```vbscript
title: "New C++ Authorized APIs in CAA V5R17 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIMfgCopyOperation", "CATIPrdTransactionalEventMgt", "CATITPSConsumable", "CATI2DLMainWkbAddin", "CATInstantCollabDesignCAAItf", "CATIMfgUndoManager", "CATI2DLBackWkbAddin", "CATIColMergeContextRole", "CATIAVPMVDAAlternatePart", "CATImmIdentifierAcquisitionAgent", "CATIColMergeable", "CATIImmNavAddin", "CATISamAnalysisGeneralSettingAtt", "CATIMfgMultiAxisAlgorithm", "CATIAApplicationFrame", "CATIPDMUEDocumentName", "CATIColSharable", "CATIPrtUIFactory", "CATIAV4Interfaces", "CATIEhfUIPArrangeJunction"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R17GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.294353"
```

---
tags: ["CATIMfgCopyOperation", "CATIPrdTransactionalEventMgt", "CATITPSConsumable", "CATI2DLMainWkbAddin", "CATInstantCollabDesignCAAItf", "CATIMfgUndoManager", "CATI2DLBackWkbAddin", "CATIColMergeContextRole", "CATIAVPMVDAAlternatePart", "CATImmIdentifierAcquisitionAgent", "CATIColMergeable", "CATIImmNavAddin", "CATISamAnalysisGeneralSettingAtt", "CATIMfgMultiAxisAlgorithm", "CATIAApplicationFrame", "CATIPDMUEDocumentName", "CATIColSharable", "CATIPrtUIFactory", "CATIAV4Interfaces", "CATIEhfUIPArrangeJunction"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R17GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.294353"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R17 GA

* * *

The following are the new CAA V5R17 GA C++ Authorized APIs, compared with CAA V5R16 at GA level.

  * AdvancedMathematics framework
    * Macro or #define CATMUTABLE
  * AdvancedTopologicalOpe framework
    * Class CATTopExtrapolWireOpe
```vbscript
    * Global Function CATCreateTopExtrapolWireOpe
  * AnalysisMeshingToolsItf framework
```
    * Class CATMSHCustomHighlight
    * Typedef CATMSHMethodHilight
  * BasicTopologicalOpe framework
    * Class CATTopEdgePropagation
    * Enumeration CATTopEdgePropagationDiagnosis
```vbscript
    * Global Function CATCreateTopEdgePropagation
  * CATAnalysisInterfaces framework
```
    * Interface CATISamAnalysisGeneralSettingAtt
  * CATIAApplicationFrame framework
    * Class CATCafCenterGraph
  * CATIAV4Interfaces framework
```vbscript
    * Global Function CATV4iGetV4ElementFromJele
    * Global Function CATV4iGirad1
    * Global Function CATV4iGircom
  * CATImmENOVIAProvider framework
```
    * Class CATImmIdentifierAcquisitionAgent
    * Interface CATIImmNavAddin
    * Interface CATIImmSearchAddin
  * CATInstantCollabDesignCAAItf framework
    * Class CATColIMergeableAdapter
    * Class CATColISharableAdapter
    * Class CATCollabLocalInfo
    * Class CATCollabWsInfo
    * Macro or #define CATLISTP_APPLY_RELEASE
    * Macro or #define SizeCollabUUID
    * Enumeration CATIColMergeContextFlag
    * Enumeration CATIColMergeContextRole
```vbscript
    * Global Function CATColAfterMerge
    * Global Function CATColBeforeMerge
    * Global Function CATColCanBeSharedAs
    * Global Function CATColComputeMergeFlagFromContext
    * Global Function CATColGetAllSharableObjects
    * Global Function CATColGetMergeContextTable
    * Global Function CATColGetShareAccess
    * Global Function CATColIsSharable
    * Global Function CATColListAvailableShareMode
    * Global Function CATColMerge
    * Global Function CATColShareAs
    * Global Function CATCreateCATICollabServices
    * Interface CATIColId
```
    * Interface CATIColInvariantId
    * Interface CATICollabServices
    * Interface CATIColMergeable
    * Interface CATIColMergeContextTable
    * Interface CATIColMergeItem
    * Interface CATIColSharable
    * Typedef CATListOfShareAccess
  * CATPDMBase framework
```vbscript
    * Global Function ExtractDocumentSetToFileDirectory
    * Global Function GetDocumentSetFromV_IDAndRevision
    * Global Function OpenCatalogDocumentFromV_ID
    * Global Function OpenCatalogDocumentFromV_ID_AND_V_version
    * Global Function OpenPartAndDocumentFrom_V_ID_And_V_version
    * Global Function OpenPartAndDocumentFromV_ID
    * Global Function RunServerCode
    * Global Function SaveCatalogDocument
    * Global Function SavePartAndDocument
    * Global Function StartEV5Server
  * CATPDMBaseInterfaces framework
```
    * Interface CATIPDMUEDocumentName
  * CATTPSInterfaces framework
    * Interface CATITPSConsumable
    * Interface CATITPSSemanticGDTTolerance
  * CATxPDMInterfaces framework
    * Interface CATIxPDMProductItem
  * Drafting2DLInterfaces framework
    * Interface CATI2DLBackWkbAddin
    * Interface CATI2DLMainWkbAddin
  * DraftingInterfaces framework
    * Interface CATIDftDimChamfer
  * ENOVInterfaces framework
    * Class ItemInstanceReportStream
    * Interface CATIEnovCMIPDUserExit
    * Interface ENOVIDocEvents3
    * Interface ENOVIOrderCategoriesUE
    * Interface ENOVIRetrieveAccessibleFormatUE
    * Interface ENOVIVerifySpecsUE
  * ElecFlatteningItf framework
    * Interface CATIEhfFlattenManager
    * Interface CATIEhfUIPArrangeJunction
  * ElectricalInterfaces framework
    * Interface CATIElec2DRepresentation
    * Interface CATIEleDrawingServices
  * GSMInterfaces framework
    * Enumeration CATGSMReflectLineSourceType
  * GSOInterfaces framework
    * Enumeration CATGSMUnfoldSurfaceType
    * Enumeration CATGSMUnfoldTargetOrientationMode
  * GeometricOperators framework
```vbscript
    * Global Function CATConcatenateNurbsCurves
    * Global Function CATConcatenateNurbsSurfaces
  * ManufacturingInterfaces framework
```
    * Interface CATIMfgActInEditorActivity
    * Interface CATIMfgCopyOperation
    * Interface CATIMfgToolAssemblyCompensationManagement
    * Interface CATIMfgUndoManager
  * Mathematics framework
    * Class CATLISTP(CATMathBox2D)
    * Class CATTolerance
```vbscript
    * Global Function CATGetDefaultTolerance
    * Global Function Intersect
  * MechanicalModeler framework
```
```vbscript
    * Global Function CATBRepDecodeCellInBody
  * PLMSecuritySSOCClient framework
```
    * Class PLMSSOClient
    * Class PLMSSOCredential
    * Class PLMSSOCredentialSet
  * PSNInteroperability framework
```vbscript
    * Global Function CATSimpleQueryToVPM
  * PartInterfaces framework
```
```vbscript
    * Global Function CATCreateCATIPrtUIFactory
    * Interface CATIPrtUIFactory
```
  * ProductStructureInterfaces framework
    * Interface CATIPrdTransactionalEventMgt
  * SurfaceMachiningAlgoInterfaces framework
    * Interface CATIMfgMultiAxisAlgorithm
  * System framework
    * Typedef CATLONG
  * TopologicalOperators framework
    * Class CATTopReflectLine
```vbscript
    * Global Function CATCreateTopReflectLine
  * VPMDesktopObjects framework
```
    * Class ENOVIObjectAttrAccess
    * Interface CATIAVPMVDAAlternatePart
    * Interface CATIAVPMVDASubstitute
  * VPMDesktopProduct framework
    * Class ENOVARMPartServices
    * Class ENOVUserExitServices2
  * VPMInterfaces framework
    * Class CATListOfCATIAVPMItemInstance
    * Interface CATICfgProductType
    * Interface ENOVINewVersionEvent
    * Interface ENOVIUERunInteropServerCode
  * VisualizationBase framework
    * Class CAT3DCuboidRep

[Top]

* * *

History Version: **1** [Apr 2006] | Document created
---|---
[Top]

* * *

_Copyright © 1999-2006, Dassault Systèmes. All rights reserved._
```vbscript
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)

```