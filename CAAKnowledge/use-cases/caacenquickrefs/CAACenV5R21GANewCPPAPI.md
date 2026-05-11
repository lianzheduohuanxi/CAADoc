---
title: "New C++ Authorized APIs in CAA V5R21 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIPspDefinePhysicalPart", "CATICGMRemoveFace", "CATIFmtMeshDomain", "CATIMfgCCPCustom", "CATIMfgMultiAxisCurveMachiningAuxDrive", "CATIMfg5AxisSpiralMilling", "CATICGMRemoveFacesInShell", "CATIPDMUEOnCancel", "CATIFmtCustomVisualization", "CATIMfgCustomizeCSOFilter", "CATIFmtMesher", "CATIFmtSelectedElement", "CATICGMObjectsLoad", "CATIFmtMeshPartOutput", "CATIFmtTrapSelector", "CATICGMRemoveEdge", "CATIUExitPVRCommands", "CATICGMThickSurfacePlus", "CATIPDMCharacteristicScm", "CATIFmtMesh"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R21GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.505618"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R21 GA  
---|---  
  
* * *

The following are the new CAA V5R21 GA C++ Authorized APIs, compared with CAA V5R20 at GA level.

  * ABQConstants framework 
    * Enumeration eDofEnum
  * AdvancedMathematics framework 
    * Macro or #define CATMathFunctionXYTypeId
  * ApplicationFrame framework 
    * Macro or #define CATFrmMkStringFromDefine1
    * Macro or #define CATFrmMkStringFromDefine
    * Global Function CATAfrNewTransaction
  * BSFBuildtimeData framework 
    * Macro or #define WIN32_LEAN_AND_MEAN
  * BasicTopologicalOpe framework 
    * Global Function CATCreateLengthFromBodyOnWire
    * Global Function CATCreateLengthFromBodyOnWire
  * CATCommonLayoutInterfaces framework 
    * Interface CATICloPartRules
  * CATFmtModelInterfaces framework 
    * Class CATFmtConnectivityServices
    * Class CATFmtCriterionServices
    * Class CATFmtElement
    * Class CATFmtExtIConnectivity
    * Class CATFmtExtICriterion
    * Class CATFmtExtIGroupUpdate
    * Class CATFmtExtIMesher
    * Class CATFmtFEEntities
    * Class CATFmtGeometricalEngine
    * Class CATFmtListOfFEEntities
    * Class CATFmtListOfMeshPart
    * Class CATFmtMeshDomain
    * Class CATFmtMeshElementIter
    * Class CATFmtMeshNodeIter
    * Class CATFmtMeshPartElementIter
    * Class CATFmtMeshPartNodeIter
    * Class CATFmtNode
    * Class CATFmtSelectionServices
    * Class CATFmtTrapSettings
    * Enumeration CATFmtCriterionQualityStatus
    * Enumeration CATFmtFEEntityType
    * Enumeration CATFmtGroupType
    * Enumeration CATFmtSelectionType
    * Enumeration CATFmtSetType
    * Enumeration CATFmtTrapMeshType
    * Interface CATIFmtAssociativity
    * Interface CATIFmtConnectivity
    * Interface CATIFmtCriterion
    * Interface CATIFmtCustomVisualization
    * Interface CATIFmtGroupManager
    * Interface CATIFmtGroupUpdate
    * Interface CATIFmtGroup
    * Interface CATIFmtLocalSpecification
    * Interface CATIFmtMeshDomain
    * Interface CATIFmtMeshManager
    * Interface CATIFmtMeshPartOutput
    * Interface CATIFmtMeshPart
    * Interface CATIFmtMesh
    * Interface CATIFmtMesher
    * Interface CATIFmtRepManager
    * Interface CATIFmtSelectedEdge
    * Interface CATIFmtSelectedElement
    * Interface CATIFmtSelectedFace
    * Interface CATIFmtSelectedNode
    * Interface CATIFmtSelectedType
    * Typedef [3]
  * CATFmtToolsInterfaces framework 
    * Class CATFmtListOfPath
    * Class CATFmtPathFactory
    * Class CATFmtRepManagerServices
    * Class CATFmtSelectionTrap
    * Macro or #define CATFmtGeometry0D
    * Macro or #define CATFmtGeometry1D
    * Macro or #define CATFmtGeometry2D
    * Macro or #define CATFmtGeometry3D
    * Macro or #define CATFmtGeometryAll
    * Enumeration CATFmtTrapMode
    * Enumeration CATFmtViewMode
    * Interface CATFmtPath
    * Interface CATIFmtTrapSelector
    * Typedef CATFmtGeometryType
  * CATFmtUIInterfaces framework 
    * Class CATFmtSelectionTrapAgent
    * Class CATFmtUIBasicServices
    * Interface CATIFmtViewManager
  * CATIAApplicationFrame framework 
    * Macro or #define CATFrmMkStringFromDefine1
    * Macro or #define CATFrmMkStringFromDefine
  * CATIAV4Interfaces framework 
    * Global Function CATV4iGetCanonLength
    * Global Function CATV4iGetConnectorLink
    * Global Function CATV4iGetDittoLink
    * Global Function CATV4iGetMechLink
    * Global Function CATV4iGetParentOCPLink
    * Global Function CATV4iGetPipingLink
  * CATPDMBaseInterfaces framework 
    * Interface CATIPDMUEOnCancel
  * CATPDMReconcile framework 
    * Class CATEpeDocument
    * Class CATEpeFirstLevelInstance
    * Class CATEpeInstance
    * Class CATEpeNode
    * Class CATEpeObject
    * Class CATEpePartVersion
    * Class CATEpeProxyDocument
    * Class CATEpeSession
    * Class CATLISTP(CATEpeNode)
    * Class CATLISTP(CATIPDMCharacteristicScm)
    * Class CATLISTP(CATIPDMCriterionScm)
    * Class CATLISTP(CATScmPDMObject)
    * Class CATScmPDMObject
    * Macro or #define CATEpeNodeDocument
    * Macro or #define CATEpeNodeFirstLevelInstance
    * Macro or #define CATEpeNodeInstance
    * Macro or #define CATEpeNodeObject
    * Macro or #define CATEpeNodePartVersion
    * Macro or #define CATEpeNodeProxyDocument
    * Macro or #define CATEpeNodeSession
    * Macro or #define CATEpeNodeUnknown
    * Macro or #define CATScmCriterionModeList
    * Macro or #define CATScmCriterionModeXML
    * Macro or #define CATScmPDMObject_Init
    * Macro or #define CATScmPDMObject_LockByMe
    * Macro or #define CATScmPDMObject_LockByOther
    * Macro or #define CATScmPDMObject_LockStatusDefined
    * Macro or #define CATScmPDMObject_MaturityStatusDefined
    * Macro or #define CATScmPDMObject_MaturityStatusFreezed
    * Macro or #define CATScmPDMObject_PublicationExposed
    * Macro or #define CATScmPDMObject_SiteOwnershipDefined
    * Macro or #define CATScmPDMObject_SiteOwnershipLocal
    * Macro or #define CATScmPDMObject_StructureExposed
    * Interface CATIPDMCharacteristicScm
    * Interface CATIPDMCriterionScm
    * Interface CATIPDMUERecEventScm
    * Interface CATIPDMUERecRulesScm
    * Interface CATIUExitPVRCommands
  * CATPlantShipInterfaces framework 
    * Class CATPspWPCheckViolation
    * Macro or #define Violation_WPObject
    * Interface CATIPspDefinePhysicalPart
  * CATSchPlatformInterfaces framework 
    * Macro or #define ListOfVarBaseUnknown
  * CATTTRSInterfaces framework 
    * Macro or #define CATMmrTTRSTypeGeneral
    * Macro or #define CATMmrTTRSTypePatternOfAngularTabsSlots
    * Macro or #define CATMmrTTRSTypePatternOfCircles
    * Macro or #define CATMmrTTRSTypePatternOfCylPinsHoles
    * Macro or #define CATMmrTTRSTypePatternOfCylTabsSlots
    * Macro or #define CATMmrTTRSTypePatternOfCylinders
    * Macro or #define CATMmrTTRSTypePatternOfHoles
    * Macro or #define CATMmrTTRSTypePatternOfNotCylPinsHoles
    * Macro or #define CATMmrTTRSTypePatternOfPlanes
    * Macro or #define CATMmrTTRSTypePatternOfSpheres
    * Macro or #define CATMmrTTRSTypePatternOfTabsSlots
    * Macro or #define CATMmrTTRSTypePatternOfThreads
    * Macro or #define CATMmrTTRSTypeProfile
    * Macro or #define CATMmrTTRSTypeRelated01
    * Macro or #define CATMmrTTRSTypeSupport
    * Macro or #define CATMmrTTRSTypeUndefined
    * Macro or #define CATMmrTTRSTypeUnknown
  * CDMAInteroperability framework 
    * Interface CATIPDMUEPrePostProcessSave
  * DMAPSInterfaces framework 
    * Macro or #define NULL_string
  * Dialog framework 
    * Typedef CATULong
  * ENOVDDManager framework 
    * Typedef CATListOfObjectVersion
  * ENOVInterfaces framework 
    * Macro or #define E_PVNotChildOfAR
    * Typedef CATListPtrENOVIABO
  * FreeFormOperators framework 
    * Class CATFrFSmoothingOper
    * Macro or #define NULL
    * Global Function CATFrFCreateSmoothingOper
  * GMModelInterfaces framework 
    * Macro or #define NULL
    * Enumeration CATTopRelimitByVolumeSelectionType
    * Global Function CATCGMCreatePickOperator
    * Global Function CATCGMCreateRelimitByVolume
    * Interface CATCGMPickOperatorPickedObject
    * Interface CATCGMPickOperatorResultIterator
    * Interface CATCGMPickOperator
    * Interface CATCGMTessID
    * Interface CATCGMTessParam
    * Interface CATICGMTopRelimitByVolume
    * Typedef CATCGMTessBodyList
    * Typedef CATTopSign
  * GMOperatorsInterfaces framework 
    * Macro or #define CATFrFTopologicalSweep_ListPOfCATCurve
    * Macro or #define NULL
    * Enumeration CATDistanceSignMode
    * Enumeration CATDynFilletFaceFaceInitMode
    * Enumeration CATTopBlendBehaviour_Mode
    * Enumeration CATTopCleanCrvC1ToC2Management
    * Enumeration TYPEDEF_ENUM
    * Global Function CATCGMCreateDistancePointBody
    * Global Function CATCGMCreateRemoveEdge
    * Global Function CATCGMCreateRemoveFace
    * Global Function CATCGMCreateRemoveFacesInShell
    * Global Function CATCGMCreateShellOperatorPlus
    * Global Function CATCGMCreateThickPlus
    * Global Function CATCGMCreateThickSurfacePlus
    * Global Function CATCGMCreateTopClashOperator
    * Global Function CATCGMCreateTopPositionPtFaceOperator
    * Global Function CATCGMFrFCreateSmoothingOper
    * Global Function CATCGMTopCreateSolidCuboid
    * Global Function CATCGMTopCreateSolidCylinder
    * Global Function CATCGMTopCreateSolidCylinder
    * Global Function CATCGMTopCreateSolidPyramid
    * Global Function CATCGMTopCreateSolidPyramid
    * Global Function CATCGMTopCreateSolidSphere
    * Global Function CATCGMTopCreateSolidTorus
    * Global Function CreateConvertCrvToNurbsCrv
    * Interface CATICGMDistancePointBody
    * Interface CATICGMFrFSmoothingOper
    * Interface CATICGMRemoveEdge
    * Interface CATICGMRemoveFace
    * Interface CATICGMRemoveFacesInShell
    * Interface CATICGMShellOperatorPlus
    * Interface CATICGMThickPlus
    * Interface CATICGMThickSurfacePlus
    * Interface CATICGMTopClashOperator
    * Interface CATICGMTopPositionPtFaceOperator
  * GeometricObjects framework 
    * Class CATICGMObjectsLoad
    * Class CATICGMObjectsSave
    * Enumeration CATCGMObjectsUnserialize
    * Typedef CATLoadCATCGMOperator
  * ManufacturingInterfaces framework 
    * Interface CATIMfgCCPCustom
    * Interface CATIMfgCustomizeCSOFilter
    * Interface CATIMfgInsertActivity
  * Mathematics framework 
    * Class CATCGMProgressBar
    * Class CATLISTP(CATMathAxis)
    * Class CATLISTP(CATMathVector2D)
    * Class CATLISTP(CATMathVector2Df)
    * Class CATLISTP(CATMathpointf)
    * Class CATLISTV(CATMathPoint2D)
    * Macro or #define CATAcos
    * Macro or #define CATCos
    * Macro or #define CATExp
    * Macro or #define CATLog
    * Macro or #define CATSin
    * Macro or #define CATSqrt
    * Macro or #define CATTan
    * Enumeration CATVerificationMode
    * Typedef CATCGMInterruptFunction
    * Typedef CATCGMProgressBarInterruptFunction
  * MecModInterfaces framework 
    * Enumeration CATMfBRepSelectInitMode
    * Enumeration CATMmrFondType
    * Typedef CATMfSuperBRepType
  * NavigatorInterfaces framework 
    * Interface CATIAnnotatedViewsXML
  * NewTopologicalObjects framework 
    * Class CATTopPositionPtFaceOperator
    * Class CATTopRelimitByVolume
    * Global Function CATCreateTopClashOperator
    * Global Function CATCreateTopPositionPtFaceOperator
    * Interface CATTopClashOperator
  * ObjectModelerSystem framework 
    * Macro or #define SEQUENCE
  * ObjectSpecsModeler framework 
    * Class CATLISTP(IID)
  * PartInterfaces framework 
    * Global Function CATCreateCATIPrtThreadStandardServices
  * SDMRuntime framework 
    * Typedef SdaiAppInstanceH
    * Typedef SdaiAttrH
    * Typedef SdaiEntityH
    * Typedef SdaiEntityInstanceH
  * SpaceAnalysisInterfaces framework 
    * Macro or #define CATDMUAllData
    * Macro or #define CATDMUClashData
    * Macro or #define CATDMUClash
    * Macro or #define CATDMUDistanceData
    * Macro or #define CATDMUDistance
    * Macro or #define CATDMUMeasureData
    * Macro or #define CATDMUMeasure
    * Macro or #define CATDMUSectionData
    * Macro or #define CATDMUSection
    * Global Function CATDMUCopyData
    * Interface CATIDMUUpdateDuringSimulation
    * Typedef CATDMUDataType
  * SpecialAPI framework 
    * Macro or #define FAILED
    * Macro or #define NULL
    * Macro or #define SUCCEEDED
    * Typedef BYTE
    * Typedef CATLONG
    * Typedef CATUC2Bytes
    * Typedef DWORD
    * Typedef HRESULT
    * Typedef LONG
    * Typedef ULONG
    * Typedef WORD
  * SurfaceMachiningInterfaces framework 
    * Interface CATIMfg5AxisSpiralMilling
    * Interface CATIMfgMultiAxisCurveMachiningAuxDrive
  * System framework 
    * Class CATSysSettingRepository
    * Macro or #define CATLISTV
    * Macro or #define CATRCOLL
    * Macro or #define FALSE
    * Macro or #define TRUE
    * Macro or #define throw
    * Global Function BuildSafeArrayVariant
    * Global Function BuildSafeArrayVariant
    * Global Function CATSysInstantiateSettingRepository
    * Global Function CATSysInstantiateSettingRepository
    * Global Function DSYStgRep
    * Global Function ~DSYStgRep
    * Interface CATIASettingRepository
    * Typedef CATCallbackEvent
    * Typedef CATCallback
    * Typedef CATClassId
    * Typedef CATSubscriberData
    * Typedef CATSubscriberMethod
  * TopologicalOperators framework 
    * Class CATRemoveEdge
    * Macro or #define NULL
    * Global Function CATCreateRemoveEdge
    * Global Function CATCreateRemoveEdge
    * Global Function CATCreateRemoveFace
    * Global Function CATTopCreateSolidCuboid
    * Global Function CATTopCreateSolidCylinder
    * Global Function CATTopCreateSolidCylinder
    * Global Function CATTopCreateSolidPyramid
    * Global Function CATTopCreateSolidPyramid
    * Global Function CATTopCreateSolidTorus
    * Interface CATRemoveFace
  * TopologicalOperatorsLight framework 
    * Macro or #define NULL
    * Global Function CATCreateRemoveFacesInShell
    * Global Function CATCreateTopDisconnect
    * Global Function CATCreateTopProject
    * Global Function CATTopCreateSolidSphere
    * Interface CATRemoveFacesInShell
  * VPMInterfaces framework 
    * Macro or #define suffixeActionSE
    * Interface CATIAVPMIIProductSpecification
  * VPMSTEPExchanges framework 
    * Typedef CATHashDicoOfCATUnicodeString
    * Typedef CATHashDicoOfSdaiAppInstance
  * VisualizationBase framework 
    * Macro or #define INVALID_STORAGEID
    * Macro or #define NULL

[Top]

* * *

History Version: **1** [Mar 2011] | Document created  
---|---  
[Top]  
  
* * *

_Copyright © 1999-2011, Dassault Systèmes. All rights reserved._  
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)
