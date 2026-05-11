---
title: "New C++ Authorized APIs in CAA V5R11 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIMSHSelectedElement", "CATITPSNoa", "CATIMfResultManagement", "CATICkeFunctionFactory", "CATISchPostPaste", "CATIParmManipulator", "CATIEleUipFilteringCriteria", "CATISchAppObsoleteClass", "CATIEhiPrtWkbCfgAddin", "CATIMSHSelectedFace", "CATIDftGDT", "CATISchAppSourcePostPaste", "CATIMfgDesignHole", "CATICkeUnit", "CATIMfgMacrosTabPage", "CATInitBatchOnHost", "CATIDesktopDocUE", "CATIBRepAccess", "CATISketchPositioning", "CATIParmSelector"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R11GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.082066"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R11 GA  
---|---  
  
* * *

The following are the new CAA V5R11 GA C++ Authorized APIs, compared with CAA V5R10 at GA level.

  * Administration framework 
    * CATGetHFXLevel
  * AnalysisMeshingModel framework 
    * CATIMSHSelectedEdge
    * CATIMSHSelectedElement
    * CATIMSHSelectedFace
    * CATIMSHSelectedNode
    * CATMSHExtIMesher
    * CATMSHModifyNotification
  * AutomationInterfaces framework 
    * CATScriptUtilities
  * CATAnalysisGPSInterfaces framework 
    * CATAnalysisGenerativeFEM
    * CATIGPSCfgAddin
    * CATIGPSStructuralTemplate
  * CATAnalysisInterfaces framework 
    * CATISamAnalysisSetInit
    * CATISamBasicComponentManager
    * CATISamCtxMenuProvider
    * CATISamProviders
    * CATSamAggregationMode
    * CATSamApplyQualifier
    * CATSamCompareType
    * CATSamDataType
    * CATSamDof
    * CATSamListType
    * CATSamMathType
    * CATSamPhysicalType
    * CATSamPosition
    * CATSamRefFrame
    * CATSamRefFrameType
    * CATSamStatus
    * CATSamSubType
    * CATSamValue
    * SAMHiddenState
    * SAMReadOnlyState
  * CATAnalysisResources framework 
    * CATEAnalysisSetInit
    * CATSamBasicComponentManagerAdaptor
  * CATAssemblyInterfaces framework 
    * CATIAsmSelectMove3D
  * CATHullConceptualInterfaces framework 
    * CATIHCDCfgWorkbenchAddin
  * CATIAApplicationFrame framework 
    * CATISelectMove3D
  * CATMatInterfaces framework 
    * CATIPositionedMaterial
  * CATPDMBaseInterfaces framework 
    * CATIPDMUnixNTMapping
  * CATSchPlatformInterfaces framework 
    * CATEASchAppCCPCGCntrInfo
    * CATEASchAppObsoleteClass
    * CATEASchAppSourcePostPaste
    * CATEASchAppTargetPostPaste
    * CATISchAppCCPCGCntrInfo
    * CATISchAppObsoleteClass
    * CATISchAppSourcePostPaste
    * CATISchAppTargetPostPaste
    * CATISchCntrConnect
    * CATISchObsoleteModel
    * CATISchMovable2
    * CATISchPostPaste
  * CATSchPlatformModeler framework 
    * CATSchEventServices
  * CATTPSInterfaces framework 
    * CATITPSDrawable
    * CATITPSNoa
    * CATITPSNoaRepresentation
    * CATTPSNoaRepType
  * CATTubingInterfaces framework 
    * CATITubCfgAddin
  * ComponentsCatalogsInterfaces framework 
    * CATCciCatalogBrowserDisplayOptions
  * ConstraintModeler framework 
    * CATDimAngle0PI
    * CATDimAngle1PI
    * CATDimAngle2PI
    * CATDimAngleUnspec
    * CATDimMath
    * CATDimSector
    * CATDimSectorCompl
    * CATDimSectorOpposite
    * CATDimTempCst
    * CATDimVisualizationAdapter
    * CATICstFactory
    * CATMfPossibleCst
    * CATMfREQUIRE_DIMMATH
    * CATMfREQUIRE_TEMPDIM
    * CATMfTS_FEAT_CHANGE
    * CATMfTS_FIRST_CHANGE
    * CATMfTS_PARAMETER_CHANGE
    * CATMfTS_PART_CHANGE
  * ConstraintModelerInterfaces framework 
    * CATFeatureType
    * CATIAncestry
    * CATIBloc
    * CATICst
    * CATICstData
    * CATLISTV(CATICst_var)
  * DMAPSInterfaces framework 
    * CATPcsNavigProvider
    * CATSPPLogicalActivitiesFilter
  * DNBInspectInterfaces framework 
    * DNBIInsCircleMathServices
    * DNBIInsConstFeature
    * DNBIInsCylinderMathServices
    * DNBIInsLineMathServices
    * DNBIInsPlaneMathServices
    * DNBIInsPointMathServices
    * DNBIInsSphereMathServices
    * DNBIInsTagPoint
    * DNBInsWarningAttribute
  * Dialog framework 
    * CATDlgMultiListSortMethod
  * DraftingInterfaces framework 
    * CATDftRefreshContext
    * CATIDftAnnotation
    * CATIDftGDT
    * CATIDftMotifPattern
    * CATIDftProperties
    * CATIDftText
    * CATIDftTextProperties
    * CATIDftTextRange
    * DftAnchorPoint
    * DftAssociativityMode
    * DftFrameType
    * DftGDTModifier
    * DftGDTModifiers
    * DftGDTSymbol
    * DftGDTValueType
    * DftJustification
    * DftOrientationReference
    * DftRoughText
    * DftTextSetting
    * DftThreadType
    * DftWrappingMode
  * ENOVDDManager framework 
    * DDMNGUtil
  * ENOVInterfaces framework 
    * CATIDesktopDocUE
    * ENOVIABODocument
    * ENOVIABOFolder
    * ENOVIABOPartInstance
    * ENOVIABOPartReference
    * ENOVIABOProductClass
    * ENOVIABOProductComponent
    * ENOVIABOProductInstance
    * ENOVIABOProductRootClass
    * ENOVIABOProductSpecification
    * ENOVIABORelation
    * ENOVIABOVersionMaster
    * ENOVIABusinessObject
  * ENOVaultClientCPP framework 
    * ENOVIVaultResultSet
    * VAULT_E_READ_ONLY
  * ElecDeviceItf framework 
    * CATElbDevice
    * CATElecDevice
    * CATIElbPrdWkbCfgAddin
    * CATIElbPrtWkbCfgAddin
    * CATIElbUipDevices
  * ElecHarnessItf framework 
    * CATIEhiPrdWkbCfgAddin
    * CATIEhiPrtWkbCfgAddin
  * ElecRoutingItf framework 
    * CATEwrEquipotential
    * CATEwrWire
    * CATIEwrUipEquipotentials
    * CATIEwrUipWires
    * CATIEwrWkbCfgAddin
  * ElecSchematicItf framework 
    * CATIEdiReplaceCable
    * CATIEdiWireCtr
  * ElectricalInterfaces framework 
    * CATIEleUipFilteringCriteria
    * CATIEleUipSystems
  * FreeFormOperators framework 
    * CATCrvDegreeModification
    * CATSurDegreeModification
    * CreateCrvDegreeModification
    * CreateSurDegreeModification
  * GSMInterfaces framework 
    * CATGSMCornerTrimMode
    * CATGSMPositionDirCompMode
    * CATGSMSweepTrimMode
    * CATIGSMCircleCenterTangent
    * CATIGSMFilletTriTangent
  * GeometricObjects framework 
    * CATCGMAttribute_CreateAttribute
    * CATCloseCGMContainer
    * CATCreateCGMContainer
    * CATLoadCGMContainer
    * CATSaveCGMContainer
    * CATTopCheckJournalType
  * GeometricOperators framework 
    * CATCreateDistanceMin
    * CATCreateNurbsCurveTools
    * CATCreateNurbsSurfaceTools
    * CATCreateProjection
    * CATCreateReflectCurve
    * CATNurbsCurveTools
    * CATNurbsSurfaceTools
    * CATNurbsToolsInfo
    * IsError
    * IsFatal
    * IsInfo
    * IsOK
  * InteractiveInterfaces framework 
    * CATICCPable
  * KnowledgeInterfaces framework. Most of these APIs come from the LiteralFeatures framework. 
    * Boolean
    * CATCke
    * CATCkeEvalContext
    * CATCkeFrameStyle
    * CATCkeGlobalFunctions
    * CATCkeListOf
    * CATCkeListOfArg
    * CATCkeListOfInst
    * CATCkeListOfMagnitude
    * CATCkeListOfObject
    * CATCkeListOfParm
    * CATCkeListOfRelation
    * CATCkeListOfSignature
    * CATCkeListOfType
    * CATCkeListOfUnit
    * CATIAddLibrary
    * CATIAttributesDescription
    * CATICkeAddParametersDlg
    * CATICkeArg
    * CATICkeExpression
    * CATICkeFeature
    * CATICkeFunction
    * CATICkeFunctionFactory
    * CATICkeInst
    * CATICkeLaw
    * CATICkeMKSUnit
    * CATICkeMagnitude
    * CATICkeNaming
    * CATICkeOleSheet
    * CATICkeParamFrame
    * CATICkeParameterSet
    * CATICkeParm
    * CATICkeParmFactory
    * CATICkeRelation
    * CATICkeRelationExp
    * CATICkeRelationFactory
    * CATICkeSheet
    * CATICkeSignature
    * CATICkeTextSheet
    * CATICkeType
    * CATICkeUnit
    * CATIDesignTable
    * CATIEnumere
    * CATIKweActivable
    * CATIList
    * CATIOptConstraint
    * CATIParameterEditor
    * CATIParameterEditorFactory
    * CATIParmAsStored
    * CATIParmDictionary
    * CATIParmEvents
    * CATIParmManipulator
    * CATIParmPublisher
    * CATIParmSelector
    * CATIParmTolerance
    * CATIParmValuator
    * CATIRelationEvents
  * ManufacturingInterfaces framework 
    * CATIMfgCatalogFactories
    * CATIMfgDesignHole
    * CATIMfgMacroMotionsGeomMapping
    * CATIMfgMacrosTabPage
    * CATIMfgMappingForMachiningAxis
    * CATIMfgResourceQueryDocument
  * MecModInterfaces framework 
    * CATI3DGeometricalElement
    * CATLISTP(CATIBRepAccess)
  * MechanicalModeler framework 
    * CATIMfResultManagement
    * CATLISTP(CATIRSur)
  * Navigator4DIDEAS framework 
    * RunIDEASMS7Conversion
    * RunIDEASMS8Conversion
    * RunIDEASMS9Conversion
  * Navigator4DUG framework 
    * RunUG16Conversion
    * RunUG17Conversion
    * RunUG18Conversion
    * RunUGNXConversion
  * NavigatorInterfaces framework 
    * CATIDMUNavigatorAddin
  * NewTopologicalObjects framework 
    * AddResults
    * ReplaceResult
  * ObjectModelerBase framework 
    * CATINavigateFilter
    * CATOmbDocPropertyServices
  * OptimizationInterfaces framework 
    * CATOptApproximationGradientAlgorithmAttributeAccessName
    * CATOptApproximationGradientAlgorithmCATIType
    * CATOptApproximationGradientAlgorithmConvergenceSpeedAttribute
    * CATOptConstraintAttributeAccessName
    * CATOptConstraintCATIType
    * CATOptConstraintDistanceAttribute
    * CATOptConstraintPrecisionAttribute
    * CATOptConstraintPriorityAttribute
    * CATOptConstraintSatisfactionAttribute
    * CATOptConstraintSatisfactionCATIType
    * CATOptDelegateInstanciationName
    * CATOptFeatureCATIType
    * CATOptFreeParameterAttributeAccessName
    * CATOptFreeParameterCATIType
    * CATOptFreeParameterHasRangesStepAttribute
    * CATOptFreeParameterInfRangeAttribute
    * CATOptFreeParameterParmAttribute
    * CATOptFreeParameterStepAttribute
    * CATOptFreeParameterSupRangeAttribute
    * CATOptFreeParameterValueAttribute
    * CATOptFullDoeAlgorithmAttributeAccessName
    * CATOptFullDoeAlgorithmCATIType
    * CATOptFullDoeAlgorithmLastDoneExperimentNbAttribute
    * CATOptFullDoeAlgorithmListOfLevelsAttribute
    * CATOptGenericAlgorithmAttributeAccessName
    * CATOptGenericAlgorithmCATIType
    * CATOptGenericAlgorithmMaxTimeAttribute
    * CATOptGenericAlgorithmMaxWoImprovementAttribute
    * CATOptGenericAlgorithmNbUpdatesMaxAttribute
    * CATOptGenericAlgorithmStoppingCriterionAttribute
    * CATOptGenericDoeAlgorithmCATIType
    * CATOptGenericOptimAlgorithmCATIType
    * CATOptGoalAttributeAccessName
    * CATOptGoalCATIType
    * CATOptGoalCommentAttribute
    * CATOptGoalGoalTypeAttribute
    * CATOptGoalParameterAttribute
    * CATOptGoalPrecisionAttribute
    * CATOptGoalPriorityAttribute
    * CATOptGoalTargetValueAttribute
    * CATOptGradientAlgorithmAttributeAccessName
    * CATOptGradientAlgorithmCATIType
    * CATOptGradientAlgorithmConvergenceSpeedAttribute
    * CATOptOptimizationAlgorithmAttribute
    * CATOptOptimizationAttributeAccessName
    * CATOptOptimizationCATIType
    * CATOptOptimizationFreeParametersAttribute
    * CATOptOptimizationOptimizationLogAttribute
    * CATOptOptimizationPackageName
    * CATOptOptimizationProblemAttribute
    * CATOptOptimizationSetCATIType
    * CATOptOptimizationSetOptimizationsAttribute
    * CATOptOptimizationUpdateVisuAttribute
    * CATOptProblemAttributeAccessName
    * CATOptProblemCATIType
    * CATOptProblemCommentAttribute
    * CATOptProblemConstraintsAttribute
    * CATOptProblemGoalsAttribute
    * CATOptSimAnnealingAlgorithmAttributeAccessName
    * CATOptSimAnnealingAlgorithmCATIType
    * CATOptSimAnnealingAlgorithmConvergenceSpeedAttribute
    * CATOptimizationLogAttributeAccessName
    * CATOptimizationLogBestParmAttribute
    * CATOptimizationLogCATIType
    * CATOptimizationLogIndexOfBestSolInDTAttribute
    * CATOptimizationLogNbEvalParmAttribute
    * CATOptimizationLogPointsDTAttribute
    * OPTNLSFileName
  * PSNInteroperability framework 
    * CATCreateVPMProductStructure
    * CATGetVPMEnvironment
    * CATInitBatchOnHost
  * PrintBase framework 
    * CATLISTP(CATPrinter)
    * CATLISTV(CATPrintForm)
  * ProductStructure framework 
    * CATIContextualProduct
  * SketcherInterfaces framework 
    * CATI2DConnectCurve
    * CATISketchPositioning
    * CATSktPosDirection
    * CATSktPosOrientationMode
    * CATSktPosOriginMode
    * CATSktPosSupportMode
  * SketcherToolsUI framework 
    * CATSketcherSettings
  * System framework 
    * CATCreateInstance
    * CATDeclareComponent
    * CATGMT
    * CATGetDLName
    * CATGetDLNameExp
    * CATGetDLNameList
    * CATGetDLNameMulti
    * CATGetFilePathFromOfficialVariable
    * CATGetPrintablePath
    * CATGetRealPath
    * CATIIniSettingManagement
    * CATINTPTR
    * CATLONG32
    * CATLONGPTR
    * CATMakeLogicalPath
    * CATSysUTF8Str
    * CatScriptLibraryType
    * CATUINTPTR
    * CATULONG32
    * CATULONGPTR
  * ToolPathEditorInterfaces framework 
    * CATIMfgTPECutAreasEditor
    * CATIMfgTPECutAreasUserHeader
  * TopologicalOperators framework 
    * CATCreateExtrapolateBody
    * CATCreateTopBoundary
    * CATCreateTopExtrapolWireOnShell
    * CATCreateWireExtrapolationOp
    * CATExtrapolateBody
    * CATHybBoundary
    * CATTopExtrapolWireOnShell
    * CATWireExtrapolationOp
  * VPMInterfaces framework 
    * CATIAVPMBOProductClass
    * CATICfgMilestoneCallBack
    * CATListOfCATICfgSimpleSpecification_var
    * CATListOfCATICfgValue_var
    * CATListOfVPMIWflActivity.
    * CATListOfVPMIWflApplication.
    * CATListOfVPMIWflData.
    * CATListOfVPMIWflParticipant.
    * CATListOfVPMIWflProcess.
    * CATListOfVPMIWflRegularActivity.
    * ENOVIPartNewVersionEvent
    * ENOVIRulePredicate
    * ENOVIUEAutomaticInstanceCreation
    * ENOVIUENamedObject
    * GetWflApplicationHandler
    * GetWflCreationMgr
    * VPMIWflActivityListener
    * VPMIWflApplicationHandler
    * VPMIWflDataListener
    * VPMIWflProcessListener
    * VPMIWflQuery
  * VPMSTEPExchanges framework 
    * ENOVIExReportLogFormat
    * ERROR_CHECKDATA_CHILD
    * ERROR_CHECKDATA_COMPAREPC
    * ERROR_CHECKDATA_COMPAREPRC
    * ERROR_CHECKDATA_DIFCV
    * ERROR_CHECKDATA_DOCFILE
    * ERROR_CHECKDATA_DOCITER
    * ERROR_CHECKDATA_DOCVAULT
    * ERROR_CHECKDATA_GENERAL
    * ERROR_CHECKDATA_ID
    * ERROR_CHECKDATA_IITREE
    * ERROR_CHECKDATA_MATRIX
    * ERROR_CHECKDATA_MERGE
    * ERROR_CHECKDATA_MULTIPRC
    * ERROR_CHECKDATA_NOCV
    * ERROR_CHECKDATA_NOPRC
    * ERROR_CHECKDATA_NOVERSION
    * ERROR_CHECKDATA_PARENT
    * ERROR_CHECKDATA_PARENTPC
    * ERROR_CHECKDATA_PARENTPRC
    * ERROR_CHECKDATA_PRC
    * ERROR_CHECKDATA_TOC
    * ERROR_CHECKDATA_TREE
    * ERROR_CHECKDATA_TYPE
    * ERROR_CREATEDATA
    * ERROR_CREATEDATAINFO
    * ERROR_CREATEDATAINFO_PLUS
    * ERROR_CREATEDATAREF
    * ERROR_CREATEDATAREF_PLUS
    * ERROR_CREATEDATA_PLUS
    * ERROR_CREATE_EDX
    * ERROR_CREATE_EDX_PLUS
    * ERROR_DELETEDATA
    * ERROR_DELETELINK
    * ERROR_ENV_ATBMG
    * ERROR_ENV_BOUNDING
    * ERROR_ENV_CFGMGR
    * ERROR_ENV_CLOSEVAULTFILE
    * ERROR_ENV_DBSAVE
    * ERROR_ENV_DOCMGR
    * ERROR_ENV_EDX
    * ERROR_ENV_EDXSTRUCTURE
    * ERROR_ENV_EXPDATA
    * ERROR_ENV_FACTORY
    * ERROR_ENV_GETINVAULT
    * ERROR_ENV_HISTMGR
    * ERROR_ENV_LOGIN
    * ERROR_ENV_MODEL
    * ERROR_ENV_PTYMGR
    * ERROR_ENV_ROOTDESKTOP
    * ERROR_ENV_SCRIPT
    * ERROR_ENV_SECUMGR
    * ERROR_ENV_SESSION
    * ERROR_ENV_SETINVAULT
    * ERROR_ENV_STEPFILE
    * ERROR_ENV_TSMODE
    * ERROR_ENV_UNSYNCLOG
    * ERROR_ENV_UPDATESCRIPT
    * ERROR_ENV_VAULT
    * ERROR_ENV_VAULTDOC
    * ERROR_ENV_VAULTNAMES
    * ERROR_ENV_VAULTSESSION
    * ERROR_ENV_VAULTUSERSESSION
    * ERROR_ENV_WRITEFILE
    * ERROR_ENV_XCOMPO
    * ERROR_ENV_XCOMPOFAILED
    * ERROR_EXPORT
    * ERROR_EXPORT_PLUS
    * ERROR_GETDATA
    * ERROR_GETDATAINFO_ATTR
    * ERROR_GETDATAINFO_KOSYNC
    * ERROR_GETDATA_REF
    * ERROR_GETDBINFO
    * ERROR_GETDBINFO_PLUS
    * ERROR_GETEDXINFO
    * ERROR_GETEDXINFO_PLUS
    * ERROR_GETOBJECT
    * ERROR_GET_EDX
    * ERROR_GET_EDX_PLUS
    * ERROR_LINKDBREF
    * ERROR_LINKDBREF_PLUS
    * ERROR_RECONCILIATEDATA
    * ERROR_RECONCILIATEDATA_PLUS
    * ERROR_SETDBREF
    * ERROR_SETDBREF_PLUS
    * ERROR_SETEDXINFO
    * ERROR_SETEDXINFO_PLUS
    * ERROR_WORKWITHREF
    * ERROR_WORKWITHREF_PLUS
    * PROCESS_CHECKDATA
    * PROCESS_CHECKDATA_PLUS
    * PROCESS_EXPORT
    * PROCESS_EXPORT_PLUS
    * PROCESS_IMPORT
    * PROCESS_IMPORT_PLUS
    * PROCESS_IMPORT_VAULT
    * ReportAttrKind
    * ReportModifKind
  * VisualizationBase framework 
    * CAT3DGeomRep
    * CATVizBaseIUnknown
    * DrawMenb
  * XMLParser framework 
    * CATISAXAttributes
    * CATISAXContentHandler
    * CATISAXDeclHandler
    * CATISAXLexicalHandler
    * CATISAXXMLFilter
    * CATISAXXMLReader
    * CATSAXDefaultHandler
    * CATSAXDefaultXMLFilter
    * CATSAXNotRecognizedException
    * CATSAXNotSupportedException
    * CATSAXParserAdapter
    * CATSAXXMLReaderAdapter
    * CATSAXXMLReaderOptions

[Top]

* * *

History Version: **1** [Feb 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
