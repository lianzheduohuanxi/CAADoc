// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CAA2DLAddin
//   Addin to add CAA sample commands to 2DL workbench.
//   Provide implementation for CATI2DLMainWkbAddin interface.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007  Creation
//=============================================================================

//---------------------------------------------- Include File of this extension
#include "CAA2DLAddin.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATCreateWorkshop.h"

//-------------------------------------------------CAADrafting2DLInterfaces.edu
#include "CAA2DLHeader.h"

//--------------------------------------------------------- Supported Interface
#include "TIE_CATI2DLMainWkbAddin.h"
TIE_CATI2DLMainWkbAddin(CAA2DLAddin);

CATImplementClass (CAA2DLAddin, DataExtension, CATBaseUnknown, CAA2DLAddinObj);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAA2DLAddin::CAA2DLAddin ()
{}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAA2DLAddin::~CAA2DLAddin ()
{}


//-----------------------------------------------------------------------------
// CreateCommands                                           CATI2DLMainWkbAddin
//-----------------------------------------------------------------------------
void CAA2DLAddin::CreateCommands ()
{
  new CAA2DLHeader("CAA2DLPrintToDraftingHdr", // Header name
                   "CAA2DLPrintToDrafting", // Module containing the command
                   "CAA2DLPrintToDraftingCmd", // Command class name
                   (void*)NULL);
}


//-----------------------------------------------------------------------------
// CreateToolbars                                           CATI2DLMainWkbAddin
//-----------------------------------------------------------------------------
CATCmdContainer * CAA2DLAddin::CreateToolbars ()
{
  // Create container and starter
  NewAccess (CATCmdContainer, opCAA2DLContainer, CAA2DLSampleTlb);

    NewAccess (CATCmdStarter, pStarterCAA2DL1, ButtonCAA2DL1);
    SetAccessCommand (pStarterCAA2DL1, "CAA2DLPrintToDraftingHdr");
    SetAccessChild (opCAA2DLContainer, pStarterCAA2DL1);

  // Invisible Toolbar (-1) that appear Undocked
  AddToolbarView (opCAA2DLContainer, -1, UnDock);

  return (opCAA2DLContainer);
}
