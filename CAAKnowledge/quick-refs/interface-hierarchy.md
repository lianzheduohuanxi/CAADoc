---
title: "接口继承树"
type: "quick-reference"
verified: true
---

# CATIA CAA V5 接口继承树

> 本文档展示接口的完整继承关系


## CATBaseUnknown (根接口)

- **CAA2DLAddin**: CAA2DLAddin → CATBaseUnknown
- **CAA2DLPrintToDraftingWatcher**: CAA2DLPrintToDraftingWatcher → CATBaseUnknown
- **CAAAfrGeneralWksAdn**: CAAAfrGeneralWksAdn → CATBaseUnknown
- **CAAAfrGeoAnalysisWkb**: CAAAfrGeoAnalysisWkb → CATBaseUnknown
- **CAAAfrGeoChartWindowAdn**: CAAAfrGeoChartWindowAdn → CATBaseUnknown
- **CAAAfrGeoClippingAdn**: CAAAfrGeoClippingAdn → CATBaseUnknown
- **CAAAfrGeoCreationWkb**: CAAAfrGeoCreationWkb → CATBaseUnknown
- **CAAAfrGeoOperationAdn**: CAAAfrGeoOperationAdn → CATBaseUnknown
- **CAAAfrGeometryWks**: CAAAfrGeometryWks → CATBaseUnknown
- **CAAAfrMRUManager**: CAAAfrMRUManager → CATBaseUnknown
- **CAAAniADImport**: CAAAniADImport → CATBaseUnknown
- **CAAAniAeroDynamicTransition**: CAAAniAeroDynamicTransition → CATBaseUnknown
- **CAAAniCataProvider**: CAAAniCataProvider → CATBaseUnknown
- **CAAAniCfg**: CAAAniCfg → CATBaseUnknown
- **CAAAniCfgTemplate**: CAAAniCfgTemplate → CATBaseUnknown
- **CAAAniCtxMenu**: CAAAniCtxMenu → CATBaseUnknown
- **CAAAniExplicitMP**: CAAAniExplicitMP → CATBaseUnknown
- **CAAAniFifDoc**: CAAAniFifDoc → CATBaseUnknown
- **CAACATPDMAllowLoad**: CAACATPDMAllowLoad → CATBaseUnknown
- **CAACV5EV5IntegrationToolbar**: CAACV5EV5IntegrationToolbar → CATBaseUnknown
- **CAACafGeometryEltSettingCtrl**: CAACafGeometryEltSettingCtrl → CATBaseUnknown
- **CAACafGeometryViewSettingCtrl**: CAACafGeometryViewSettingCtrl → CATBaseUnknown
- **CAACafViewerFeedbackManager**: CAACafViewerFeedbackManager → CATBaseUnknown
- **CAAConcatenateStringUserFunction**: CAAConcatenateStringUserFunction → CATBaseUnknown
- **CAACurveV4DataSaver**: CAACurveV4DataSaver → CATBaseUnknown
- **CAADataTranslator**: CAADataTranslator → CATBaseUnknown
- **CAADegGeoSDOAdn**: CAADegGeoSDOAdn → CATBaseUnknown
- **CAADlgBBEditorMessageHandler**: CAADlgBBEditorMessageHandler → CATBaseUnknown
- **CAADlgElement**: CAADlgElement → CATBaseUnknown
- **CAADlgObject**: CAADlgObject → CATBaseUnknown
- **CAADlgTessellation**: CAADlgTessellation → CATBaseUnknown
- **CAADrwAddin**: CAADrwAddin → CATBaseUnknown
- **CAAE5iUEDocumentName**: CAAE5iUEDocumentName → CATBaseUnknown
- **CAAEAfrActivateWorkbenchOnPart**: CAAEAfrActivateWorkbenchOnPart → CATBaseUnknown
- **CAAEAfrAliasDocument**: CAAEAfrAliasDocument → CATBaseUnknown
- **CAAEAfrCollection**: CAAEAfrCollection → CATBaseUnknown
- **CAAEAfrCommandHeaderRepForComboColor**: CAAEAfrCommandHeaderRepForComboColor → CATBaseUnknown
- **CAAEAfrCommandHeaderRepForEltCount**: CAAEAfrCommandHeaderRepForEltCount → CATBaseUnknown
- **CAAEAfrCommandHeaderRepForMRU**: CAAEAfrCommandHeaderRepForMRU → CATBaseUnknown
- **CAAEAfrContextualSubMenuPlane**: CAAEAfrContextualSubMenuPlane → CATBaseUnknown
- **CAAEAfrDocAlias**: CAAEAfrDocAlias → CATBaseUnknown
- **CAAEAfrDocumentChartWindow**: CAAEAfrDocumentChartWindow → CATBaseUnknown
- **CAAEAfrDocumentEdit**: CAAEAfrDocumentEdit → CATBaseUnknown
- **CAAEAfrEditor**: CAAEAfrEditor → CATBaseUnknown
- **CAAEAfrEditorDocument**: CAAEAfrEditorDocument → CATBaseUnknown
- **CAAEAfrInit**: CAAEAfrInit → CATBaseUnknown
- **CAAEAfrInitDocument**: CAAEAfrInitDocument → CATBaseUnknown
- **CAAEAfrPaletteOptions**: CAAEAfrPaletteOptions → CATBaseUnknown
- **CAAEAfrTemporaryObjectColor**: CAAEAfrTemporaryObjectColor → CATBaseUnknown
- **CAAEAniCfgInit**: CAAEAniCfgInit → CATBaseUnknown

