---
title: "New C++ Authorized APIs in CAA V5-6R2013 GA"
category: "general"
module: "CAACenQuickRefs"
tags: ["CATICGMHybTrim", "CATITPSThreadGeometrySpecification", "CATICGMHybIntersect", "CATIMmiUseDatumFactory", "CATIMmiUseSolidInsertion", "CATIMmiMechanicalFeature_var", "CATITPSAssociatedTextVisu", "CATIMmiUseCharacteristicExtremity", "CATITPSTextVisu", "CATIVpmLightVersion", "CATIMmiUseStructureAnalyse", "CATIMmiUseMfBRep", "CATIMmiUseREdge", "CATICGMDynAdvancedFillet", "CATIMmiBRepScanServices", "CATIStrPPGExecLogSettingAtt", "CATICGMDynAdvancedDraft", "CATICGMTopExtrude", "CATICGMTopExtractFace", "CATIMmiUsePrtPart"]
source_file: "Doc\online\CAACenQuickRefs\CAACenV5R23GANewCPPAPI.htm"
converted: "2026-05-11T17:33:47.535004"
---

CAA V5 Encyclopedia |  New C++ Authorized APIs in CAA V5-6R2013 GA  
---|---  
  
* * *

The following are the new CAA V5-6R2013 GA C++ Authorized APIs, compared with CAA V5-6R2012 at GA level.

  * CATFmtToolsInterfaces framework 
    * Class CATFmtFEMRepFactory
  * CATGSMUseItf framework 
    * Interface CATIGSMUseMultipleSolutionsManager
  * CATIAV4Interfaces framework 
    * Global Function CATV4iIsExternalWsp
  * CATMecModExtendItf framework 
    * Class CATMf3DBehaviorAdapter
    * Class CATMmrUseSolidInsertionAdapt
    * Interface CATIMmiAlgoConfigServices
    * Interface CATIMmiErrUpdate
    * Interface CATIMmiFeatureAttributes
    * Interface CATIMmiUpdateError
  * CATMecModLiveUseItf framework 
    * Class CATLISTV(CATIMmiMechanicalFeature_var)
    * Interface CATIMmiMechanicalFeature
    * Interface CATIMmiUseBodyContent
    * Interface CATIMmiUsePrtPart
  * CATMecModUseItf framework 
    * Class CATLISTP(CATIMmiUseBRepAccess)
    * Class CATLISTP(CATIMmiUseRSur)
    * Class CATLISTV(CATIMmiUseBRepAccess_var)
    * Class CATLISTV(CATIMmiUseMfBRep_var)
    * Enumeration CATMmrBRepFilterType
    * Interface CATIMmiBRepFactory
    * Interface CATIMmiBRepScanServices
    * Interface CATIMmiPrtContainer
    * Interface CATIMmiSubElemProperties
    * Interface CATIMmiUseBRepAccess
    * Interface CATIMmiUseBRepDecodeServices
    * Interface CATIMmiUseBRep
    * Interface CATIMmiUseBasicInsertion
    * Interface CATIMmiUseBorderFVertex
    * Interface CATIMmiUseBorderREdge
    * Interface CATIMmiUseCharacteristicAxis
    * Interface CATIMmiUseCharacteristicExtremity
    * Interface CATIMmiUseCharacteristicPlanarSubElement
    * Interface CATIMmiUseDatumFactory
    * Interface CATIMmiUseFVertexAccess
    * Interface CATIMmiUseFVertex
    * Interface CATIMmiUseFeaturize
    * Interface CATIMmiUseGeometricalElement
    * Interface CATIMmiUseGeometryAccess
    * Interface CATIMmiUseLinearBodyServices
    * Interface CATIMmiUseMechanicalTool
    * Interface CATIMmiUseMfBRep
    * Interface CATIMmiUseMfEdge
    * Interface CATIMmiUsePointOnEdge
    * Interface CATIMmiUseREdgeAccess
    * Interface CATIMmiUseREdge
    * Interface CATIMmiUseRSur
    * Interface CATIMmiUseSolidInsertion
    * Interface CATIMmiUseStructureAnalyse
    * Interface CATIMmiUseTopoAccess
    * Interface CATIMmiUseUpdateError
    * Interface CATIMmiUseWireFVertex
    * Interface CATIMmiUseWireREdge
    * Typedef CATCkeListOfParm
  * CATPDMReconcile framework 
    * Macro or #define CATScmPDMObject_HasACATUuid
  * CATTPSInterfaces framework 
    * Enumeration CATTPSConstrainingDOF
    * Enumeration CATTPSIndividualElementControl
    * Enumeration CATTPSToleranceThreadGeometry
    * Interface CATITPSAssociatedTextVisu
    * Interface CATITPSIndependency
    * Interface CATITPSIndividualElementControl
    * Interface CATITPSReciprocity
    * Interface CATITPSStatisticalTolerancing
    * Interface CATITPSTextVisu
    * Interface CATITPSThreadGeometrySpecification
  * CCWInterfaces framework 
    * Interface CCWICVNonGraphicProperty
  * ENOVaultClientCPP framework 
    * Macro or #define VAULT_E_MAX_FILE_SIZE_EXCEEDED
  * FeatureModelerExt framework 
    * Class CATFmAttributeName
    * Class CATFmAttributeValuationInfo
    * Class CATFmAttributeValue
    * Class CATFmCCPContext
    * Class CATFmCatalogFacade
    * Class CATFmContainerFacade
    * Class CATFmContainerServices
    * Class CATFmCredentials
    * Class CATFmEvent
    * Class CATFmFeatureCustomizationAdaptor
    * Class CATFmFeatureFacade
    * Class CATFmFeatureIterator
    * Class CATFmPointingFeatureIterator
    * Class CATFmStartUpFacade
    * Class CATOmbObjectInContext
    * Macro or #define E_FMAGGREGATIONERROR
    * Macro or #define E_FMEXCEPTIONRAISED
    * Macro or #define E_FMINVALIDFEATURE
    * Macro or #define E_FMKEYNOTFOUND
    * Macro or #define E_FMLOADINGMODE
    * Macro or #define E_FMNOLOCALVALUE
    * Macro or #define E_FMNOPLMSESSION
    * Macro or #define E_FMNOTALIST
    * Macro or #define E_FMNOTAPARAMETER
    * Macro or #define E_FMNOTASINGLE
    * Macro or #define E_FMNOTLOADED
    * Macro or #define E_FMOPERATIONNOTALLOWED
    * Macro or #define E_FMOUTOFBOUND
    * Macro or #define E_FMPARAMETER
    * Macro or #define E_FMPRIVATEVALUE
    * Macro or #define E_FMPROTECTEDRESOURCE
    * Macro or #define E_FMREADONLY
    * Macro or #define E_FMREDIRECTED
    * Macro or #define E_FMTYPEMISMATCH
    * Macro or #define E_FMUPDATEERROR
    * Enumeration CATFmAttributeAndValueKind
    * Enumeration CATFmAttributeUpdateBehavior
    * Enumeration CATFmAttributeValuationMode
    * Global Function CATFmGetLastError
    * Interface CATIFmFeatureBehaviorCustomization
    * Typedef CATFmEventSubscriberMethod
  * GMModelInterfaces framework 
    * Enumeration CATLengthType
    * Global Function CATCGMCreateBodyFromLengthOnWire
    * Interface CATICGMBodyFromLengthOnWire
  * GMOperatorsInterfaces framework 
    * Macro or #define CATPatternKOAndFar
    * Macro or #define CATPatternKO
    * Macro or #define CATPatternOKWithBoolean
    * Macro or #define CATPatternOKWithDuplication
    * Macro or #define CATPatternOKWithSewing
    * Enumeration CATDynDraftPrevisualization
    * Enumeration CATFrFTopologicalDowngradeSetting_Type
    * Global Function CATCGMCreateCompatibleForCGM
    * Global Function CATCGMCreateDirNewBodyExtremum
    * Global Function CATCGMCreateDynAdvancedChamfer
    * Global Function CATCGMCreateDynAdvancedDraft
    * Global Function CATCGMCreateDynAdvancedFillet
    * Global Function CATCGMCreateFaceReplaceSurfaceOperator
    * Global Function CATCGMCreateTopEuclidianDistanceTool
    * Global Function CATCGMCreateTopExtractFace
    * Global Function CATCGMCreateTopGeodesicDistanceTool
    * Global Function CATCGMCreateTopPattern
    * Global Function CATCGMCreateTopPattern
    * Global Function CATCGMCreateTopSilhouette
    * Interface CATICGMDynAdvancedChamfer
    * Interface CATICGMDynAdvancedDraft
    * Interface CATICGMDynAdvancedFillet
    * Interface CATICGMHybBoolean
    * Interface CATICGMHybIntersect
    * Interface CATICGMHybProject
    * Interface CATICGMHybTrim
    * Interface CATICGMSkinExtrapol
    * Interface CATICGMTopCompatible
    * Interface CATICGMTopExtractFace
    * Interface CATICGMTopExtrude
    * Interface CATICGMTopFaceReplaceSurface
    * Interface CATICGMTopPattern
    * Interface CATICGMTopSilhouette
  * GeometricObjects framework 
    * Class CATLISTP(CATCGMJournalInfo)
    * Macro or #define CATBodyMode
    * Macro or #define CATGeoCreateBodyDelayed
    * Macro or #define CATGeoCreateBodyNameDelayed
    * Macro or #define CATGeoCreateBodyName
    * Macro or #define CatBodyMode_Delayed
    * Macro or #define CatBodyMode_Working
  * ManufacturingInterfaces framework 
    * Interface CATIMfgGeomContours
    * Interface CATIMfgGeometryDefinition
    * Interface CATIMfgGeometryParameters
  * Mathematics framework 
    * Class CATLISTV(CATMathPlane)
    * Class CATLISTV(CATMathVector)
    * Enumeration CATCGMScaleCategory
    * Enumeration CATCGMScaleRange
  * ObjectSpecsModeler framework 
    * Class CATOsmCatalogAccessServices
  * PartInterfaces framework 
    * Global Function CATCreateCATIPrtThreadStandardServices
  * StructureInterfaces framework 
    * Interface CATIStrPPGExecLogSettingAtt
  * TopologicalOperators framework 
    * Global Function CATCreateDirNewBodyExtremum
  * TopologicalOperatorsLight framework 
    * Global Function CATCreateTopEuclidianDistanceTool
    * Global Function CATCreateTopGeodesicDistanceTool
  * VPMDesktopProduct framework 
    * Interface ENOVIChangeStatusOfWP
  * VPMInterfaces framework 
    * Interface CATICfgModificationUE
  * VPMPsImplSDM framework 
    * Interface CATIVpmLightVersion

[Top]

* * *

History Version: **1** [Sep 2012] | Document created  
---|---  
[Top]  
  
* * *

_Copyright © 1999-2012, Dassault Systèmes. All rights reserved._  
Special Notices [CAA V5 CATIA](../CAADocQuickRefs/CAADocSpecialNoticesCATIA.htm) | [CAA V5 DELMIA](../CAADocQuickRefs/CAADocSpecialNoticesDELMIA.htm) | [CAA V5 ENOVIA](../CAADocQuickRefs/CAADocSpecialNoticesENOVIA.htm)
