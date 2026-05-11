// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegAnalysisNumericCmd.h"
#include "CAADegAnalysisNumericDlg.h"
#include "CAADegChoiceBehaviorDlg.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogAgent.h"
#include "CATDialogTransition.h"

//ApplicationFrame Framework       
#include "CATApplicationFrame.h"  // to attach the dialog box
#include "CATFrmEditor.h"         // To get the editor (CSO managment)
  
//CAASystem.edu Framework 
#include "CAAISysLine.h"         
#include "CAAISysPoint.h"        
#include "CAAISysCircle.h"       
#include "CAAISysEllipse.h"      
#include "CAAISysPlane.h"  

// Visualization Framework
#include "CATSO.h" 
#include "CATCSO.h"
#include "CATPathElement.h"

//other
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegAnalysisNumericCmd);
//
//----------------------LifeCycle's PART ----------------------------------

CAADegAnalysisNumericCmd::CAADegAnalysisNumericCmd():CATStateCommand("AnalysisNumericCmdId"),
            _daMultiAcquisitionSelModes(NULL),
            _daMultiAcquisitionCtrl(NULL),
            _daMultiAcquisitionUserCtrl(NULL),
            _pCAADegAnalysisNumericDlg(NULL),
            _pCAADegChoiceBehaviorDlg(NULL),
            _daCAADegAnalysisNumericDlgDiaClose(NULL),
            _daCAADegAnalysisNumericDlgWndClose(NULL),
            _daCAADegChoiceBehaviorDlgWndClose(NULL),
            _daCAADegChoiceBehaviorDlgDiaCancel(NULL),
            _daCAADegChoiceBehaviorDlgDiaOk(NULL),
            _Choice(0)
                                   
{
  cout << "CAADegAnalysisNumericCmd constructor" << endl ;
}

//----------------------------------------------------------------------------------

CAADegAnalysisNumericCmd::~CAADegAnalysisNumericCmd()
{
  cout << "CAADegAnalysisNumericCmd destructor" << endl ;

  if ( NULL != _daMultiAcquisitionSelModes  )  
  {
     _daMultiAcquisitionSelModes -> RequestDelayedDestruction()  ;
     _daMultiAcquisitionSelModes = NULL ;
  }
  if ( NULL != _daMultiAcquisitionCtrl )
  {
     _daMultiAcquisitionCtrl -> RequestDelayedDestruction()  ;
     _daMultiAcquisitionCtrl = NULL ;
  }
  if ( NULL != _daMultiAcquisitionUserCtrl )
  {
     _daMultiAcquisitionUserCtrl -> RequestDelayedDestruction()  ;
     _daMultiAcquisitionUserCtrl = NULL ;
  }

  if ( NULL != _daCAADegAnalysisNumericDlgDiaClose  )  
  {
     _daCAADegAnalysisNumericDlgDiaClose -> RequestDelayedDestruction()  ;
     _daCAADegAnalysisNumericDlgDiaClose = NULL ;
  }

  if ( NULL != _daCAADegAnalysisNumericDlgWndClose  )  
  {
     _daCAADegAnalysisNumericDlgWndClose -> RequestDelayedDestruction()  ;
     _daCAADegAnalysisNumericDlgWndClose = NULL ;
  }
  if ( NULL != _daCAADegChoiceBehaviorDlgWndClose  )  
  {
     _daCAADegChoiceBehaviorDlgWndClose -> RequestDelayedDestruction()  ;
     _daCAADegChoiceBehaviorDlgWndClose = NULL ;
  }
 
  if ( NULL != _daCAADegChoiceBehaviorDlgDiaCancel  )  
  {
     _daCAADegChoiceBehaviorDlgDiaCancel -> RequestDelayedDestruction()  ;
     _daCAADegChoiceBehaviorDlgDiaCancel = NULL ;
  }      
  if ( NULL != _daCAADegChoiceBehaviorDlgDiaOk  )  
  {
     _daCAADegChoiceBehaviorDlgDiaOk -> RequestDelayedDestruction()  ;
     _daCAADegChoiceBehaviorDlgDiaOk = NULL ;
  }      

  if ( NULL !=   _pCAADegAnalysisNumericDlg )
  {
     _pCAADegAnalysisNumericDlg->RequestDelayedDestruction() ;
     _pCAADegAnalysisNumericDlg= NULL ;           
  }

  if ( NULL !=   _pCAADegChoiceBehaviorDlg )
  {
     _pCAADegChoiceBehaviorDlg->RequestDelayedDestruction() ;
     _pCAADegChoiceBehaviorDlg= NULL ;           
  }
}

