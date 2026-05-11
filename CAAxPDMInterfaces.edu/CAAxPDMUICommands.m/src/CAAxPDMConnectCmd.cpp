// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMConnectCmd.h"

//include System
#include "CATGetEnvValue.h"
#include "CATSysDRMRights.h"
#include "CATSysDRMHR.h"
//include Dialog
#include "CATDlgNotify.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
#include "CATDlgNotify.h"
//include CATxPDMInterfaces
#include "CATxPDMSessionUIServices.h"
#include "CATxPDMSessionServices.h"
//include CAAxPDMInterfaces.edu
#include "CAAxPDMManager.h"
#include "CAAxPDMConnectPanel.h"
#include "CAASysDRMCtrl.h"

#include "CATCreateExternalObject.h"
CATCreateClass(CAAxPDMConnectCmd);

CATUnicodeString CAAxPDMConnectCmd::_User = "";

CATImplementClass(CAAxPDMConnectCmd, Implementation, CATStateCommand,CATNull);

//========================================================================
// Commande
//========================================================================

//------------------------------------------------------------------------
//	Constructeur/Destructeur
//------------------------------------------------------------------------
CAAxPDMConnectCmd::CAAxPDMConnectCmd():CATStateCommand("ConnectToPX1")
{
   _Panel=NULL;
   _PanelOKAcq=NULL;
   _PanelCANCELAcq=NULL;
}
//------------------------------------------------------------------------
CAAxPDMConnectCmd::~CAAxPDMConnectCmd()
{
   _Panel=NULL;
   _PanelOKAcq=NULL;
   _PanelCANCELAcq=NULL;
}
//------------------------------------------------------------------------
void CAAxPDMConnectCmd::BuildGraph()
{
   CATApplicationFrame* AppliFr = CATApplicationFrame::GetApplicationFrame();
   if (NULL==AppliFr) {RequestDelayedDestruction();return;}
   CATDialog * TempoParent = (CATDialog *) AppliFr -> GetMainWindow();
   _Panel = new CAAxPDMConnectPanel(TempoParent);
   if (NULL==_Panel) {RequestDelayedDestruction();return;}
   
   //--------------Create Selections's Agents--------
   //selection in panel
   _PanelOKAcq = new CATDialogAgent ("AgentOK"); 
   _PanelCANCELAcq = new CATDialogAgent ("AgentCANCEL"); 
   if (NULL==_PanelOKAcq) {RequestDelayedDestruction();return;}
   if (NULL==_PanelCANCELAcq) {RequestDelayedDestruction();return;}
   _PanelOKAcq     -> AcceptOnNotify (_Panel,_Panel->GetDiaOKNotification());
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaCANCELNotification());
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetWindCloseNotification());
   
   //--------------Define Statechart's States--------------
   CATDialogState* state1 = GetInitialState("Connect");
   if (NULL==state1) {RequestDelayedDestruction();return;}
   state1->AddDialogAgent(_PanelOKAcq);
   state1->AddDialogAgent(_PanelCANCELAcq);

   //Activate this variable for automatic connection without logon panel
   if (CATGetEnvValue ("CAAxPDM_AutoConnect", 0)==CATLibSuccess)
      _PanelOKAcq->Accept();

   //-----------Define Statechart's Transitions-----------
   // OK
   AddTransition (state1,NULL,IsOutputSetCondition(_PanelOKAcq),Action((ActionMethod)&CAAxPDMConnectCmd::Connect));
   // CANCEL
   AddTransition (state1,NULL,IsOutputSetCondition(_PanelCANCELAcq),Action((ActionMethod)&CAAxPDMConnectCmd::Quit));
}

//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMConnectCmd::Activate(CATCommand*, CATNotification*)
{
   if (_Panel)
      _Panel->SetVisibility(CATDlgShow);
   return CATStatusChangeRCCompleted;
}

//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMConnectCmd::Cancel(CATCommand* cmd, CATNotification* notif)
{
   if (_Panel) _Panel->RequestDelayedDestruction();
   _Panel = NULL;
   if (_PanelOKAcq) _PanelOKAcq->RequestDelayedDestruction();
   _PanelOKAcq = NULL;
   if (_PanelCANCELAcq) _PanelCANCELAcq->RequestDelayedDestruction();
   _PanelCANCELAcq = NULL;
   return CATStateCommand::Cancel(cmd, notif);
}

//------------------------------------------------------------------------
//   Action : Cancel button
//------------------------------------------------------------------------
boolean CAAxPDMConnectCmd::Quit(void*)
{
   ExecuteUndoAtEnd();
   return TRUE;
}

