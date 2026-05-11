---
title: "Setting Controller Reference"
category: "general"
module: "CAAScdInfTechArticles"
tags: ["CATImmLogonSettingCtrl", "CATIdeIgesSettingCtrl", "CATIColCollabIdentificationSettingCtrl", "CATIColCollabNetworkSettingCtrl", "CATIColConnectivitySettingCtrl"]
source_file: "Doc\online\CAAScdInfTechArticles\CAAInfTabPageList.htm"
converted: "2026-05-11T17:31:52.475701"
---

## Infrastructure
 
 | 
 
 ## Setting Controller Reference  
   
 ---|---  
   
 * * *
 
 This table lists the property pages that are associated with a setting controller.
 
     * The **Solution** , **Workbench** , and **Property Page** columns help you locate a given property page as it appears in the **Tools- >Options...** command dialog box. A None workbench indicates that the property page is displayed when clicking on the solution.
     * The **Object** column lists the Automation setting controller object(s) that manage(s) the setting attributes of this property page.
     * The **Type** column gives: 
       * The setting controller object type for a setting controller managed by a dedicated object.
       * The setting controller attribute documentation if the setting controller is managed by the generic SettingRepository object.
 
 Pass it as an argument of the `Item` method of the setting controller collection object when you want to create a setting controller object. Using Automation to administrate your settings in described in [1].
 
 Solutions | Workbenches | Property Pages | Objects | Types  
 ---|---|---|---|---  
 Analysis & Simulation | None | Post Processing | AnalysisPostProSettingAtt | CATSPMAnalysisPostProSettingCtrl  
 Reporting | AnalysisReportingSettingAtt | CATSPMAnalysisReportingSettingCtrl  
 Digital Mockup | DMU Fastening Review | Display | SettingRepository | [GBiWDisplay](../CAAScrSettings/GBiWDisplay.htm)  
 General | SettingRepository | [GBiWGeneral](../CAAScrSettings/GBiWGeneral.htm)  
 DMU Fitting | DMU Fitting | FittingSettingAtt | CATSiFiFittingSettingCtrl  
 DMU Manipulation | ManipSettingAtt | CATSiFiManipSettingCtrl  
 DMU Space Analysis | DMU Clash | SettingRepository | [DMUClashSettings](../CAAScrSettings/DMUClashSettings.htm)  
 DMU Clash - Detailed Computation | SettingRepository | [DMUClashDetailedComputation](../CAAScrSettings/DMUClashDetailedComputation.htm)  
 DMU Clash - Penetration | SettingRepository | [DMUClashPenetration](../CAAScrSettings/DMUClashPenetration.htm)  
 DMU Clash - Process | SettingRepository | [DMUClashProcess](../CAAScrSettings/DMUClashProcess.htm)  
 DMU Clash - Rule | SettingRepository | [DMUClashRule](../CAAScrSettings/DMUClashRule.htm)  
 DMU Distance | SettingRepository | [DMUDistance](../CAAScrSettings/DMUDistance.htm)  
 DMU Sectioning | SettingRepository | [SectioningRepository](../CAAScrSettings/SectioningRepository.htm)  
 DMU Tolerancing Review | DMU Tolerancing | DMUTolSettingAtt | CATTPSBrowserUIDMUTolSettingCtrl  
 SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 None | DMU 2D Workshop | SettingRepository | [DMU2DSettings](../CAAScrSettings/DMU2DSettings.htm)  
 DMU Marker | SettingRepository | [DMUMarker](../CAAScrSettings/DMUMarker.htm)  
 DMU Navigator | SettingRepository | [DMUNavigator](../CAAScrSettings/DMUNavigator.htm)  
 SettingRepository | [DMUSAC](../CAAScrSettings/DMUNavigator.htm)  
 General | SettingRepository | [DMUGeneral](../CAAScrSettings/DMUGeneral.htm)  
 Multiprocess Settings | SettingRepository | [Multiprocess](../CAAScrSettings/Multiprocess.htm)  
 Overlay Settings | SettingRepository | [DMUOverlay](../CAAScrSettings/DMUOverlay.htm)  
 Digital Process for Manufacturing | DPM Shop Floor Viewer  | General | SettingsGeneralSettingAtt | DNBSHFSettingsGeneralSettingCtrl  
 None | Compare Tool | SettingRepository | [DNBDpmCompareTool](../CAAScrSettings/DNBDpmCompareTool.htm)  
 GANTT Chart | SettingRepository | [DNBGanttSettings](../CAAScrSettings/DNBGanttSettings.htm)  
 Libraries | LibTabSettingAtt | CATSPPLibTabSettingCtrl  
 MBOM | SettingRepository | [DNBBomSettings](../CAAScrSettings/DNBBomSettings.htm)  
 Manufacturing Hub | MfgHubSettingAtt | DNBMHIMfgHubSettingCtrl  
 PERT Chart | SettingRepository | [PERTConfig](../CAAScrSettings/PERTConfig.htm)  
 PPR Navigator | NavigatorSettingAtt | DNBPRMNavigatorSettingCtrl  
 Part Consumption | SettingRepository | [DNBDpmPartConsumptionSettings](../CAAScrSettings/DNBDpmPartConsumptionSettings.htm)  
 State Management | SettingRepository | [DNBStateSettings](../CAAScrSettings/DNBStateSettings.htm)  
 Tree | TreeTabSettingAtt | CATSPPTreeTabSettingCtrl  
 Verification | SettingRepository | [DNBSimStatic](../CAAScrSettings/DNBSimStatic.htm)  
 Structure Manufacturing Preparation | Activities | SettingRepository | [DpmMfgToolsSettings](../CAAScrSettings/DpmMfgToolsSettings.htm)  
 Features | SettingRepository | [DpmMfgSettings](../CAAScrSettings/DpmMfgSettings.htm)  
 Templates | SettingRepository | [DpmMfgTemplatesSettings](../CAAScrSettings/DpmMfgTemplatesSettings.htm)  
 DPM - Assembly Process Planner | Commands | SettingRepository | [DNBDpmAPNSettings](../CAAScrSettings/DNBDpmAPNSettings.htm)  
 DPM - Fastening Process Planner | Commands | SettingRepository | [DNBDpmBIWSettings](../CAAScrSettings/DNBDpmBIWSettings.htm)  
 Fastener Attributes | SettingRepository | [DNBDpmBIWSettings](../CAAScrSettings/DNBDpmBIWSettings.htm)  
 Fastener Visualization | SettingRepository | [DNBDpmBIWSettings](../CAAScrSettings/DNBDpmBIWSettings.htm)  
 DPM - Shop Order Release | Image Capture Settings | ImgPropertySettingAtt | DNBSORImgPropertySettingCtrl  
 Order Create Settings | GeneralPropertySettingAtt | DNBSORGeneralPropertySettingCtrl  
 DPM - Structure Lofting | Activities | SettingRepository | [DpmStrToolsSettings](../CAAScrSettings/DpmStrToolsSettings.htm)  
 Features | SettingRepository | [DpmStrSettings](../CAAScrSettings/DpmStrSettings.htm)  
 Templates | SettingRepository | [DpmStrTemplatesSettings](../CAAScrSettings/DpmStrTemplatesSettings.htm)  
 DPM - Work Instructions | General | SettingRepository | [DNBWorkGeneral](../CAAScrSettings/DNBWorkGeneral.htm)  
 Work Instruction Text 3D Display | SettingRepository | [DNBWKIWorkRenderSettings](../CAAScrSettings/DNBWKIWorkRenderSettings.htm)  
 MSD - Manufacturing System Definition | General | SettingRepository | [DNBMSDResUtilSettings](../CAAScrSettings/DNBMSDResUtilSettings.htm)  
 ENOVIA V5 VPM | None | ENOVIA V5 VPM Logon | LogonSettingAtt | CATImmLogonSettingCtrl  
 Product View Result | SettingRepository | [PVRProperties](../CAAScrSettings/PVRProperties.htm)  
 Equipment & Systems | Electrical 3D Design Assembly | General | SettingRepository | [ElectricalLibraryAccess1](../CAAScrSettings/ElectricalLibraryAccess1.htm)  
 Harness Flattening | SettingRepository | [ElectricalHarnessFlattening](../CAAScrSettings/ElectricalHarnessFlattening.htm)  
 Harness Management | SettingRepository | [ElectricalHarnessInstallation](../CAAScrSettings/ElectricalHarnessInstallation.htm)  
 Electrical Assembly Design | Electrical Library Access | SettingRepository | [ElectricalLibraryAccess2](../CAAScrSettings/ElectricalLibraryAccess2.htm)  
 General | SettingRepository | [ElectricalLibraryAccess1](../CAAScrSettings/ElectricalLibraryAccess1.htm)  
 Electrical Harness Flattening | General | SettingRepository | [ElectricalHarnessFlattening](../CAAScrSettings/ElectricalHarnessFlattening.htm)  
 Electrical Harness Installation | Harness Management | SettingRepository | [ElectricalHarnessInstallation](../CAAScrSettings/ElectricalHarnessInstallation.htm)  
 None | Electrical Mapping | SettingRepository | [ElectricalCommon](../CAAScrSettings/ElectricalCommon.htm)  
 Electrical Process Interfacing | SettingRepository | [EleciXFIntegration](../CAAScrSettings/EleciXFIntegration.htm)  
 Structure Discipline | Equipment Support Structures - General | ColorESSObjectSettingAtt | CATStrColorESSObjectSettingCtrl  
 MaterialESSObjectSettingAtt | CATStrMaterialESSObjectSettingCtrl  
 PathESSRessourcesSettingAtt | CATStrPathESSRessourcesSettingCtrl  
 TypeESSObjectSettingAtt | CATStrTypeESSObjectSettingCtrl  
 Structure Functional System Design - General | EndCutESSObjectSettingAtt | CATStrEndCutESSObjectSettingCtrl  
 Ergonomics Design & Analysis | Human Activity Analysis | Ergonomic Analysis | HAAErgoAnalysisSettingAtt | SWKHmiHAAErgoAnalysisSettingCtrl  
 Human Builder | Display | HBRDisplaySettingAtt | SWKHmiHBRDisplaySettingCtrl  
 General | HBRGeneralSettingAtt | SWKHmiHBRGeneralSettingCtrl  
 Vehicle Occupant Accommodation | SettingRepository | [CATHBRVOASetting](../CAAScrSettings/CATHBRVOASetting.htm)  
 Human Measurements Editor | Anthropometry | HMEAnthroSettingAtt | SWKHmiHMEAnthroSettingCtrl  
 Human Posture Analysis | Postural Score | HPAPosturalScoreSettingAtt | SWKHmiHPAPosturalScoreSettingCtrl  
 Human Task Simulation | Cut Copy Paste | HtsCCPSettingAtt | DNBHtsCCPSettingCtrl  
 General | HtsGeneralSettingAtt | DNBHtsGeneralSettingCtrl  
 HumanTask Display | HtsTaskDisplaySettingAtt | DNBHtsTaskDisplaySettingCtrl  
 Joint Speed | HtsJointSpeedSettingsAtt | DNBHtsJointSpeedSettingCtrl  
 General | Compatibility | 3D XML | Export3DXmlSettingAtt | CAT3DXmlExportSettingCtrl  
 CCD | SettingRepository | [CCDCompatibilitySettings](../CAAScrSettings/CCDCompatibilitySettings.htm)  
 DELMIA D5 | ImportD5SettingAtt | DNBD5IImportD5SettingCtrl  
 DXF | SettingRepository | [DXF](../CAAScrSettings/DXF.htm)  
 Electrical | SettingRepository | [E3DMigrationOptions](../CAAScrSettings/E3DMigrationOptions.htm)  
 ENOVIA V6/3DEXPERIENCE | V6SettingAtt | ENO3DEXPSettingCtrl  
 External Formats | MultiCADSettingAtt | CATMciMultiCADSettingCtrl  
 IGES | IgesSettingAtt | CATIdeIgesSettingCtrl  
 IGES 2D | SettingRepository | [IG2](../CAAScrSettings/IG2.htm)  
 Migration Batch | MigrBatchSettingAtt | CATV4IMigrBatchSettingCtrl  
 STEP | StepSettingAtt | CATSdeStepSettingCtrl  
 Saving as V4 Data | V4WritingSettingAtt | CATV4IV4WritingSettingCtrl  
 V4 Data Reading | InteropSettingAtt | CATV4IInteropSettingCtrl  
 V4 V5 DRAW | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 V4 V5 SPACE | V4V5SpaceSettingAtt | CATV4IV4V5SpaceSettingCtrl  
 V4 V5 SPEC | SpecV4SettingAtt | CATV4ISpecV4SettingCtrl  
 V4 V5 TUBING | TubingMigrSettingAtt | CATV4ITubingMigrSettingCtrl  
 VRML | VrmlSettingAtt | CATVisVrmlSettingCtrl  
 Display | Navigation | VisualizationSettingAtt | CATVizVisualizationSettingCtrl  
 Performance | VisualizationSettingAtt | CATVizVisualizationSettingCtrl  
 Tree Appearance | TreeVizManipSettingAtt | CATCafTreeVizManipSettingCtrl  
 Tree Manipulation | TreeVizManipSettingAtt | CATCafTreeVizManipSettingCtrl  
 Visualization | VisualizationSettingAtt | CATVizVisualizationSettingCtrl  
 None | Document | DLNameSettingAtt | CATSysDLNameSettingCtrl  
 General | DisconnectionSettingAtt | CATSysDisconnectionSettingCtrl  
 GeneralSessionSettingAtt | CATCafGeneralSessionSettingCtrl  
 MemoryWarningSettingAtt | CATSysMemoryWarningSettingCtrl  
 Help | DocumentationSettingAtt | CATCafDocumentationSettingCtrl  
 Licensing | LicenseSettingAtt | CATSysLicenseSettingCtrl  
 Macros | MacrosSettingAtt | CATScriptMacrosSettingCtrl  
 PCS | SettingRepository | [GeneralPCS](../CAAScrSettings/GeneralPCS.htm)  
 Printers | PrintersSettingAtt | CATPrtPrintersSettingCtrl  
 Search | SearchSettingAtt | CATCafSearchSettingCtrl  
 Server Manager | SettingRepository | ServerManager  
 Shareable Products | DynLicenseSettingAtt | CATSysDynLicenseSettingCtrl  
 Statistics | AccesslogStatisticsSettingAtt | CATSysAccesslogStatisticsSettingCtrl  
 CommandStatisticsSettingAtt | CATSysCommandStatisticsSettingCtrl  
 ErrorlogStatisticsSettingAtt | CATSysErrorlogStatisticsSettingCtrl  
 GlobalStatisticsSettingAtt | CATSysGlobalStatisticsSettingCtrl  
 PCSStatisticsSettingAtt | CATSysPCSStatisticsSettingCtrl  
 ServerStatisticsSettingAtt | CATSysServerStatisticsSettingCtrl  
 SessionStatisticsSettingAtt | CATSysSessionStatisticsSettingCtrl  
 WorkbenchStatisticsSettingAtt | CATSysWorkbenchStatisticsSettingCtrl  
 Parameters and Measure | Constraints and Dimensions | SettingRepository | [ConstraintsAndDimensions](../CAAScrSettings/ConstraintsAndDimensions.htm)  
 Knowledge | KnowledgeSheetSettingAtt | CATLieKnowledgeSheetSettingCtrl  
 Knowledge Environment | LanguageSheetSettingAtt | CATLieLanguageSheetSettingCtrl  
 Measure Tools | SettingRepository | [MeasureSettings](../CAAScrSettings/MeasureSettings.htm)  
 Parameters Tolerance | ToleranceSheetSettingAtt | CATLieToleranceSheetSettingCtrl  
 Report Generation | ReportGenerationSheetSettingAtt | CATLieReportGenerationSheetSettingCtrl  
 Scale | SettingRepository | [ShapeDesignGeometricalScale](../CAAScrSettings/ShapeDesignGeometricalScale.htm)  
 Units | UnitsSheetSettingAtt | CATLieUnitsSheetSettingCtrl  
 Infrastructure | 3D Annotations Infrastructure | Administration | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Annotation | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Display | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Manipulators | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Tolerancing | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 View Annotation Plane | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Collaboration Infrastructure | Connectivity | ConnectivitySettingAtt | CATIColConnectivitySettingCtrl  
 Identification | CollabIdentificationSettingAtt | CATIColCollabIdentificationSettingCtrl  
 Network | CollabNetworkSettingAtt | CATIColCollabNetworkSettingCtrl  
 DELMIA Infrastructure | Analysis | AnalysisSettingAtt | DNBSimAnalysisSettingCtrl  
 Device Analysis | DevAnalysisSettingAtt | DNBSimDevAnalysisSettingCtrl  
 IO Sensor | IOAnalysisSettingAtt | DNBSimIOAnalysisSettingCtrl  
 Robot Analysis | RobAnalysisSettingAtt | DNBSimRobAnalysisSettingCtrl  
 Simulation | SimulationSettingAtt | DNBSimSimulationSettingCtrl  
 Simulation Trace | SimTraceSettingAtt | DNBSimSimTraceSettingCtrl  
 Material Library | Shading Display | VisualizationSettingAtt | CATVizVisualizationSettingCtrl  
 Part Infrastructure | Display | PartInfrastructureSettingAtt | CATMmuPartInfrastructureSettingCtrl  
 General | PartInfrastructureSettingAtt | CATMmuPartInfrastructureSettingCtrl  
 Part Document | PartInfrastructureSettingAtt | CATMmuPartInfrastructureSettingCtrl  
 Photo Studio | Display | SettingRepository | [RenderingSettingsDisplay](../CAAScrSettings/RenderingSettingsDisplay.htm)  
 General | SettingRepository | [RenderingSettingsGeneral](../CAAScrSettings/RenderingSettingsGeneral.htm)  
 Output | SettingRepository | [RenderingSettingsOutput](../CAAScrSettings/RenderingSettingsOutput.htm)  
 Satellites | SettingRepository | [RenderingSettingsSatellites](../CAAScrSettings/RenderingSettingsSatellites.htm)  
 Sticker | SettingRepository | [RenderingSettingsSticker](../CAAScrSettings/RenderingSettingsSticker.htm)  
 Product Structure | Cache Management | CacheSettingAtt | CATSysCacheSettingCtrl  
 Cgr Management | CacheSettingAtt | CATSysCacheSettingCtrl  
 VisualizationSettingAtt | CATVizVisualizationSettingCtrl  
 Real Time Rendering | Display | SettingRepository | [RenderingSettingsDisplay](../CAAScrSettings/RenderingSettingsDisplay.htm)  
 General | SettingRepository | [RenderingSettingsGeneral](../CAAScrSettings/RenderingSettingsGeneral.htm)  
 Sticker | SettingRepository | [RenderingSettingsSticker](../CAAScrSettings/RenderingSettingsSticker.htm)  
 Knowledgeware | Business Process Knowledge Template | Business Knowledge Template | BehaviorSettingAtt | CATBKTBehaviorSettingCtrl  
 Product Functional Definition | General | FunctionalSystemSettingAtt | CATFsyFunctionalSystemSettingCtrl  
 Machining | None | General | SettingRepository | [NCMfgDisplay](../CAAScrSettings/NCMfgDisplay.htm)  
 Operation | SettingRepository | [NCMfgOperation](../CAAScrSettings/NCMfgOperation.htm)  
 Output | SettingRepository | [NCMfgOutput](../CAAScrSettings/NCMfgOutput.htm)  
 Photo Video | SettingRepository | [NCMfgSimulation](../CAAScrSettings/NCMfgSimulation.htm)  
 Program | SettingRepository | [NCMfgAutosequence](../CAAScrSettings/NCMfgAutosequence.htm)  
 Resources | SettingRepository | [NCMfgResources](../CAAScrSettings/NCMfgResources.htm)  
 Machining Simulation | NC Machine Tool Simulation | General | SettingRepository | [DNBVNCSettings](../CAAScrSettings/DNBVNCSettings.htm)  
 Simulation | SettingRepository | [DNBVNCSimulSettings](../CAAScrSettings/DNBVNCSimulSettings.htm)  
 Mechanical Design | 2D Layout for 3D Design | Administration | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.htm)  
 Display | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.htm)  
 Geometry | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.htm)  
 View Creation | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.htm)  
 Visualization | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.htm)  
 Aerospace Sheet Metal Design | Display | ViewCharacteristicCurvesSettingAtt | CATStmViewCharacteristicCurvesSettingCtrl  
 General | CatalogSHMObjectSettingAtt | CATStmCatalogSHMObjectSettingCtrl  
 Assembly Design | Constraints | AsmConstraintSettingAtt | CATAsmConstraintSettingCtrl  
 SettingRepository | [AssemblyConstraints](../CAAScrSettings/AssemblyConstraints.htm)  
 General | AsmGeneralSettingAtt | CATAsmGeneralSettingCtrl  
 SettingRepository | [AssemblyGeneral](../CAAScrSettings/AssemblyGeneral.htm)  
 Drafting | Administration | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Annotation and Dress-Up | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Dimension | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 General | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Generation | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Geometry | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Layout | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Manipulators | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 View | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.htm)  
 Functional Tolerancing & Annotation | Administration | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Annotation | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Constructed Geometry | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Dimension | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Display | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Manipulators | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Tolerances | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Tolerancing | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 View Annotation Plane | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.htm)  
 Generative Sheetmetal Design | General | CatalogSHMObjectSettingAtt | CATStmCatalogSHMObjectSettingCtrl  
 Mold Tooling Design | Add Remove | SettingRepository | [MoldDesignBodies](../CAAScrSettings/MoldDesignBodies.htm)  
 Catalogs | SettingRepository | [MoldDesignCatalog](../CAAScrSettings/MoldDesignCatalog.htm)  
 Component | SettingRepository | [MoldDesignComponent](../CAAScrSettings/MoldDesignComponent.htm)  
 Miscellaneous | SettingRepository | [MoldDesignMisc](../CAAScrSettings/MoldDesignMisc.htm)  
 Split | SettingRepository | [MoldDesignSplit](../CAAScrSettings/MoldDesignSplit.htm)  
 Viewer Mapping | SettingRepository | [MoldDesignMapping](../CAAScrSettings/MoldDesignMapping.htm)  
 Sketcher | Sketcher | SettingRepository | [Sketcher](../CAAScrSettings/Sketcher.htm)  
 Structure Design | General | ColorSTDObjectSettingAtt | CATStrColorSTDObjectSettingCtrl  
 PPGExecLogSettingAtt | CATStrPPGExecLogSettingCtrl  
 Resource Detailing | None | 2D Graph | Tree2DGraphSettingAtt | DNBIgpTree2DGraphSettingCtrl  
 Action Libraries | UserActionsLibSettingAtt | DNBIgpUserActionsLibSettingCtrl  
 Frames Visualization | SettingRepository | [DNBDBldFramesOfIntSettings](../CAAScrSettings/DNBDBldFramesOfIntSettings.htm)  
 Graphic Reporting | FASReportingSettingAtt | DNBIgpFASReportingSettingCtrl  
 Offline Programming | IgpOlpSettingAtt | DNBIgpOlpSettingCtrl  
 RRS | RRSSettingAtt | DNBRobRRSSettingCtrl  
 Resource Layout | SettingRepository | [DNBMfgLayoutSettings](../CAAScrSettings/DNBMfgLayoutSettings.htm)  
 Robot Task Display | TaskVisuSettingAtt | DNBIgpTaskVisuSettingCtrl  
 Teach Dialog Settings | TeachDlgSettingAtt | DNBIgpTeachDlgSettingCtrl  
 Shape | Automotive BiW Fastening | Display | SettingRepository | [GBiWDisplay](../CAAScrSettings/GBiWDisplay.htm)  
 General | SettingRepository | [GBiWGeneral](../CAAScrSettings/GBiWGeneral.htm)  
 Automotive Class A | Tolerance | SettingRepository | [FreeStyleGlobalUserSettings](../CAAScrSettings/FreeStyleGlobalUserSettings.htm)  
 Digitized Shape Editor | Display Modes | SettingRepository | [DSESettingsGeneral](../CAAScrSettings/DSESettingsGeneral.htm)  
 SettingRepository | [DSESettingsDisplayModes](../CAAScrSettings/DSESettingsDisplayModes.htm)  
 General | SettingRepository | [DSESettingsGeneral](../CAAScrSettings/DSESettingsGeneral.htm)  
 SettingRepository | [DSESettingsDisplayModes](../CAAScrSettings/DSESettingsDisplayModes.htm)  
 FreeStyle | General | SettingRepository | [FreeStyleGlobalUserSettings](../CAAScrSettings/FreeStyleGlobalUserSettings.htm)  
 Manipulators | SettingRepository | [FreeStyleGlobalUserSettings](../CAAScrSettings/FreeStyleGlobalUserSettings.htm)  
 Imagine & Shape | Display | SettingRepository | [CATDesSettingDisplay](../CAAScrSettings/CATDesSettingDisplay.htm)  
 General | SettingRepository | [CATDesSettingGeneral](../CAAScrSettings/CATDesSettingGeneral.htm)  
 Shape Sculptor | Parameters | SettingRepository | [StyGlobalSettings](../CAAScrSettings/StyGlobalSettings.htm)  
   
 [Top]
 
 * * *
 
 ### References
 
 [1] | [Administrating Settings with Automation](CAAInfSettings.htm)  
 ---|---  
   
 _Copyright 1999-2013, Dassault Systmes. All rights reserved._
