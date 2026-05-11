// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegHistogramChartWindowCmd.h"
#include "CAADegHstChartWndDlg.h" 
#include "CAADegEditor1SelectedNotification.h"
#include "CAADegEditor1DeselectedNotification.h"
#include "CAADegPointErrorBox.h"

// CAASystem.edu Framework 
#include "CAAISysDocumentChartWindow.h" // To create the window which contains the histo.

//DialogEngine Framework
#include "CATDialogTransition.h"
#include "CATPanelState.h"
#include "CATCustomizableTransition.h"
#include "CATDialogAgent.h"

//Visualization Framework 
#include "CATCSO.h" 

//ApplicationFrame Framework
#include "CATFrmEditor.h"  
#include "CATApplicationFrame.h"  

// ObjectModelerbase  Framework
#include "CATDocument.h"   

//others
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegHistogramChartWindowCmd);

//----------------------LifeCycle's PART ----------------------------------
CAADegHistogramChartWindowCmd::CAADegHistogramChartWindowCmd():
                        CATStateCommand("HistogramChartWindowCmdId"),
                        _pHstChartWndDlg(NULL),_daEditor1Selected(NULL),
                        _daEditor1Deselected(NULL)
{
  cout << "CAADegHistogramChartWindowCmd constructor" << endl ;
}

//-----------------------------------------------------------------------

CAADegHistogramChartWindowCmd::~CAADegHistogramChartWindowCmd()
{
  cout << "CAADegHistogramChartWindowCmd destructor" << endl ;

  if ( NULL != _pHstChartWndDlg ) 
  {
     _pHstChartWndDlg->RequestDelayedDestruction() ;
     _pHstChartWndDlg = NULL ;
  }
  
  if ( NULL != _daEditor1Selected )
  {
     _daEditor1Selected->RequestDelayedDestruction();
     _daEditor1Selected = NULL ;
  }
  
  if ( NULL != _daEditor1Deselected )
  {
     _daEditor1Deselected->RequestDelayedDestruction();
     _daEditor1Deselected = NULL ;
  }
}

//----------------------BuildGraph PART -----------------------------------

void CAADegHistogramChartWindowCmd::BuildGraph()
{
  cout << "CAADegHistogramChartWindowCmd BuildGraph" << endl ;
  
  // Retrieves the Dialog Object parent of the Dialog Box 
  CATApplicationFrame * pFrame = NULL ;
  CATDialog * pParent = NULL ;
  pFrame = CATApplicationFrame::GetFrame() ;
  if ( NULL != pFrame )
  {
	   // pParent is the Dialog object dedicated to the current document. 
       //
       pParent = pFrame->GetMainWindow() ;
  }

  if ( NULL != pParent )
  {

     //Creates the dialog box 
     //........................
  
     _pHstChartWndDlg = new CAADegHstChartWndDlg(pParent);
     _pHstChartWndDlg->Build();

     // Creates dialog agent to receive notification from editors 
     _daEditor1Selected = new CATDialogAgent("Editor1SelectedId");	
     _daEditor1Selected->SetBehavior(CATDlgEngRepeat);
     _daEditor1Selected->AcceptOnNotify(_pHstChartWndDlg,"CAADegEditor1SelectedNotification");

     _daEditor1Deselected = new CATDialogAgent("Editor1SelectedId");	
     _daEditor1Deselected->SetBehavior(CATDlgEngRepeat);
     _daEditor1Deselected->AcceptOnNotify(_pHstChartWndDlg,"CAADegEditor1DeselectedNotification");
  
     // Creates the State associated with the dialog box 
     // In the NLS file, with id=stPanelStateId, you have the message
     // which appears in the status bar 
     //...............................................................

     CATPanelState * stPanelState = new CATPanelState (this, "stPanelStateId", _pHstChartWndDlg);
     SetInitialState(stPanelState);
     stPanelState->AddDialogAgent(_daEditor1Selected);

     CATPanelState * stPanelState1 = new CATPanelState (this, "stPanelState1Id", _pHstChartWndDlg);
     AddDialogState(stPanelState1);
     stPanelState1->AddDialogAgent(_daEditor1Selected);
     stPanelState1->AddDialogAgent(_daEditor1Deselected);

     // Defines transitions 
     // ..............................
     CATDialogTransition *pTransition1 = AddTransition
     (
        stPanelState,
        stPanelState1,
        IsLastModifiedAgentCondition(_daEditor1Selected),
        Action( (ActionMethod) & CAADegHistogramChartWindowCmd::Editor1Selected)
     ) ;

     CATDialogTransition *pTransition2 = AddTransition
     (
        stPanelState1,
        stPanelState1,
        IsLastModifiedAgentCondition(_daEditor1Selected),
        Action( (ActionMethod) & CAADegHistogramChartWindowCmd::Editor1Selected)
     ) ;

     CATDialogTransition *pTransition3 = AddTransition
     (
        stPanelState1,
        stPanelState,
        IsLastModifiedAgentCondition(_daEditor1Deselected),
        Action( (ActionMethod) & CAADegHistogramChartWindowCmd::Editor1Deselected)
     ) ;

     // Completes the Ok transition
     //..............................

     // Sets a condition to the Ok transition
     CATCustomizableTransition * pOkTransition = stPanelState->GetOkTransition() ;

     if ( NULL != pOkTransition )
     {
        // Sets an action to the Ok transition
        pOkTransition-> SetAction(Action((ActionMethod)&CAADegHistogramChartWindowCmd::CreateHistogramChartWindow));
     }

     // As the state was created explicitely by "new" instead of the 
     // GetInitialState method, it must be released.
     stPanelState -> Release();
     stPanelState=NULL;

     stPanelState1 -> Release();
     stPanelState1=NULL;
  }
}