_... 还有 297 个接口_

## IUnknown (根接口)

- **CAAICafGeometryEltSettingAtt**: CAAICafGeometryEltSettingAtt → IUnknown
- **CAAICafGeometryViewSettingAtt**: CAAICafGeometryViewSettingAtt → IUnknown

## 其他根接口


### CATStateCommand (61 个派生接口)

- CAAAniCreateOneImageCmd
- CAAAniExportCmd
- CAAAniSelectNodeCmd
- CAACafCenterGraphCmd
- CAACafCollapseExpandCmd
- CAACafSearchCmd
- CAADegAnalysisEltTypeCmd
- CAADegAnalysisLogCmd
- CAADegAnalysisNumericCmd
- CAADegClippingByBoxCmd
- CAADegClippingBySphereCmd
- CAADegCreateBoxCmd
- CAADegCreateCircleCmd
- CAADegCreateCylinder1Cmd
- CAADegCreateCylinder2Cmd
- CAADegCreateEllipseCmd
- CAADegCreateLineCmd
- CAADegCreatePlaneCmd
- CAADegCreatePointCmd
- CAADegCreatePolylineBy2TrianglesCmd
_... 还有 41 个接口_

### CATDlgDialog (40 个派生接口)

- CAAAfrBoundingElementCmd
- CAAAfrMRUAddElementCmd
- CAAAfrMRUSelElementCmd
- CAAAfrPlaneEditCmd
- CAAAfrPointEditDlg
- CAAAfrProgressTaskSampleCmd
- CAACafCircleWindowCmd
- CAACafSearchDlg
- CAADegAnalysisNumericDlg
- CAADegChoiceBehaviorDlg
- CAADegHstChartWndDlg
- CAADegPointEditor
- CAADegRadiusEllipseEditor
- CAADlgFrameReplaceDlg
- CAADlgMoreButtonDlg
- CAADlgMoreRadioDlg
- CAAGSMCircleSweepTgDlg
- CAAGSMSewSkinBasicDlg
- CAAMcaUdfLoftDlg
- CAAMmrBrowserCmdDlg
_... 还有 20 个接口_

### CATNotification (33 个派生接口)

- CAAAfrComboColorNotification
- CAAAfrMRUManagerNotification
- CAACafLaunchNextQueryNotification
- CAACircleSweepTgUIRemoveElement
- CAADegBoxCreationChoiceNotification
- CAADegEditor1DeselectedNotification
- CAADegEditor1SelectedNotification
- CAADlgAddNotification
- CAADlgBBMessageNotification
- CAADlgErrorNotification
- CAADlgModifNotification
- CAADlgRemoveNotification
- CAAGSMSewSkinBasicUIRemoveElement
- CAAPeoUserAlgorithmNotif
- CAAPriEditSketchNotification
- CAASysCollectionEmptyNotif
- CAASysCollectionFilledNotif
- CAASysCollectionModifNotif
- CAASysCollectionNotification
- CAASysRingNotification
_... 还有 13 个接口_

