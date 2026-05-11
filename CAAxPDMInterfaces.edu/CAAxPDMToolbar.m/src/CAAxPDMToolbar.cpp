// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAxPDMToolbar.cpp
//
//===================================================================
//
// Usage notes:
//
//===================================================================
#include "CAAxPDMToolbar.h"

// ApplicationFrame
#include "CATCommandHeader.h"
#include "CATCreateWorkshop.h"
#include "CATCmdContainer.h"
#include "CAAxPDMTSTCommandHeader.h"

//MacDeclareHeader(CAAxPDMTSTCommandHeader);

CATImplementClass( CAAxPDMToolbar,Implementation,CATBaseUnknown,CATNull);

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIAfrGeneralWksAddin.h"
TIE_CATIAfrGeneralWksAddin(CAAxPDMToolbar);

//-----------------------------------------------------------------------------
// CAAxPDMToolbar : constructor
//-----------------------------------------------------------------------------
CAAxPDMToolbar::CAAxPDMToolbar():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAxPDMToolbar : destructor
//-----------------------------------------------------------------------------
CAAxPDMToolbar::~CAAxPDMToolbar()
{
}


void CAAxPDMToolbar::CreateCommands()
{
   new CAAxPDMTSTCommandHeader("CAASaveSessionToDirectoryHdr", "CAAxPDMUICommands", "CAAxPDMPackSessionCmd", (void*)0);
   new CAAxPDMTSTCommandHeader("CAAPX1ConnectHdr", "CAAxPDMUICommands", "CAAxPDMConnectCmd", (void*)0,CATFrmAvailable,1);
   new CAAxPDMTSTCommandHeader("CAAPX1DisconnectHdr", "CAAxPDMUICommands", "CAAxPDMDisconnectCmd", (void*)0);
   new CAAxPDMTSTCommandHeader("CAAPX1PropertiesHdr", "CAAxPDMUICommands", "CAAxPDMPropertyCmd", (void*)0);

   new CAAxPDMTSTCommandHeader("CAAPX1DRMTemplateHdr", "CAAxPDMUICommands", "CAAxPDMDRMTemplateCmd", (void*)0);

   static CATString CheckIn("CheckIn");
   new CAAxPDMTSTCommandHeader("CAAPX1CheckInHdr", "CAAxPDMUICommands", "CAAxPDMCheckInOutCmd", (void*)&CheckIn);
   static CATString CheckOut("CheckOut");
   new CAAxPDMTSTCommandHeader("CAAPX1CheckOutHdr", "CAAxPDMUICommands", "CAAxPDMCheckInOutCmd", (void*)&CheckOut);
}

CATCmdContainer* CAAxPDMToolbar::CreateToolbars()
{
   NewAccess(CATCmdContainer, pTSTCAAxPDMToolbar, CAAxPDMToolbar);
   
   NewAccess(CATCmdStarter, pCAAConnect, CAAConnect);    
   SetAccessCommand(pCAAConnect, "CAAPX1ConnectHdr");
   SetAccessChild(pTSTCAAxPDMToolbar, pCAAConnect);
      
   NewAccess(CATCmdStarter, pCAACheckOut, CAACheckOut);    
   SetAccessCommand(pCAACheckOut, "CAAPX1CheckOutHdr");
   SetAccessNext(pCAAConnect, pCAACheckOut);

   NewAccess(CATCmdStarter, pCAAProperty, CAAProperty);    
   SetAccessCommand(pCAAProperty, "CAAPX1PropertiesHdr");
   SetAccessNext(pCAACheckOut, pCAAProperty);

   NewAccess(CATCmdStarter, pCAADRMTemplate, CAADRMTemplate);    
   SetAccessCommand(pCAADRMTemplate, "CAAPX1DRMTemplateHdr");
   SetAccessNext(pCAAProperty, pCAADRMTemplate);

   NewAccess(CATCmdStarter, pCAASaveSession, CAASaveSession);    
   SetAccessCommand(pCAASaveSession, "CAASaveSessionToDirectoryHdr");
   SetAccessNext(pCAADRMTemplate, pCAASaveSession);

   NewAccess(CATCmdStarter, pCAACheckIn, CAACheckIn);    
   SetAccessCommand(pCAACheckIn, "CAAPX1CheckInHdr");
   SetAccessNext(pCAASaveSession, pCAACheckIn);

   NewAccess(CATCmdStarter, pCAADisconnect, CAADisconnect);    
   SetAccessCommand(pCAADisconnect, "CAAPX1DisconnectHdr");
   SetAccessNext(pCAACheckIn, pCAADisconnect);

   pTSTCAAxPDMToolbar->SetTitle("PX1 CAASample");
   AddToolbarView(pTSTCAAxPDMToolbar, -1, Top);
   
   return pTSTCAAxPDMToolbar;
}
