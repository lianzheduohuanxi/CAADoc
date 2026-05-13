---
```vbscript
title: "New C++ Authorized APIs in CAA V5R8 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATISchAppCntrColor", "CATIMf3DBehavior", "CATISchAppAddCommand", "CATIAVPMVDAExists", "CATIMfgTPSaveData", "CATIMfgActivityMacroMotion", "CATIEhiNetworkExtremity", "CATIGSMAxisToAxis", "CATIMfgActivityMachinableDesignFeature", "CATIMfgMappingForProfileContouring", "CATIUdfFeatureSet", "CATIMfgToolPathCycle", "CATITPSFactoryAdvanced", "CATIDftGenView", "CATISchAppDeleteCheck", "CATIPrintables", "CATIMfgAuxiliaryOperation", "CATICkeParameterSet", "CATIRuleSet", "CATIMfgActivityElementaryMotion"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R8GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.614918"
```

---
tags: ["CATISchAppCntrColor", "CATIMf3DBehavior", "CATISchAppAddCommand", "CATIAVPMVDAExists", "CATIMfgTPSaveData", "CATIMfgActivityMacroMotion", "CATIEhiNetworkExtremity", "CATIGSMAxisToAxis", "CATIMfgActivityMachinableDesignFeature", "CATIMfgMappingForProfileContouring", "CATIUdfFeatureSet", "CATIMfgToolPathCycle", "CATITPSFactoryAdvanced", "CATIDftGenView", "CATISchAppDeleteCheck", "CATIPrintables", "CATIMfgAuxiliaryOperation", "CATICkeParameterSet", "CATIRuleSet", "CATIMfgActivityElementaryMotion"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R8GANewCPPAPI.htmmd"
converted: "2026-05-11T17:33:47.614918"
CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R8 GA

* * *

The following are the new CAA V5R8 GA C++ Authorized APIs, compared with CAA V5R7 at GA level.

  * AdvancedTopologicalOpe framework
    * CATCreateTopCleanCrvOperator
    * CATTopCleanCrvOperator
    * CatTopCleanCrvCellStatus
    * CatTopCleanCrvPriorityMode
    * NULL
  * AnalysisMeshingModel framework
    * CATMSHMeshDomain
  * CATAnalysisBase framework
    * CATSamApplyQualifier (now in CATAnalysisInterfaces)
  * CATAnalysisInterfaces framework
    * CATISamAnalysisEntityInit
    * CATISamSetChildFilter
    * CATSamQuerySelectFocusNotification
    * CATSamTypeQuery
    * SAM_CollectParameter
  * CATIAApplicationFrame framework
    * CATExtIContextualMenu
    * CATIContextualMenu
  * CATSchPlatformInterfaces framework
    * CATEASchAppAddCATStateCommand
    * CATEASchAppAddCommand
    * CATEASchAppCntrColor
    * CATEASchAppObjectFactory2
    * CATEASchAppRouteCATDlgFrame
    * CATEASchAppRouteDialog
    * CATEASchAppScalingRule
    * CATISchAppAddCATStateCommand
    * CATISchAppAddCommand
    * CATISchAppCntrColor
    * CATISchAppDeleteCheck
    * CATISchAppObjectFactory2
    * CATISchAppRouteCATDlgFrame
    * CATISchAppRouteDialog
    * CATISchAppScalingRule
    * CATISchComponent2
    * CATISchEventManager
    * CATSchEvent
    * CATSchNotification
    * CATSchRouteDataChangeNotification
    * CATSchRouteNotification
    * CATSchRouteTerminateNotification
  * CATTPSInterfaces framework
    * CATITPSFactoryAdvanced
    * CATITPSProjectedToleranceZone
    * CATITPSRetrieveServices
    * CATITPSShiftedProfileTolerance
    * CATTPSSetScanMode
  * DNBInspectInterfaces framework
    * DNBIInsActivateDCCMode
    * DNBIInsActivitiesFactory
    * DNBIInsAlignment
    * DNBIInsAlignment321
    * DNBIInsAlignmentMgtFactory
    * DNBIInsCircle
    * DNBIInsCircleFtrPath
    * DNBIInsConFtrFactory
    * DNBIInsConstAlignment
    * DNBIInsCylinder
    * DNBIInsCylinderFtrPath
    * DNBIInsEvaluateAngle
    * DNBIInsEvaluateDistance
    * DNBIInsFeature
    * DNBIInsFtrFactory
    * DNBIInsFtrPathRules
    * DNBIInsFtrPosition
    * DNBIInsHitPoint
    * DNBIInsInspectServices
    * DNBIInsLine
    * DNBIInsLineFtrPath
    * DNBIInsMPath
    * DNBIInsMPathFactory
    * DNBIInsPCS
    * DNBIInsPlane
    * DNBIInsPlaneFtrPath
    * DNBIInsPoint
    * DNBIInsPointFtrPath
  * DraftingInterfaces framework
    * CATDftTextBoxDisplay
    * CATDimPositioningDomain
    * CATDrwDimAnalysisType
    * CATDrwDimAngleSector
    * CATDrwDimChfRepType
    * CATDrwDimChfValFormat
    * CATDrwDimDimValueOrientationMode
    * CATDrwDimMode
    * CATDrwDimRepresentation
    * CATDrwDimType
    * CATDrwDimViewMode
    * CATDrwUnitDisplayMode
    * CATIDftGenGeom
    * CATIDftGenGeomAccess
    * CATIDftGenView
    * CATIDrwPicture
    * DftGenShowMode
    * ThreadType
  * ENOVDDManager framework
    * ENOVIDocumentInterface
  * ENOVInterfaces framework
    * ENOVICWEvents
    * ENOVIDocEvents
  * ENOVReportSolutionServer framework
    * ENOVIReportServices
    * ENOVReportConverter
  * ENOVaultClientCPP framework
    * VAULT_E_INVALIDPROPERTY
  * ElecHarnessItf framework
    * CATIEhiBundleSegment
    * CATIEhiGeoBundle
    * CATIEhiNetwork
    * CATIEhiNetworkExtremity
  * ElectricalInterfaces framework
    * CATIEleDocServices
  * GSMInterfaces framework
    * CATGSMReflectLineSolutionType
    * CATIGSMAxisToAxis
    * CATIGSMLineCorner
    * CATIGSMPolyline
  * GeometricObjects framework
    * CATICGMUnknown
  * GeometricOperators framework
    * CreateConfusion
    * GeodesicDistanceToolType_Euclidian
    * GeodesicDistanceToolType_Geodesic
  * KnowHow framework
    * CATExpertReportEnum
    * CATExpertRuleEnum
    * CATExpertSolveModeEnum
    * CATICheck
    * CATICheckReport
    * CATIGenericRuleBaseComponent
    * CATIReportObject
    * CATIReportOptions
    * CATIRule
    * CATIRuleBase
    * CATIRuleBaseComponent
    * CATIRuleBaseFactory
    * CATIRuleSet
    * conflictingImportFunctionPtr
  * KnowledgeInterfaces framework (created in V5R8 in LiteralFeatures. This framework was moved to KnowledgeInterfaces in V5R11)
    * CATICkeParameterSet
    * CATICkeRelationFactory
    * CATICkeSheet
    * CATIList
  * ManufacturingInterfaces framework
    * CATIMfgActivityElementaryMotion
    * CATIMfgActivityMachinableDesignFeature
    * CATIMfgActivityMacroMotion
    * CATIMfgActivityMacroParameters
    * CATIMfgActivityToolAxis
    * CATIMfgAuxiliaryOperation
    * CATIMfgCoordinateSystem
    * CATIMfgMacroEditorActivity
    * CATIMfgMappingRuleName
    * CATIMfgProfileContouringPartDirection
    * CATIMfgResourceQueryCatalog
    * CATIMfgTPMultipleMotion
    * CATIMfgTPSaveData
    * CATIMfgToolPathCycle
  * MecModInterfaces framework
    * CATCstDisplayMode
    * CATMfBRepAccessElementType
    * CATMfBRepBuildError
    * CATMfBRepBuildType
    * CATMfBRepDecodeType
    * CATMfBRepFlags
    * CATMfBRepSelectType
    * CATMfBRepSupport
    * CATMfBRepSupportType
    * CATMfBRepType
    * CATMfBRepUpdateSupport
    * CATMfConnexityType
    * CATMfNodeReportType
    * CATMfSharpnessType
    * CATMfTypeNamingReference
  * MechanicalCommands framework
    * CATIUdfFactory
    * CATIUdfFeature
    * CATIUdfFeatureInstance
    * CATIUdfFeatureSet
    * CATIUdfFeatureUser
    * CATIUdfInstantiate
  * MechanicalModeler framework
    * CATIMf3DBehavior
    * CATIMfInfiniteResult
  * NewTopologicalObjects framework
    * CATBodyFreezeMode
    * CATCGMDuplicateLyingOn
  * ObjectSpecsModeler framework
    * CATGroupServices
    * CATIProviders
    * CATIStructureAnalyse
    * CATIUpdateProvider
    * CATListUserExtensionsFromCatalog
    * CATPublicSpecType
  * PSNInteroperability framework
    * CATCompleteSessionFromVPM
    * CATCreateVPMSession
  * PartInterfaces framework
    * CATIFillet
  * PrintBase framework (created in V5R8 in Print. This framework was split into Print and PrintBase in V5R10)
    * CATIPrintables
    * CATPrintVisuParameters
  * PrismaticMachiningInterfaces framework
    * CATIMfgMappingForFollowCurve
    * CATIMfgMappingForPocketing
    * CATIMfgMappingForProfileContouring
  * ProductStructureInterfaces framework
    * CatProductSource
  * SDMRuntime framework
    * CATListPtrSdaiAppInstance
    * SdaiAbstractBaseType
    * SdaiAbstractType
    * SdaiAggrInstance
    * SdaiAppInstance
    * SdaiAppInstanceH
    * SdaiAttr
    * SdaiAttrH
    * SdaiBaseTypeH
    * SdaiBinary
    * SdaiBoolean
    * SdaiDictionaryInstance
    * SdaiEntity
    * SdaiEntityH
    * SdaiEntityInstance
    * SdaiEntityInstanceH
    * SdaiEnum
    * SdaiExplicitAttr
    * SdaiInstance
    * SdaiIntegerH
    * SdaiIterInstance
    * SdaiLogical
    * SdaiModel
    * SdaiNamedType
    * SdaiPrimitiveH
    * SdaiRealH
    * SdaiRoot
    * SdaiSelectH
    * SdaiSessionInstance
    * SdaiString
    * SdaiStringH
  * SketcherInterfaces framework
    * CAT2DOffsetCornerType
    * CAT2DOffsetPropagType
    * CAT2DOperatorType
  * System framework
    * CATCmpGuid
    * CATDbBinary
    * CATDbBinaryH
    * CATHashKey
    * CATUuid
    * CATVariantClear
  * Tessellation framework
    * CATTessFanIter
  * VPMDesktopObjects framework
    * CATIAVPMVDAExists
    * CATIVPMVDAModify2
  * VPMInterfaces framework
    * CATICfgAttachable
    * CATICfgLnk
    * CATICfgUserExit
    * CATIVpmAFLData
    * CATIVpmAFLLink
    * CATIVpmAFLProduct
    * CATIVpmAFLResp
    * CATIVpmAFLSubscribePV
    * CATIVpmPathExpression
    * CATIVpmPredicate
    * CATIVpmQuery
    * CreatePathExpression
    * CreateQuery
    * DATA_EVENT_INIT
    * DECLARE_BinaryPredicate
    * DECLARE_PathExpressionPredicate
    * DECLARE_SimplePathExprPredicate
    * ENOVIConnectable
    * ENOVIConnexion
    * ENOVIDeleteEvent
    * ENOVIHistoricalConnexion
    * ENOVINewVersionSameFFFEvent
    * ENOVIPlugin
    * ENOVIProperty
    * ENOVIUEModify
    * EVENT_FIRE
    * GetVPMIDicMgr
    * IsNOT
    * ORIENTED_LINK
    * SYMETRIC_LINK
    * VPMCheckingGlobalMethod
    * VPMCheckingObjectSecuredMethod
    * VPMGenericFactorySecuredMethod
    * VPMIDicElement
    * VPMIDicMgr
    * VPMIWflCmdRequest
    * VPMSecuredMethod
    * VPM_ACCESS_DENIED
    * VPM_ACCESS_GRANTED
    * operator
  * VPMPersistency framework
    * ENOVEventController
  * VPMSTEPExchanges framework
    * ENOVIExInputer
    * ENOVIExOutputer
    * StdInputer
    * StdMapper
  * Visualization framework
    * CATModelForRep2D
    * CATModelForRep3D
  * VisualizationBase framework (created in V5R8 in Visualization. This framework was split into Visualization and VisualizationBase in V5R9)
    * CAT2DArcEllipseRep
    * CATLongMotionEvent
    * CATModelForRep
    * CATReadCgr
    * CATWriteCgr

[Top]

* * *

History Version: **1** [Mar 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
