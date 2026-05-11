---
title: "New C++ Authorized APIs in CAA V5R19 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIEhiMechanicalImport", "CATIMfgCatalogServices", "CATIDlgTableViewLineModel", "CATIDrwCumulatedDimSystem", "CATITPSCylinder", "CATIDftElementInSystem", "CATIDrwDimSystem", "CATITPSThread", "CATIIniSearchJapaneseGraphNameCriterion", "CATICfgCatLnk", "CATIPspPlacePartOnRun", "CATICkeParm_var", "CATITPSPlane", "CATIPrdHandleImpactsOnInstance", "CAACloudQsrItf", "CATIDlgTableViewColumnModel", "CATIAApplicationFrame", "CATImplementHandler", "CATIQsrCAAPowerFit", "CATIGSMMask"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R19GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.426935"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R19 GA  
---|---  
  
* * *

The following are the new CAA V5R19 GA C++ Authorized APIs, compared with CAA V5R18 at GA level.

  * AdvancedMathematics framework 
    * Macro or #define CATPolynomXR19NbStaticCoeff
    * Macro or #define CATPolynomXYR19NbStaticCoeff
    * Global Function ComputeOptimalImage
    * Global Function ComputeOptimalImage
    * Global Function IsMonotone
    * Global Function MinimizeNewton
    * Global Function SolveNewton
  * ApplicationFrame framework 
    * Global Function CATAfrSetCommandHeaderIconName
    * Global Function CATAfrSetCommandHeaderTitle
  * CAACloudQsrItf framework 
    * Interface CATIQsrCAAFactory
    * Interface CATIQsrCAAPowerFit
  * CATIAApplicationFrame framework 
    * Class CATDlgTableView
    * Class CATExtIDlgTableViewColumnModel
    * Class CATExtIDlgTableViewController
    * Class CATExtIDlgTableViewLineModel
    * Class CATExtIDlgTableViewModel
    * Macro or #define CATDlgTableBottomJustify
    * Macro or #define CATDlgTableCellCustom
    * Macro or #define CATDlgTableCellError
    * Macro or #define CATDlgTableCellNormal
    * Macro or #define CATDlgTableCellOK
    * Macro or #define CATDlgTableCellWarning
    * Macro or #define CATDlgTableCenterJustify
    * Macro or #define CATDlgTableColumnHidden
    * Macro or #define CATDlgTableColumnVisible
    * Macro or #define CATDlgTableHeaderAlwaysVisible
    * Macro or #define CATDlgTableHeaderFullWidth
    * Macro or #define CATDlgTableLeftJustify
    * Macro or #define CATDlgTableLeftScroll
    * Macro or #define CATDlgTableMiddleJustify
    * Macro or #define CATDlgTableMultipleSelect
    * Macro or #define CATDlgTableNoSelection
    * Macro or #define CATDlgTableRightJustify
    * Macro or #define CATDlgTableRightScroll
    * Macro or #define CATDlgTableSingleSelect
    * Macro or #define CATDlgTableSortable
    * Macro or #define CATDlgTableTopJustify
    * Macro or #define CATLeftScroll
    * Macro or #define CATListHeaderAlwaysVisible
    * Macro or #define CATListHeaderFullWidth
    * Macro or #define CATListSortable
    * Macro or #define CATRightScroll
    * Interface CATIDlgTableViewColumnModel
    * Interface CATIDlgTableViewController
    * Interface CATIDlgTableViewLineModel
    * Interface CATIDlgTableViewModel
    * Typedef CATDlgTableStyle
    * Typedef CATListOfCATBaseUnknown_var
  * CATImmENOVIAProvider framework 
    * Class CATPDMNavServices
  * CATPDMBase framework 
    * Class CATPDMCATIAServices
    * Class CATPDMCSServices
    * Global Function E2ESendTo
    * Global Function LoadFromPDM
    * Global Function SetEV5PersistencyMode
  * CATPDMBaseInterfaces framework 
    * Class CATListOfCATIPLMIdentificator
    * Interface CATIPDMUEResId
    * Interface CATIPLMIdentificator
  * CATPlantShipInterfaces framework 
    * Interface CATIPspPlacePartOnRun
  * CATTPSInterfaces framework 
    * Interface CATITPSCylinder
    * Interface CATITPSPlane
    * Interface CATITPSThread
  * DNBD5IInterfaces framework 
    * Interface DNBID5IExtractKinematics
  * DNBMHIInterfaces framework 
    * Interface DNBIMHILoadParameters
    * Interface DNBIMHIOpenAccess
    * Interface DNBIMHISaveAccess
  * Dialog framework 
    * Class CATDlgComboCloseUpNotification
  * Drafting2DLInterfaces framework 
    * Class CAT2DLDrawingServices
  * DraftingInterfaces framework 
    * Class CATDimSystemDefinition
    * Enumeration CATDrwDimSystemType
    * Enumeration CATDrwSystOffsetMode
    * Enumeration CATDrwSystValueAlignment
    * Interface CATIDftElementInSystem
    * Interface CATIDrwCumulatedDimSystem
    * Interface CATIDrwDimSystem
    * Interface CATIDrwStackedDimSystem
  * ENOCESInterfaces framework 
    * Enumeration CESSearchProjectOption
    * Enumeration CESSearchType
    * Interface ENOVICESAuthentication
    * Interface ENOVICESState
    * Interface ENOVICESViewAttribute
    * Interface ENOVIPartSelection
  * ENOVInterfaces framework 
    * Interface ENOVIActionEvents
  * ElecHarnessItf framework 
    * Interface CATIEhiMechanicalImport
  * GSMInterfaces framework 
    * Enumeration CATGSMMaskType
    * Interface CATIGSMMaskFactory
    * Interface CATIGSMMaskSet
    * Interface CATIGSMMask
  * GeometricObjects framework 
    * Macro or #define CATBoneFilletType
    * Macro or #define CATConeManifoldType
    * Macro or #define CATContextualManifoldType
    * Macro or #define CATCylinderManifoldType
    * Macro or #define CATDatumManifoldType
    * Macro or #define CATDeclarativeManifoldType
    * Macro or #define CATEvaluableManifoldType
    * Macro or #define CATGeoPolyBodyType
    * Macro or #define CATGeoPolyCurveType
    * Macro or #define CATGeoPolySurfaceType
    * Macro or #define CATJointFilletType
    * Macro or #define CATPlaneManifoldType
    * Macro or #define CATSphereManifoldType
    * Macro or #define CATSubdivisionManifoldType
    * Macro or #define CATTorusManifoldType
    * Global Function SetNotScaledKnotVector
  * GeometricOperators framework 
    * Class CATCurveUserParameterization
    * Global Function CATCreateCurveUserParameterization
  * InteractiveInterfaces framework 
    * Interface CATIIniSearchJapaneseGraphNameCriterion
    * Interface CATIIniSearchJapaneseNameCriterion
  * KnowledgeInterfaces framework 
    * Class CATLISTV(CATICkeParm_var)
  * ManufacturingInterfaces framework 
    * Interface CATIMfgActivityToolVisu
    * Interface CATIMfgCatalogServices
  * Mathematics framework 
    * Macro or #define CATToleranceCheckDefault
    * Macro or #define CATToleranceCheckStandard
    * Macro or #define CATTolerance_CheckValue
    * Macro or #define CATTolerance_ControlDefault
    * Global Function CATToleranceError
  * MecModInterfaces framework 
    * Interface CATIMmiInternalCopyWithLink
  * ObjectModelerBase framework 
    * Class CATDocumentIntegrityServices
    * Interface CATIOmbContainerLinksUpdateStatus
  * ObjectModelerSystem framework 
    * Class CATListPtrCATBaseUnknown
  * ObjectSpecsModeler framework 
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
  * ProductStructure framework 
    * Class CATPrsWorkModeServices
  * ProductStructureInterfaces framework 
    * Interface CATIPrdHandleImpactsOnInstance
    * Interface CATIPrdHandleImpactsOnReference
  * System framework 
    * Macro or #define CATDeclareHandler
    * Macro or #define CATImplementHandler
    * Macro or #define CATLISTP_DEFINE
    * Macro or #define CATLISTV_DEFINE
  * TopologicalOperators framework 
    * Global Function CATCreateTopNewSplitShell
    * Global Function CATCreateTopTrim
  * VPMInterfaces framework 
    * Interface CATICfgCatLnk
    * Interface ENOVIMultiSiteObjectMng
    * Interface ENOVIObjectServiceCode
  * VisualizationBase framework 
    * Class CATGraphicElementGlobalNormale
    * Class CATPickOptions
    * Enumeration DITHER_MODE

[Top]

* * *

History Version: **1** [Mar 2008] | Document created  
---|---  
[Top]  
  
* * *

_Copyright © 1999-2008, Dassault Systèmes. All rights reserved._  
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.md) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.md) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.md)
