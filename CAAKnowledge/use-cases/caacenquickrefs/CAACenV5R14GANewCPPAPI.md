---
title: "New C++ Authorized APIs in CAA V5R14 GA"
category: "general"
module: "CAACenQuickRefs"
tags: ["CATICfgUserExit2", "CATIV4IV4WritingSettingAtt", "CATIMf3DBehavior", "CATIAVPMVDAUnlock", "CATISPAMeasureSettingAtt", "CATISchematicInit", "CATIPDAdapterInterfaces", "CATIMciMultiCADSettingAtt", "CATIDftFormat", "CATIMfgActivityInformation", "CATILieToleranceSheetSettingAtt", "CATIArrAttachSubscriber", "CATIStrColorSTDObjectSettingAtt", "CATITPSEditorUIFTASettingAtt", "CATIMfGeometryAccess", "CATIArrAttachmentFactory", "CATIStrMaterialSFDObjectSettingAtt", "CATISPASectioningSettingAtt", "CATIMfTriDimResult", "CATIDftSheetFormat"]
source_file: "Doc\online\CAACenQuickRefs\CAACenV5R14GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.180388"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R14 GA  
---|---  
  
* * *

The following are the new CAA V5R14 GA C++ Authorized APIs, compared with CAA V5R13 at GA level.

  * AdvancedTopologicalOpe framework
    * Class  CATTopShellOrientation
    * Class  CATTopSpine
    * Enumeration  CATTopBlendBehaviour_Mode
    * Enumeration  CATTopSpineRelimitation_Type
    * Global Function  CATCreateTopShellOrientation
    * Global Function  CATCreateTopSpine
  * AnalysisMeshingModel framework
    * Class  CATMSHListOfMeshPart
  * ApplicationFrame framework
    * Class  CATAfrCommandHeaderRep
    * Class  CATAfrDialogCommandHeader
    * Interface  CATIAfrCommandHeaderRep
  * AutomationInterfaces framework
    * Interface  CATIScriptMacrosSettingAtt
  * CATAnalysisBase framework
    * Class  CATSamModelDataServices
  * CATAnalysisInterfaces framework
    * Macro or #define  CATSamVisuModeGeometry
    * Macro or #define  CATSamVisuModeMeshing
    * Macro or #define  CATSamVisuModePostProcessing
    * Macro or #define  CATSamVisuModePreProcessing
    * Macro or #define  CATSamVisuModeRealDeformation
    * Interface  CATISamEditionCusto
    * Interface  CATISamEntityVisu
    * Interface  CATISamEnumManager
    * Interface  CATISamGeneralSettingAtt
    * Interface  CATISamImportDefine
    * Typedef  CATSamAnalysisType
    * Typedef  CATSamVisuMode
  * CATAnalysisResources framework
    * Class  CATEAnalysisEditionCusto
    * Class  CATEAnalysisEntityVisu
    * Class  CATEAnalysisVisibility
    * Class  CATESamEnumManager
    * Class  CATESamImportDefineAdaptor
    * Class  CATSamToolsForExplicitation
  * CATArrangementInterfaces framework
    * Class  CATEArrAppProductAdapter
    * Macro or #define  CatRouSectionFirst
    * Macro or #define  CatRouSectionLast
    * Macro or #define  CatRouSetPointFirst
    * Macro or #define  CatRouSetPointLast
    * Enumeration  CATRouNodeGeomStatus
    * Enumeration  CATRouSectionTypes
    * Enumeration  CATRouSetPointNames
    * Interface  CATIArrAttachmentFactory
    * Interface  CATIArrAttachSubscriber
    * Interface  CATIArrIgpAttachment
    * Interface  CATIArrNode
    * Interface  CATIArrSegment
    * Interface  CATIArrSegmentsString
    * Interface  CATIRouRadiusCornerSection
    * Interface  CATIRouRectSection
    * Interface  CATIRouRoundSection
    * Interface  CATIRouSection
  * CATCommonLayoutInterfaces framework
    * Interface  CATICloAppWeldOffset
  * CATFunctSystemItf framework
    * Interface  CATIFsyFunctionalSystemSettingAtt
  * CATHullConceptualInterfaces framework
    * Interface  CATIHullBoundingBox
    * Interface  CATIHullMoldedForm
    * Interface  CATIHullOrientation
    * Interface  CATIHullShipInfo
  * CATHullFunctionalInterfaces framework
    * Interface  CATIStrColorESSObjectSettingAtt
    * Interface  CATIStrColorSFDObjectSettingAtt
    * Interface  CATIStrColorSTDObjectSettingAtt
    * Interface  CATIStrMaterialESSObjectSettingAtt
    * Interface  CATIStrMaterialSFDObjectSettingAtt
    * Interface  CATIStrPathESSRessourcesSettingAtt
    * Interface  CATIStrTypeESSObjectSettingAtt
  * CATIAApplicationFrame framework
    * Interface  CATICafDocumentationSettingAtt
    * Interface  CATICafGeneralSessionSettingAtt
    * Interface  CATICafTreeVizManipSettingAtt
  * CATIAV4Interfaces framework
    * Enumeration  CATV4IV4V5SpecDraftMigrationEnum
    * Enumeration  CATV4IV5V4AssociativityModeEnum
    * Enumeration  CATV4IV5V4ErrorFeatureCreationEnum
    * Enumeration  CATV4IV5V4InternalCurveCreationEnum
    * Interface  CATIV4IInteropSettingAtt
    * Interface  CATIV4IMigrBatchSettingAtt
    * Interface  CATIV4ISpecV4SettingAtt
    * Interface  CATIV4IV4V5SpaceSettingAtt
    * Interface  CATIV4IV4WritingSettingAtt
  * CATIPDAdapterInterfaces framework
    * Interface  DNBIMHIMfgHubSettingAtt
  * CATIdeSettingsInterfaces framework
    * Interface  CATIIdeIgesSettingAtt
  * CATMultiCADInterfaces framework
    * Interface  CATIMciMultiCADSettingAtt
  * CATOBMInterfaces framework
    * Interface  CATIBKTBehaviorSettingAtt
  * CATPDMBaseInterfaces framework
    * Class  CATEnoAttrMappingEnumDef
    * Interface  CATIPDMSaveInfo1
  * CATPLMDictionary framework
    * Macro or #define  _VPMDicPRIMITIVETypeNumber
    * Enumeration  VPMDicCONTENT
    * Enumeration  VPMDicPERSISTENT
    * Enumeration  VPMDicPRIMITIVEType
    * Enumeration  VPMDicTYPE
    * Enumeration  VPMDicVISIBILITY
    * Global Function  GetVPMIDicMgr
    * Interface  VPMIDicElement
    * Interface  VPMIDicMgr
  * CATPlantShipInterfaces framework
    * Interface  CATIPspStretchableData
  * CATRdgInterfaces framework
    * Interface  CATIRdgRenderingSettingAtt
  * CATSchPlatformInterfaces framework
    * Class  CATEASchAppListContMem
    * Class  CATSchEventServices
    * Interface  CATISchAppListContMem
    * Interface  CATISchCSOFilter
    * Interface  CATISchematicInit
    * Interface  CATISchInPlaceSiteVeto
    * Interface  CATISchSelectMoveSelector
  * CATSdeSettingInterfaces framework
    * Interface  CATISdeStepSettingAtt
  * CATSmInterfaces framework
    * Interface  CATIStmCatalogSHMObjectSettingAtt
  * CATTPSInterfaces framework
    * Global Function  CATCreateCATITPSGeometryList
    * Interface  CATITPSBrowserUIDMUTolSettingAtt
    * Interface  CATITPSEditorUIFTAInfraSettingAtt
    * Interface  CATITPSEditorUIFTASettingAtt
    * Interface  CATITPSGeometryList
  * CATTechOptimizerItf framework
    * Interface  CATIFsyFuncSysOptimisationSettingAtt
  * DMAPSInterfaces framework
    * Enumeration  CATPcs3DViewerType
    * Interface  CATISPPLibTabSettingAtt
    * Interface  CATISPPTreeTabSettingAtt
    * Interface  CATISPPVerifTabSettingAtt
  * DNBD5IInterfaces framework
    * Interface  DNBID5IImportD5SettingAtt
  * DNBDeviceInterfaces framework
    * Interface  DNBISimDevAnalysisSettingAtt
  * DNBErgoAnalysisUI framework
    * Interface  SWKIErgoAnalysisWkbAddin
  * DNBHumanModelingUI framework
    * Interface  SWKIAnthroWksAddin
    * Interface  SWKIBodyElementsWksAddin
    * Interface  SWKIManikinWkbAddin
  * DNBIgpOlpUI framework
    * Interface  DNBIIgpOlpSettingAtt
  * DNBInspectInterfaces framework
    * Interface  DNBIInsFeatureBounds
  * DNBRobotInterfaces framework
    * Interface  DNBIRobRRSSettingAtt
    * Interface  DNBISimRobAnalysisSettingAtt
  * DNBSimulationInterfaces framework
    * Enumeration  DNBAnalysisLevel
    * Enumeration  DNBSimNavigationMode
    * Enumeration  DNBVisualizationMode
    * Interface  DNBISimAnalysisSettingAtt
    * Interface  DNBISimSimTraceSettingAtt
    * Interface  DNBISimSimulationSettingAtt
  * Dialog framework
    * Typedef  CATDlgHCursor
  * DialogEngine framework
    * Typedef  ElementProvider
  * DraftingInterfaces framework
    * Enumeration  CatDrwNewSheetFrom
    * Enumeration  CATFormatOrientationsType
    * Enumeration  CATSheetOrientation
    * Enumeration  DrwPictureFormat
    * Interface  CATIDftCustomFormat
    * Interface  CATIDftDrawingFormats
    * Interface  CATIDftFormat
    * Interface  CATIDftSheetFormat
    * Interface  CATIDrwCalloutAccess
    * Interface  CATIDrwDraftingSettingAtt
  * ENOVDesktopDocumentBOCmds framework
    * Interface  ENOVIAVDADocCreate
  * ENOVInterfaces framework
    * Interface  ENOVIBuildDynAppProcess
    * Interface  ENOVIConfigProductSpec
    * Interface  ENOVICWChangeTeam
    * Interface  ENOVIFISecondaryVaultUE
    * Interface  ENOVISynchUE
  * FittingInterfaces framework
    * Enumeration  CATFittingShuttleVector
    * Enumeration  CATManipAutoInsertMode
    * Enumeration  CATManipClashMode
    * Interface  CATISiFiFittingSettingAtt
    * Interface  CATISiFiManipSettingAtt
  * FreeFormOperators framework
    * Global Function  CATCreateInterproxCrv
    * Global Function  CATCreateInterproxSur
    * Global Function  CATCreateLiss
  * GSMInterfaces framework
    * Enumeration  CATGSMCanonicalSurfaceDetection
    * Enumeration  CATGSMCSCorrectionMode
    * Enumeration  CATGSMImplicitLawInterpolationMode
    * Enumeration  CATGSMOffsetType
    * Interface  CATIGSMAxisExplicit
    * Interface  CATIGSMCircleCenterAxis
    * Interface  CATIGSMFactoryInternal
    * Interface  CATIGSMGridFace
    * Interface  CATIGSMGridSubset
    * Interface  CATIGSMIntegratedLaw
    * Interface  CATIGSMTransfo
  * GeometricObjects framework
    * Macro or #define  CATCGMImplVirtualAttributeBRepCompact
  * GeometricOperators framework
    * Class  CATMathNurbsCurveTools
    * Class  CATMathNurbsSurfaceTools
    * Enumeration  MathNurbsDimension
    * Global Function  CATCreateLocalAnalysis
    * Global Function  CATCreateMathNurbsCurveTools
    * Global Function  CATCreateMathNurbsSurfaceTools
  * InteractiveInterfaces framework
    * Interface  CATIIniSearchSVisibilityCriterion
  * KnowledgeInterfaces framework
    * Interface  CATICkeCheck
    * Interface  CATICkeSetOfEquations
    * Interface  CATICkeSetOfEquationsFactory
    * Interface  CATILieKnowledgeSheetSettingAtt
    * Interface  CATILieLanguageSheetSettingAtt
    * Interface  CATILieReportGenerationSheetSettingAtt
    * Interface  CATILieToleranceSheetSettingAtt
    * Interface  CATILieUnitsSheetSettingAtt
  * LatheMachiningInterfaces framework
    * Interface  CATILatheProgramAddin
  * ManufacturingInterfaces framework
    * Interface  CATIMfgActivityInformation
    * Interface  CATIMfgDeclareCommandHeaders
    * Interface  CATIMfgGeometryAnalyser
    * Interface  CATIMfgMachinableAreaUserFeature
    * Interface  CATIMfgMachiningProcessInstantiate
    * Interface  CATIMfgMachiningProcessLog
    * Interface  CATIMfgManufacturingFeatureFactory
    * Interface  CATIMfgStartupFactories
    * Interface  CATIMfgToolAssemblyTabPageDisplay
    * Interface  CATIMfgUserRepresentation
  * Mathematics framework
    * Class  CATLISTP(CATMathVector)
    * Macro or #define  CATCGMStreamDumpCommentBEGIN
    * Macro or #define  CATCGMStreamDumpCommentEND
    * Macro or #define  CATCGMStreamDumpXMLCommentBEGIN
    * Global Function  CATTan
  * MecModInterfaces framework
    * Class  CATLISTP(CATIRSur)
    * Interface  CATIFeaturize
    * Interface  CATIMechanicalFeature
    * Interface  CATIMechanicalImport
    * Interface  CATIMechanicalProperties
    * Interface  CATIMechanicalTool
    * Interface  CATIMf3DBehavior
    * Interface  CATIMfBiDimResult
    * Interface  CATIMfBRep
    * Interface  CATIMfBRepFactory
    * Interface  CATIMfGeometryAccess
    * Interface  CATIMfMonoDimResult
    * Interface  CATIMfTriDimResult
    * Interface  CATIMfZeroDimResult
    * Interface  CATIMmiGeometricalSet
    * Interface  CATIMmiNonOrderedGeometricalSet
    * Interface  CATIMmiOrderedGeometricalSet
    * Interface  CATIShapeFeatureBody
  * MechanicalModeler framework
    * Class  CATMf3DBehavior2Adapter
    * Interface  CATIMf3DBehavior2
  * MkUtilities framework
    * Class  mkHashCodeCollec
  * NavigatorInterfaces framework
    * Interface  CATIDMUN4DNavigatorSettingAtt
  * ODDAirPDM framework
    * Class  ODDAirDocumentServices
  * ObjectModelerBase framework
    * Interface  CATI3DVisuProvider
    * Interface  CATINavigateProvider
    * Interface  CATINavigNodeCtrl
    * Interface  CATIParmProvider
  * ObjectSpecsModeler framework
    * Class  CATLISTP(CATSpecPointing)
    * Class  CATSpecPointing
  * OptimizationInterfaces framework
    * Class  CATOptValuesAndDerivativesAdapter
    * Interface  CATIOptValuesAndDerivativesAccess
  * PSNInteroperability framework
    * Global Function  ExecuteOnServer
  * ProcessPlatformVisu framework
    * Interface  CATIWSPROCAddin
  * ProductStructureInterfaces framework
    * Interface  CATICustoIconProduct
    * Interface  CATIPrdPLMPersistency
  * SPAAcisToCATIAV5 framework
    * Enumeration  InitStatus
  * SPACATIAV5ToAcis framework
    * Enumeration  InitStatus
  * SPAProeToCATIAV5 framework
    * Macro or #define  DECL_PROECATIAV5WR
    * Global Function  RunProEDirectConversion
  * SketcherInterfaces framework
    * Interface  CATI2DFixTogether
  * SpaceAnalysisInterfaces framework
    * Interface  CATISPAMeasureSettingAtt
    * Interface  CATISPASectioningSettingAtt
  * SpecialAPI framework
    * Macro or #define  CATINT32ToPtr
    * Macro or #define  CATLONG32ToPtr
    * Macro or #define  CATPtrToINT32
    * Macro or #define  CATPtrToLONG32
    * Macro or #define  CATPtrToUINT32
    * Macro or #define  CATPtrToULONG32
    * Macro or #define  CATUINT32ToPtr
    * Macro or #define  CATULONG32ToPtr
  * StructureInterfaces framework
    * Interface  CATIStructureFactory
  * System framework
    * Class  CATMsg
    * Enumeration  CATSysStatisticsDateFormat
    * Enumeration  CATSysStatisticsOutputFormat
    * Enumeration  CATSysStatisticsTimeUnit
    * Interface  CATISysAccesslogStatisticsSettingAtt
    * Interface  CATISysCommandStatisticsSettingAtt
    * Interface  CATISysDynLicenseSettingAtt
    * Interface  CATISysErrorlogStatisticsSettingAtt
    * Interface  CATISysGeneralStatisticsSettingAtt
    * Interface  CATISysGlobalStatisticsSettingAtt
    * Interface  CATISysLicenseSettingAtt
    * Interface  CATISysServerStatisticsSettingAtt
    * Interface  CATISysSessionStatisticsSettingAtt
    * Interface  CATISysWorkbenchStatisticsSettingAtt
    * Interface  IUnknown
    * Typedef  Handle
    * Typedef  PFCompare
    * Typedef  PFHash
  * Tessellation framework
    * Class  CATTessVertexIter
  * TopologicalOperators framework
    * Class  CATBodyChecker
    * Class  CATLayDownOperator
    * Enumeration  CATFilletLawId
    * Global Function  CATCreateTopLayDown
  * VPMDesktopObjects framework
    * Interface  CATIAVPMVDAUnlock
  * VPMInterfaces framework
    * Interface  CATICfgUserExit2
  * VPMPersistency framework
    * Interface  ENOVIEventAttributes
  * VisualizationBase framework
    * Macro or #define  CAT_STENCIL_BUFFER_BIT
    * Macro or #define  MAX_VIEWPOINT_BUFFER
    * Interface  CATIVizVisualizationSettingAtt

[Top]

* * *

History Version: **1** [Jul 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2004, Dassault Systmes. All rights reserved._
