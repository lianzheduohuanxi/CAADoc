// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
// CAACV5EV5IntergrationToolbar.cpp
// Creation : BZQ - 08.29.2007
//
//===================================================================

/*
* @quickreview SDM ZPL 08:12:04 Added var CAAEnoviaV5SaveToPDMCmd_ODT to support new ODT CAACV5AccessEV5nSaveToPDM
* @fullReview BZQ 07:08:29 Creation
*/

#include"CAACV5EV5IntegrationToolbar.h"

#include"CATCommandHeader.h"
MacDeclareHeader(CAACV5EV5ToolbarHeader);

CATImplementClass(CAACV5EV5IntegrationToolbar, DataExtension, CATBaseUnknown, CAACV5EV5Toolbar);

#include "TIE_CATIAfrGeneralWksAddin.h"
TIE_CATIAfrGeneralWksAddin(CAACV5EV5IntegrationToolbar);

#include "CATCmdContainer.h"
#include "CATCreateWorkshop.h"
#include "CATMsgCatalog.h"
#include "CATGetEnvValue.h"

//-----------------------------------------------------------------------------
// CAACV5EV5IntegrationToolbar Constructor
//-----------------------------------------------------------------------------
CAACV5EV5IntegrationToolbar::CAACV5EV5IntegrationToolbar() : CATBaseUnknown() {}


//-----------------------------------------------------------------------------
// CAACV5EV5IntegrationToolbar Destructor
//-----------------------------------------------------------------------------
CAACV5EV5IntegrationToolbar::~CAACV5EV5IntegrationToolbar() {}

//-----------------------------------------------------------------------------
// CAACV5EV5IntegrationToolbar CreatCommands
//-----------------------------------------------------------------------------
void CAACV5EV5IntegrationToolbar::CreateCommands()
{
  //ZPL: New ODT code to be called with this toolbar command, hence added it inside the variable
  if (CATGetEnv("CAAEnoviaV5SaveToPDMCmd_ODT"))
  {
    new CAACV5EV5ToolbarHeader("CAAEnoviaV5SaveCmdHdr", "CAAEnoviaV5SaveToPDM", "CAAEnoviaV5SaveToPDMCmd", (void*)NULL);
  }
  // Create Instance of the "CAAEnoviaV5SaveCmd" Command Header
  else
  {
    new CAACV5EV5ToolbarHeader("CAAEnoviaV5SaveCmdHdr", "CAAEnoviaV5SaveCmd", "CAAEnoviaV5SaveCmd", (void*)NULL);
  }
}

//-----------------------------------------------------------------------------
// CAACV5EV5IntegrationToolbar CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer * CAACV5EV5IntegrationToolbar::CreateToolbars()
{
  NewAccess(CATCmdContainer, pCAACV5EV5Toolbar, CAACV5EV5IntegrationToolbar);

  //ZPL: New ODT code to be called with this toolbar command, hence added it inside the variable
  if (CATGetEnv("CAAEnoviaV5SaveToPDMCmd_ODT"))
  {
    NewAccess(CATCmdStarter, pCAAEnoviaV5SaveCmdStarter, CAAEnoviaV5SaveToPDMCmd); 
    SetAccessCommand(pCAAEnoviaV5SaveCmdStarter, "CAAEnoviaV5SaveCmdHdr");
    SetAccessChild(pCAACV5EV5Toolbar, pCAAEnoviaV5SaveCmdStarter);
  }
  else 
  {
    NewAccess(CATCmdStarter, pCAAEnoviaV5SaveCmdStarter, CAAEnoviaV5SaveCmd);
    SetAccessCommand(pCAAEnoviaV5SaveCmdStarter, "CAAEnoviaV5SaveCmdHdr");
    SetAccessChild(pCAACV5EV5Toolbar, pCAAEnoviaV5SaveCmdStarter);
  }

  CATUnicodeString title = CATMsgCatalog::BuildMessage("CAACV5EV5IntegrationToolbar", "CAACV5EV5IntegrationToolbar.Title");   
  pCAACV5EV5Toolbar->SetTitle(title);
  
  AddToolbarView(pCAACV5EV5Toolbar, 1, Right);

  return pCAACV5EV5Toolbar;
}
