---
title: "New C++ Authorized APIs in CAA V5R10 GA"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATIMSHSelectedElement", "CATICatalogBrowserFactory", "CATIDOMDocumentType", "CATIEleUipFilteringCriteria", "CATITTRSList", "CATIElbTermination", "CATIDOMCharacterData", "CATICatalogEnable", "CATIMfgManufacturingBatch", "CATICatalogSynchronize", "CATICatalogInstantiation", "CATIGSOWrapSurface", "CATIDOMTreeWalker", "CATIDOMEntityReference", "CATIDOMEntity", "CATICatalogPersistentQuery", "CATInstanciationContext", "CATIElbEquipment", "CATIMfgUserDataFeature", "CATIDOMNodeIterator"]
source_file: "Doc/online/CAACenQuickRefs/CAACenV5R10GANewCPPAPI.md"
converted: "2026-05-11T17:33:47.025274"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5R10 GA  
---|---  
  
* * *

The following are the new CAA V5R10 GA C++ Authorized APIs, compared with CAA V5R9 at GA level.

  * AdvancedTopologicalOpe framework
    * CATCreateSkinExtrapolation
    * CATCreateTopBlend
    * CATCreateTopGeodesicDistanceTool
    * CATSkinExtrapolation
    * CATTopBlend
  * AnalysisMeshingModel framework
    * CATIMSHSelectedElement
    * CATMSHModifyNotification
  * CATAnalysisInterfaces framework
    * CATSamSubType
  * CATAnalysisVisuInterfaces framework
    * CATISamImage
    * CATISamImageColorMap
    * CATISamImageDisplayManager
    * CATISamImageFactory
    * CATSamVisuTypeName
  * CATIAApplicationFrame framework
    * CATCompassState
    * CATI3DCompass
    * CATMMUpdateSettings
  * CATMatInterfaces framework
    * CATIPositionedMaterial
  * CATSchPlatformInterfaces framework
    * CATEASchAppCntrName
    * CATEASchAppGroup
    * CATISchAppCntrName
    * CATISchAppGroup
  * CATSchPlatformModeler framework
    * CATSchEventServices
  * CATTPSInterfaces framework
    * CATITPS3DGeoVisu
    * CATTPSDimensionType
    * CATTPSLinearDimensionSubType
  * CATTTRSInterfaces framework
    * CATCreateCATITTRSList
    * CATIRGE
    * CATIRGETopology
    * CATITTRS
    * CATITTRSAdvanced
    * CATITTRSList
    * CATMathComplexRGE
    * CATMathCylindricalRGE
    * CATMathPlanarRGE
    * CATMathPrismaticRGE
    * CATMathRGE
    * CATMathRevoluteRGE
    * CATMathSphericalRGE
    * CATMmrTTRSAdmissibleType
    * CATMmrTTRSAssociationCase
    * CATMmrTTRSClass
    * CATMmrTTRSFeatureOfSize
    * CATMmrTTRSRepresented
    * CATMmrTTRSSurfaceCanonicity
    * CATMmrTTRSType
    * CATMmrTTRSValidityState
    * CATTTRSClass
  * CATxPDMInterfaces framework
    * CATIxPDMItem
    * CATIxPDMSession
  * ComponentsCatalogsInterfaces framework
    * CATCciCatalogBrowserDisplayOptions
    * CATICatalogBrowser
    * CATICatalogBrowserFactory
    * CATICatalogChapter
    * CATICatalogChapterFactory
    * CATICatalogDescription
    * CATICatalogEnable
    * CATICatalogInstantiation
    * CATICatalogKeyword
    * CATICatalogLink
    * CATICatalogPersistentQuery
    * CATICatalogQuery
    * CATICatalogQueryResult
    * CATICatalogSynchronize
    * CATLISTV(CATICatalogChapter_var)
    * CATLISTV(CATICatalogDescription_var)
    * CATLISTV(CATICatalogKeyword_var)
    * CATLISTV(CATICatalogPersistentQuery_var)
  * DNBInspectInterfaces framework
    * DNBIInsCone
    * DNBIInsConeFtrPath
    * DNBIInsOutput
    * DNBIInsTagPoint
  * DraftingInterfaces framework
    * CATAnnInfo
    * CATDftRefreshContext
    * CATIDftAnnotation
    * CATIDftBalloon
    * CATIDftDatumFeature
    * CATIDftDimCumulate
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
  * ElecDeviceItf framework
    * CATElbDevice
    * CATElecDevice
    * CATIElbBackShell
    * CATIElbBundleCnctPt
    * CATIElbCavity
    * CATIElbConnectorShell
    * CATIElbEquipment
    * CATIElbExternalSplice
    * CATIElbInternalSplice
    * CATIElbSingleConnector
    * CATIElbTermination
    * CATIElbUipDevices
  * ElecRoutingItf framework
    * CATEwrWire
    * CATIEwrUipWires
  * ElecSchematicItf framework
    * CATIEdiReplaceCable
  * ElectricalInterfaces framework
    * CATIEleUipFilteringCriteria
    * CATIEleUipSystems
  * FreeFormOperators framework
    * CATCrvDegreeModification
    * CATSurDegreeModification
    * CreateCrvDegreeModification
    * CreateSurDegreeModification
  * GSMInterfaces framework
    * CATGSMLineLengthType
    * CATGSMTolerantModelingSmoothingType
    * CATGSMTranslateVectorType
    * CATIGSMThickness
  * GSOInterfaces framework
    * CATGSOWrapSurfaceRefDirType
    * CATIGSOWrapSurface
  * GeometricOperators framework
    * CATCreateIntersection
  * InteractiveInterfaces framework
    * CATIActivate
  * KnowledgeInterfaces framework
    * CATDelegateInstanciationAdapter
    * CATIDelegateInstanciation
    * CATInstanciationContext
  * KnowledgeInterfaces framework (created in V5R10 in LiteralFeatures. This framework was moved to KnowledgeInterfaces in V5R11)
    * CATICkeAddParametersDlg
    * CATICkeExpression
    * CATICkeOleSheet
    * CATIOptConstraint
    * CATKWEErrorSeverity
    * CATKweInstanceAdapter
  * ManufacturingInterfaces framework
    * CATIMfgInsert
    * CATIMfgManufacturingBatch
    * CATIMfgToolAssembly
    * CATIMfgUserDataAccess
    * CATIMfgUserDataFeature
    * CATIMfgUserEditorActivity
  * Mathematics framework
    * CATLISTP(CATMathTransformation)
  * Navigator4DFormats framework
    * CATMCIExportFunction
    * CATMCIReplaceFunction
  * Navigator4DIDEAS framework
    * RunIDEASMS7Conversion
    * RunIDEASMS8Conversion
    * RunIDEASMS9Conversion
  * Navigator4DUG framework
    * RunUG16Conversion
    * RunUG17Conversion
    * RunUG18Conversion
  * ObjectModelerBase framework
    * CATINavigateFilter
  * OptimizationInterfaces framework
    * CATIOptAlgorithm
    * CATIOptAlgorithmUIFactory
    * CATIOptFactory
    * CATIOptFreeParameter
    * CATIOptGoal
    * CATIOptOptimization
    * CATIOptProblem
    * CATIOptimizationLog
    * CATOptAlgorithmAdapter
    * CATOptTerminationNoImprovement
    * CATOptTerminationTime
  * PSNInteroperability framework
    * CATCreateVPMProductStructure
  * SPAAcisCATIArd framework (in SPAAcisCATIArd in V5R10, renamed to SPACATIAV5ToAcis in V5R11)
    * CATV5ToAcis
    * CATV5ToAcisAttrMap
  * SPAAcisToCATIAV5 framework (in SPAAcisCATIAwr in V5R10, renamed to SPAAcisToCATIAV5 in V5R11)
    * CATAcisToV5
    * CATAcisToV5AttrMap
  * SketcherToolsUI framework
    * CATSketcherSettings
  * System framework
    * CATGetDLName
    * CATGetDLNameExp
    * CATGetDLNameList
    * CATGetDLNameMulti
    * CATGetPrintablePath
    * CATGetRealPath
    * CATIVBExtension
    * CATMakeLogicalPath
  * TopologicalOperators framework
    * CATCreateTopDisconnectShell
    * CATCreateTopDisconnectWire
    * CATCreateTopEuclidianDistanceTool
    * CATCreateTopExtrapolWireOnShell
    * CATCreateTopTrimShell
    * CATCreateTopTrimShellWithKeepRemove
    * CATCreateTopTrimWire
    * CATCreateTopTrimWireWithKeepRemove
    * CATCreateTopTrim
    * CATTopExtrapolWireOnShell
    * CATTopSweepWireSkin
  * VPMInterfaces framework
    * CATListOfCATIVpmAFLProduct
    * ENOVIUEAutomaticInstanceCreation
    * VPMIWflApplicationHandler
    * VPMIWflCreation
  * VPMSTEPExchanges framework
    * ENOVIExUEAssyDataX
  * Visualization framework
    * CATIVisuFilter
  * VisualizationBase framework
    * CAT3DArrowGP
    * CATReadCgr
    * CATWriteCgr
  * XMLParser framework
    * CATDOMException
    * CATDOMNodeFilterType
    * CATIDOMAttr
    * CATIDOMCDATASection
    * CATIDOMCharacterData
    * CATIDOMComment
    * CATIDOMDocument
    * CATIDOMDocumentFragment
    * CATIDOMDocumentTraversal
    * CATIDOMDocumentType
    * CATIDOMElement
    * CATIDOMEntity
    * CATIDOMEntityReference
    * CATIDOMImplementation
    * CATIDOMNamedNodeMap
    * CATIDOMNode
    * CATIDOMNodeFilter
    * CATIDOMNodeIterator
    * CATIDOMNodeList
    * CATIDOMNotation
    * CATIDOMProcessingInstruction
    * CATIDOMText
    * CATIDOMTreeWalker
    * CATISAXAttributeList
    * CATISAXDTDHandler
    * CATISAXDocumentHandler
    * CATISAXEntityResolver
    * CATISAXErrorHandler
    * CATISAXInputSource
    * CATISAXLocator
    * CATISAXParser
    * CATIXMLDOMDocumentBuilder
    * CATIXMLSAXFactory
    * CATSAXException
    * CATSAXHandlerBase
    * CATSAXIOException
    * CATSAXParseException
    * CreateCATIXMLDOMDocumentBuilder
    * CreateCATIXMLSAXFactory

[Top]

* * *

History Version: **1** [Oct 2002] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
