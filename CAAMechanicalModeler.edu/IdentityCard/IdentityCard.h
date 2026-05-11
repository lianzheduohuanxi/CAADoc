//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
// -->Prereq Components Declaration
AddPrereqComponent("ApplicationFrame" ,Public);
AddPrereqComponent("CATIAApplicationFrame" ,Public);
AddPrereqComponent("Dialog" ,Public);
AddPrereqComponent("DialogEngine" ,Public);
AddPrereqComponent("GSMInterfaces" ,Public);
AddPrereqComponent("GeometricObjects" ,Public);
AddPrereqComponent("LiteralFeatures" ,Public);
AddPrereqComponent("KnowledgeInterfaces",Public);// pour la CXR9
AddPrereqComponent("Mathematics" ,Public);
AddPrereqComponent("MecModInterfaces" ,Public);
AddPrereqComponent("MechanicalCommands" ,Public);
AddPrereqComponent("MechanicalModeler" ,Public);
AddPrereqComponent("MechanicalModelerUI" ,Public);
AddPrereqComponent("NewTopologicalObjects" ,Public);
AddPrereqComponent("ObjectModelerBase" ,Public);
AddPrereqComponent("ObjectSpecsModeler" ,Public);
AddPrereqComponent("System" ,Public);
AddPrereqComponent("TopologicalOperators" ,Public);
AddPrereqComponent("Visualization" ,Public);
AddPrereqComponent("VisualizationBase" ,Public);
AddPrereqComponent("ComponentsCatalogsInterfaces",Public);
AddPrereqComponent("InteractiveInterfaces",Public);
AddPrereqComponent("SketcherInterfaces",Public);
// fda bypass link forte 6.1
AddPrereqComponent("ProductStructure" ,Public);
AddPrereqComponent("ProductStructureUI" ,Public);
AddPrereqComponent("CATGraphicProperties", Public);  //Necessary for CAAMmrMultiMeasure & CAAMmrMesureSet Visu implémentation

// pcc 15/11/02 - Split MechanicalModeler/ConstraintModeler/ConstraintModelerInterfaces
AddPrereqComponent ("ConstraintModelerInterfaces",  Public);

AddPrereqComponent ("CATMecModUseItf",  Public);
AddPrereqComponent ("CATMecModLiveUseItf",  Public);






