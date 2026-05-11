// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMDRMTemplateCmd.h"
#include "CAAxPDMDRMTemplatePanel.h"

//include ApplicationFrame
#include "CATApplicationFrame.h"
//include DialogEngine
#include "CATDialogState.h"
#include "CATDialogTransition.h"

#include "CATCreateExternalObject.h"
CATCreateClass(CAAxPDMDRMTemplateCmd);


CATImplementClass(CAAxPDMDRMTemplateCmd, Implementation, CATStateCommand,CATNull);


//------------------------------------------------------------------------
//	Constructeur/Destructeur
//------------------------------------------------------------------------
CAAxPDMDRMTemplateCmd::CAAxPDMDRMTemplateCmd():CATStateCommand("DRMTemplate"),
_PanelOKAcq(NULL),_PanelCANCELAcq(NULL),_Panel(NULL)
{
}
//------------------------------------------------------------------------
CAAxPDMDRMTemplateCmd::~CAAxPDMDRMTemplateCmd()
{
   _Panel=NULL;
   _PanelOKAcq=NULL;
   _PanelCANCELAcq=NULL;
}
//------------------------------------------------------------------------
void CAAxPDMDRMTemplateCmd::BuildGraph()
{
   CATApplicationFrame* AppliFr = CATApplicationFrame::GetApplicationFrame();
   if (NULL==AppliFr) {RequestDelayedDestruction();return;}
   CATDialog * TempoParent = (CATDialog *) AppliFr -> GetMainWindow();
   _Panel = new CAAxPDMDRMTemplatePanel(TempoParent);
   if (NULL==_Panel) {RequestDelayedDestruction();return;}
   
   //--------------Create Selections's Agents--------
   //selection in panel
   _PanelCANCELAcq = new CATDialogAgent ("AgentCANCEL"); 
   if (NULL==_PanelCANCELAcq) {RequestDelayedDestruction();return;}
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaCANCELNotification());
   _PanelCANCELAcq -> AcceptOnNotify (_Panel,_Panel->GetWindCloseNotification());
   _PanelOKAcq = new CATDialogAgent ("AgentOK"); 
   if (NULL==_PanelOKAcq) {RequestDelayedDestruction();return;}
   _PanelOKAcq -> AcceptOnNotify (_Panel,_Panel->GetDiaOKNotification());
   
   //--------------Define Statechart's States--------------
   CATDialogState* state1 = GetInitialState("DRMTemplate");
   if (NULL==state1) {RequestDelayedDestruction();return;}
   state1->AddDialogAgent(_PanelCANCELAcq);
   state1->AddDialogAgent(_PanelOKAcq);
   
   //-----------Define Statechart's Transitions-----------
   // CANCEL
   AddTransition (state1,NULL,IsOutputSetCondition(_PanelCANCELAcq),Action((ActionMethod)&CAAxPDMDRMTemplateCmd::Quit));
   AddTransition (state1,NULL,IsOutputSetCondition(_PanelOKAcq),Action((ActionMethod)&CAAxPDMDRMTemplateCmd::Validate));
}

//------------------------------------------------------------------------
//   Action : Close button
//------------------------------------------------------------------------
boolean CAAxPDMDRMTemplateCmd::Quit(void*)
{
   ExecuteUndoAtEnd();
   return TRUE;
}
boolean CAAxPDMDRMTemplateCmd::Validate(void*)
{
   if (_Panel)
      _Panel->Validate();
   return TRUE;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMDRMTemplateCmd::Activate(CATCommand*, CATNotification*)
{
   if (_Panel)
   {
      _Panel->Refresh();
      _Panel->SetVisibility(CATDlgShow);
   }
   return CATStatusChangeRCCompleted;
}
//------------------------------------------------------------------------
CATStatusChangeRC CAAxPDMDRMTemplateCmd::Cancel(CATCommand* cmd, CATNotification* notif)
{
   if (_Panel) _Panel->RequestDelayedDestruction();
   _Panel = NULL;
   if (_PanelOKAcq) _PanelOKAcq->RequestDelayedDestruction();
   _PanelOKAcq = NULL;
   if (_PanelCANCELAcq) _PanelCANCELAcq->RequestDelayedDestruction();
   _PanelCANCELAcq = NULL;
   return CATStateCommand::Cancel(cmd, notif);
}

