---
title: "New C++ Authorized APIs in CAA V5R13 GA"
category: "general"
module: "CAACenQuickRefs"
tags: ["CATINT32", "CATIElbMountingEquipment", "CATITPSCaptureList", "CATITPSSetVisu", "CATIEhfFlatteningParameters", "CATIEhiMultiBranchable", "CATIStructurePlate", "CATIBatchElementsCAA", "CATIAVPMVDAValidateAttributeChg", "CATIStructureObject", "CATISchGRRRoute2", "CATIEhiBranchable", "CATIMfgToolAssembly3DVisuCustom", "CATIMfgActivitySyntax", "CATIPDMUEReadMode", "CATIniInputDescriptionAdaptor", "CATISysSettingController", "CATImplementSettingCtrl", "CATIMfgToolAssemblyEditorCustom", "CATIBatchCAA"]
source_file: "Doc\online\CAACenQuickRefs\CAACenV5R13GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.138016"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R13 GA  
---|---  
  
* * *

The following are the new CAA V5R13 GA C++ Authorized APIs, compared with CAA V5R12 at GA level.

  * AdvancedMachiningInterfaces framework
    * Interface CATIAMGProgramAddin
  * AdvancedTopologicalOpe framework
    * Enumeration CATTopCleanCrvC1ToC2Management
  * AnalysisMeshingModel framework
    * Class CATMSHCriterionServices
  * ApplicationFrame framework
    * Class CATAfrCheckHeaderAccessor
    * Class CATBatchFrame
    * Class CATLISTP(CATCommandHeader)
    * Class CATLISTP(CATFrmEditor)
    * Class CATStackableCommandSet
    * Global Function CATAfrGetCommandHeader
    * Global Function CATAfrStartCommand
    * Interface CATIAfrActivateWorkbench
    * Interface CATIAfrCmdPaletteOptions
    * Interface CATIAfrPaletteOptions
  * BasicTopologicalOpe framework
    * Class CATTopPolarExtremumOperator
    * Enumeration CatTopPolarExtremum
    * Global Function CATCreateTopPolarExtremumOperator
  * BatchInfrastructure framework
    * Class CATBatchLogCAA
    * Class CATBatchParameters
    * Class CATBatStatePubCAA
    * Enumeration ExportedByCATBatchUtils
    * Global Function GetCATIBatchCAA
    * Interface CATIBatchCAA
    * Interface CATIBatchElementCAA
    * Interface CATIBatchElementsCAA
  * CATAnalysisInterfaces framework
    * Class CATSamAnalysisContext
    * Class CATSamCatalogFactory
    * Enumeration CATSamBendingType
    * Enumeration CATSamWallType
  * CATAnalysisResources framework
    * Class CATEAnalysisGroup
    * Class CATEAnalysisSupportFilter
  * CATGraphicProperties framework
    * Class CATExtIVisProperties
  * CATIAV4Interfaces framework
    * Global Function CATV4iGiresi
    * Global Function CATV4iGirevi
    * Global Function CATV4iGirmat
    * Interface CATIV4DataTranslator
  * CATPDMBaseInterfaces framework
    * Interface CATIPDMUEReadMode
  * CATSchPlatformInterfaces framework
    * Class CATEASchAppCntrDocLink
    * Enumeration CATSchGRRRouteReshapeMode
    * Interface CATISchAppCntrDocLink
    * Interface CATISchFrameInfo
    * Interface CATISchGRRRoute2
    * Interface CATISchPostReplace
  * CATTPSInterfaces framework
    * Enumeration CATTPSDimLimType
    * Enumeration CATTPSLinkWithGeomType
    * Enumeration CATTPSSearchAlgoType
    * Global Function CATCreateCATITPSCaptureList
    * Global Function CATCreateCATITPSViewList
    * Interface CATITPSAssociativeGroup
    * Interface CATITPSCapture
    * Interface CATITPSCaptureFactory
    * Interface CATITPSCaptureList
    * Interface CATITPSDefaultAnnotation
    * Interface CATITPSGeometry
    * Interface CATITPSOrientedDimension
    * Interface CATITPSSetVisu
    * Interface CATITPSSpecific
  * Communications framework
    * Enumeration CATComFileType
  * DNBInspectInterfaces framework
    * Enumeration DNBInsAlignmentType
    * Enumeration DNBInsDirectionSpecifier
    * Enumeration DNBInsTangentSolution
  * Dialog framework
    * Class CATDlgStdFile
  * DialogEngine framework
    * Class CATEditAgent
  * DraftingInterfaces framework
    * Enumeration CATAssPositioningBehavior
    * Enumeration CATAssProjectingMode
    * Enumeration CATDftGenViewsPosMode
    * Interface CATIDft2DPrintArea
  * ENOVDDManager framework
    * Class ENOVDDMNGAccessLog
  * ENOVDesktopDocumentBOCmds framework
    * Global Function GetDocCommandFactory
    * Interface ENOVIAVDADocCheckIn
    * Interface ENOVIAVDADocCheckOut
    * Interface ENOVIAVDADocConvertToMultiSheet
    * Interface ENOVIAVDADocCreateNewFormat
    * Interface ENOVIAVDADocDetach
    * Interface ENOVIAVDADocPaste
    * Interface ENOVIAVDADocRetrieve
  * ENOVEdeIntegrationItf framework
    * Interface ENOVIExUE_EH_MH_integration
  * ENOVInterfaces framework
    * Class CATListPtrENOVIABO
    * Interface CATIDocRevEventListener
    * Interface ENOVIABODocumentFile
    * Interface ENOVIABODocumentTOC
    * Interface ENOVIDocEvents2
    * Interface ENOVIVpmPostIntrospection
  * ENOVReportSolutionServer framework
    * Class ENOVReportUtilities
  * ElecDeviceItf framework
    * Interface CATIElbMountingEquipment
    * Interface CATIElbMountingEquipmentReference
  * ElecFlatteningItf framework
    * Interface CATIEhfEnvironment
    * Interface CATIEhfFlatteningParameters
  * ElecHarnessItf framework
    * Enumeration CatEhiInsertMode
    * Enumeration CatEhiSupportMode
    * Interface CATIEhiBranchable
    * Interface CATIEhiMultiBranchable
  * GSMInterfaces framework
    * Enumeration CATGSMFeatureContextType
  * GSOInterfaces framework
    * Enumeration CATGSMTypeOfTransfer
  * GeometricObjects framework
    * Class CATLISTP(CATCurve)
  * GeometricOperators framework
    * Global Function CATCreateEdgeCurveComputation
    * Global Function CATCreateInclusion
    * Global Function CATCreatePlanarMapping
  * InteractiveInterfaces framework
    * Class CATIniInputDescriptionAdaptor
    * Interface CATIInputDescription
  * ManufacturingInterfaces framework
    * Interface CATIMfgActivitySyntax
    * Interface CATIMfgToolAssembly3DVisuCustom
    * Interface CATIMfgToolAssemblyEditorCustom
  * MecModInterfaces framework
    * Interface CATIGSMTool
  * MechanicalModeler framework
    * Class CATMmrLinearBodyServices
  * NewTopologicalObjects framework
    * Global Function CATCreatePositionPtFaceOperator
  * ObjectModelerBase framework
    * Class CATLISTP(CATIDocId)
    * Class CATOmbWarmStartServices
    * Global Function CATOmbPerformAfterContainerCreation
  * OptimizationInterfaces framework
    * Interface CATIKwoWorkshopAddin
    * Interface CATIOptUpdateManagement
  * SPACATIAV5ToGeneric framework
    * Class CATV5ToGeneric
  * SPAXGeneric framework
    * Class SPAXEndPsConversionTaskEvent
    * Class SPAXEndPsReadFileTaskEvt
    * Class SPAXStartPsConversionTaskEvt
    * Class SPAXStartPsReadFileTaskEvt
  * SPAXIDIToCATIAV5 framework
    * Macro or #define DECL_IDITOV5
    * Global Function RunIDIV5Conversion
  * SketcherInterfaces framework
    * Interface CATI2DEquivalentTopology
  * SpecialAPI framework
    * Typedef CATINT32
    * Typedef CATINTPTR
    * Typedef CATLONG32
    * Typedef CATLONG64
    * Typedef CATLONGINT
    * Typedef CATLONGPTR
    * Typedef CATUINT32
    * Typedef CATUINTPTR
    * Typedef CATULONG32
    * Typedef CATULONG64
    * Typedef CATULONGINT
    * Typedef CATULONGPTR
  * StructureInterfaces framework
    * Interface CATIStructureMember
    * Interface CATIStructureObject
    * Interface CATIStructurePlate
  * System framework
    * Class CATLISTV(CATBaseUnknown_var)
    * Class CATSysAutoSettingController
    * Class CATSysSettingController
    * Macro or #define CATDeclareAutoSettingCtrl
    * Macro or #define CATDeclareSettingCtrl
    * Macro or #define CATImplAutoSettingCtrl
    * Macro or #define CATImplAutoSettingCtrlInfoMethod
    * Macro or #define CATImplementBOA
    * Macro or #define CATImplementSettingCtrl
    * Macro or #define CATSysAddImplSettingCtrlLocks
    * Macro or #define CATSysBeginImplSettingCtrlLocks
    * Macro or #define CATSysDeclareAutoSettingCtrlLocks
    * Macro or #define CATSysDeclareSettingCtrlLocks
    * Macro or #define CATSysEndImplSettingCtrlLocks
    * Macro or #define CATSysImplAutoSettingCtrlLocks
    * Macro or #define CATSysImplementSettingCtrlLocks
    * Macro or #define CATSysSettingCtrlDispatch
    * Enumeration CATSysErrorLogSeverity
    * Interface CATIASettingController
    * Interface CATISysSettingController
  * TopologicalOperators framework
    * Class CATTopBodyExtremum
    * Enumeration CATMinMax
    * Global Function CATCreateDirBodyExtremum
  * VPMDesktopObjects framework
    * Class ENOVCustoCommandUtils
    * Interface CATIAVPMVDAValidateAttributeChg
  * VPMDesktopServices framework
    * Class VPMIListOfAttributes
  * VPMInterfaces framework
    * Interface CATICfgUEValidateEff
    * Interface ENOVIAttachGCoEvent
    * Interface ENOVIEventPlugin
    * Interface ENOVIMoveEvent
    * Interface ENOVINewVersionDiffFFFEvent
    * Interface ENOVIPasteEvent
    * Interface ENOVISaveEvent
    * Interface ENOVIUESaveFile
  * Visualization framework
    * Class CATVisViewerFeedbackEvent
  * VisualizationBase framework
    * Enumeration CATVizCGRAccessMode

[Top]

* * *

History Version: **1** [Nov 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
