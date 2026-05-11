// COPYRIGHT DASSAULT SYSTEMES 2006
/**
* 06:01:16 Support Record Mode for ODTs on Save Directory Initialization
* 06:02:10 Better display name for item loaded from ENOVIA VPM or ENOVIA V5
* 06:03:20 Add Support of Rules Check before Save
* 06:12:07 Add Init save directory with CATIA current directory
*/
#include "CAAxPDMPackSessionCmd.h"
#include "CAAxPDMPackSessionPanel.h"
#include "CAAxPDMCheckSessionPanel.h"

//include System
#include "CATListOfCATUnicodeString.h"
#include "CATGetEnvValue.h"
//include ApplicationFrame
#include "CATApplicationFrame.h"
#include "CATDlgNotify.h"
//include DialogEngine
#include "CATDialogState.h"
#include "CATDialogTransition.h"
//include ObjectModelerBase
#include "CATIDocEnvironment.h"
#include "CATIDocId.h"
#include "CATLISTP_CATIReporterInfo.h"
#include "CATIReporter.h"
#include "CATIReporterInfo.h"
//include CATxPDMInterfaces
#include "CATxPDMSessionServices.h"
#include "CATxPDMSessionUIServices.h"

#include "CATCreateExternalObject.h"
CATCreateClass(CAAxPDMPackSessionCmd);


CATImplementClass(CAAxPDMPackSessionCmd, Implementation, CATStateCommand,CATNull);

//-----------------------------------------------------------------------------
// RetrieveNameFromPath
//-----------------------------------------------------------------------------
CATUnicodeString RetrieveNameFromPath(CATUnicodeString& iPath)
{
   CATUnicodeString rc;
   int Length = -1;
   int idxBackSlash = iPath.SearchSubString("\\", 0, CATUnicodeString::CATSearchModeBackward);
   int idxSlash = iPath.SearchSubString("/", 0, CATUnicodeString::CATSearchModeBackward);
   if (idxBackSlash!=-1)
      Length=idxBackSlash;
   if (idxSlash!=-1 && idxSlash>Length)
      Length=idxSlash;
   if (Length != -1)
   {
      int NbLength = iPath.GetLengthInChar();
      rc = iPath.SubString(Length + 1, NbLength - (Length+1));
   }
   else rc=iPath;
   return rc;
}

//========================================================================
// Commande
//========================================================================

