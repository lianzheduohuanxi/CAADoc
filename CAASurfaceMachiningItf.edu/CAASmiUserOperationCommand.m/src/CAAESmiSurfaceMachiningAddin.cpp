// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiSurfaceMachiningAddin :
//
// Sample code for : CAA Workbench Management
//
// Mission         : Implementation of the interface CATISmgProgramAddin to create 
//                   an add-in in the Surface Machining Workbench.
//					 We want to add a new toolbar in this workbench in order to be able
//                   to instanciate 2 new types of activity.
//
// Type            : Interactive functionality.
//
//=============================================================================

// Local Framework
#include "CAAESmiSurfaceMachiningAddin.h"

// ApplicationFrame Framework 
#include <CATCreateWorkshop.h>   
 
// Declaration of a new Command Header Class 
#include "CATCommandHeader.h"        
MacDeclareHeader(CAASmiHeader);

CATImplementClass( CAAESmiSurfaceMachiningAddin,
                   DataExtension,
                   CATBaseUnknown,
                   CAASmiWksAddin );
 
// Tie the implementation to its interface
#include "TIE_CATISmgProgramAddin.h"
TIE_CATISmgProgramAddin( CAAESmiSurfaceMachiningAddin);

//========================================================================
// Constructor
//========================================================================
CAAESmiSurfaceMachiningAddin::CAAESmiSurfaceMachiningAddin():
    CATBaseUnknown()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiSurfaceMachiningAddin::~CAAESmiSurfaceMachiningAddin()
{
}
 
//========================================================================
// CreateCommands
//========================================================================
void CAAESmiSurfaceMachiningAddin::CreateCommands()
{
	// Creation of CAASmgOperation
    static CATString CAASmgOperation ("CAASmgOperation");
	new CAASmiHeader("CreateUserActivity","CAASmiUserOperationCommand","CAASmiCreateUserOperationCom",(void *)&CAASmgOperation); 
	
    
    // Creation of CAASmgOperationWithMA
    static CATString CAASmgOperationWithMA ("CAASmgOperationWithMA");
	new CAASmiHeader("CreateUserActivityWithMA","CAASmiUserOperationCommand","CAASmiCreateUserOperationCom",(void *)&CAASmgOperationWithMA); 
}

//========================================================================
// CreateToolbars
//========================================================================
CATCmdContainer * CAAESmiSurfaceMachiningAddin::CreateToolbars()
{
	// Creation of User Activity Toolbar
    NewAccess(CATCmdContainer,PaletteUserActMain,ManufacturingUserActMain);
	SetAccessTitle(PaletteUserActMain,"CAA SMG Tool Bar");
	AddToolbarView(PaletteUserActMain,1,Left);

	// Command CAASmgOperation
	NewAccess(CATCmdStarter,CreateUserActivity,CreateUserActivity);
    SetAccessCommand(CreateUserActivity,"CreateUserActivity");
	SetAccessChild(PaletteUserActMain,CreateUserActivity);

	// Command CAASmgOperationWithMA
	NewAccess(CATCmdStarter,CreateUserActivityWithMA,CreateUserActivityWithMA);
    SetAccessCommand(CreateUserActivityWithMA,"CreateUserActivityWithMA");
	SetAccessNext(CreateUserActivity,CreateUserActivityWithMA);

	return PaletteUserActMain;
}


