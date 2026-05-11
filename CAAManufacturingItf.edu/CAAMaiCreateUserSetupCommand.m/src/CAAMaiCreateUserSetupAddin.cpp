// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAMaiCreateUserSetupAddin:
//
// Sample code for : CAA Manufacturing
// Mission         : Implementation of the interface CATIManufacturingProgramAddin to create 
//                   an add-in in the Prismatic Machining Workbench.
//                   We want to add a new toolbar in this workbench in order to be able
//                   to instanciate a new type of setup.
//                   The start up of this new setup is defined in the CAAMaiGenerateUserSetupCatalog
//                   use case.
//
// Type            : Interactive functionality.
//
// How to run it   : 1-You need the Use Case CAAMaiGenerateUserSetupCatalog in order to generate 
//                     a new type of setup ("UserSetup") in a new catalog of Setup.
//                   2-Build the CAAMaiCreateUserSetupCommand library.
//                     In this library there is the code that defines the command, and the code
//                     for an add-in in Prismatic Machining Workbench, to define a new command
//                     header "User Setup" that will enable you to instanciate a setup
//                     "UserSetup" under process node.
//                   3-Create the runtime view.
//                     You must have a line in your .dico file like this one:
//
//                     CAAMaiCreateUserSetupAddin     CATIManufacturingProgramAddin   libCAAMaiCreateUserSetupCommand
//                      
//                   4-Launch CATIA.
//                   5-Enter in Prismatic machining workbench in NC Manufacturing workshop.
//                   6-Click on the "UserSetup" Command
//                   7-Select Process or a previously created setup
//
//                   => A new Setup "UserSetup.1" will appear in the graph.
//                         You will be abble to edit this setup. 
//                         You will be able to overload itst editor.
//
//=============================================================================
// Local Framework
#include "CAAMaiCreateUserSetupAddin.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

// Declaration of a new Command Header Class 
#include "CATCommandHeader.h"        
MacDeclareHeader(CAAMaiUserSetupHeader);
MacDeclareHeader(CAAMaiUserSetupHeader_vers1);
MacDeclareHeader(CAAMaiUserSetupHeader_vers2);

// Implement the interface CATIManufacturingProgramAddin to create an add-in in the Prismatic Machining Workbench
#include <TIE_CATIManufacturingProgramAddin.h>
TIE_CATIManufacturingProgramAddin(CAAMaiCreateUserSetupAddin);

CATImplementClass(CAAMaiCreateUserSetupAddin, DataExtension, CATNull, CAAMaiCreateUserSetupAdn);


CAAMaiCreateUserSetupAddin::CAAMaiCreateUserSetupAddin()
{}

CAAMaiCreateUserSetupAddin::~CAAMaiCreateUserSetupAddin()
{}

void CAAMaiCreateUserSetupAddin::CreateCommands()
{
  
  static CATString CreateUserSetup ("UserSetup");
  new CAAMaiUserSetupHeader ( "CreateUserSetup","CAAMaiCreateUserSetupCommand","CAAMaiCreateUserSetupCom",(void *)&CreateUserSetup); 
  
  static CATString CreateUserSetup_vers1 ("UserSetup_vers1");
  new CAAMaiUserSetupHeader_vers1 ( "CreateUserSetup_vers1","CAAMaiCreateUserSetupCommand","CAAMaiCreateUserSetupCom",(void *)&CreateUserSetup_vers1); 
  
  static CATString CreateUserSetup_vers2 ("UserSetup_vers2");
  new CAAMaiUserSetupHeader_vers2 ( "CreateUserSetup_vers2","CAAMaiCreateUserSetupCommand","CAAMaiCreateUserSetupCom",(void *)&CreateUserSetup_vers2); 
  
}

CATCmdContainer * CAAMaiCreateUserSetupAddin::CreateToolbars()
{
  
  // ---------------------------------------------------------
  // Creation of User Setup Toolbar
  // ---------------------------------------------------------
  NewAccess(CATCmdContainer,PaletteUserActMain,ManufacturingUserActMain);
  SetAccessTitle(PaletteUserActMain,"Manufacturing User Setup");
  SetAccessCustomerName(PaletteUserActMain,"ManufacturingUserActMain");
  AddToolbarView(PaletteUserActMain,1,Right);
  
  // ---------------------------------------------------------
  // Creation of User Setup Command
  // ---------------------------------------------------------
  {
    
    // Commande Create User Setup
    NewAccess(CATCmdStarter,CreateUserSetup,CreateUserSetup);
    SetAccessCommand(CreateUserSetup,"CreateUserSetup");
    NewAccess(CATCmdStarter,CreateUserSetup_vers1,CreateUserSetup_vers1);
    SetAccessCommand(CreateUserSetup_vers1,"CreateUserSetup_vers1");
    SetAccessNext (CreateUserSetup, CreateUserSetup_vers1 );
    NewAccess(CATCmdStarter,CreateUserSetup_vers2,CreateUserSetup_vers2);
    SetAccessCommand(CreateUserSetup_vers2,"CreateUserSetup_vers2");
    SetAccessNext (CreateUserSetup_vers1, CreateUserSetup_vers2 );
    SetAccessChild(PaletteUserActMain,CreateUserSetup);
    
  }
  
  return PaletteUserActMain;
  
}