//------------------------------------------------------------------------
//	Constructeur/Destructeur
//------------------------------------------------------------------------
CAAxPDMPackSessionCmd::CAAxPDMPackSessionCmd():CATStateCommand("SaveSession"),
_PanelOKAcq(NULL),_PanelAPPLYAcq(NULL),_PanelCANCELAcq(NULL),_Panel(NULL),
_PanelCheckOKAcq(NULL),_PanelCheckCANCELAcq(NULL),_PanelCheck(NULL)
{
   _ListItem=NULL;
}
//------------------------------------------------------------------------
CAAxPDMPackSessionCmd::~CAAxPDMPackSessionCmd()
{
   _Panel=NULL;
   _PanelCheck=NULL;
   _PanelOKAcq=NULL;
   _PanelAPPLYAcq=NULL;
   _PanelCANCELAcq=NULL;
   _PanelCheckOKAcq=NULL;
   _PanelCheckCANCELAcq=NULL;
   if (_ListItem) delete _ListItem; _ListItem=NULL;
}
//------------------------------------------------------------------------
void CAAxPDMPackSessionCmd::BuildGraph()
{
   CATApplicationFrame* AppliFr = CATApplicationFrame::GetApplicationFrame();
   if (NULL==AppliFr) {RequestDelayedDestruction();return;}
   CATDialog * TempoParent = (CATDialog *) AppliFr -> GetMainWindow();
   _Panel = new CAAxPDMPackSessionPanel(TempoParent);
   if (NULL==_Panel) {RequestDelayedDestruction();return;}
   _PanelCheck = new CAAxPDMCheckSessionPanel(TempoParent);
   if (NULL==_PanelCheck) {RequestDelayedDestruction();return;}
   
   //--------------Create Selections's Agents--------
   //selection in panel
   _PanelOKAcq = new CATDialogAgent ("AgentOK");
   _PanelAPPLYAcq = new CATDialogAgent ("AgentAPPLY"); 
   _PanelCANCELAcq = new CATDialogAgent ("AgentCANCEL"); 
   if (NULL==_PanelOKAcq||NULL==_PanelAPPLYAcq||NULL==_PanelCANCELAcq) {RequestDelayedDestruction();return;}
   _PanelOKAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaOKNotification());
   _PanelAPPLYAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaAPPLYNotification());
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaCANCELNotification());
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetWindCloseNotification());
   //selection in panel with checks
   _PanelCheckOKAcq = new CATDialogAgent ("AgentCheckOK");
   _PanelCheckCANCELAcq = new CATDialogAgent ("AgentCheckCANCEL"); 
   if (NULL==_PanelCheckOKAcq||NULL==_PanelCheckCANCELAcq) {RequestDelayedDestruction();return;}
   _PanelCheckOKAcq -> AcceptOnNotify (_PanelCheck,_PanelCheck->GetDiaOKNotification());
   _PanelCheckCANCELAcq -> AcceptOnNotify (_PanelCheck,_PanelCheck->GetDiaCANCELNotification());
   _PanelCheckCANCELAcq -> AcceptOnNotify (_PanelCheck,_PanelCheck->GetWindCloseNotification());

   
   //--------------Define Statechart's States--------------
   CATDialogState* state1 = GetInitialState("ListToSave");
   if (NULL==state1) {RequestDelayedDestruction();return;}
   state1->AddDialogAgent(_PanelOKAcq);
   state1->AddDialogAgent(_PanelAPPLYAcq);
   state1->AddDialogAgent(_PanelCANCELAcq);
   
   CATDialogState* state2 = AddDialogState("Check");
   if (NULL==state2) {RequestDelayedDestruction();return;}
   state2->AddDialogAgent(_PanelCheckOKAcq);
   state2->AddDialogAgent(_PanelCheckCANCELAcq);

   //-----------Define Statechart's Transitions-----------
   // APPLY
   AddTransition (state1, state2,AndCondition(IsOutputSetCondition(_PanelAPPLYAcq),Condition((ConditionMethod)&CAAxPDMPackSessionCmd::CheckOnly)),
      Action((ActionMethod)&CAAxPDMPackSessionCmd::ExecuteEnd));
   // CANCEL
   AddTransition (state1,NULL,IsOutputSetCondition(_PanelCANCELAcq),
      Action((ActionMethod)&CAAxPDMPackSessionCmd::Quit));
   // OK
   AddTransition (state1, state2,AndCondition(IsOutputSetCondition(_PanelOKAcq),Condition((ConditionMethod)&CAAxPDMPackSessionCmd::ValidateChecks)),
      Action((ActionMethod)&CAAxPDMPackSessionCmd::ExecuteEnd));
   //OK on Check Panel
   AddTransition (state2, NULL,AndCondition(IsOutputSetCondition(_PanelCheckOKAcq),Condition((ConditionMethod)&CAAxPDMPackSessionCmd::Validate)),
      Action((ActionMethod)&CAAxPDMPackSessionCmd::ExecuteEnd));
   //CANCEL on Check Panel
   AddTransition (state2,state1,IsOutputSetCondition(_PanelCheckCANCELAcq),
      Action((ActionMethod)&CAAxPDMPackSessionCmd::RefuseChecks));

   if (!RefreshPanel())
   {
      CATDlgNotify* notif = new CATDlgNotify(AppliFr->GetApplicationDocument(),"Notif",CATDlgNfyInformation);
      CATUnicodeString texte=CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","Warning1",NULL,0,"Nothing");
      notif->DisplayBlocked(texte,"Warning");
      notif->RequestDelayedDestruction();
      RequestDelayedDestruction();
   }
   _Panel->SetVisibility(CATDlgShow);
}

static CATUnicodeString lastUsedDirectory;


