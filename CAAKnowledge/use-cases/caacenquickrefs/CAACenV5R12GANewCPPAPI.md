---
title: "New C++ Authorized APIs in CAA V5R12 GA"
category: "general"
module: "CAACenQuickRefs"
tags: ["CATINT32", "CATIAVPMVDAImport", "CATIMeasurablePoint", "CATIElbFactory", "CATIRepeatableCommand", "CATIMfgNavigateMachinableFeatView", "CATIIniSearchDimensionCriterion", "CATIIniSearchIntegerCriterion", "CATIIniSearchRealCriterion", "CATIMfgTPMultipleMotionSynchro", "CATIPspPhysicalProduct", "CATIIniSearchStringCriterion", "CATIPspAttribute", "CATIPspSpatial", "CATITPSViewFactory", "CATIMeasurableCircle", "CATIMf3DAxisSystemManager", "CATISamSupportFilter", "CATIPspCntrFlow", "CATIMfgNavigateActivityView"]
source_file: "Doc\online\CAACenQuickRefs\CAACenV5R12GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.111006"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R12 GA  
---|---  
  
* * *

The following are the new CAA V5R12 GA C++ Authorized APIs, compared with CAA V5R11 at GA level.

  * Administration framework
    * Global Function CATIsInstalled
  * AdvancedTopologicalOpe framework
    * Macro or #define CATFrFTopologicalSweep_ListPOfCATCurve
  * AnalysisMeshingModel framework
    * Interface CATIMSHGroup
    * Interface CATIMSHLocalSpecification
    * Interface CATIMSHVisuManager
  * ApplicationFrame framework
    * Interface CATIAfrGeneralWksAddin
    * Interface CATIRepeatableCommand
  * CATAnalysisBase framework
    * Class CATAnalysisCollectorArchiver
    * Class CATAnalysisExplicitTopologyNotification
  * CATAnalysisInterfaces framework
    * Enumeration CATSamComponent
    * Enumeration CATSamMeshType
    * Interface CATISamAnalysisConnectionDesign
    * Interface CATISamCatalogProvider
    * Interface CATISamCCPFilter
    * Interface CATISamCCPFilterProvider
    * Interface CATISamCheckDesignTable
    * Interface CATISamGenMeshPartMgt
    * Interface CATISamMeshPartFilter
    * Interface CATISamSupportFilter
    * Interface CATISamViewManager
  * CATAnalysisResources framework
    * Class CATEAnalysisEntityPreproSubscriber
  * CATAssemblyInterfaces framework
    * Global Function CATAsmCstSetFeatGetCont
    * Interface CATIAsmCstSetFeatFactory
    * Interface CATIAsmCstSetFeature
  * CATHVDiagramInterfaces framework
    * Interface CATIHvuWkbCfgAddin
  * CATIAV4Interfaces framework
    * Class CATV4iV4Element
    * Global Function CATV4iGetMaster
    * Global Function CATV4iGirele
    * Global Function CATV4iGiride
    * Global Function CATV4iGirlay
    * Global Function CATV4iGirtex
    * Global Function CATV4iGirtps
    * Global Function CATV4iGirtxt
    * Global Function CATV4iGirvis
    * Global Function CATV4iGirwdi
    * Global Function CATV4iGisels
    * Global Function CATV4iGisset
    * Global Function CATV4iGiswsp
    * Global Function CATV4iGmappl
    * Global Function CATV4iGmarel
    * Global Function CATV4iGmares
    * Global Function CATV4iGmarln
    * Global Function CATV4iGmasel
    * Global Function CATV4iGmasln
    * Global Function CATV4iGmasst
    * Global Function CATV4iGmdrdl
    * Global Function CATV4iGmdrds
    * Global Function CATV4iGmdrdv
    * Global Function CATV4iGmdrnd
    * Global Function CATV4iGmlanl
    * Global Function CATV4iGmlesc
  * CATPDMBase framework
    * Class CATPDMServices
  * CATPDMBaseInterfaces framework
    * Enumeration CATPDMLogStatus
    * Enumeration CATPDMModType
    * Interface CATIPDMId0
    * Interface CATIPDMLog0
    * Interface CATIPDMLogObject0
    * Interface CATIPDMSaveAction
    * Interface CATIPDMSaveInfo
    * Interface CATIPDMUECreate
    * Interface CATIPDMUESaveProcess
  * CATPIDiagramInterfaces framework
    * Interface CATIPiuWkbCfgAddin
  * CATPlantShipInterfaces framework
    * Enumeration CATPspCntrFlowCapability
    * Enumeration CATPspCntrFlowReality
    * Enumeration CATPspFunctionStatus
    * Enumeration CATPspPartConnectorTypeEnum
    * Interface CATIPspApplication
    * Interface CATIPspAttribute
    * Interface CATIPspClass
    * Interface CATIPspCntrFlow
    * Interface CATIPspConnectable
    * Interface CATIPspConnection
    * Interface CATIPspConnector
    * Interface CATIPspDomainEnvironment
    * Interface CATIPspFunctional
    * Interface CATIPspGroup
    * Interface CATIPspGroupable
    * Interface CATIPspID
    * Interface CATIPspLogicalLine
    * Interface CATIPspObject
    * Interface CATIPspPartConnector
    * Interface CATIPspPhysical
    * Interface CATIPspPhysicalProduct
    * Interface CATIPspResource
    * Interface CATIPspShareData
    * Interface CATIPspSpatial
  * CATPlantShipModeler framework
    * Class CATPspListServices
    * Class CATPspObjAttrNameServices
    * Class CATPspObjectNameServices
    * Class CATPspServices
  * CATSchPlatformInterfaces framework
    * Class CATEASchAppDeleteCheck2
    * Class CATEASchAppModelInit
    * Enumeration CATSchRouteUnsetGapsMode
    * Interface CATISchAppDeleteCheck2
    * Interface CATISchAppModelInit
    * Interface CATISchPostPaste02
  * CATTBDiagramInterfaces framework
    * Interface CATITbuWkbCfgAddin
  * CATTPSInterfaces framework
    * Enumeration CATTPSTypeWithDRF
    * Enumeration CATTPSTypeWithoutDRF
    * Enumeration CATTPSViewAssociativity
    * Interface CATITPSFactoryElementary
    * Interface CATITPSServicesContainers
    * Interface CATITPSViewFactory
  * CATWGDiagramInterfaces framework
    * Interface CATIWguWkbCfgAddin
  * CDMAInteroperability framework
    * Interface CATIPDMUESave
  * DMAPSInterfaces framework
    * Enumeration CATSPPExpandCollapseActivation
  * DNBInspectInterfaces framework
    * Enumeration DNBInsConFtrMtd
  * DraftingInterfaces framework
    * Enumeration CATDimPositioningMode
    * Enumeration CATDrwScaleMode
    * Interface CATIDftRough
    * Interface CATIDrwGenDrawShape
  * ENOVInterfaces framework
    * Interface CATIVpmPostIntrospection
    * Interface ENOVIExternalBatchProcess
  * ElecDeviceItf framework
    * Interface CATIElbBackShellCnctPt
    * Interface CATIElbConnectorCnctPt
    * Interface CATIElbFactory
    * Interface CATIElbSingleConnectorReference
  * ElecFlatteningItf framework
    * Interface CATIEhfPrdWkbCfgAddin
  * ElecHarnessItf framework
    * Interface CATIEhiProtection
  * GSMInterfaces framework
    * Enumeration CATGSMAxisLineType
    * Enumeration CATGSMExplicitSweepCase
    * Enumeration CATGSMTransfoMode
    * Interface CATIGSM3DCurveOffset
    * Interface CATIGSMAxisLine
    * Interface CATIGSMCylinder
    * Interface CATIGSMProceduralView
  * GSOInterfaces framework
    * Interface CATIGSMUnfold
  * GeometricObjects framework
    * Macro or #define CATCGMImplAttributeBRep
  * GeometricOperators framework
    * Global Function CATCreateConfusion
  * InteractiveInterfaces framework
    * Class CATIniSearchEnumeration
    * Interface CATIIniSearchAndCriterion
    * Interface CATIIniSearchBooleanCriterion
    * Interface CATIIniSearchColorCriterion
    * Interface CATIIniSearchCombinationCriterion
    * Interface CATIIniSearchContext
    * Interface CATIIniSearchCriterion
    * Interface CATIIniSearchDashedCriterion
    * Interface CATIIniSearchDimensionCriterion
    * Interface CATIIniSearchEngine
    * Interface CATIIniSearchExceptCriterion
    * Interface CATIIniSearchGraphNameCriterion
    * Interface CATIIniSearchIntegerCriterion
    * Interface CATIIniSearchLayerCriterion
    * Interface CATIIniSearchListingCriterion
    * Interface CATIIniSearchNameCriterion
    * Interface CATIIniSearchOrCriterion
    * Interface CATIIniSearchRealCriterion
    * Interface CATIIniSearchServices
    * Interface CATIIniSearchStringCriterion
    * Interface CATIIniSearchTypeCriterion
    * Interface CATIIniSearchUserCriterion
    * Interface CATIIniSearchV4ModelCriterion
    * Interface CATIIniSearchVisibilityCriterion
    * Interface CATIIniSearchWeightCriterion
  * KnowledgeInterfaces framework
    * Interface CATIObjectRightsManager
    * Typedef CATKweRight
  * ManufacturingInterfaces framework
    * Interface CATIMfgActivityToolPathPackManagement
    * Interface CATIMfgApply
    * Interface CATIMfgAxialOperationCheckFaces
    * Interface CATIMfgAxialRadialMove
    * Interface CATIMfgMachinableAreaSites
    * Interface CATIMfgMachinableGeomItems
    * Interface CATIMfgNavigateActivityView
    * Interface CATIMfgNavigateFeatureView
    * Interface CATIMfgNavigateMachinableFeatView
    * Interface CATIMfgNavigatePatternView
    * Interface CATIMfgNavigateToolView
    * Interface CATIMfgToolPathMotionCommand
    * Interface CATIMfgTPCycleLinkingMotion
    * Interface CATIMfgTPMultipleMotionNurbs
    * Interface CATIMfgTPMultipleMotionSynchro
    * Interface CATIMfgTPNurbsDescription
    * Interface CATIMfgTPRemoveCutterProfileData
    * Interface CATIMfgTPReplaySelectedPosition
    * Interface CATIMfgTPSynchro
  * MeasureGeometryInterfaces framework
    * Enumeration CATExtend
    * Enumeration CATIMeasurableType
    * Enumeration CATMeasResultData
    * Enumeration CATMeasurableName
    * Enumeration CATSiCalculationType
    * Enumeration CATSiMeasureEdgeType
    * Enumeration CATSiMeasureSurfaceType
    * Interface CATIMeasurable
    * Interface CATIMeasurableAxisSystem
    * Interface CATIMeasurableCircle
    * Interface CATIMeasurableCone
    * Interface CATIMeasurableCurve
    * Interface CATIMeasurableCylinder
    * Interface CATIMeasurableLine
    * Interface CATIMeasurablePlane
    * Interface CATIMeasurablePoint
    * Interface CATIMeasurableSphere
    * Interface CATIMeasurableSurface
    * Interface CATIMeasurableVolume
  * MecModInterfaces framework
    * Class CATLISTV(CATIMf3DAxisSystem_var)
    * Enumeration CATAxisSystemDirectionType
    * Enumeration CATAxisSystemIsDirect
    * Enumeration CATAxisSystemPointType
    * Enumeration CATAxisSystemType
    * Enumeration CATAxisSystemXYZNumber
    * Interface CATIMf3DAxisSystem
    * Interface CATIMf3DAxisSystemFactory
    * Interface CATIMf3DAxisSystemManager
    * Interface CATIPrtManagement
  * NewTopologicalObjects framework
    * Class CATRecomposeShells
    * Class CATTopSewSkin
    * Global Function CATCreateRecomposeShells
    * Global Function CATCreateSewSkin
  * OptimizationInterfaces framework
    * Class CATOptAlgorithmUIFactoryAdapter
    * Macro or #define CATOptApproxAlgorithmAttributeAccessName
    * Macro or #define CATOptApproxAlgorithmCATIType
    * Macro or #define CATOptLocalWPrioritiesAlgorithmAttributeAccessName
    * Macro or #define CATOptLocalWPrioritiesAlgorithmCATIType
  * Print framework
    * Class CATPrintTextImage
  * ProductStructure framework
    * Interface CATIBlockMovable
  * SketcherInterfaces framework
    * Class CATSketcherCommands
    * Enumeration CAT2DCstPointDefinitionMode
    * Enumeration CAT2DOffsetModeType
    * Interface CATI2DArc
    * Interface CATI2DConicCurve
  * System framework
    * Class CATSysPreferenceRepository
    * Global Function FreeVariantSafeArray
    * Interface IClassFactory
    * Typedef BOOL
    * Typedef CATBaseUnknown_ptr
    * Typedef CATINT32
    * Typedef CATSafeArray
    * Typedef CATUINT32
  * TopologicalOperators framework
    * Class CATTopSweepSkinSkinSegment
    * Macro or #define CATTopSweepWireSkinSegment
    * Global Function CATCreateTopSweepSkinSkinSegment
    * Global Function CATCreateTopSweepWireSkinSegment
  * V5ToV4Geo framework
    * Interface CATIV4DataSaver
  * VPMDesktopObjects framework
    * Class ENOVApplicationQuery
    * Interface CATIAVPMVDAComputeInstanceID
    * Interface CATIAVPMVDAImport
    * Interface ENOVCustomCommand
  * VPMInterfaces framework
    * Interface ENOVINewItemInstanceEvent
    * Interface VPMIWflActivity
    * Interface VPMIWflApplication
    * Interface VPMIWflData
    * Interface VPMIWflParticipant
    * Interface VPMIWflProcess
    * Interface VPMIWflRegularActivity
    * Interface VPMIWflTransition
  * Visualization framework
    * Class CATExtIBasicVisProperties
  * VisualizationBase framework
    * Class CATLISTP(CATPathElement)
    * Class CATModelForRep
    * Class CATPathElement
    * Enumeration CATVisInteractiveContext

[Top]

* * *

History Version: **1** [Jul 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
