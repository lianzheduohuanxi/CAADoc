// COPYRIGHT DASSAULT SYSTEMES 2009
//===================================================================
//
// IdentityCard.h
// Supplies the list of prerequisite components for framework CAACATPDMReconcile.edu
//
//===================================================================
//
// Usage notes:
//   For every prereq framework FW, use the syntax:
//   AddPrereqComponent ("FW", Public);
//
//===================================================================
//
//  
//===================================================================

// -->Prereq Components Declaration

// --- System Frameworks

AddPrereqComponent( "System"                     , Public ) ;
//AddPrereqComponent( "ApplicationFrame"           , Public ) ;

// --- V5 Object Model
AddPrereqComponent( "ObjectModelerBase"          , Public ) ;

// --- Access to transformation
AddPrereqComponent( "Mathematics"                , Public ) ;

// --- Product Structure
AddPrereqComponent( "ProductStructure"           , Public ) ;
AddPrereqComponent( "ProductStructureInterfaces" , Public ) ;
//AddPrereqComponent( "CATIAModelEditor"           , Public ) ;

// --- PDM
AddPrereqComponent( "CATPDMBase"                 , Public ) ;
AddPrereqComponent( "CATPDMBaseInterfaces"       , Public ) ;
AddPrereqComponent( "CATPDMReconcile"            , Public ) ;