//------------------------------------------------------------------------
//   Action : OK button
//------------------------------------------------------------------------
boolean CAAxPDMConnectCmd::Connect(void*)
{
   CATDlgNotify* notif=NULL;
   CATUnicodeString texte;
   CATApplicationFrame*pApplication = CATApplicationFrame::GetFrame();
   if (_Panel && pApplication)
   {
      CATUnicodeString User = _Panel->GetUserId();
      HRESULT rc=E_FAIL;

      //If we try to connect again in session, with another user and with some document
      //loaded in session, it could lead to unpredictible behavior with DRM protections
      //because you change dynamically in session authorizations (it could lead to revoke
      //of read authorization)
      CATListValCATIxPDMItem_var* oListOfLoadedItem=new CATListValCATIxPDMItem_var;
      CATxPDMSessionServices::GetxPDMItemsInSession(oListOfLoadedItem);
      if (_User.GetLengthInChar() && User!=_User && oListOfLoadedItem && oListOfLoadedItem->Size())
      {
         CATApplicationFrame* AppliFr = CATApplicationFrame::GetApplicationFrame();
         if (AppliFr)
         {
            CATDialog * TempoParent = (CATDialog *) AppliFr -> GetMainWindow();
            CATDlgNotify* notif = new CATDlgNotify(TempoParent,"Error",CATDlgNfyError);
            CATUnicodeString texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","NoChangeUser");
            CATUnicodeString title=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","Error");
            notif->DisplayBlocked(texte,title);
            notif->RequestDelayedDestruction(); notif=NULL;
         }
      }
      else
      {
         //------------------------------------------------------------------
         //------------------------------------------------------------------
         //PERFORM HERE YOUR CONNECTION TO YOUR PDM
         //------------------------------------------------------------------
         //------------------------------------------------------------------
         //Connect To DRM System
         CAASysDRMCtrl *ctrl = CAASysDRMCtrl::GetCtrl();
         if (ctrl)
         {
            CATUnicodeString Pwd= _Panel->GetPassword();
            int role = _Panel->GetRole();
            if (User.GetLengthInChar() && Pwd.GetLengthInChar())
            {
               //Keep current user in memory
               _User = User;
               //Set Current User and Password
               ctrl->UpdateCtrl(User.ConvertToChar(), Pwd.ConvertToChar());
               //Set Default Rights
               CATUnicodeString * DRMUser = new CATUnicodeString [1];
               DRMUser [0] = User;
               DWORD* DRMRight = new DWORD [1];
               DWORD Right = 0;
               if (role==0) //AUTHOR
               {
                  //Initialize Controller for New documents
                  ctrl->SetDRMActivation(1);
                  int criptmode = 16;
                  ctrl->SetSymetricKeySize(criptmode);
                  //Choose Rights
                  Right |= CATDRM_READ;
                  Right |= CATDRM_SAVE;
                  Right |= CATDRM_SAVEAS;
                  //Right |= CATDRM_INHERIT_SAVEAS; //Not necessary as CATDRM_SAVEAS is available
                  Right |= CATDRM_EXPORT;
                  Right |= CATDRM_DUPLICATE_SPECS;
                  Right |= CATDRM_EDITRIGHT;
                  Right |= CATDRM_COLLABORATION;
                  Right |= CATDRM_COPY;
                  Right |= CATDRM_COPY_GEOMETRY;
                  DRMRight [0] = Right;
                  ctrl->SetAuthorization(DRMUser,DRMRight,1);
                  //Allow Save of document without DRM
                  ctrl->DRMSetProfile(0);
               }
               else if (role==1) //DESIGN SUPPLIER
               {
                  //Initialize Controller for New documents
                  ctrl->SetDRMActivation(1);
                  int criptmode = 16;
                  ctrl->SetSymetricKeySize(criptmode);
                  //Choose Rights
                  Right |= CATDRM_READ;
                  Right |= CATDRM_SAVE;
                  Right |= CATDRM_INHERIT_SAVEAS;
                  DRMRight [0] = Right;
                  ctrl->SetAuthorization(DRMUser,DRMRight,1);
                  //Forbid Save of document without DRM for better security
                  ctrl->DRMSetProfile(1);
               }
               else if (role==2) //DOWNSTREAM SUPPLIER
               {
                 Right |= CATDRM_READ;
                 Right |= CATDRM_COPY_GEOMETRY;
                 DRMRight [0] = Right; 
                 ctrl->SetAuthorization(DRMUser,DRMRight,1);
                  //Allow Save of document without DRM
                  //ctrl->SetDRMActivation(0);
                  ctrl->DRMSetProfile(2);
               }
               if (DRMUser) delete [] DRMUser; DRMUser=NULL;
               if (DRMRight) delete [] DRMRight; DRMRight=NULL;
            }
         }

         //Connect to PX1
         rc = CATxPDMSessionUIServices::ConnectToPX1();

         //Activate PX1 icons
         if (SUCCEEDED(rc))
         {
            CAAxPDMManager* xPDMManager = CAAxPDMManager::GetCAAxPDMManager();
            if(xPDMManager)
               xPDMManager->Connect();
         }
      }
      if (oListOfLoadedItem)
         delete oListOfLoadedItem; oListOfLoadedItem=NULL;
      //Display report
      CATDlgNotify* notif=NULL;
      CATUnicodeString texte;
      CATApplicationFrame*pApplication = CATApplicationFrame::GetFrame();
      if (pApplication)
      {
         if (rc==E_FAIL)
         {
            notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyError);
            texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","ConnectFailed",NULL,0,"Connect Failed");
         }
         else if (rc==S_FALSE)
         {
            notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyInformation|CATDlgWndNoButton);
            texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","AlreadyConnect",NULL,0,"Already Connect");
         }
         else if (rc==S_OK)
         {
            notif = new CATDlgNotify(pApplication->GetApplicationDocument(),"Notif",CATDlgNfyInformation|CATDlgWndNoButton);
            texte=CATMsgCatalog::BuildMessage("CAAxPDMConnectCmd","ConnectOK",NULL,0,"Connect Successfull");
         }
         if (notif)
         {
            notif->DisplayBlocked(texte,"Warning");
            notif->RequestDelayedDestruction();
         }
      }
   }
   RequestDelayedDestruction();
   return CATStatusChangeRCCompleted;
}