//----------------------BuildGraph PART -----------------------------------

void CAADegAnalysisNumericCmd::BuildGraph()
{
   cout << "CAADegAnalysisNumericCmd BuildGraph" << endl ;

   //1- Dialog agents creation
   //----------------------------
 
   // The three CATPathElementAgent agents have a common behavior 
   // CATDlgEngWithPSOHSO and CATDlgEngWithPrevaluation. The selected element 
   // are highlighted when the selection is done and there is a pre-highlight
   // on the available elements
   // 

   //1-a CATDlgEngMultiAcquisitionSelModes
   //
   //    You can use the trap (all the elements completly in are selected) 
   //    or indicate an element 
   //                                  
   _daMultiAcquisitionSelModes = new CATPathElementAgent("PathEltMultiAcquisitionSelModes");

   //
   _daMultiAcquisitionSelModes->SetBehavior( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation|
                              CATDlgEngMultiAcquisitionSelModes ); 
   
   // Possible type of elements selectable
   _daMultiAcquisitionSelModes->AddElementType(IID_CAAISysPoint);
   _daMultiAcquisitionSelModes->AddElementType(IID_CAAISysLine);
   _daMultiAcquisitionSelModes->AddElementType(IID_CAAISysEllipse);
   _daMultiAcquisitionSelModes->AddElementType(IID_CAAISysCircle);
   _daMultiAcquisitionSelModes->AddElementType(IID_CAAISysPlane);
  
   //1-b CATDlgEngMultiAcquisitionCtrl
   //
   //    A dialog box is displayed to choose the way to select the element.
   //    The three possibilites are (from left to right)
   //      - Indication or selection by trap 
   //          (for the trap, all the elements completly in are selected) 
   //      - Selection only by trap 
   //          (all the elements completly in are selected) 
   //      - Selection only by trap 
   //          (all the elements completly or partialy in are selected)
   //    The selection is finished when the OK button of this dialog box
   //    is pushed. It enable to the end user to modify or complete its
   //    selection: 
   //       - In using the Ctrl key, all the new selected elements already 
   //         selected are de-selected, the new selected are added 
   //         to the previously selected 
   //       - Otherwise, only the new selected elements are taken account. 
   //    
   //
   _daMultiAcquisitionCtrl = new CATPathElementAgent("PathEltMultiAcquisitionCtrl");

   //
   _daMultiAcquisitionCtrl->SetBehavior( CATDlgEngWithPSOHSO |CATDlgEngWithPrevaluation|
                              CATDlgEngMultiAcquisitionCtrl ); 
   
   // Possible type of elements selectable
   _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysPoint);
   _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysLine);
   _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysEllipse);
   _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysCircle);
   _daMultiAcquisitionCtrl->AddElementType(IID_CAAISysPlane);

   //1-c CATDlgEngMultiAcquisitionUserCtrl
   //
   //    The same dialog box, as in the previous case, is displayed 
   //    to choose the way to select the elements. So, there are also
   //    the same three possibilites to make the selection.  
   //    As soon as the indication or the trap is ended, the selection is
   //    finished. 
   //    The end user can choose to switch with the previous behavior 
   //    (those of CATDlgEndMultiACquisitionCtrl) in 
   //    selecting the "N" button. 
   //    
   _daMultiAcquisitionUserCtrl = new CATPathElementAgent("PathEltMultiAcquisitionUserCtrl");

   //
   _daMultiAcquisitionUserCtrl->SetBehavior( CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation |
                              CATDlgEngMultiAcquisitionUserCtrl ); 
   
   // Possible type of elements selectable
   _daMultiAcquisitionUserCtrl->AddElementType(IID_CAAISysPoint);
   _daMultiAcquisitionUserCtrl->AddElementType(IID_CAAISysLine);
   _daMultiAcquisitionUserCtrl->AddElementType(IID_CAAISysEllipse);
   _daMultiAcquisitionUserCtrl->AddElementType(IID_CAAISysCircle);
   _daMultiAcquisitionUserCtrl->AddElementType(IID_CAAISysPlane);

   //2- Dialog boxes creation
   //------------------------
   //
   CATApplicationFrame * pFrame = NULL ;
   pFrame = CATApplicationFrame::GetFrame() ;
 
   if ( NULL != pFrame )
   {
       // pParent is the Dialog object dedicated to the current document. 
       //
       CATDialog * pParent = pFrame->GetMainWindow() ;

       // 2-a To display the count of selected elements and finish
       //     command
       if ( NULL != pParent )
       {
          _pCAADegAnalysisNumericDlg = new CAADegAnalysisNumericDlg(pParent);
          _pCAADegAnalysisNumericDlg->Build();

          // To be prevent when the dialog box is closed:

          // When the end user clicks on the close window
          _daCAADegAnalysisNumericDlgWndClose = new CATDialogAgent("CAADegAnalysisNumericDlgWndCloseId");

          // When the end user clicks on the close button 
          _daCAADegAnalysisNumericDlgDiaClose = new CATDialogAgent("CAADegAnalysisNumericDlgDiaCloseId");

          _daCAADegAnalysisNumericDlgWndClose->AcceptOnNotify(_pCAADegAnalysisNumericDlg,
                _pCAADegAnalysisNumericDlg->GetWindCloseNotification());

          _daCAADegAnalysisNumericDlgWndClose->AcceptOnNotify(_pCAADegAnalysisNumericDlg,
                _pCAADegAnalysisNumericDlg->GetDiaCLOSENotification());
       }

       // 2-b To choose the behavior of the selection agent
       //
       if ( NULL != pParent )
       {
          _pCAADegChoiceBehaviorDlg = new CAADegChoiceBehaviorDlg(pParent);
          _pCAADegChoiceBehaviorDlg->Build();

          // To be prevent when the end user clicks Cancel/Ok or 
          // closes the window

          // When the end user clicks on the close window
          _daCAADegChoiceBehaviorDlgWndClose = new CATDialogAgent("CAADegChoiceBehaviorWndCloseId");

          // When the end user clicks on the Cancel button 
          _daCAADegChoiceBehaviorDlgDiaCancel = new CATDialogAgent("CAADegChoiceBehaviorDlgDiaCancelId");

           // When the end user clicks on the Ok button 
          _daCAADegChoiceBehaviorDlgDiaOk = new CATDialogAgent("CAADegChoiceBehaviorDlgDiaOKId");

          _daCAADegChoiceBehaviorDlgWndClose->AcceptOnNotify(_pCAADegChoiceBehaviorDlg,
                    _pCAADegChoiceBehaviorDlg->GetWindCloseNotification());

          _daCAADegChoiceBehaviorDlgDiaCancel->AcceptOnNotify(_pCAADegChoiceBehaviorDlg,
                    _pCAADegChoiceBehaviorDlg->GetDiaCANCELNotification());

          _daCAADegChoiceBehaviorDlgDiaOk->AcceptOnNotify(_pCAADegChoiceBehaviorDlg,
                    _pCAADegChoiceBehaviorDlg->GetDiaOKNotification());
       }
   }

   // 3- States creation 
   // ------------------
   CATDialogState *stChoiceBehaviorState = GetInitialState("stChoiceBehaviorStateId");
   stChoiceBehaviorState->AddDialogAgent(_daCAADegChoiceBehaviorDlgWndClose) ;
   stChoiceBehaviorState->AddDialogAgent(_daCAADegChoiceBehaviorDlgDiaOk) ;
   stChoiceBehaviorState->AddDialogAgent(_daCAADegChoiceBehaviorDlgDiaCancel) ;

   CATDialogState *stMultiAcquisitionSelModesState = AddDialogState("stMultiAcquisitionSelModesStateId");
   stMultiAcquisitionSelModesState->AddDialogAgent(_daMultiAcquisitionSelModes);
   stMultiAcquisitionSelModesState->AddDialogAgent(_daCAADegAnalysisNumericDlgWndClose) ;
   stMultiAcquisitionSelModesState->AddDialogAgent(_daCAADegAnalysisNumericDlgDiaClose) ;

   CATDialogState *stMultiAcquisitionCtrlState = AddDialogState("stMultiAcquisitionCtrlStateId");
   stMultiAcquisitionCtrlState->AddDialogAgent(_daMultiAcquisitionCtrl);
   stMultiAcquisitionCtrlState->AddDialogAgent(_daCAADegAnalysisNumericDlgWndClose) ;
   stMultiAcquisitionCtrlState->AddDialogAgent(_daCAADegAnalysisNumericDlgDiaClose) ;

   CATDialogState *stMultiAcquisitionUserCtrlState = AddDialogState("stMultiAcquisitionUserCtrlStateId");
   stMultiAcquisitionUserCtrlState->AddDialogAgent(_daMultiAcquisitionUserCtrl);
   stMultiAcquisitionUserCtrlState->AddDialogAgent(_daCAADegAnalysisNumericDlgWndClose) ;
   stMultiAcquisitionUserCtrlState->AddDialogAgent(_daCAADegAnalysisNumericDlgDiaClose) ;

   CATDialogState *stEndState = AddDialogState("stEndStateId");
   stEndState->AddDialogAgent(_daCAADegAnalysisNumericDlgWndClose) ;
   stEndState->AddDialogAgent(_daCAADegAnalysisNumericDlgDiaClose) ;

   // 4- Transitions creation
   // -----------------------
   CATDialogTransition *pTransition1 =    AddTransition
   (
      stChoiceBehaviorState,
      NULL,
      OrCondition(IsOutputSetCondition(_daCAADegChoiceBehaviorDlgWndClose),
                  IsOutputSetCondition(_daCAADegChoiceBehaviorDlgDiaCancel)),
	  NULL
   ) ; 

   CATDialogTransition *pTransition21 =    AddTransition
   (
      stChoiceBehaviorState ,
      stMultiAcquisitionSelModesState,
      AndCondition(IsOutputSetCondition(_daCAADegChoiceBehaviorDlgDiaOk),
                  Condition((ConditionMethod) & CAADegAnalysisNumericCmd::CheckCase, (void*)1)),
      Action((ActionMethod) & CAADegAnalysisNumericCmd::EndChoice,NULL,NULL,(void*)1)
   ) ; 

   CATDialogTransition *pTransition22 =    AddTransition
   (
      stChoiceBehaviorState ,
      stMultiAcquisitionCtrlState,
      AndCondition(IsOutputSetCondition(_daCAADegChoiceBehaviorDlgDiaOk),
                  Condition((ConditionMethod) & CAADegAnalysisNumericCmd::CheckCase, (void*)2)),
      Action((ActionMethod) & CAADegAnalysisNumericCmd::EndChoice,NULL,NULL,(void*)2)
   ) ; 

   CATDialogTransition *pTransition23 =    AddTransition
   (
      stChoiceBehaviorState ,
      stMultiAcquisitionUserCtrlState,
      AndCondition(IsOutputSetCondition(_daCAADegChoiceBehaviorDlgDiaOk),
                  Condition((ConditionMethod) & CAADegAnalysisNumericCmd::CheckCase, (void*)3)),
      Action((ActionMethod) & CAADegAnalysisNumericCmd::EndChoice,NULL,NULL,(void*)3)
   ) ; 

   CATDialogTransition *pTransition31 =    AddTransition
   (
      stMultiAcquisitionSelModesState,
      NULL,
      OrCondition(IsOutputSetCondition(_daCAADegAnalysisNumericDlgWndClose),
                  IsOutputSetCondition(_daCAADegAnalysisNumericDlgDiaClose)),
	  NULL
   ) ;

   CATDialogTransition *pTransition32 =    AddTransition
   (
      stMultiAcquisitionSelModesState,
      stEndState,
      IsOutputSetCondition(_daMultiAcquisitionSelModes), 
      Action((ActionMethod) & CAADegAnalysisNumericCmd::DisplaySelectedElement,NULL,NULL,(void*)1)
   ) ; 

   CATDialogTransition *pTransition41 =    AddTransition
   (
      stMultiAcquisitionCtrlState,
      NULL,
      OrCondition(IsOutputSetCondition(_daCAADegAnalysisNumericDlgWndClose),
                  IsOutputSetCondition(_daCAADegAnalysisNumericDlgDiaClose)),
	  NULL
   ) ;

   CATDialogTransition *pTransition42 =    AddTransition
   (
      stMultiAcquisitionCtrlState,
      stEndState,
      IsOutputSetCondition(_daMultiAcquisitionCtrl), 
      Action((ActionMethod) & CAADegAnalysisNumericCmd::DisplaySelectedElement,NULL,NULL,(void*)2)
   ) ; 

   CATDialogTransition *pTransition51 =    AddTransition
   (
      stMultiAcquisitionUserCtrlState,
      NULL,
      OrCondition(IsOutputSetCondition(_daCAADegAnalysisNumericDlgWndClose),
                  IsOutputSetCondition(_daCAADegAnalysisNumericDlgDiaClose)),
	  NULL
   ) ;

   CATDialogTransition *pTransition52 =    AddTransition
   (
      stMultiAcquisitionUserCtrlState,
      stEndState,
      IsOutputSetCondition(_daMultiAcquisitionUserCtrl), 
      Action((ActionMethod) & CAADegAnalysisNumericCmd::DisplaySelectedElement,NULL,NULL,(void*)3)
   ) ; 

   CATDialogTransition *pTransition6 =    AddTransition
   (
      stEndState,
      NULL,
      OrCondition(IsOutputSetCondition(_daCAADegAnalysisNumericDlgWndClose),
                  IsOutputSetCondition(_daCAADegAnalysisNumericDlgDiaClose)),
	  NULL
   ) ; 
}