//------------------------------------------------------------------------
//   Action : Update Panel Display
//------------------------------------------------------------------------
boolean CAAxPDMPackSessionCmd::RefreshPanel()
{
   if (!lastUsedDirectory.GetLengthInChar())
   {
      char *slash_tmp = NULL;
      if (CATGetEnvValue("ADL_ODT_TMP", &slash_tmp) == CATLibSuccess)
         lastUsedDirectory = slash_tmp;
      if (slash_tmp) free(slash_tmp); slash_tmp=NULL;
   }
   if (!lastUsedDirectory.GetLengthInChar())
   {
      //Initialiaze with CATIA last used directory
      CATxPDMSessionUIServices::GetCurrentDirectory(lastUsedDirectory);
   }
   if (!lastUsedDirectory.GetLengthInChar())
   {
      char *slash_tmp = NULL;
      if (CATGetEnvValue("CATTemp", &slash_tmp) == CATLibSuccess)
         lastUsedDirectory = slash_tmp;
      if (slash_tmp) free(slash_tmp); slash_tmp=NULL;
   }
   boolean sortie=FALSE;
   if (_Panel)
   {
      _Panel->SetCurrentPath( lastUsedDirectory );
      CATxPDMSessionServices::GetxPDMItemsInSession(_ListItem);
      sortie = _Panel->RefreshPanel(_ListItem);
   }
   return sortie;
}

//------------------------------------------------------------------------
boolean CAAxPDMPackSessionCmd::RefreshCheckPanel(CATListValCATIxPDMItem_var* oItemsWithError,CATIReporter* oReporter)
{
   if (_PanelCheck && oItemsWithError && oReporter)
   {
      const CATLISTP(CATIReporterInfo) listerror = oReporter->GetListReporterInfo();
      CATListOfCATUnicodeString list1,list2,list3;
      for (int i=1;i<=listerror.Size();i++)
      {
         CATIReporterInfo* info = listerror[i];
         if (info)
         {
            CATUnicodeString oStr;
            info->GetAssociatedString(oStr);
            CATError* error=NULL;
            info->GetError(error);
            if (error)
            {
               list1.Append(oStr);
               int ier = error->GetId();
               CATUnicodeString err;
               err.BuildFromNum(ier);
               list2.Append(err);
               list3.Append(error->GetNLSMessage());
               error->Release(); error=NULL;
            }
         }
      }
      _PanelCheck->SetListInfo(list1,list2,list3,oItemsWithError);
   }
   return TRUE;
}

//------------------------------------------------------------------------
//   Action : OK button
//------------------------------------------------------------------------
boolean CAAxPDMPackSessionCmd::ValidateChecks(void*)
{
   //Launch the checker
   boolean sortie=TRUE;
   if (_Panel)
   {
      CATListOfCATString iListOfRulesToCheck = _Panel->GetListOfChecks();
      CATListValCATIxPDMItem_var* oItemsWithError=NULL;
      CATIReporter* oReporter=NULL;
      HRESULT rc = S_OK;
      if (iListOfRulesToCheck.Size())
         rc = CATxPDMSessionServices::CheckDesignRules(iListOfRulesToCheck,oItemsWithError,oReporter);
      if (SUCCEEDED(rc))
      {
         if (rc==S_FALSE)
         {
            //There is some errors to check
            if (_PanelCheck)
            {
               RefreshCheckPanel(oItemsWithError,oReporter);
               _PanelCheck->SetVisibility(CATDlgShow);
            }
         }
         else
         {
            //No error, we skip this validation step automatically
            if (_PanelCheckOKAcq)
            {
               _PanelCheckOKAcq->Accept();
               _PanelOKAcq->InitializeAcquisition();
               _PanelAPPLYAcq->InitializeAcquisition();
            }
         }
      }
      else
      {
         if (_PanelOKAcq)
            _PanelOKAcq->InitializeAcquisition();
         if (_PanelAPPLYAcq)
            _PanelAPPLYAcq->InitializeAcquisition();
         CATApplicationFrame* applicationFrame=CATApplicationFrame::GetFrame();
         if (applicationFrame)
         {
            CATDlgNotify* notif = new CATDlgNotify(applicationFrame->GetApplicationDocument(),"Notif",CATDlgNfyError|CATDlgWndOK);
            CATUnicodeString num=CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","CheckFail",NULL,0,"OK");
            num.Append("\n");
            CATError * pError = CATError::CATGetLastError(rc);
            if ( NULL != pError )
               num.Append(pError->GetNLSMessage());
            CATError::CATCleanLastError();
            notif->DisplayBlocked(num,"Error");
            notif->RequestDelayedDestruction();
         }
         sortie=FALSE;
      }
      if (oReporter) oReporter->Release(); oReporter=NULL;
      //No delete, lifecycle is managed by panel
      //if (oItemsWithError) delete oItemsWithError; oItemsWithError=NULL;
   }
   return sortie;
}

