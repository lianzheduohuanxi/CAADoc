//
// COPYRIGHT DASSAULT SYSTEMES 1994-2000
//
AddPrereqComponent("System"               ,Public);
AddPrereqComponent("InfInterfaces"        ,Public);
AddPrereqComponent("MecModInterfaces"     ,Public);
AddPrereqComponent("GSMInterfaces"        ,Public);

AddPrereqComponent("ObjectModelerBase"    ,Public);
AddPrereqComponent("ObjectSpecsModeler"   ,Public);
AddPrereqComponent("MechanicalModeler"    ,Public);

AddPrereqComponent("Mathematics"          ,Public);
AddPrereqComponent("GeometricObjects"     ,Public);
AddPrereqComponent("NewTopologicalObjects",Public);
AddPrereqComponent("BasicTopologicalOpe"  ,Public);
AddPrereqComponent("TopologicalOperators" ,Public);

// pcc 15/11/02 - Split MechanicalModeler/ConstraintModeler/ConstraintModelerInterfaces
AddPrereqComponent ("ConstraintModeler",  Public);
AddPrereqComponent ("ConstraintModelerInterfaces",  Public);