//----------------------Condition methods's PART -----------------------------

CATBoolean CAADegAnalysisNumericCmd::CheckCase(void * iData)
{
  CATBoolean rc = FALSE ;
  int CaseAgent = CATPtrToINT32(iData) ;
  cout << "CAADegAnalysisNumericCmd::CheckCase"  << CaseAgent << endl ;
  
  if ( NULL != _pCAADegChoiceBehaviorDlg )
  {
     int Choice = 0 ;
     _pCAADegChoiceBehaviorDlg->GetChoice(Choice);
     if ( Choice == CaseAgent )
     {
         rc = TRUE ;
     }
  }

  return rc ;
}
//----------------------Action methods's PART -----------------------------

CATBoolean CAADegAnalysisNumericCmd::EndChoice(void * iData)
{
  int CaseAgent = CATPtrToINT32(iData) ;
  cout << "CAADegAnalysisNumericCmd::EndChoice"  << CaseAgent << endl ;

  _Choice = CaseAgent ;

  if ( NULL != _pCAADegChoiceBehaviorDlg )
  {
     _pCAADegChoiceBehaviorDlg->SetVisibility(CATDlgHide);
  }
  if ( NULL != _pCAADegAnalysisNumericDlg )
  {
     _pCAADegAnalysisNumericDlg->SetVisibility(CATDlgShow);
  }

  return TRUE;
}

