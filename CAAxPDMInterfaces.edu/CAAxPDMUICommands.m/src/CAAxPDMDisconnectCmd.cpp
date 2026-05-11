// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMDisconnectCmd.h"

//include ApplicationFrame
#include "CATApplicationFrame.h"
#include "CATDlgNotify.h"
//include CATxPDMInterfaces
#include "CATxPDMSessionUIServices.h"
//include CAAxPDMInterfaces.edu
#include "CAAxPDMManager.h"
#include "CAASysDRMCtrl.h"

#include "CATCreateExternalObject.h"
CATCreateClass(CAAxPDMDisconnectCmd);


CATImplementClass(CAAxPDMDisconnectCmd, Implementation, CATStateCommand,CATNull);

//========================================================================
// Commande
//========================================================================

//------------------------------------------------------------------------
//	Constructeur/Destructeur
//------------------------------------------------------------------------
CAAxPDMDisconnectCmd::CAAxPDMDisconnectCmd():CATStateCommand("DisconnectFromPX1")
{
}
//------------------------------------------------------------------------
CAAxPDMDisconnectCmd::~CAAxPDMDisconnectCmd()
{
}
//------------------------------------------------------------------------
void CAAxPDMDisconnectCmd::BuildGraph()
{
}

//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMDisconnectCmd::Activate(CATCommand*, CATNotification*)
{
   //------------------------------------------------------------------
   //------------------------------------------------------------------
   //PERFORM HERE YOUR DISCONNECT FROM YOUR PDM
   //------------------------------------------------------------------
   //------------------------------------------------------------------

   //Deactivate DRM
   CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
   if (ctrl)
   {
      ctrl->SetDRMActivation(0);
      ctrl->UpdateCtrl(NULL,NULL);
   }

   //Disconnect from PX1
   HRESULT rc = CATxPDMSessionUIServices::DisconnectFromPX1();

   //Deactivate PX1 icons
   if (SUCCEEDED(rc))
   {
      CAAxPDMManager* xPDMManager = CAAxPDMManager::GetCAAxPDMManager();
      if(xPDMManager)
         xPDMManager->Disconnect();
   }


   //Display report
   CATDlgNotify* notif=NULL;
   CATUnicodeString texte;
   CATApplicationFrame*pApplication = CATApplicationFrame::GetFrame();
   if (pApplication)
   {
      if (rc==E_FAIL)
      {
         notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyError);
         texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","DisconnectFailed",NULL,0,"Disconnect Failed");
      }
      else if (rc==S_FALSE)
      {
         notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyInformation|CATDlgWndNoButton);
         texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","NotConnect",NULL,0,"Not Connected");
      }
      else if (rc==S_OK)
      {
         notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyInformation|CATDlgWndNoButton);
         texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","DisconnectOK",NULL,0,"Disconnect Successfull");
      }
      if (notif)
      {
         notif->DisplayBlocked(texte,"Warning");
         notif->RequestDelayedDestruction();
      }
   }
   RequestDelayedDestruction();
   return CATStatusChangeRCCompleted;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMDisconnectCmd::Cancel(CATCommand* cmd, CATNotification* notif)
{
   return CATStateCommand::Cancel(cmd, notif);
}

