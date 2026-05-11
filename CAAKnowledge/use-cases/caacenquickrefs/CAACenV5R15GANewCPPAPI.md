---
title: "New C++ Authorized APIs in CAA V5R15 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATISchAppToolsOptionsData", "CATIMfgPrismaticReworkArea", "CATIBlock", "CATIMfResultManagement", "CATIDegreesOfFreedom", "CATIEwrRouteSegment", "CATISPMProcessAccess", "CATISchAppCmdInfo", "CATICATALOGWorkshopAddin", "CATIMfgMachinableGeomMngt", "CATIMfgToolAxis", "CATIMfgTPEExtraVisu", "CATIMfgMultiAxisFlankContouring", "CATIMfgUserReverseMachiningConditions", "CATIPspLightPart", "CATIPrtProceduralView", "CATIMmiTemporaryVisProperties", "CATIMfExtremity", "CATIDimCst2", "CATICfgSpecExpression"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R15GANewCPPAPI.md"
converted: "2026-05-11T17:33:47.243440"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R15 GA  
---|---  
  
* * *

The following are the new CAA V5R15 GA C++ Authorized APIs, compared with CAA V5R14 at GA level.

  * AdvancedMachiningInterfaces framework
    * Interface  CATIMfgMultiAxisFlankContouring
  * AdvancedTopologicalOpe framework
    * Class  CATSketchGeodesic
    * Class  CATSketchOperators
    * Class  CATTopGeodesicPtPt
    * Class  CATTopMostContinuousGeoInWireOperator
    * Class  CATTopSimilarCurve
    * Enumeration  CATTopBlendCouplingMode
    * Global Function  CATCreateGeodesicPointDir
    * Global Function  CATCreateTopMostContinuousGeoInWireOperator
    * Global Function  CATCreateTopSimilarCurve
  * AnalysisMeshingModel framework
    * Class  CATMSHSelectionTrap
    * Enumeration  CATMSHExternalReferenceStatus
    * Enumeration  CATMSHTrapMode
    * Interface  CATIMSHTrapSelector
  * ApplicationFrame framework
    * Global Function  CATAfrEmptyUndoRedoStacks
    * Global Function  CATAfrGetWorkbenchIdentifierFromNLSName
    * Global Function  CATAfrLockUndoRedoTransactions
    * Global Function  CATAfrStartWorkbench
    * Global Function  CATAfrUnlockUndoRedoTransactions
    * Global Function  CATApplyCameraToViewer
    * Global Function  CATApplyCameraToViewpoint
    * Global Function  CATCreateCameraFromViewer
    * Global Function  CATCreateCameraFromViewpoint
    * Interface  CATIAfrUIActivation
  * BasicTopologicalOpe framework
    * Class  CATTopGeodesicLineOperator
    * Global Function  CATCreateGeodesicLinePtPt
    * Global Function  CATCreateTopGeodesicLineOperatorFromDirection
    * Global Function  CATCreateTopStableSpline
    * Global Function  CATCreateTopStableSplineOperator
  * CATAnalysisBase framework
    * Class  CATAnalysisAssemblyManager
    * Class  CATAnalysisExplicitVirtualElement
    * Class  CATAnalysisExplicitVirtualNode
  * CATAnalysisGPSInterfaces framework
    * Interface  CATIGPSConnectionDesign
    * Interface  CATIGPSSensorFactory
  * CATAnalysisInterfaces framework
    * Class  CATSamAnalysisEntityAdaptIDL
    * Class  CATSamAnalysisEntityImpl
    * Class  CATSamAnalysisModelNotification
    * Class  CATSamAnalysisSetImpl
    * Class  CATSamDocNotification
    * Class  CATSamDocumentTools
    * Macro or #define  CATSamCatalog_AnalysisEntity
    * Macro or #define  CATSamCatalog_AnalysisSet
    * Macro or #define  CATSamCatalog_BasicComponent
    * Macro or #define  CATSamCatalog_MSHPart
    * Macro or #define  CATSamCatalog_SetBasicComponent
    * Macro or #define  CATSamCatalog_SetDataType
    * Macro or #define  CATSamCatalog_SetLabels
    * Macro or #define  CATSamCatalog_SetPhysicalType
    * Macro or #define  CATSamCatalog_SetValuesDim
    * Macro or #define  CATSamVisuModeGroups
    * Macro or #define  CATSamVisuModeMeshingRes
    * Enumeration  CATSamCheckType
    * Enumeration  CATSamDocActionType
    * Enumeration  CATSamGroupType
    * Enumeration  CATSamModelNotifAction
    * Enumeration  CATSamModelNotifType
    * Enumeration  CATSamSpace1DType
    * Enumeration  CATSamSpace2DType
    * Enumeration  CATSamSpace3DType
    * Enumeration  CATSamSpaceVectorType
    * Enumeration  CATSamValuesDistributionMode
    * Interface  CATICharacCollector
    * Interface  CATISamAnalysisContextCheck
    * Interface  CATISamDisplayModel
    * Interface  CATISamGroup
    * Interface  CATISamUpgrade
  * CATAnalysisResources framework
    * Class  CATEAnalysisAxis
    * Class  CATEAnalysisContextCheck
    * Class  CATEAnalysisUpgrade
    * Enumeration  CollectorArchiveFlag
  * CATAnalysisVisuInterfaces framework
    * Class  CATESamImageDeformation
    * Class  CATESamImageOwner
    * Interface  CATISamImageDeformation
    * Interface  CATISamImageGroup
    * Interface  CATISamImageOutput
    * Interface  CATISamImageOwner
    * Interface  CATISPMProcess
    * Interface  CATISPMProcessAccess
  * CATArrangementInterfaces framework
    * Enumeration  CATArrAlignmentConnectorTypeEnum
    * Enumeration  CATArrFaceConnectorTypeEnum
    * Enumeration  CATArrOrientationConnectorTypeEnum
    * Interface  CATIArrAppProduct
    * Interface  CATIArrConnectorFactory
  * CATAssemblyInterfaces framework
    * Class  CATAsmConstraintServices
    * Class  CATAsmConstraintSetServices
    * Global Function  GetCATAsmConstraintSettingCtrl
    * Global Function  GetCATAsmGeneralSettingCtrl
    * Interface  CATIAsmConstraintSettingAtt
    * Interface  CATIAsmGeneralSettingAtt
    * Interface  CATIProdDraftingProperties
  * CATCommonLayoutInterfaces framework
    * Class  CATECloAppBendableAdapter
    * Class  CATECloPartSelectionAdapter
    * Interface  CATICloAppBendable
    * Interface  CATICloPartSelection
  * CATDataExchControlAlgo framework
    * Class  CATDECProductToPartConvertor
    * Global Function  CATCreateProductToPartConvertor
  * CATHullConceptualInterfaces framework
    * Interface  CATISPLDesignTabSettingAtt
  * CATPlantShipInterfaces framework
    * Class  CATPspKweUserAttrAdapter
    * Interface  CATIPspAppFactory
    * Interface  CATIPspBranchConnection
    * Interface  CATIPspBuildPart
    * Interface  CATIPspKweUserAttr
    * Interface  CATIPspLightBend
    * Interface  CATIPspLightConnector
    * Interface  CATIPspLightPart
  * CATSchPlatformInterfaces framework
    * Class  CATEASchAppCmdInfo
    * Class  CATEASchAppCntrData
    * Class  CATEASchAppToolsOptionsData
    * Class  CATScuAlignCompInfo
    * Class  CATScuFlipCompInfo
    * Class  CATScuFlowAllInfo
    * Class  CATScuGapInfo
    * Class  CATScuRotateCompInfo
    * Class  CATScuRouteFixInfo
    * Class  CATScuRouteLineInfo
    * Class  CATScuSelectiveUpdateInfo
    * Enumeration  CATScuAlignMode
    * Enumeration  CATScuFlipMode
    * Enumeration  CATScuFlowAllMode
    * Enumeration  CATScuGapAllMode
    * Enumeration  CATScuRotateMode
    * Interface  CATISchAppCmdInfo
    * Interface  CATISchAppCntrData
    * Interface  CATISchAppToolsOptionsData
  * CATSchPlatformModeler framework
    * Class  CATSchEventServices
  * CATSmInterfaces framework
    * Interface  CATIStmViewCharacteristicCurvesSettingAtt
  * CATTPSInterfaces framework
    * Interface  CATITPSParallelOnScreen
  * CATTTRSInterfaces framework
    * Class  CATITTRSGeometry
  * CATxPDMInterfaces framework
    * Class  CATLISTP(CATIxPDMItem_var)
    * Class  CATxPDMFileServices
    * Class  CATxPDMSessionServices
  * ComponentsCatalogsInterfaces framework
    * Interface  CATICATALOGWorkshopAddin
  * ConstraintModeler framework
    * Class  CATConstraintServices
    * Enumeration  CATDoFStatusEnum
    * Enumeration  CATDoFTypeEnum
    * Interface  CATIDegreesOfFreedom
  * ConstraintModelerInterfaces framework
    * Interface  CATIBlock
    * Interface  CATIDimCst2
  * Dialog framework
    * Class  CATDlgBlackBox
    * Class  CATDlgMotif
    * Class  CATDlgWindows
  * DraftingInterfaces framework
    * Interface  CATIDftGenViewFactory
  * ENOVDDManager framework
    * Typedef  CATLISTV
  * ENOVDesktopDocument framework
    * Interface  ENOVIChangeStatusTOCUE
  * ENOVInterfaces framework
    * Interface  CATIAVPMUEFilterVersionning
    * Interface  CATIVPMUESynchronize
    * Interface  ENOVIABOPartInstanceExtended
    * Interface  ENOVIABOPartReferenceExtended3
    * Interface  ENOVIAttachProductCategory
    * Interface  ENOVIFilterVersion
    * Interface  ENOVIFLDEvents
    * Interface  ENOVIPropagateEffectivity
    * Interface  ENOVIRBOList
    * Interface  ENOVITransfer
    * Interface  ENOVIVariantConfigurable
    * Interface  ENOVIWhereUsedInfo
  * ENOVReplicationServices framework
    * Class  ENOVRBOListUtils
  * ElecHarnessItf framework
    * Enumeration  CATEhiProfileType
    * Interface  CATIEhiFLEX
  * ElecRoutingItf framework
    * Interface  CATIEwrRouteSegment
  * ElecSchematicItf framework
    * Interface  CATIEluWkbCfgAddin
  * GSMInterfaces framework
    * Enumeration  CATGSMFeatureLimitType
    * Enumeration  CATGSMRotationType
    * Interface  CATIGSMExtractMulti
  * GeometricObjects framework
    * Class  CATLISTP(CATMathFunctionX)
    * Class  CATLISTP(CATSurLimit)
    * Class  CATLISTP(CATSurParams)
    * Macro or #define  CATCGMImplAttribute
    * Interface  CATSweepSurface
  * GeometricOperators framework
    * Class  CATCurveCurvilinearParameterization
    * Global Function  CATCreateCurveCurvilinearParameterization
  * InteractiveInterfaces framework
    * Class  CATLISTP(CATIIniLayer)
    * Class  CATLISTP(CATIIniLayersFilter)
    * Class  CATLISTP(CATISelectionSetElement_var)
    * Class  CATLISTP(CATListOfCATISelectionSet_var)
    * Interface  CATIIniDocumentFiltersDefinition
    * Interface  CATIIniDocumentLayersDefinition
    * Interface  CATIIniLayer
    * Interface  CATIIniLayersFilter
    * Interface  CATISelectionSet
    * Interface  CATISelectionSetElement
    * Interface  CATISelectionSetsFactory
    * Typedef  CATSelectionSetMode
  * KnowledgeInterfaces framework
    * Class  CATAttributeInfos
    * Class  CATCkeLawAdapter
    * Class  CATKweInstanceExtensionAdapter
    * Interface  CATIAllowUserInfo
    * Interface  CATIInstanceExtension
    * Interface  CATIInstanceListener
    * Typedef  CATParameterEditorStyle
  * ManufacturingInterfaces framework
    * Interface  CATIMfgActivityNCCodeFileManagement
    * Interface  CATIMfgActivityReplaceResourceMgt
    * Interface  CATIMfgActivityReplayControlPoints
    * Interface  CATIMfgActivityWorkpiecePosition
    * Interface  CATIMfgCopy
    * Interface  CATIMfgCustomizeSetupProduct
    * Interface  CATIMfgDirection
    * Interface  CATIMfgFormulaManagement
    * Interface  CATIMfgGenerateToolChanges
    * Interface  CATIMfgMachinableAreaMngt
    * Interface  CATIMfgMachinableBaseMngt
    * Interface  CATIMfgMachinableFeatureMngt
    * Interface  CATIMfgMachinableGeomMngt
    * Interface  CATIMfgMachiningAxisSystem
    * Interface  CATIMfgMachiningContainer
    * Interface  CATIMfgMachiningFeatureFactory
    * Interface  CATIMfgMachiningOperationUpdateCustom
    * Interface  CATIMfgPocketingStartingPoint
    * Interface  CATIMfgPrismaticReworkArea
    * Interface  CATIMfgProcess
    * Interface  CATIMfgProfileContouringRelimitingElement
    * Interface  CATIMfgProgramISOFile
    * Interface  CATIMfgResource3DVisu
    * Interface  CATIMfgSetup
    * Interface  CATIMfgTabularViewColumn
    * Interface  CATIMfgToolAssemblyActivityEditorCustom
    * Interface  CATIMfgToolAxis
    * Interface  CATIMfgTPDuplicate
    * Interface  CATIMfgTransitionPathMngt
    * Interface  CATIMfgUpgradeProcessDocument
    * Interface  CATIMfgUserOppositeHandMachiningOptions
    * Interface  CATIMfgUserReverseMachiningConditions
  * Mathematics framework
    * Class  CATLISTP(CATMathDirection)
    * Class  CATLISTP(CATMathPlane)
    * Class  CATLISTP(CATMathpoint)
    * Macro or #define  CATMathematicType
  * MecModInterfaces framework
    * Class  CATMfError
    * Class  CATMfErrUpdate
    * Interface  CATIDatumFactory
    * Interface  CATIIsolate
    * Interface  CATIMechanicalCCP
    * Interface  CATIMechanicalRootFactory
    * Interface  CATIMechanicalVisu
    * Interface  CATIMf3DBehavior2
    * Interface  CATIMfAxis
    * Interface  CATIMfBorderFvertex
    * Interface  CATIMfBorderRedge
    * Interface  CATIMfExtremity
    * Interface  CATIMfFedge
    * Interface  CATIMfFsur
    * Interface  CATIMfFvertex
    * Interface  CATIMfGeom
    * Interface  CATIMfInfiniteResult
    * Interface  CATIMfIntersectApplicativeResolution
    * Interface  CATIMfIntersectionEdge
    * Interface  CATIMfLine
    * Interface  CATIMfPlanarSubElement
    * Interface  CATIMfPlane
    * Interface  CATIMfPoint
    * Interface  CATIMfPointOnEdge
    * Interface  CATIMfProcReport
    * Interface  CATIMfRedge
    * Interface  CATIMfResultManagement
    * Interface  CATIMfRsur
    * Interface  CATIMfWireFvertex
    * Interface  CATIMfWireRedge
    * Interface  CATIMmiTemporaryVisProperties
    * Interface  CATIPersistentSubElement
    * Interface  CATIPrtProceduralView
    * Interface  CATIShapeFeatureProperties
    * Interface  CATIUpdateError
  * MechanicalModeler framework
    * Class  CATMmrAlgoConfigServices
    * Class  CATMmrBRepScanServices
    * Class  CATMmrInterPartCopy
    * Global Function  CATMmrGetCanonicBRepFromGeometricalElement
  * NewTopologicalObjects framework
    * Class  CATLISTP(CATWire)
    * Class  CATTopCAACompliantJournalChecker
    * Class  CATTopPropagationEdge
    * Enumeration  CAATopCheckForPartType
    * Global Function  operator<
    * Global Function  <
  * ObjectModelerBase framework
    * Class  CATLISTP(CATIReporterInfo)
    * Class  CATOmbDocIdFinder
    * Interface  CATIGraphLink
    * Interface  CATIReporter
    * Interface  CATIReporterInfo
  * ObjectSpecsModeler framework
    * Class  CATOsmExtensionServices
    * Class  CATOsmUpdateAdapter
    * Interface  CATIOsmExtendable
    * Interface  CATIOsmExtension
    * Interface  CATIOsmExtensionFactory
    * Interface  CATIOsmUpdate
    * Interface  CATIOsmVolatileContainer
  * OptimizationInterfaces framework
    * Interface  CATIOptCntSatisfaction
  * PLMSecuritySSOBase framework
    * Interface  PLMISecSSOCLogContentProvider
  * PartInterfaces framework
    * Interface  CATIPrtCenterCurve
  * Print framework
    * Class  CATPrintPixelImageDevice
    * Class  CATVectorImage
  * PrintBase framework
    * Class  ostream_withassign
  * PrismaticMachiningInterfaces framework
    * Interface  CATIMfgPrismaticStartupFactory
    * Interface  CATIMfgPrismMachiningDirectionMgt
  * ProductStructure framework
    * Class  CATLISTP(CATIProduct).
  * SketcherInterfaces framework
    * Interface  CATI2DOffset
    * Interface  CATI2DOffsetCurve
    * Interface  CATI2DOffsetOperator
  * SketcherToolsUI framework
    * Class  CATSketcherToolbox
  * SurfaceMachiningInterfaces framework
    * Interface  CATIMfgMultiAxisContourDriven
    * Interface  CATIMfgMultiAxisIsoparametricMachining
    * Interface  CATIMfgMultiAxisSweeping
  * System framework
    * Class  CATSysSettingCtrlNotif
    * Macro or #define  INVALIDMEM
    * Enumeration  CATSysCloseMode
    * Enumeration  CATSysCreateMode
    * Enumeration  CATSysOpenMode
    * Enumeration  CATSysSharing
    * Interface  CATILockBytes
    * Interface  CATISysCacheSettingAtt
    * Interface  CATISysDisconnectionSettingAtt
    * Interface  CATISysDLNameSettingAtt
    * Interface  CATISysMemoryWarningSettingAtt
    * Interface  CATISysPCSStatisticsSettingAtt
    * Interface  CATIUExitCrypt
    * Interface  CATIUExitCryptedILockBytes
    * Typedef  CATMemHandle
  * Tessellation framework
    * Class  CATTessPointPolyIter
  * ToolPathEditorInterfaces framework
    * Interface  CATIMfgTPEExtraVisu
  * VPMDesktopObjects framework
    * Interface  CATIAVPMVDASynch
  * VPMInterfaces framework
    * Class  CATListOfCATIAVPMProductSpecification2_var
    * Class  CATLISTV(CATICfgVariabilitySpace_var)
    * Class  CATLISTV(CATICfgXEff)
    * Interface  CATIAVPMIIProductSpec
    * Interface  CATIAVPMProductSpecification2
    * Interface  CATICfgSpecExpression
    * Interface  CATICfgSpecInclusion
    * Interface  CATICfgVariabilitySpace
    * Interface  CATICfgXEff
    * Interface  CATIVpmLongTransaction
    * Interface  ENOVIFctAuthorizedValues
    * Interface  ENOVIFctDefaultValue
    * Interface  ENOVIGraphManagement
  * VPMPosManager framework
    * Class  ENOVPosListener
    * Interface  ENOVIPosEvent
  * VPMSTEPExchanges framework
    * Macro or #define  ExCREATION_PROCESS
    * Macro or #define  ExGetReadableAttribut
    * Macro or #define  ExGetWritableAttribut
    * Macro or #define  ExRECONCILIATION_PROCESS
    * Interface  ENOVIExDataServices
  * Visualization framework
    * Macro or #define  NB_VISU_LINETHICKNESS
    * Global Function  sCATGetMMThicknessFromViewer
    * Global Function  sCATGetPixelThicknessFromViewer
    * Interface  CATIVisVrmlSettingAtt
  * VisualizationBase framework
    * Class  CATVisMeasurableGP
    * Enumeration  CATGeomType
    * Enumeration  CATVisMeasurableType

[Top]

* * *

History Version: **1** [Jan 2005] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