//---------------------------------------------------------------------------

CATBoolean CAADegHistogramChartWindowCmd::CreateHistogramChartWindow(void *iDummy)
{
  cout << "CAADegHistogramChartWindowCmd::CreateHistogramChartWindow" << endl ;

  CATFrmEditor * pEditor = GetEditor(); 
  if ( NULL != pEditor )
  {
	  CATDocument * pDocument = pEditor->GetDocument();
	  if ( NULL != pDocument )
	  {
		  CAAISysDocumentChartWindow * pIDocumentChartWnd = NULL ;
		  HRESULT rc = pDocument->QueryInterface(IID_CAAISysDocumentChartWindow, 
			                                     (void**)&pIDocumentChartWnd);
		  if ( SUCCEEDED(rc) )
		  {
             pIDocumentChartWnd->CreateHistogramWindow();

             pIDocumentChartWnd->Release();
             pIDocumentChartWnd = NULL ;
		  }
	  }
  }
  return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegHistogramChartWindowCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegHistogramChartWindowCmd::Activate" << endl;

  if ( NULL != _pHstChartWndDlg )
  {
     _pHstChartWndDlg->SetVisibility(CATDlgShow);
  }

  // this command does't use the cso, so if you don't want its elements
  // you can empty it
  CATFrmEditor * pEditor =GetEditor();
  
  if ( NULL != pEditor )
  {
     CATCSO * pCso = pEditor->GetCSO() ;
     if ( NULL != pCso ) 
     {
       pCso->Empty();
     }
  }

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAADegHistogramChartWindowCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegHistogramChartWindowCmd::Desactivate" << endl;

  if ( NULL != _pHstChartWndDlg )
  {
     _pHstChartWndDlg->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAADegHistogramChartWindowCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegHistogramChartWindowCmd::Cancel" << endl;

  if ( NULL != _pHstChartWndDlg )
  {
     _pHstChartWndDlg->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATBoolean CAADegHistogramChartWindowCmd::Editor1Selected(void *iUsefulData)
{
    CATBoolean ret = TRUE;

    cout << " CAADegHistogramChartWindowCmd::Editor1Selected"<< endl;

    return ret;
}

//-------------------------------------------------------------------------------

CATBoolean CAADegHistogramChartWindowCmd::Editor1Deselected(void *iUsefulData)
{
    CATBoolean ret = TRUE;

    cout << " CAADegHistogramChartWindowCmd::Editor1Deselected"<< endl;

    return ret;
}