### CATExtIVisu (32 个派生接口)

- CAAECafVisuEllipse
- CAAEMmrCCDataExtensionVisu
- CAAEMmrMeasureSetVisu
- CAAEMmrMultiMeasureVisu
- CAAEPstINFVisuLine
- CAAEPstINFVisuPoint
- CAAEPstINFVisuRoot
- CAAEPstINFVisuWire
- CAAESchAppCntrVisu
- CAAESchAppCompVisu
- CAAESchAppRouteVisu
- CAAEV5V6ExtMmrCCDataExtensionVisu
- CAAEV5V6ExtMmrMeasureSetVisu
- CAAEV5V6ExtMmrMultiMeasureVisu
- CAAEVis2DGraphVisuForObject
- CAAEVis3DGeoVisuForCGRObject
- CAAEVis3DGeoVisuForCuboid
- CAAEVis3DGeoVisuForSet
- CAAEVis3DGeoVisuForSphere
- CAAEVisHistogramChartVisuForRootObject
_... 还有 12 个接口_

### CATCommand (23 个派生接口)

- CAA2DLPrintToDraftingCmd
- CAAAfrChangeViewNormalCmd
- CAAAfrDumpCmd
- CAAAfrPointEditCmd
- CAAAfrQueryExploreCmd
- CAACafViewerFeedbackCmd
- CAADegBoxPaletteChoiceCmd
- CAADlgContainer
- CAADlgModel
- CAADlgTimeOutCommand
- CAADlgViewPlot
- CAADlgViewScreen
- CAAMaiStandardMPCom
- CAAMaiStandardMPCom2
- CAAPeoUserCmd
- CAAPstCtxMenuCmd
- CAAPstINFEditCmdPoint
- CAAPuiPRDWorkshopAddinCmd
- CAAPuiPRDWorkshopConfigCmd
- CAAPuiPrsConfigAddinCmd
_... 还有 3 个接口_

### CATInteractiveApplication (21 个派生接口)

- CAABasicAuthenticationPanelApplication
- CAACafComboApplication
- CAADlgApplication
- CAADlgBBReceiverApplication
- CAADlgBBSenderApplication
- CAADlgBurgerApplication
- CAADlgDemoApplication
- CAADlgHelloApplication
- CAADlgInterApplication
- CAAGemBrowserApplication
- CAAIDDBasicCalcApplication
- CAAIDDBurgerApplication
- CAALifApplication
- CAALifApplication2
- CAAPrtApplication
- CAAVisBaseApplication
- CAAVisBasicApplication
- CAAVisManagerApplication
- CAAVisRepApplication
- CATInteractiveApplication
_... 还有 1 个接口_

### CATDlgDocument (18 个派生接口)

- CAABasicAuthenticationPanelWindow
- CAACafComboWindow
- CAADlgBBReceiverWindow
- CAADlgBBSenderWindow
- CAADlgBurgerWindow
- CAADlgDemoWindow
- CAADlgHelloWindow
- CAADlgInterWindow
- CAAGemBrowserDocument
- CAALifWindow
- CAALifWindow2
- CAAPrtDialog
- CAAVisBaseApplicationFrame
- CAAVisBasicWindow
- CAAVisManagerApplicationFrame
- CAAVisRepWindow
- CATDlgDocument
- CATTestListViewDocument

### CAAPspBaseEnv (13 个派生接口)

- CAAPspApplication
- CAAPspBaseEnv
- CAAPspBuildPart
- CAAPspConnectivity
- CAAPspFunctionPhysical
- CAAPspGroup
- CAAPspLightPart
- CAAPspLogicalLine
- CAAPspPart
- CAAPspProperties
- CAAPspServices
- CAAPspStretchable
- CAAPspUserProperties

### CATExtIEdit (11 个派生接口)

