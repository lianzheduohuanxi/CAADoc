---
```vbscript
title: "CAA Authorized APIs Replacing ProtectedInterfaces"
category: use-case
module: "CAACenAPIChangesR23"
version: "V5R23"
tags: ["CATIDOMElement", "CATIDrwSectionCallout", "CATIKinMechanism", "CATIBuildPath", "CATIMfgPrismaticReworkArea", "CATIMfResultManagement", "CATINewStream", "CATIDegreesOfFreedom", "CATILiteralsRoot", "CATIAfrCommandHeaderRep", "CATICkeFunctionFactory", "CATIEwrRouteSegment", "CATIArrNode", "CATIUuid", "CATIDOMText", "CATIRouNode", "CATIMfgActivityContainer", "CATIMfPartExtReferences", "CATISysCacheSettingAtt", "CATIDoF"]
source_file: "Doc/online/CAACenAPIChangesR23/CAACenAuditReplacingAPIs.htmmd"
converted: "2026-05-11T17:33:51.770133"
```

---
# CAA V5 Encyclopedia

|
##

|
### CAA Authorized APIs Replacing ProtectedInterfaces

_Mapping reported ProtectedInterfaces to CAA Authorized APIs_
---|---|---
Technical Article

* * *

Technical Article
```vbscript
If you were using ... | Use instead ...

```