CATBoolean CAADegAnalysisNumericCmd::DisplaySelectedElement(void * iData)
{

  int CaseAgent = CATPtrToINT32(iData) ;
  cout << "CAADegAnalysisNumericCmd::DisplaySelectedElement"  << CaseAgent << endl ;
  
  int nbplane = 0 ;
  int nbpoint = 0 ;  
  int nbline = 0 ;
  int nbcircle = 0 ;
  int nbellipse = 0 ;
  
  // To update the CSO with the selected elements
  CATFrmEditor * pEditor =GetEditor();
  CATCSO * pCSO = NULL ;
  if ( NULL != pEditor )
  {
     pCSO = pEditor->GetCSO() ;
  }

  // Retrieve the new selected elements
  CATSO * pSO = NULL ;
  
  if ( 1 == CaseAgent ) pSO = _daMultiAcquisitionSelModes->GetListOfValues();
  if ( 2 == CaseAgent ) pSO = _daMultiAcquisitionCtrl->GetListOfValues();
  if ( 3 == CaseAgent ) pSO = _daMultiAcquisitionUserCtrl->GetListOfValues();

  if ( NULL != pSO )
  {
     int lg = pSO->GetSize();
     
     for ( int i=0 ; i < lg ; i++)
     {
      // In case of Dialog Engine, the SO contains CATPathElement
      // The cast is possible
      //
      CATPathElement * pPath = (CATPathElement*) (*pSO)[i] ;

      if ( NULL != pPath )
      {
         // Gets the leaf of the path
         int leaf = ( pPath->GetSize() -1 );
   
         // Set the complete path of the current element
         if ( NULL != pCSO )
           pCSO->AddElement(pPath);
   
         // To decode the selected element
         CATBaseUnknown * pElt = (*pPath)[leaf];
   
         if (  NULL != pElt )
         {
            CAAISysPlane * piSysPlane = NULL;                
            HRESULT rc = pElt->QueryInterface(IID_CAAISysPlane, 
                                               (void**)&piSysPlane);
              
            if (SUCCEEDED(rc))   
            {
               nbplane++ ;
               piSysPlane->Release();
               piSysPlane= NULL ;
            }
      
            CAAISysPoint * piSysPoint = NULL;                
            rc = pElt->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
              
            if (SUCCEEDED(rc))   
            {
               nbpoint++ ;
               piSysPoint->Release();
               piSysPoint= NULL ;
            }
      
            CAAISysLine * piSysLine = NULL;                
            rc = pElt->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
              
            if (SUCCEEDED(rc))   
            {
               nbline++ ;
               piSysLine->Release();
               piSysLine = NULL ;
            }
      
            CAAISysCircle * piSysCircle = NULL;                
            rc = pElt->QueryInterface(IID_CAAISysCircle ,(void**)&piSysCircle);
              
            if (SUCCEEDED(rc))   
            {
               nbcircle++ ;
               piSysCircle->Release();
               piSysCircle = NULL ;
            }
      
            CAAISysEllipse * piSysEllipse = NULL;                
            rc = pElt->QueryInterface(IID_CAAISysEllipse ,(void**)&piSysEllipse);
              
            if (SUCCEEDED(rc))   
            {
               nbellipse++ ;
               piSysEllipse->Release();
               piSysEllipse = NULL ;
            }
         }
      }
    }
  }

  // The dialog box is updated with the new value for each 
  // type of element.
  //
  if ( NULL != _pCAADegAnalysisNumericDlg )
  {
     _pCAADegAnalysisNumericDlg->UpdateValues(nbplane,nbpoint,nbline,nbcircle,nbellipse);
  }

  return TRUE ;
}


