---
```vbscript
title: "New C++ Authorized APIs in CAA V5R18 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIPrtThreadStandardServices", "CATIEnovUEAffectedObject", "CATImmCAAServices", "CATI2DLayoutLayout", "CATISchAnnotationBreak", "CATIEhfManageLengthTolerance", "CATITPSTangentPlane", "CATIMmiResultFreeze", "CATICciCompositesWorkbenchAddin", "CATITPSVisualization", "CATI2DLayoutSheet", "CATIMeasurableInContext", "CATICloudQsrAddin", "CATIEhfBundleSegmentLink", "CATISchAppMultiImage", "CATIElbFillerPlugInstance", "CATIPDMUEAllowDocumentLoading", "CATIDrwBGAddin", "CATImportAgentBehavior", "CATIAVPMVDADuplicatePRC"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R18GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.358944"
```

---
tags: ["CATIPrtThreadStandardServices", "CATIEnovUEAffectedObject", "CATImmCAAServices", "CATI2DLayoutLayout", "CATISchAnnotationBreak", "CATIEhfManageLengthTolerance", "CATITPSTangentPlane", "CATIMmiResultFreeze", "CATICciCompositesWorkbenchAddin", "CATITPSVisualization", "CATI2DLayoutSheet", "CATIMeasurableInContext", "CATICloudQsrAddin", "CATIEhfBundleSegmentLink", "CATISchAppMultiImage", "CATIElbFillerPlugInstance", "CATIPDMUEAllowDocumentLoading", "CATIDrwBGAddin", "CATImportAgentBehavior", "CATIAVPMVDADuplicatePRC"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R18GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.358944"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R18 GA  

* * *

The following are the new CAA V5R18 GA C++ Authorized APIs, compared with CAA V5R17 at GA level.

  * AdvancedTopologicalOpe framework
    * Class CATGeometrySizeOptimization
    * Global Function CATCreateGeometrySizeOptimization
  * BatchInfrastructure framework
    * Class CATBatchEndNotifCAA
    * Class CATBatchNotif
    * Macro or #define SIZE_T_ID
    * Global Function CATBatchParamToSplitAccess
    * Global Function CloseParameterFile
    * Global Function GetBatchPublisherCAA
    * Global Function GetBatchRootCAA
    * Global Function GetOutputXMLFile
    * Global Function InitParameterFile
    * Interface CATBatClientMonitorCAA
  * CAACompositesItf framework
    * Interface CATICciCompositesWorkbenchAddin
  * CATCloudEditorInterfaces framework
    * Interface CATICloudEditorAddin
    * Interface CATICloudStlAddin
  * CATCloudQsrInterfaces framework
    * Interface CATICloudQsrAddin
  * CATImmENOVIAProvider framework
    * Class CATImmCAAServices
  * CATPDMBase framework
    * Global Function ExtractDocsToFileDirectory
  * CATPDMBaseInterfaces framework
    * Interface CATIPDMUEAllowDocumentLoading
  * CATPlantShipInterfaces framework
    * Class CATEAPspDesignValidation
    * Class CATEAPspValidation
    * Class CATPspCheckViolation
    * Macro or #define Validation_Connection
    * Macro or #define Validation_Context
    * Macro or #define Validation_Document
    * Macro or #define Validation_FromTo
    * Macro or #define Validation_FromToFunction
    * Macro or #define Validation_Function
    * Macro or #define Validation_GroupMembers
    * Macro or #define Validation_Integration
    * Macro or #define Validation_Object
    * Macro or #define Validation_PhysicalIntegration
    * Macro or #define Violation_NotApplicable
    * Macro or #define Violation_Unset
    * Macro or #define ViolationObject_FromTo
    * Macro or #define ViolationObject_Function
    * Macro or #define ViolationObject_Product
    * Interface CATIPspDesignValidation
    * Interface CATIPspPlacePart
    * Interface CATIPspValidation
  * CATSchPlatformInterfaces framework
    * Class CATEASchAppMultiImage
    * Class CATEASchAppMultiImageMaster
    * Enumeration CATSchMIOImageStatus
    * Enumeration CATSchRouteSymbolUpdateMode
    * Interface CATISchAnnotationBreak
    * Interface CATISchAppMultiImage
    * Interface CATISchAppMultiImageMaster
    * Interface CATISchRouteSymbol
  * CATStylingInterfaces framework
    * Interface CATIStylingAddin
  * CATTPSInterfaces framework
    * Enumeration CATTPSFreeState
    * Enumeration CATTPSTangentPlane
    * Enumeration CATTPSViewType
    * Interface CATITPSFreeState
    * Interface CATITPSTangentPlane
    * Interface CATITPSVisualization
  * CATTTRSInterfaces framework
    * Interface CATITTRSGeometry
  * CATxPDMInterfaces framework
    * Class CATxPDMProductServices
  * DMAPSInterfaces framework
    * Enumeration CATSPP3DRenderStyle
    * Enumeration CATSPPDisplayNameMode
    * Interface CATISPPProductIO
  * DNBD5IInterfaces framework
    * Enumeration FrameVisibility
  * DNBManufacturingLayoutItf framework
    * Interface CATIArrAttachmentFactory
    * Interface CATIArrAttachSubscriber
    * Interface CATIArrIgpAttachment
  * Dialog framework
    * Class CATBasicAuthenticationPanel
  * Drafting2DLInterfaces framework
    * Class CAT2DLayoutServices
    * Enumeration CAT2DLViewSide
    * Enumeration CatVisuBackgroundMode
    * Interface CATI2DLayoutLayout
    * Interface CATI2DLayoutSheet
    * Interface CATI2DLayoutView
  * DraftingInterfaces framework
    * Enumeration CATDftThreadTypeEnum
    * Interface CATIDrwBGAddin
  * ENOVInterfaces framework
    * Interface CATIEnovUEAffectedObject
    * Interface ENOVIExternalRBOResolutionEngine
  * ElecDeviceItf framework
    * Interface CATIElbContactInstance
    * Interface CATIElbFillerPlugInstance
  * ElecFlatteningItf framework
    * Interface CATIEhfBundleSegmentLink
    * Interface CATIEhfLengthTolerance
    * Interface CATIEhfManageLengthTolerance
    * Interface CATIEhfUIPLengthTolerance
  * GSMInterfaces framework
    * Enumeration CATGSMBlendConnection
    * Enumeration CATGSMFilletRadiusType
    * Enumeration CATGSMFilletSectionType
    * Enumeration CATGSMSweepFillMode
    * Interface CATIGSMAttributes
    * Interface CATIGSMCuttingPoint
  * GSOInterfaces framework
    * Enumeration CATGSMUnfoldEdgeToTearPositioning
  * ManufacturingInterfaces framework
    * Interface CATIMfgMachiningWorkbenchVisuBehavior
  * Mathematics framework
    * Class CATLISTP(CATMathLine)
    * Class CATSoftwareModification
  * MecModInterfaces framework
    * Enumeration CATMmiDimension
    * Enumeration CATMmiDimensionType
    * Enumeration CATMmrLimitationType
    * Enumeration CATMmrSupportType
    * Interface CATIMmiResultFreeze
    * Typedef CATMfFeaturizeMode
  * MechanicalModeler framework
    * Class CATMmrFeatureAttributes
  * MechanicalModelerUI framework
    * Class CATFeatureAgent
    * Class CATFeatureImportAgent
    * Class CATMmuViewServices
    * Typedef CATFeatureAgentBehavior
    * Typedef CATImportAgentBehavior
  * ObjectSpecsModeler framework
    * Interface CATOsmSUHandler
  * PartInterfaces framework
    * Interface CATIPrtThreadStandardServices
  * PrintBase framework
    * Enumeration CATPrintClipping_State
    * Enumeration CATPrintTextClipping
    * Enumeration CATPrintTextSupport
  * SpaceAnalysisInterfaces framework
    * Enumeration CATMeasModeOfCalc
    * Interface CATIMeasurableInContext
  * System framework
    * Global Function CATGetAppName
  * TopologicalOperators framework
    * Enumeration CATFilletSectionType
    * Global Function CATCreateTopNewSplitShell
    * Global Function CATCreateTopNewSplitWire
  * VPMDesktopObjects framework
    * Interface CATIAVPMVDADuplicatePRC
  * Visualization framework
    * Global Function CATVisGetCurvedPipeGPFromRep
    * Global Function CATVisGetCylinderGPFromRep
    * Interface CATColorManager
    * Interface CATIColorChooser
  * VisualizationBase framework
    * Macro or #define COLOR_INHERITANCE
    * Macro or #define LINETYPE_INHERITANCE
    * Macro or #define LINEWIDTH_INHERITANCE
    * Macro or #define RESET_INHERITANCE
    * Interface CATIVisCGRAdhesionSettingAtt

[Top]

* * *

History Version: **1** [Apr 2007] | Document created  
---|---  
[Top]  

* * *

_Copyright © 1999-2007, Dassault Systèmes. All rights reserved._  
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)
