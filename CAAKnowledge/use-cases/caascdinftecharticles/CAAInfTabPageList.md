---
title: "Setting Controller Reference"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATImmLogonSettingCtrl", "CATIdeIgesSettingCtrl", "CATIColCollabIdentificationSettingCtrl", "CATIColCollabNetworkSettingCtrl", "CATIColConnectivitySettingCtrl"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfTabPageList.md"
converted: "2026-05-11T17:31:52.475701"
---
## Infrastructure
 
 | 
 ## Setting Controller Reference  
   
   
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
 Digital Mockup | DMU Fastening Review | Display | SettingRepository | [GBiWDisplay](../CAAScrSettings/GBiWDisplay.md)  
 General | SettingRepository | [GBiWGeneral](../CAAScrSettings/GBiWGeneral.md)  
 DMU Fitting | DMU Fitting | FittingSettingAtt | CATSiFiFittingSettingCtrl  
 DMU Manipulation | ManipSettingAtt | CATSiFiManipSettingCtrl  
 DMU Space Analysis | DMU Clash | SettingRepository | [DMUClashSettings](../CAAScrSettings/DMUClashSettings.md)  
 DMU Clash - Detailed Computation | SettingRepository | [DMUClashDetailedComputation](../CAAScrSettings/DMUClashDetailedComputation.md)  
 DMU Clash - Penetration | SettingRepository | [DMUClashPenetration](../CAAScrSettings/DMUClashPenetration.md)  
 DMU Clash - Process | SettingRepository | [DMUClashProcess](../CAAScrSettings/DMUClashProcess.md)  
 DMU Clash - Rule | SettingRepository | [DMUClashRule](../CAAScrSettings/DMUClashRule.md)  
 DMU Distance | SettingRepository | [DMUDistance](../CAAScrSettings/DMUDistance.md)  
 DMU Sectioning | SettingRepository | [SectioningRepository](../CAAScrSettings/SectioningRepository.md)  
 DMU Tolerancing Review | DMU Tolerancing | DMUTolSettingAtt | CATTPSBrowserUIDMUTolSettingCtrl  
 SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 None | DMU 2D Workshop | SettingRepository | [DMU2DSettings](../CAAScrSettings/DMU2DSettings.md)  
 DMU Marker | SettingRepository | [DMUMarker](../CAAScrSettings/DMUMarker.md)  
 DMU Navigator | SettingRepository | [DMUNavigator](../CAAScrSettings/DMUNavigator.md)  
 SettingRepository | [DMUSAC](../CAAScrSettings/DMUNavigator.md)  
 General | SettingRepository | [DMUGeneral](../CAAScrSettings/DMUGeneral.md)  
 Multiprocess Settings | SettingRepository | [Multiprocess](../CAAScrSettings/Multiprocess.md)  
 Overlay Settings | SettingRepository | [DMUOverlay](../CAAScrSettings/DMUOverlay.md)  
 Digital Process for Manufacturing | DPM Shop Floor Viewer  | General | SettingsGeneralSettingAtt | DNBSHFSettingsGeneralSettingCtrl  
 None | Compare Tool | SettingRepository | [DNBDpmCompareTool](../CAAScrSettings/DNBDpmCompareTool.md)  
 GANTT Chart | SettingRepository | [DNBGanttSettings](../CAAScrSettings/DNBGanttSettings.md)  
 Libraries | LibTabSettingAtt | CATSPPLibTabSettingCtrl  
 MBOM | SettingRepository | [DNBBomSettings](../CAAScrSettings/DNBBomSettings.md)  
 Manufacturing Hub | MfgHubSettingAtt | DNBMHIMfgHubSettingCtrl  
 PERT Chart | SettingRepository | [PERTConfig](../CAAScrSettings/PERTConfig.md)  
 PPR Navigator | NavigatorSettingAtt | DNBPRMNavigatorSettingCtrl  
 Part Consumption | SettingRepository | [DNBDpmPartConsumptionSettings](../CAAScrSettings/DNBDpmPartConsumptionSettings.md)  
 State Management | SettingRepository | [DNBStateSettings](../CAAScrSettings/DNBStateSettings.md)  
 Tree | TreeTabSettingAtt | CATSPPTreeTabSettingCtrl  
 Verification | SettingRepository | [DNBSimStatic](../CAAScrSettings/DNBSimStatic.md)  
 Structure Manufacturing Preparation | Activities | SettingRepository | [DpmMfgToolsSettings](../CAAScrSettings/DpmMfgToolsSettings.md)  
 Features | SettingRepository | [DpmMfgSettings](../CAAScrSettings/DpmMfgSettings.md)  
 Templates | SettingRepository | [DpmMfgTemplatesSettings](../CAAScrSettings/DpmMfgTemplatesSettings.md)  
 DPM - Assembly Process Planner | Commands | SettingRepository | [DNBDpmAPNSettings](../CAAScrSettings/DNBDpmAPNSettings.md)  
 DPM - Fastening Process Planner | Commands | SettingRepository | [DNBDpmBIWSettings](../CAAScrSettings/DNBDpmBIWSettings.md)  
 Fastener Attributes | SettingRepository | [DNBDpmBIWSettings](../CAAScrSettings/DNBDpmBIWSettings.md)  
 Fastener Visualization | SettingRepository | [DNBDpmBIWSettings](../CAAScrSettings/DNBDpmBIWSettings.md)  
 DPM - Shop Order Release | Image Capture Settings | ImgPropertySettingAtt | DNBSORImgPropertySettingCtrl  
 Order Create Settings | GeneralPropertySettingAtt | DNBSORGeneralPropertySettingCtrl  
 DPM - Structure Lofting | Activities | SettingRepository | [DpmStrToolsSettings](../CAAScrSettings/DpmStrToolsSettings.md)  
 Features | SettingRepository | [DpmStrSettings](../CAAScrSettings/DpmStrSettings.md)  
 Templates | SettingRepository | [DpmStrTemplatesSettings](../CAAScrSettings/DpmStrTemplatesSettings.md)  
 DPM - Work Instructions | General | SettingRepository | [DNBWorkGeneral](../CAAScrSettings/DNBWorkGeneral.md)  
 Work Instruction Text 3D Display | SettingRepository | [DNBWKIWorkRenderSettings](../CAAScrSettings/DNBWKIWorkRenderSettings.md)  
 MSD - Manufacturing System Definition | General | SettingRepository | [DNBMSDResUtilSettings](../CAAScrSettings/DNBMSDResUtilSettings.md)  
 ENOVIA V5 VPM | None | ENOVIA V5 VPM Logon | LogonSettingAtt | CATImmLogonSettingCtrl  
 Product View Result | SettingRepository | [PVRProperties](../CAAScrSettings/PVRProperties.md)  
 Equipment & Systems | Electrical 3D Design Assembly | General | SettingRepository | [ElectricalLibraryAccess1](../CAAScrSettings/ElectricalLibraryAccess1.md)  
 Harness Flattening | SettingRepository | [ElectricalHarnessFlattening](../CAAScrSettings/ElectricalHarnessFlattening.md)  
 Harness Management | SettingRepository | [ElectricalHarnessInstallation](../CAAScrSettings/ElectricalHarnessInstallation.md)  
 Electrical Assembly Design | Electrical Library Access | SettingRepository | [ElectricalLibraryAccess2](../CAAScrSettings/ElectricalLibraryAccess2.md)  
 General | SettingRepository | [ElectricalLibraryAccess1](../CAAScrSettings/ElectricalLibraryAccess1.md)  
 Electrical Harness Flattening | General | SettingRepository | [ElectricalHarnessFlattening](../CAAScrSettings/ElectricalHarnessFlattening.md)  
 Electrical Harness Installation | Harness Management | SettingRepository | [ElectricalHarnessInstallation](../CAAScrSettings/ElectricalHarnessInstallation.md)  
 None | Electrical Mapping | SettingRepository | [ElectricalCommon](../CAAScrSettings/ElectricalCommon.md)  
 Electrical Process Interfacing | SettingRepository | [EleciXFIntegration](../CAAScrSettings/EleciXFIntegration.md)  
 Structure Discipline | Equipment Support Structures - General | ColorESSObjectSettingAtt | CATStrColorESSObjectSettingCtrl  
 MaterialESSObjectSettingAtt | CATStrMaterialESSObjectSettingCtrl  
 PathESSRessourcesSettingAtt | CATStrPathESSRessourcesSettingCtrl  
 TypeESSObjectSettingAtt | CATStrTypeESSObjectSettingCtrl  
 Structure Functional System Design - General | EndCutESSObjectSettingAtt | CATStrEndCutESSObjectSettingCtrl  
 Ergonomics Design & Analysis | Human Activity Analysis | Ergonomic Analysis | HAAErgoAnalysisSettingAtt | SWKHmiHAAErgoAnalysisSettingCtrl  
 Human Builder | Display | HBRDisplaySettingAtt | SWKHmiHBRDisplaySettingCtrl  
 General | HBRGeneralSettingAtt | SWKHmiHBRGeneralSettingCtrl  
 Vehicle Occupant Accommodation | SettingRepository | [CATHBRVOASetting](../CAAScrSettings/CATHBRVOASetting.md)  
 Human Measurements Editor | Anthropometry | HMEAnthroSettingAtt | SWKHmiHMEAnthroSettingCtrl  
 Human Posture Analysis | Postural Score | HPAPosturalScoreSettingAtt | SWKHmiHPAPosturalScoreSettingCtrl  
 Human Task Simulation | Cut Copy Paste | HtsCCPSettingAtt | DNBHtsCCPSettingCtrl  
 General | HtsGeneralSettingAtt | DNBHtsGeneralSettingCtrl  
 HumanTask Display | HtsTaskDisplaySettingAtt | DNBHtsTaskDisplaySettingCtrl  
 Joint Speed | HtsJointSpeedSettingsAtt | DNBHtsJointSpeedSettingCtrl  
 General | Compatibility | 3D XML | Export3DXmlSettingAtt | CAT3DXmlExportSettingCtrl  
 CCD | SettingRepository | [CCDCompatibilitySettings](../CAAScrSettings/CCDCompatibilitySettings.md)  
 DELMIA D5 | ImportD5SettingAtt | DNBD5IImportD5SettingCtrl  
 DXF | SettingRepository | [DXF](../CAAScrSettings/DXF.md)  
 Electrical | SettingRepository | [E3DMigrationOptions](../CAAScrSettings/E3DMigrationOptions.md)  
 ENOVIA V6/3DEXPERIENCE | V6SettingAtt | ENO3DEXPSettingCtrl  
 External Formats | MultiCADSettingAtt | CATMciMultiCADSettingCtrl  
 IGES | IgesSettingAtt | CATIdeIgesSettingCtrl  
 IGES 2D | SettingRepository | [IG2](../CAAScrSettings/IG2.md)  
 Migration Batch | MigrBatchSettingAtt | CATV4IMigrBatchSettingCtrl  
 STEP | StepSettingAtt | CATSdeStepSettingCtrl  
 Saving as V4 Data | V4WritingSettingAtt | CATV4IV4WritingSettingCtrl  
 V4 Data Reading | InteropSettingAtt | CATV4IInteropSettingCtrl  
 V4 V5 DRAW | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
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
 PCS | SettingRepository | [GeneralPCS](../CAAScrSettings/GeneralPCS.md)  
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
 Parameters and Measure | Constraints and Dimensions | SettingRepository | [ConstraintsAndDimensions](../CAAScrSettings/ConstraintsAndDimensions.md)  
 Knowledge | KnowledgeSheetSettingAtt | CATLieKnowledgeSheetSettingCtrl  
 Knowledge Environment | LanguageSheetSettingAtt | CATLieLanguageSheetSettingCtrl  
 Measure Tools | SettingRepository | [MeasureSettings](../CAAScrSettings/MeasureSettings.md)  
 Parameters Tolerance | ToleranceSheetSettingAtt | CATLieToleranceSheetSettingCtrl  
 Report Generation | ReportGenerationSheetSettingAtt | CATLieReportGenerationSheetSettingCtrl  
 Scale | SettingRepository | [ShapeDesignGeometricalScale](../CAAScrSettings/ShapeDesignGeometricalScale.md)  
 Units | UnitsSheetSettingAtt | CATLieUnitsSheetSettingCtrl  
 Infrastructure | 3D Annotations Infrastructure | Administration | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Annotation | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Display | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Manipulators | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Tolerancing | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 View Annotation Plane | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
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
 Photo Studio | Display | SettingRepository | [RenderingSettingsDisplay](../CAAScrSettings/RenderingSettingsDisplay.md)  
 General | SettingRepository | [RenderingSettingsGeneral](../CAAScrSettings/RenderingSettingsGeneral.md)  
 Output | SettingRepository | [RenderingSettingsOutput](../CAAScrSettings/RenderingSettingsOutput.md)  
 Satellites | SettingRepository | [RenderingSettingsSatellites](../CAAScrSettings/RenderingSettingsSatellites.md)  
 Sticker | SettingRepository | [RenderingSettingsSticker](../CAAScrSettings/RenderingSettingsSticker.md)  
 Product Structure | Cache Management | CacheSettingAtt | CATSysCacheSettingCtrl  
 Cgr Management | CacheSettingAtt | CATSysCacheSettingCtrl  
 VisualizationSettingAtt | CATVizVisualizationSettingCtrl  
 Real Time Rendering | Display | SettingRepository | [RenderingSettingsDisplay](../CAAScrSettings/RenderingSettingsDisplay.md)  
 General | SettingRepository | [RenderingSettingsGeneral](../CAAScrSettings/RenderingSettingsGeneral.md)  
 Sticker | SettingRepository | [RenderingSettingsSticker](../CAAScrSettings/RenderingSettingsSticker.md)  
 Knowledgeware | Business Process Knowledge Template | Business Knowledge Template | BehaviorSettingAtt | CATBKTBehaviorSettingCtrl  
 Product Functional Definition | General | FunctionalSystemSettingAtt | CATFsyFunctionalSystemSettingCtrl  
 Machining | None | General | SettingRepository | [NCMfgDisplay](../CAAScrSettings/NCMfgDisplay.md)  
 Operation | SettingRepository | [NCMfgOperation](../CAAScrSettings/NCMfgOperation.md)  
 Output | SettingRepository | [NCMfgOutput](../CAAScrSettings/NCMfgOutput.md)  
 Photo Video | SettingRepository | [NCMfgSimulation](../CAAScrSettings/NCMfgSimulation.md)  
 Program | SettingRepository | [NCMfgAutosequence](../CAAScrSettings/NCMfgAutosequence.md)  
 Resources | SettingRepository | [NCMfgResources](../CAAScrSettings/NCMfgResources.md)  
 Machining Simulation | NC Machine Tool Simulation | General | SettingRepository | [DNBVNCSettings](../CAAScrSettings/DNBVNCSettings.md)  
 Simulation | SettingRepository | [DNBVNCSimulSettings](../CAAScrSettings/DNBVNCSimulSettings.md)  
 Mechanical Design | 2D Layout for 3D Design | Administration | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.md)  
 Display | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.md)  
 Geometry | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.md)  
 View Creation | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.md)  
 Visualization | SettingRepository | [CAT2DLToolsOptions](../CAAScrSettings/CAT2DLToolsOptions.md)  
 Aerospace Sheet Metal Design | Display | ViewCharacteristicCurvesSettingAtt | CATStmViewCharacteristicCurvesSettingCtrl  
 General | CatalogSHMObjectSettingAtt | CATStmCatalogSHMObjectSettingCtrl  
 Assembly Design | Constraints | AsmConstraintSettingAtt | CATAsmConstraintSettingCtrl  
 SettingRepository | [AssemblyConstraints](../CAAScrSettings/AssemblyConstraints.md)  
 General | AsmGeneralSettingAtt | CATAsmGeneralSettingCtrl  
 SettingRepository | [AssemblyGeneral](../CAAScrSettings/AssemblyGeneral.md)  
 Drafting | Administration | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Annotation and Dress-Up | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Dimension | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 General | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Generation | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Geometry | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Layout | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Manipulators | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 View | SettingRepository | [DraftingOptions](../CAAScrSettings/DraftingOptions.md)  
 Functional Tolerancing & Annotation | Administration | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Annotation | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Constructed Geometry | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Dimension | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Display | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Manipulators | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Tolerances | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Tolerancing | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 View Annotation Plane | SettingRepository | [CATTPSEditor](../CAAScrSettings/CATTPSEditor.md)  
 Generative Sheetmetal Design | General | CatalogSHMObjectSettingAtt | CATStmCatalogSHMObjectSettingCtrl  
 Mold Tooling Design | Add Remove | SettingRepository | [MoldDesignBodies](../CAAScrSettings/MoldDesignBodies.md)  
 Catalogs | SettingRepository | [MoldDesignCatalog](../CAAScrSettings/MoldDesignCatalog.md)  
 Component | SettingRepository | [MoldDesignComponent](../CAAScrSettings/MoldDesignComponent.md)  
 Miscellaneous | SettingRepository | [MoldDesignMisc](../CAAScrSettings/MoldDesignMisc.md)  
 Split | SettingRepository | [MoldDesignSplit](../CAAScrSettings/MoldDesignSplit.md)  
 Viewer Mapping | SettingRepository | [MoldDesignMapping](../CAAScrSettings/MoldDesignMapping.md)  
 Sketcher | Sketcher | SettingRepository | [Sketcher](../CAAScrSettings/Sketcher.md)  
 Structure Design | General | ColorSTDObjectSettingAtt | CATStrColorSTDObjectSettingCtrl  
 PPGExecLogSettingAtt | CATStrPPGExecLogSettingCtrl  
 Resource Detailing | None | 2D Graph | Tree2DGraphSettingAtt | DNBIgpTree2DGraphSettingCtrl  
 Action Libraries | UserActionsLibSettingAtt | DNBIgpUserActionsLibSettingCtrl  
 Frames Visualization | SettingRepository | [DNBDBldFramesOfIntSettings](../CAAScrSettings/DNBDBldFramesOfIntSettings.md)  
 Graphic Reporting | FASReportingSettingAtt | DNBIgpFASReportingSettingCtrl  
 Offline Programming | IgpOlpSettingAtt | DNBIgpOlpSettingCtrl  
 RRS | RRSSettingAtt | DNBRobRRSSettingCtrl  
 Resource Layout | SettingRepository | [DNBMfgLayoutSettings](../CAAScrSettings/DNBMfgLayoutSettings.md)  
 Robot Task Display | TaskVisuSettingAtt | DNBIgpTaskVisuSettingCtrl  
 Teach Dialog Settings | TeachDlgSettingAtt | DNBIgpTeachDlgSettingCtrl  
 Shape | Automotive BiW Fastening | Display | SettingRepository | [GBiWDisplay](../CAAScrSettings/GBiWDisplay.md)  
 General | SettingRepository | [GBiWGeneral](../CAAScrSettings/GBiWGeneral.md)  
 Automotive Class A | Tolerance | SettingRepository | [FreeStyleGlobalUserSettings](../CAAScrSettings/FreeStyleGlobalUserSettings.md)  
 Digitized Shape Editor | Display Modes | SettingRepository | [DSESettingsGeneral](../CAAScrSettings/DSESettingsGeneral.md)  
 SettingRepository | [DSESettingsDisplayModes](../CAAScrSettings/DSESettingsDisplayModes.md)  
 General | SettingRepository | [DSESettingsGeneral](../CAAScrSettings/DSESettingsGeneral.md)  
 SettingRepository | [DSESettingsDisplayModes](../CAAScrSettings/DSESettingsDisplayModes.md)  
 FreeStyle | General | SettingRepository | [FreeStyleGlobalUserSettings](../CAAScrSettings/FreeStyleGlobalUserSettings.md)  
 Manipulators | SettingRepository | [FreeStyleGlobalUserSettings](../CAAScrSettings/FreeStyleGlobalUserSettings.md)  
 Imagine & Shape | Display | SettingRepository | [CATDesSettingDisplay](../CAAScrSettings/CATDesSettingDisplay.md)  
 General | SettingRepository | [CATDesSettingGeneral](../CAAScrSettings/CATDesSettingGeneral.md)  
 Shape Sculptor | Parameters | SettingRepository | [StyGlobalSettings](../CAAScrSettings/StyGlobalSettings.md)  
   
 [Top]
 
 * * *
 ### References
 
 [1] | [Administrating Settings with Automation](CAAInfSettings.md)  
 ---|---  
   
 _Copyright 1999-2013, Dassault Systmes. All rights reserved._