//------------------------------------------------------------------------
//   Action : OK button
//------------------------------------------------------------------------
boolean CAAxPDMPackSessionCmd::CheckOnly(void*)
{
   //Launch the checker
   boolean sortie=TRUE;
   if (_Panel)
   {
      CATListOfCATString iListOfRulesToCheck = _Panel->GetListOfChecks();
      CATListValCATIxPDMItem_var* oItemsWithError=NULL;
      CATIReporter* oReporter=NULL;
      HRESULT rc = S_OK;
      if (iListOfRulesToCheck.Size())
         rc = CATxPDMSessionServices::CheckDesignRules(iListOfRulesToCheck,oItemsWithError,oReporter);
      if (SUCCEEDED(rc))
      {
         if (rc==S_FALSE)
         {
            //There is some errors to check
            if (_PanelCheck)
            {
               RefreshCheckPanel(oItemsWithError,oReporter);
               _PanelCheck->SetVisibility(CATDlgShow);
            }
         }
         else
         {
            //No error, we refuse transition
            sortie=FALSE;
            if (_PanelAPPLYAcq)
            {
               _PanelAPPLYAcq->InitializeAcquisition();
               CATApplicationFrame* applicationFrame=CATApplicationFrame::GetFrame();
               if (applicationFrame)
               {
                  CATDlgNotify* notif = new CATDlgNotify(applicationFrame->GetApplicationDocument(),"Notif",CATDlgNfyInformation|CATDlgWndOK);
                  CATUnicodeString num=CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","NoCheckProblem",NULL,0,"OK");
                  num.Append("\n");
                  CATError * pError = CATError::CATGetLastError(rc);
                  if ( NULL != pError )
                     num.Append(pError->GetNLSMessage());
                  notif->DisplayBlocked(num,"Error");
                  notif->RequestDelayedDestruction();
               }
            }
         }
      }
      else
      {
         if (_PanelAPPLYAcq)
            _PanelAPPLYAcq->InitializeAcquisition();
         CATApplicationFrame* applicationFrame=CATApplicationFrame::GetFrame();
         if (applicationFrame)
         {
            CATDlgNotify* notif = new CATDlgNotify(applicationFrame->GetApplicationDocument(),"Notif",CATDlgNfyError|CATDlgWndOK);
            CATUnicodeString num=CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","CheckFail",NULL,0,"OK");
            num.Append("\n");
            CATError * pError = CATError::CATGetLastError(rc);
            if ( NULL != pError )
               num.Append(pError->GetNLSMessage());
            notif->DisplayBlocked(num,"Error");
            notif->RequestDelayedDestruction();
         }
         sortie=FALSE;
      }
      if (oReporter) oReporter->Release(); oReporter=NULL;
      //No delete, lifecycle is managed by panel
      //if (oItemsWithError) delete oItemsWithError; oItemsWithError=NULL;
   }
   return sortie;
}