```vbscript
If you were using ... | Use instead ...
AdvancedTopologicalOpe | CATCreateSimilarCurve | AdvancedTopologicalOpe |  CATCreateTopSimilarCurve
AnalysisMeshingModel | CATMSHSupportManager | AnalysisMeshingModel |  CATIMSHAssociativity
ApplicationFrame | CATAfrDialogStdRep | ApplicationFrame |  CATIAfrCommandHeaderRep
ApplicationFrame | CATCheckHeader | ApplicationFrame |  CATAfrCheckHeaderAccessor
ApplicationFrame | CATCmdRep | ApplicationFrame |  CATAfrDialogCommandHeader
ApplicationFrame | CATDiaNoEngine | ApplicationFrame |  CATAfrEmptyUndoRedoStacks,  CATAfrLockUndoRedoTransactions, and  CATAfrUnlockUndoRedoTransactions in CATAfrUndoRedoServices.h
ApplicationFrame | CATFrmDialog | Dialog |  CATDlgDialog
ApplicationFrame | CATIInPlaceSiteVeto | ApplicationFrame | Include CATAfrCATIInPlaceSiteVetoIID.h
ApplicationFrame | CATWorkbenchServices | ApplicationFrame |  CATAfrStartWorkbench and  CATAfrGetWorkbenchIdentifierFromNLSName in CATAfrWorkbenchServices.h
BasicTopologicalOpe | CATBodyFromLengthOnWire | BasicTopologicalOpe |  CATComputePointOnWire
BasicTopologicalOpe | CATGlobalRatio | BasicTopologicalOpe |  CATComputePointOnWire
BasicTopologicalOpe | CreateGeodesicLinePtPt | BasicTopologicalOpe |  CATCreateGeodesicLinePtPt
BasicTopologicalOpe | StaticGlobalRatio | BasicTopologicalOpe |  CATComputePointOnWire
CATArrangementInterfaces | CATIArrConnectorManager | CATArrangementInterfaces |  CATIArrConnectorFactory
CATArrangementInterfaces | CATIRouNode | CATArrangementInterfaces |  CATIArrNode
CATArrangementInterfaces | CATIRouSegmentsString | CATArrangementInterfaces |  CATIArrSegmentsString
CATArrangementInterfaces | CATIRouString | CATArrangementInterfaces |  CATIArrSegmentsString
CATIAApplicationFrame | CATISelectMoveSelector | CATIAApplicationFrame | Include CATCafCATISelectMoveSelectorIID.h
ConstraintModeler | CATIDoF | ConstraintModeler |  CATIDegreesOfFreedom
DraftingInterfaces | CATIDrwSectionCallout | DraftingInterfaces |  CATIDrwCalloutAccess
DraftingInterfaces | CATIOwner | DraftingInterfaces |  CATIDftGenViewFactory
DraftingInterfaces | CATISection | DraftingInterfaces |  CATIDftGenViewFactory
ElectricalInterfaces | CATIElecBundleSegment | ElecRoutingItf |  CATIEwrRouteSegment
KinematicsInterfaces | CATISiMechUpdate | KinematicsInterfaces |  CATIKinMechanism
KnowledgeInterfaces | CATILiteralsRoot | KnowledgeInterfaces |  CATICkeFunctionFactory and  CATIParmPublisher
KnowledgeModeler | CATCkeServices | KnowledgeInterfaces |  CATICkeFunctionFactory
LiteralFeatures | CATCkeNumbersDisplay | KnowledgeInterfaces |  CATILieUnitsSheetSettingAtt
ManufacturingInterfaces | CATIMfg2DRAFeature | ManufacturingInterfaces |  CATIMfgPrismaticReworkArea
ManufacturingInterfaces | CATIMfgActivityContainer | ManufacturingInterfaces |  CATIMfgManufacturingFactories
ManufacturingInterfaces | CATIMfgFeatureFactory | ManufacturingInterfaces |  CATIMfgMachiningFeatureFactory
ManufacturingInterfaces | CATIMfgSequence | ManufacturingInterfaces |  CATIAMachiningProcess
MechanicalModeler | CATIMechanicalImportFactory | MechanicalModeler |  CATMmrInterPartCopy
MechanicalModeler | CATIMfInternalImportFactory | MechanicalModeler |  CATMmrInterPartCopy
MechanicalModeler | CATIMfPartExtReferences | InfInterfaces |  CATIASendToService
MechanicalModeler | CATIMfScopeAccess | MecModInterfaces |  CATIMfResultManagement
MechanicalModeler | CATISlaveGeometry | MecModInterfaces |  CATIBRepAccess::GetInitialMasterFeature
MechanicalModeler | CATMfAlgoConfigServices | MechanicalModeler |  CATMmrAlgoConfigServices
MecModInterfaces | CATIPrtManagement | MecModInterfaces |  CATIPrtPart
ObjectModelerBase | CATEOmbProperty | ObjectModelerBase |  CATIProperty is now implemented on TTRS
ObjectModelerBase | CATINewStream | ObjectSpecsModeler |  CATIOsmVolatileContainer
ObjectModelerBase | CATIUuid | CATxPDMInterfaces |  CATxPDMFileServices and  CATxPDMSessionServices
ProductStructure | CATIIconProvider | ProductStructureInterfaces |  CATICustoIconProduct
PSNInteroperability | CATVPMDocServices |  PSNInteroperability | Functions in CATBatchServices.h
SketcherToolsUI | CATSktEditorToolbox | SketcherToolsUI |  CATSketcherToolbox
System | CATCacheSetting | System |  CATISysCacheSettingAtt
System | CATErrorInits |  BatchInfrastructure | Classes CATBatch*
Visualization | CATIPathAccess | InteractiveInterfaces |  CATIBuildPath
VisualizationBase | CATOutlineFont | VisualizationBase |  CATFont::sGetFontOtherGeneralInformation
VPMDesktopObjects | VPMTransferObj::ChangeObjOwnerWithDesc | ENOVInterfaces |  ENOVITransfer
VPMSTEPExchanges | StdExtractor | VPMSTEPExchanges |  ENOVIExDataServices
XMLParser | DOM_Document | XMLParser |  CATIDOMDocument
XMLParser | DOM_Element | XMLParser |  CATIDOMElement
XMLParser | DOM_Node | XMLParser |  CATIDOMNode
XMLParser | DOM_NodeList | XMLParser |  CATIDOMNodeList
XMLParser | DOM_Text | XMLParser |  CATIDOMText
XMLParser | DOMString | System |  CATUnicodeString

Some L0 interfaces are also temporarily provided to solve the following errors:

If you were using ... | Use instead ...
```

Some L0 interfaces are also temporarily provided to solve the following errors:
If you were using ... | Use instead ...
CATCloudEditorInterfaces | CATICldFactory | CATCloudEditorInterfaces | CATICldCAAFactory and CATICLDGeom
CATPDMBaseInterfaces | CATILCADocEnvServices | VPMInterfaces | ENOVIUERunInteropServerCode

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
