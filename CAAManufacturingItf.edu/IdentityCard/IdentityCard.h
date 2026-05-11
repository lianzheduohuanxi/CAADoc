// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
// -->Prereq Components Declaration
AddPrereqComponent("ManufacturingInterfaces",Public);
AddPrereqComponent("ApplicationFrame", Public);
AddPrereqComponent("Dialog", Public);
AddPrereqComponent("DialogEngine",Public);
AddPrereqComponent("DMAPSInterfaces", Public);
AddPrereqComponent("GeometricObjects", Public);
AddPrereqComponent("KnowledgeInterfaces", Public);
AddPrereqComponent("LiteralsEditor", Public);
AddPrereqComponent("LiteralFeatures", Public);
AddPrereqComponent("Mathematics", Public);
AddPrereqComponent("MechanicalCommands",Public);
AddPrereqComponent("MechanicalModeler",Public);
AddPrereqComponent("MecModInterfaces",Public);
AddPrereqComponent("ObjectModelerBase", Public);
AddPrereqComponent("ObjectSpecsModeler",Public);
AddPrereqComponent("PartInterfaces", Public);
AddPrereqComponent("ProcessPlatformVisu", Public);
AddPrereqComponent("SketcherInterfaces", Public);
AddPrereqComponent("System", Public);
AddPrereqComponent("Visualization",Public);
AddPrereqComponent("VisualizationBase",Public);

// pcc 15/11/02 - Split MechanicalModeler/ConstraintModeler/ConstraintModelerInterfaces
AddPrereqComponent ("ConstraintModeler",  Public);
AddPrereqComponent ("ConstraintModelerInterfaces",  Public);