- CAAEAfrEditPlane
- CAAEAfrEditPoint
- CAAEGSMCircleSweepTgEdit
- CAAEGSMSewSkinBasicEdit
- CAAEMcaEditUdfLoft
- CAAEMmrCombinedCurveEdit
- CAAEMmrMultiMeasureEdit
- CAAEPstINFEditPoint
- CAAEV5V6ExtMmrCombinedCurveEdit
- CAAEV5V6ExtMmrMultiMeasureEdit
- CATExtIEdit

### CATIGenericFactory (10 个派生接口)

- CAAIAfrGeoAnalysisWkbFactory
- CAAIAfrGeoCreationWkbFactory
- CAAIAfrGeometryWksFactory
- CAAIAniConfigurationFactory
- CAAICafColorPropertyPageEdtFactory
- CAAICafElementPropertyPageEdtFactory
- CAAICafTexturePropertyPageEdtFactory
- CAAICafViewPropertyPageEdtFactory
- CAAIPuiPRDWorkshopConfigFactory
- CATIGenericFactory

### CATDlgFrame (10 个派生接口)

- CAACafColorPropertyPageDlg
- CAACafElementPropertyPageDlg
- CAACafTexturePropertyPageDlg
- CAACafViewPropertyPageDlg
- CAAPeoUserAlgoSettingsFrame
- CAASmiUserOperationGeometryPanel
- CAASmiUserOperationWithMAGeometryPanel
- CAAxPDMDRMRightEditionFrame
- CAAxPDMItemPreviewFrame
- CATDlgFrame

### CATExtIModelEvents (6 个派生接口)

- CAAEMmrCCDataExtensionModelEvent
- CAAEPstINFModelEvents
- CAAEV5V6ExtMmrCCDataExtensionModelEvent
- CAAEVisModelEvents
- CAAEVisModelEventsForObject
- CATExtIModelEvents

### CATExtIVisProperties (6 个派生接口)

- CAAEMmrMultiMeasureAndMeasureSetVisProperties
- CAAEPstINFVisPropertiesLine
- CAAEPstINFVisPropertiesPoint
- CAAEPstINFVisPropertiesWire
- CAAEV5V6ExtMmrMultiMeasureVisProperties
- CATExtIVisProperties

### CATIWorkbenchAddin (6 个派生接口)

- CAAIAfrGeoAnalysisWkbAddin
- CAAIAfrGeoCreationWkbAddin
- CAAIAfrGeometryWksAddin
- CAAIAniAddin
- CAAIPuiPRDWorkshopConfigAddin
- CATIWorkbenchAddin

### CATCommandHeader (6 个派生接口)

- CAA2DLHeader
- CAAAfrDumpCommandHeader
- CAAPuiPrsConfigAddinHeader
- CAATpiHeader
- CAAxPDMTSTCommandHeader
- CATCommandHeader

### CATFmFeatureCustomizationAdaptor (5 个派生接口)

- CAAEV5V6FmExtBehaviorCustomizationAdd
- CAAEV5V6FmExtBehaviorCustomizationSquare
- CAAEV5V6OsmBehaviorCustomizationAdd
- CAAEV5V6OsmBehaviorCustomizationSquare
- CATFmFeatureCustomizationAdaptor

### CATParmPublisherAdapter (5 个派生接口)

- CAAEMmrCCDataExtensionParmPublisher
- CAAEV5V6ExtMmrCCDataExtensionParmPublisher
- CAAEV5V6ExtMmrMultiMeasureParmPublisher
- CAALifMyPublisher
- CATParmPublisherAdapter

### CATKweInstanceAdapter (5 个派生接口)

- CAAEGSMFeaturesSplCkeInstance
- CAAEMmrCombCrvCkeFeature
- CAALifInstanceScrewExt
- CAAPeoUserAlgoInstance
- CATKweInstanceAdapter

### CAAPspBaseEnvProtected (5 个派生接口)

- CAACloPlacePart
- CAACloPspSpatialPhysical
- CAACloSpecPlacePart
- CAACloTransferElements
- CAAPspBaseEnvProtected

### CATEditor (5 个派生接口)

- CAACafColorPropertyPageEdt
- CAACafElementPropertyPageEdt
- CAACafTexturePropertyPageEdt
- CAACafViewPropertyPageEdt
- CATEditor
