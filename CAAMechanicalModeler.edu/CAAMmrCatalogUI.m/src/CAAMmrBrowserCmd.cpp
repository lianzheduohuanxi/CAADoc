// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAMmrBrowserCmd.h"
#include "CAAMmrBrowserCmdDlg.h"

//ApplicationFrame Framework
#include "CATApplicationFrame.h"

//DialogEngine Framework
#include "CATDialog.h"
#include "CATDialogState.h"
#include "CATDialogAgent.h"

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAMmrBrowserCmd);

//----------------------------------------------------------------------------------
CAAMmrBrowserCmd::CAAMmrBrowserCmd():CATStateCommand("CAAMmrBrowserCmd"),
_pPanelOKAcq(NULL),_pPanelCANCELAcq(NULL)
{
   _pPanel=NULL;

   CATApplicationFrame * pFrame = NULL ;
   pFrame = CATApplicationFrame::GetFrame() ;
   if ( NULL != pFrame )
   {
      // pParent is the Dialog object dedicated to the current document. 
      //
      CATDialog * pParent = pFrame->GetMainWindow() ;
      if ( NULL != pParent )
      {
          _pPanel = new CAAMmrBrowserCmdDlg(pParent); 
          _pPanel->Build();
      }
   }
   
}

//----------------------------------------------------------------------------------

CAAMmrBrowserCmd::~CAAMmrBrowserCmd()
{
   if ( NULL != _pPanel )
   {
      _pPanel->RequestDelayedDestruction();
      _pPanel = NULL ;
   }
   
   if ( NULL != _pPanelOKAcq )
   {
      _pPanelOKAcq->RequestDelayedDestruction();
      _pPanelOKAcq=NULL;
   }

   if ( NULL != _pPanelCANCELAcq )
   {
      _pPanelCANCELAcq->RequestDelayedDestruction();
      _pPanelCANCELAcq=NULL;
   }
	
}


//------------------------------------------------------------------------
void CAAMmrBrowserCmd::BuildGraph ()
{
   //--------------Define Statechart's Agents--------
   
   _pPanelOKAcq = new CATDialogAgent ("AgentOK"); 
   _pPanelOKAcq -> AcceptOnNotify (_pPanel,_pPanel->GetDiaOKNotification());

   _pPanelCANCELAcq = new CATDialogAgent ("AgentCANCEL"); 
   _pPanelCANCELAcq -> AcceptOnNotify (_pPanel,_pPanel->GetDiaCANCELNotification());
   _pPanelCANCELAcq -> AcceptOnNotify (_pPanel,_pPanel->GetWindCloseNotification());

   //--------------Define Statechart's States--------------

   CATDialogState* state1 = GetInitialState("SelectDescription");
   state1->AddDialogAgent(_pPanelOKAcq);
   state1->AddDialogAgent(_pPanelCANCELAcq);

   //-----------Define Statechart's Transitions-----------
   // 
   AddTransition (state1, NULL,IsOutputSetCondition(_pPanelCANCELAcq),
				Action((ActionMethod)&CAAMmrBrowserCmd::Quit));
   // 
   AddTransition (state1, NULL,IsOutputSetCondition(_pPanelOKAcq));
		
}

//------------------------------------------------------------------------

CATBoolean CAAMmrBrowserCmd::Quit(void* data)
{
   ExecuteUndoAtEnd();
   return TRUE;
}

//------------------------------------------------------------------------

CATStatusChangeRC CAAMmrBrowserCmd::Activate(CATCommand*, CATNotification*)
{
   _pPanel->SetVisibility(CATDlgShow);

   return CATStatusChangeRCCompleted;
}

//----------------------------------------------------------------------------------

CATStatusChangeRC CAAMmrBrowserCmd::Desactivate(CATCommand*, CATNotification*)
{
    _pPanel->SetVisibility(CATDlgHide);

   return CATStatusChangeRCCompleted;
}

//----------------------------------------------------------------------------------


