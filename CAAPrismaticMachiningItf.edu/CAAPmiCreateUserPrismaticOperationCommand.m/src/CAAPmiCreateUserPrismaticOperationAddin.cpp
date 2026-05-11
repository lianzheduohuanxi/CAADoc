// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAPmiCreateUserPrismaticOperationAddin:
//
// Sample code for : CAA Manufacturing
// Mission         : Implementation of the interface CATIManufacturingProgramAddin to create 
//                   an add-in in the Prismatic Machining Workbench.
//                   We want to add a new toolbar in this workbench in order to be able
//                   to instanciate new types of user defined machining operations.
//                   The start up of these new operations are defined in the 
//                   CAAPmiGenerateUserPrismaticOperationCatalog use case.
//
// Type            : Interactive functionality.
//
// How to run it   : 1-You need the Use Case CAAPmiGenerateUserPrismaticOperationCatalog in order
//                     to generate a new type of operation ("UserDrilling", "UserProfileContouring",
//                     "UserPocketing", or "UserCircularMilling") in a new catalog of operations.
//                   2-Build the CAAPmiCreateUserDefinedPrismaticOperationCommand library.
//                     In this library there is the code that defines the command, and the code
//                     for an add-in in Prismatic Machining Workbench, to define a new command
//                     header "UserDefinedXXX" that will enable you to instanciate an operation
//                     "UserDefinedXXX" under program node.
//                   3-Create the runtime view.
//                     You must have a line in your .dico file like this one:
//
//                     CAAPmiCreateUserPrismaticOperationAddin     CATIManufacturingProgramAddin   libCAAPmiCreateUserPrismaticOperationCommand
//                      
//                   4-Launch CATIA.
//                   5-Enter in Prismatic machining workbench in NC Manufacturing workshop.
//                   6-Click on the "UserDefinedXXX" Command
//                   7-Select the program or a previously created operation
//
//                   => A new operation "UserDefinedXXX.1" will appear in the graph.
//                         You will be abble to edit this operation. 
//                         You will be able to overload its editor.
//
//=============================================================================
// Local Framework
#include "CAAPmiCreateUserPrismaticOperationAddin.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

// Declaration of a new Command Header Class 
#include "CATCommandHeader.h"        
MacDeclareHeader(CAAPmiUserDefinedDrillingHeader);
MacDeclareHeader(CAAPmiUserDefinedPocketingHeader);
MacDeclareHeader(CAAPmiUserDefinedCircularMillingHeader);
MacDeclareHeader(CAAPmiUserDefinedProfileContouringHeader);

// Implement the interface CATIManufacturingProgramAddin to create an add-in in the Prismatic Machining Workbench
#include <TIE_CATIManufacturingProgramAddin.h>
TIE_CATIManufacturingProgramAddin(CAAPmiCreateUserPrismaticOperationAddin);

CATImplementClass(CAAPmiCreateUserPrismaticOperationAddin, Implementation, CATNull, CAAPmiCreateUserPrismaticOperationAddin);

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
CAAPmiCreateUserPrismaticOperationAddin::CAAPmiCreateUserPrismaticOperationAddin()
{}

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
CAAPmiCreateUserPrismaticOperationAddin::~CAAPmiCreateUserPrismaticOperationAddin()
{}

// ---------------------------------------------------------------------------
// CreateCommands
// ---------------------------------------------------------------------------
void CAAPmiCreateUserPrismaticOperationAddin::CreateCommands()
{
  
  static CATString UserDrillingType ("UserDrilling");
  new CAAPmiUserDefinedDrillingHeader ( "CreateUserDrillingId",
                                        "CAAPmiCreateUserPrismaticOperationCommand",
                                        "CAAPmiCreateUserPrismaticOperationCmd",
                                        (void *)&UserDrillingType); 
  
  static CATString UserPocketingType ("UserPocketing");
  new CAAPmiUserDefinedPocketingHeader ( "CreateUserPocketingId",
                                         "CAAPmiCreateUserPrismaticOperationCommand",
                                         "CAAPmiCreateUserPrismaticOperationCmd",
                                         (void *)&UserPocketingType); 
  
  static CATString UserCircularMillingType ("UserCircularMilling");
  new CAAPmiUserDefinedCircularMillingHeader ( "CreateUserCircularMillingId",
                                               "CAAPmiCreateUserPrismaticOperationCommand",
                                               "CAAPmiCreateUserPrismaticOperationCmd",
                                               (void *)&UserCircularMillingType); 
  
  static CATString UserProfileContouringType ("UserProfileContouring");
  new CAAPmiUserDefinedProfileContouringHeader ( "CreateUserProfileContouringId",
                                                 "CAAPmiCreateUserPrismaticOperationCommand",
                                                 "CAAPmiCreateUserPrismaticOperationCmd",
                                                 (void *)&UserProfileContouringType); 
  

}

// ---------------------------------------------------------------------------
// CreateToolbars
// ---------------------------------------------------------------------------
CATCmdContainer * CAAPmiCreateUserPrismaticOperationAddin::CreateToolbars()
{
  
  // User defined prismatic operations Toolbar
  // -----------------------------------------
  NewAccess(CATCmdContainer,pUserPrismaticOperationToolbar,UserPrismaticOperationToolbar);

  SetAccessTitle(pUserPrismaticOperationToolbar,"User defined prismatic operation");
  SetAccessCustomerName(pUserPrismaticOperationToolbar,"UserPrismaticOperationToolbar");

  AddToolbarView(pUserPrismaticOperationToolbar,1,Left);
  
  // User defined prismatic operations creation Command
  // --------------------------------------------------
  {
    
    // Commande Create User Defined drilling
    NewAccess(CATCmdStarter,pCreateUserDrilling,CreateUserDrilling);
    SetAccessCommand(pCreateUserDrilling,"CreateUserDrillingId");

    NewAccess(CATCmdStarter,pCreateUserPocketing,CreateUserPocketing);
    SetAccessCommand(pCreateUserPocketing,"CreateUserPocketingId");

    NewAccess(CATCmdStarter,pCreateUserCircularMilling,CreateUserCircularMilling);
    SetAccessCommand(pCreateUserCircularMilling,"CreateUserCircularMillingId");

    NewAccess(CATCmdStarter,pCreateUserProfileContouring,CreateUserProfileContouring);
    SetAccessCommand(pCreateUserProfileContouring,"CreateUserProfileContouringId");

    // Toolbar organization
    SetAccessChild(pUserPrismaticOperationToolbar,pCreateUserDrilling);

    SetAccessNext (pCreateUserDrilling, pCreateUserPocketing );
    SetAccessNext (pCreateUserPocketing, pCreateUserCircularMilling );
    SetAccessNext (pCreateUserCircularMilling, pCreateUserProfileContouring );
    
  }
  
  return pUserPrismaticOperationToolbar;
  
}