boolean CAAxPDMPackSessionCmd::RefuseChecks(void*)
{
   if (_PanelOKAcq)
      _PanelOKAcq->InitializeAcquisition();
   if (_PanelAPPLYAcq)
      _PanelAPPLYAcq->InitializeAcquisition();
   if (_PanelCheckCANCELAcq)
      _PanelCheckCANCELAcq->InitializeAcquisition();
   if (_PanelCheck)
      _PanelCheck->SetVisibility(CATDlgHide);
   return TRUE;
}
//------------------------------------------------------------------------
//   Action : OK button
//------------------------------------------------------------------------
boolean CAAxPDMPackSessionCmd::Validate(void*)
{
   if (!_Panel) return FALSE;
   boolean sortie=FALSE;
   HRESULT RC=E_FAIL;
   CATUnicodeString path = lastUsedDirectory = _Panel->GetCurrentPath();
   CATListOfCATUnicodeString ListName = _Panel->GetListOfRenamedItems();
      
   CATListValCATIxPDMItem_var ListItemToRename;
   CATListOfCATUnicodeString ListNewName;
   CATLISTP_FORWARD_LOOP(ListName,kk)
   {
      CATUnicodeString name = ListName[kk];
      if (name.GetLengthInChar())
      {
         if (_ListItem && _ListItem->Size()>=kk) 
         {
            CATIxPDMItem_var item = (*_ListItem)[kk];
            ListItemToRename.Append(item);
            ListNewName.Append(name);
         }
      }
   }
   CATLISTP_END_LOOP;

   CATUnicodeString Message;
   RC = CATxPDMSessionServices::SaveSessionToDirectory(path.ConvertToChar(),Message,&ListItemToRename,&ListNewName);

   CATApplicationFrame* applicationFrame=CATApplicationFrame::GetFrame();
   if (applicationFrame)
   {
      if (SUCCEEDED(RC))
      {
         CATDlgNotify* notif = new CATDlgNotify(applicationFrame->GetApplicationDocument(),"Notif",CATDlgWndNoButton);
         CATUnicodeString num=CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","SaveOK",NULL,0,"OK");
         num.Append("\n");
         num.Append(Message);
         notif->DisplayBlocked(num,"Information");
         notif->RequestDelayedDestruction();
         sortie=TRUE;
      }
      else
      {
         CATDlgNotify* notif = new CATDlgNotify(applicationFrame->GetApplicationDocument(),"Notif",CATDlgNfyError);
         CATUnicodeString texte=CATMsgCatalog::BuildMessage("CAAxPDMPackSessionPanel","SaveKO",NULL,0,"KO");
         texte.Append("\n");
         CATError * pError = CATError::CATGetLastError(RC);
         if ( NULL != pError )
         {
            if (pError->GetId()==1108 || pError->GetId()==1109)
               texte.Append(Message);
            else
               texte.Append(pError->GetNLSMessage());
         }
         notif->DisplayBlocked(texte,"Error");
         notif->RequestDelayedDestruction();
      }
   }
   if (_PanelCheck) _PanelCheck->SetVisibility(CATDlgHide);
   if (_PanelOKAcq && sortie==FALSE) _PanelOKAcq->InitializeAcquisition();
   if (_PanelAPPLYAcq && sortie==FALSE) _PanelAPPLYAcq->InitializeAcquisition();
   if (_PanelCheckOKAcq) _PanelCheckOKAcq->InitializeAcquisition();
   return sortie;
}
//------------------------------------------------------------------------
boolean CAAxPDMPackSessionCmd::Execute(void*)
{
   return TRUE;
}
boolean CAAxPDMPackSessionCmd::ExecuteEnd(void*)
{
   return TRUE;
}
boolean CAAxPDMPackSessionCmd::Quit(void*)
{
   ExecuteUndoAtEnd();
   return TRUE;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMPackSessionCmd::Activate(CATCommand*, CATNotification*)
{
   return CATStatusChangeRCCompleted;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMPackSessionCmd::Cancel(CATCommand* cmd, CATNotification* notif)
{
   if (_Panel) _Panel->RequestDelayedDestruction();
   _Panel = NULL;
   if (_PanelOKAcq) _PanelOKAcq->RequestDelayedDestruction();
   _PanelOKAcq = NULL;
   if (_PanelAPPLYAcq) _PanelAPPLYAcq->RequestDelayedDestruction();
   _PanelAPPLYAcq = NULL;
   if (_PanelCANCELAcq) _PanelCANCELAcq->RequestDelayedDestruction();
   _PanelCANCELAcq = NULL;
   if (_PanelCheck) _PanelCheck->RequestDelayedDestruction();
   _PanelCheck = NULL;
   if (_PanelCheckOKAcq) _PanelCheckOKAcq->RequestDelayedDestruction();
   _PanelCheckOKAcq = NULL;
   if (_PanelCheckCANCELAcq) _PanelCheckCANCELAcq->RequestDelayedDestruction();
   _PanelCheckCANCELAcq = NULL;
   return CATStateCommand::Cancel(cmd, notif);
}

