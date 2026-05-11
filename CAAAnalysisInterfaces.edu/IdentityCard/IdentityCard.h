//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
// -->Prereq Components Declaration
AddPrereqComponent ("System", 					Public);
AddPrereqComponent ("ObjectSpecsModeler", 		Public);
AddPrereqComponent ("ObjectModelerBase", 		Public);
AddPrereqComponent ("Mathematics", 				Public);
AddPrereqComponent ("KnowledgeInterfaces",		Public);
AddPrereqComponent ("InfInterfaces",		Public);


// Workbench & Commands prereq
AddPrereqComponent("ApplicationFrame",Public);
AddPrereqComponent("CATIAApplicationFrame",Public);
AddPrereqComponent("Dialog",          Public);
AddPrereqComponent("DialogEngine",Public);
AddPrereqComponent("Visualization"         , Public);
AddPrereqComponent("VisualizationBase"     , Public);

// Analysis prereq
AddPrereqComponent ("CATAnalysisInterfaces", 	Public);
AddPrereqComponent ("CATAnalysisBase",			Public);
AddPrereqComponent ("CATAnalysisResources", 	Public);
AddPrereqComponent ("AnalysisMeshingModel",		Public);
AddPrereqComponent ("AnalysisMeshingToolsItf",		Public);
AddPrereqComponent ("CATAnalysisVisuInterfaces", 	Public);
//

// Mesh Commands Mechanical World.
AddPrereqComponent ("ProductStructure",		Public);
AddPrereqComponent ("MecModInterfaces",		Public);
AddPrereqComponent ("MechanicalModeler",		Public);
AddPrereqComponent ("NewTopologicalObjects",		Public);
AddPrereqComponent ("GeometricObjects",		Public);
AddPrereqComponent ("SpecialAPI", Public)
