---
title: "New C++ Authorized APIs in CAA V5R16 GA"
category: "general"
module: "CAACenQuickRefs"
tags: ["CATITPSIDServices", "CATITrack", "CATIStmFlangeSurf", "CATIXMLInputStream", "CATITPSConstructedGeomServices", "CATIMfgVirtualActivity", "CATIShot", "CATIStrMaterialESSObjectSettingAtt", "CATIAVPMVDAReplace", "CATInstantCollabDesignCAAItf", "CATIAerospaceSheetMetalFactory", "CATIStmWeb", "CATIIniSearchSymbolCriterion", "CATIMfgActivityDefaultValuesMngt", "CATIStmJoggle", "CATIEwrFilter", "CATISamEditionControl", "CATIColMergeContextRole", "CATIVariableManagement", "CATIDftStandardMediator"]
source_file: "Doc\online\CAACenQuickRefs\CAACenV5R16GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.268959"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R16 GA  
---|---  
  
* * *

The following are the new CAA V5R16 GA C++ Authorized APIs, compared with CAA V5R15 at GA level.

  * ApplicationFrame framework
    * Global Function CATAfrCreateCommandHeader
    * Global Function CATCreateDefaultCamera
  * CATAnalysisInterfaces framework
    * Class CATSamAnalysisUpdateTools
    * Interface CATISamEditionControl
  * CATAnalysisResources framework
    * Class CATEAnalysisEditionControl
  * CATBehaviorInterfaces framework
    * Interface CATIBehOperationManagement
  * CATIAApplicationFrame framework
    * Interface CATICafSearchSettingAtt
  * CATInstantCollabDesignCAAItf framework
    * Class CATColIMergeableAdapter
    * Class CATColISharableAdapter
    * Class CATCollabLocalInfo
    * Class CATCollabWsInfo
    * Macro or #define CATLISTP_APPLY_RELEASE
    * Macro or #define SizeCollabUUID
    * Enumeration CATIColMergeContextFlag
    * Enumeration CATIColMergeContextRole
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
    * Interface CATIColInvariantId
    * Interface CATICollabServices
    * Interface CATIColMergeable
    * Interface CATIColMergeBriefcase
    * Interface CATIColMergeContextTable
    * Interface CATIColMergeItem
    * Interface CATIColSharable
    * Typedef CATListOfShareAccess
  * CATOBMInterfaces framework
    * Enumeration TCIO
    * Interface CATIVariableManagement
  * CATSmaInterfaces framework
    * Interface CATIAerospaceSheetMetalFactory
    * Interface CATIStmCharacteristicCurves
    * Interface CATIStmFlangeSurf
    * Interface CATIStmJoggle
    * Interface CATIStmWeb
  * CATTPSInterfaces framework
    * Enumeration CATTPSCGType
    * Interface CATITPSConstructedGeomServices
    * Interface CATITPSIDServices
  * CATxPDMInterfaces framework
    * Interface CATIxPDMSendToService
  * DNBInspectInterfaces framework
    * Interface DNBIInsClientServices
    * Interface DNBIInsContinuousHitPoint
    * Interface DNBIInsDPMWksAddin
    * Interface DNBIInsJoPlug
    * Interface DNBIInsPathPattern
    * Interface DNBIInspectOperation
    * Interface DNBIInsSBoxPlane
    * Interface DNBIInsUIModify
    * Interface DNBIInsWksAddin
  * DNBReportingInterfaces framework
    * Interface DNBIIgpFASReportingSettingAtt
  * DNBSimulationInterfaces framework
    * Enumeration DNBActBehaviorType
    * Enumeration DNBHlnkBehaviorType
  * Drafting2DLInterfaces framework
    * Enumeration CatClippingFrameReframeOnMode
    * Enumeration CatDedicatedFilterType
    * Enumeration CatViewBackgroundMode
    * Enumeration CatViewFilterCreationMode
    * Interface CATID2o2DLSettingAtt
  * DraftingInterfaces framework
    * Interface CATIDftStandardMediator
  * ENOVInterfaces framework
    * Global Function GetCatalogManager
    * Interface CATIEnovCatalogManager
    * Interface ENOVIABOAssemblyRelation
    * Interface ENOVICfgEvents
    * Interface ENOVICfgUESolver
    * Interface ENOVIInitSpecsUE
    * Interface ENOVIRulesValidator
  * ElecRoutingItf framework
    * Class CATEwrWireGroup
    * Interface CATIEwrFilter
    * Interface CATIEwrUipWireGroups
    * Typedef CATEwrFilterOption
  * FittingInterfaces framework
    * Macro or #define CATSiFiShuttleAngle
    * Enumeration CatFitSampledRecordMode
    * Enumeration CatFitSampledRep
    * Enumeration CATFitTrackMoveMode
    * Interface CATISampled
    * Interface CATIShot
    * Interface CATISiShuttle
    * Interface CATISiShuttleFactory
    * Interface CATITrack
  * GeometricObjects framework
    * Class CATSurfaceTools
    * Interface CATHelix
  * InteractiveInterfaces framework
    * Interface CATIIniSearchSymbolCriterion
  * KnowledgeInterfaces framework
    * Interface CATICkeExpressionFactory
    * Typedef CATCkeListOfArg
    * Typedef CATCkeListOfInst
    * Typedef CATCkeListOfMagnitude
    * Typedef CATCkeListOfObject
    * Typedef CATCkeListOfParm
    * Typedef CATCkeListOfRelation
    * Typedef CATCkeListOfSignature
    * Typedef CATCkeListOfType
    * Typedef CATCkeListOfUnit
  * ManufacturingInterfaces framework
    * Interface CATIMfgActivityDefaultValuesMngt
    * Interface CATIMfgActivityTracutManagement
    * Interface CATIMfgToolCutterCompensationManagement
    * Interface CATIMfgVirtualActivity
  * Mathematics framework
    * Class CATGeometricModelTransaction
    * Class CATLISTV(CATMathLine)
    * Macro or #define CAT_ABSOLUTE_EPSILON
    * Macro or #define CATGeometricModelTransactionBegin
    * Macro or #define CATGeometricModelTransactionCatch
    * Macro or #define CATGeometricModelTransactionEnd
    * Macro or #define CATGeometricModelTransactionEndTry
    * Macro or #define CatQuickFindObjectFromTag
    * Typedef CATCGMKindOfTransaction
  * MecModInterfaces framework
    * Interface CATIMmiBRepAttributeSynchronize
    * Interface CATIMmiPartInfrastructurePreferencesAtt
    * Interface CATIMmiPartInfrastructureSettingAtt
  * MechanicalModeler framework
    * Class CATMmrApplicativeAttributes
  * NewTopologicalObjects framework
    * Class CATPositionPtVolOperator
    * Global Function CATCreatePositionPtVolOperator
  * ObjectModelerBase framework
    * Interface CATIOmbUndoRedoEvents
    * Typedef Properties
    * Typedef PropertyNames
  * PSNInteroperability framework
    * Class CATVPMServices
  * SimulationInterfaces framework
    * Macro or #define LIST_ALL_BOTTOM
    * Macro or #define LIST_ALL_BOTTOM_C
    * Macro or #define LIST_ALL_TOP
    * Macro or #define LIST_ALL_TOP_C
    * Macro or #define LIST_EMPTY
    * Macro or #define LIST_FORCED
    * Macro or #define LIST_FROM_CSO
    * Macro or #define LIST_GLOBALNOTIF
    * Macro or #define LIST_LOCALNOTIF
    * Macro or #define LIST_NONE
    * Macro or #define LIST_UNDEFINED
    * Interface CATISiList
  * StructureInterfaces framework
    * Interface CATIStrColorESSObjectSettingAtt
    * Interface CATIStrColorSTDObjectSettingAtt
    * Interface CATIStrMaterialESSObjectSettingAtt
    * Interface CATIStrPathESSRessourcesSettingAtt
    * Interface CATIStrTypeESSObjectSettingAtt
  * System framework
    * Global Function CATFChmod
    * Global Function CATFClose
    * Global Function CATFCopy
    * Global Function CATFEof
    * Global Function CATFFlush
    * Global Function CATFGetc
    * Global Function CATFGets
    * Global Function CATFOpen
    * Global Function CATFPutc
    * Global Function CATFPuts
    * Global Function CATFRead
    * Global Function CATFSeek
    * Global Function CATFSeek64
    * Global Function CATFSetTimes
    * Global Function CATFSize
    * Global Function CATFSize64
    * Global Function CATFTell
    * Global Function CATFTell64
    * Global Function CATFWrite
    * Typedef CATListOfCATString
    * Typedef CATListOfCATUnicodeString
    * Typedef CATListOfDouble
    * Typedef CATListOfFloat
    * Typedef CATListOfInt
    * Typedef CATListPV
    * Typedef CATSetOfCATString
    * Typedef CATSetOfCATUnicodeString
  * TopologicalOperators framework
    * Global Function CATCreateNewTopAssemble
  * VPMDesktopObjects framework
    * Interface CATIAVPMVDAReplace
  * VPMInterfaces framework
    * Class CATListOfENOVISubScribeGroupMod_var
    * Interface ENOVISubScribeGroupMod
  * VisualizationBase framework
    * Enumeration CATCameraType
  * XMLParser framework
    * Global Function DetectCATIXMLDOMDocumentBuilder
    * Global Function DetectCATIXMLSAXFactory
    * Interface CATIXMLInputStream

[Top]

* * *

History Version: **1** [Jun 2005] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