//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegAnalysisNumericCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisNumericCmd::Activate" << endl;

  if ( 0 == _Choice )
  {  // The behavior of the selection's agent has not been chosen.
     if ( NULL != _pCAADegChoiceBehaviorDlg )
     { 
         _pCAADegChoiceBehaviorDlg->SetVisibility(CATDlgShow);
     }
  }else
  {
     if ( NULL != _pCAADegAnalysisNumericDlg )
     {
        _pCAADegAnalysisNumericDlg->SetVisibility(CATDlgShow);
     }
  }

  return (CATStatusChangeRCCompleted) ;
}

//--------------------------------------------------------------------------------

CATStatusChangeRC CAADegAnalysisNumericCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
   cout << " CAADegAnalysisNumericCmd::Desactivate" << endl;

   // The two dialog box are hidden (even only one is displayed) 
   if ( NULL != _pCAADegAnalysisNumericDlg )
   {
     _pCAADegAnalysisNumericDlg->SetVisibility(CATDlgHide);
   }
   if ( NULL != _pCAADegChoiceBehaviorDlg )
   { 
      _pCAADegChoiceBehaviorDlg->SetVisibility(CATDlgHide);
   }
   return (CATStatusChangeRCCompleted) ;
}

//--------------------------------------------------------------------------------

CATStatusChangeRC CAADegAnalysisNumericCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisNumericCmd::Cancel" << endl;

  if ( NULL != _pCAADegAnalysisNumericDlg )
  {
     _pCAADegAnalysisNumericDlg->SetVisibility(CATDlgHide);
  }
  if ( NULL != _pCAADegChoiceBehaviorDlg )
  { 
      _pCAADegChoiceBehaviorDlg->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}

