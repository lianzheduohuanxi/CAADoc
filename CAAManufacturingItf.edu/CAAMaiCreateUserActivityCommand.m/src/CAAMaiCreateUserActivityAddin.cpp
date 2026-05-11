// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAEMaiCreateUserActitvityAddin:
//
// Sample code for : CAA Manufacturing
// Mission         : Implementation of the interface CATIManufacturingProgramAddin to create 
//                   an add-in in the Prismatic Machining Workbench.
//                   We want to add a new toolbar in this workbench in order to be able
//                   to instanciate a new type of activity.
//                   The start up of this new activity is defined in the CAAMaiGenerateUserActivityCatalog
//                   use case.
//
// Type            : Interactive functionality.
//
// How to run it   : 1-You need the Use Case CAAMaiGenerateUserActivityCatalog in order to generate 
//                     a new type of operation ("UserActivity") in a new catalog of activity.
//                   2-Build the CAAEMaiCreateUserActitvityCommand library.
//                     In this library ther is the code that defines the command, and the code
//                     for an add-in in Prismatic Machining Workbench, to define a new command
//                     header "User Activity" that will enable you to instanciate an operation
//                     "UserActivity" in a manufacturing program.
//                   3-Create the runtime view.
//                   4-Launch CATIA.
//                   5-Enter in Prismatic machining workbench in NC Manufacturing workshop.
//                   6-Click on the "User Activity" Command
//                   7-Select the program
//
//                      => A new activity "UserActivity.1" will appear in the graph. You will be abble 
//                         to edit this operation. By default, there is three TabPages in the edition
//                         panel. First one is the stratregy parameters editor (You will see the two
//                         parameters defined in the activity catalog 
//                         see Use Case CAAMaiGenerateUserActivityCatalog).
//                         The second one corresponds to the geometry tabpage (By default it is empty).
//                         The last one correspond to the Tool tabpage.
//                         You will be able to overload each one of them.
//
//=============================================================================
// Local Framework
#include "CAAMaiCreateUserActivityAddin.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...

// Declaration of a new Command Header Class 
#include "CATCommandHeader.h"        
MacDeclareHeader(CAAMaiUseractivityHeader);

// Implement the interface CATIManufacturingProgramAddin to create an add-in in the Prismatic Machining Workbench
#include <TIE_CATIManufacturingProgramAddin.h>
TIE_CATIManufacturingProgramAddin(CAAMaiCreateUserActivityAddin);

CATImplementClass(CAAMaiCreateUserActivityAddin, DataExtension, CATBaseUnknown, CAAMaiMfgWksAddin);


CAAMaiCreateUserActivityAddin::CAAMaiCreateUserActivityAddin()
{}

CAAMaiCreateUserActivityAddin::~CAAMaiCreateUserActivityAddin()
{}

void CAAMaiCreateUserActivityAddin::CreateCommands()
{
  static CATString CreateUserActivity ("UserActivity");
  new CAAMaiUseractivityHeader ( "CreateUserActivity","CAAMaiCreateUserActivityCommand","CAAMaiCreateUserActivityCom",(void *)&CreateUserActivity); 
}

CATCmdContainer * CAAMaiCreateUserActivityAddin::CreateToolbars()
{
  // ---------------------------------------------------------
  // Creation of User Activity Toolbar
  // ---------------------------------------------------------
  NewAccess(CATCmdContainer,PaletteUserActMain,ManufacturingUserActMain);
  SetAccessTitle(PaletteUserActMain,"Manufacturing User Activity");
  SetAccessCustomerName(PaletteUserActMain,"ManufacturingUserActMain");
  AddToolbarView(PaletteUserActMain,1,Right);
  
  // ---------------------------------------------------------
  // Creation of User Activity Command
  // ---------------------------------------------------------
  {
    // Commande Create User Activity
    NewAccess(CATCmdStarter,CreateUserActivity,CreateUserActivity);
    SetAccessCommand(CreateUserActivity,"CreateUserActivity");
    
    
    
    SetAccessChild(PaletteUserActMain,CreateUserActivity);
  }
  
  return PaletteUserActMain;
}

