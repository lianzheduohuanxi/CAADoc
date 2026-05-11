// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegAnalysisLogCmd.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"

//ApplicationFrame Framework
#include "CATISO.h"  
#include "CATFrmEditor.h"            

//CAASystem.edu Framework
#include "CAAISysLine.h"        
#include "CAAISysPoint.h"        
#include "CAAISysGeomFactory.h" 
#include "CAAISysAccess.h"// To get the object which can create temporary point

//Visualization Framework
#include "CATPathElement.h"   

// Dialog Framework 
#include "CATDlgPushItem.h"
#include "CATDlgContextualMenu.h"
#include "CATDlgSeparatorItem.h"
#include "CATContext.h"

//others
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegAnalysisLogCmd);
//
//----------------------LifeCycle's PART ----------------------------------
 
CAADegAnalysisLogCmd::CAADegAnalysisLogCmd():
                 CATStateCommand("AnalysisRelCmdId",0,CATCommandModeShared),
                _daPathElement(NULL),_piTemporaryPoint(NULL),
                _pContainer(NULL), _pISO(NULL)
                                   
{
  // Shared : This command freezes the last active command 
  // by default the command is in exclusive mode
  cout << "CAADegAnalysisLogCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor ) 
  {
    // Retrieves PSO 
    _pISO = pEditor->GetISO() ;

    CATPathElement UIActivePath = pEditor->GetUIActiveObject();
	   
    if ( 0 != UIActivePath.GetSize() )
    {
      // Retrieves the root object which implements CAAISysAccess
      // This interface allows to retrieves the object which implements
      // objects factory (point, line,.....) 
      CATBaseUnknown * UIActiveObject = NULL ;
      UIActiveObject = UIActivePath[UIActivePath.GetSize()-1];
      if ( NULL != UIActiveObject )
      {
         CAAISysAccess * piSysAccess = NULL;                
         HRESULT rc = UIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
         if (SUCCEEDED(rc))
         {
           piSysAccess->GetContainer(&_pContainer);
           piSysAccess->Release();
           piSysAccess=NULL;
         }  
      }  
    }
  }
}

//------------------------------------------------------------------------- 

CAADegAnalysisLogCmd::~CAADegAnalysisLogCmd()
{
  cout << "CAADegAnalysisLogCmd destructor" << endl ;

  if ( NULL != _daPathElement  )
  {
     _daPathElement ->RequestDelayedDestruction() ;
     _daPathElement = NULL ;
  }

  if ( NULL != _pContainer )
  {
     _pContainer->Release();
     _pContainer = NULL ;
  }
 
  _pISO = NULL ;

  _piTemporaryPoint = NULL ;
}

//----------------------BuildGraph PART -----------------------------------
 
void CAADegAnalysisLogCmd::BuildGraph()
{
   cout << "CAADegAnalysisLogCmd BuildGraph" << endl ;

   //1- Creates the dialog agent 
   //    -  it gets only CAAISysLine element 
   //    -  an element is selected with the right button 
   //    -  the repeat mode allows you to reuse this agent, so to revalue it
   //    -  No Undo step recorded for this agent 
   _daPathElement = new CATPathElementAgent("SelFirstLine");
   _daPathElement->AddElementType(IID_CAAISysLine);
   _daPathElement->SetBehavior( CATDlgEngWithContext |
                      CATDlgEngRepeat      |	                
                               CATDlgEngWithUndo );

   //2- Creates the states. See NLS file for the message in the status bar

   CATDialogState *stGetEltState = GetInitialState("stGetEltStateId");
   stGetEltState->AddDialogAgent(_daPathElement);

   // 3- The transition loops on the pCntxMenuTransition state 
   //    - CreateCntxMenu is activated each time the agent value changes,
   //      each time when you select a line ( event if it is the same line )
   //
   CATDialogTransition *pCntxMenuTransition =    AddTransition
   (
      stGetEltState,
      stGetEltState,
      IsLastModifiedAgentCondition(_daPathElement)  , 
      Action((ActionMethod) & CAADegAnalysisLogCmd::CreateCntxMenu)
   );  

}

//----------------------Action methods's PART -----------------------------

boolean CAADegAnalysisLogCmd::CreateCntxMenu(void * iData)
{
  cout << "CAADegAnalysisLogCmd::CreateCntxMenu"  << endl ;

  // Selected Line 
  CATPathElement * pLinePath = _daPathElement->GetValue();
  CATBaseUnknown * pLine = NULL;
  if ( (NULL != pLinePath) && ( pLinePath->GetSize() > 0 ) )
  {
    pLine = (*pLinePath)[pLinePath->GetSize()-1];
  }

  if ( NULL != pLine)
  {
    // Retrieves the contextual menu
    CATNotification *pNotif = GetLastNotification();
    if ( NULL != pNotif)
    {
       CATDlgContextualMenu *pCntxMenu = ((CATContext*)pNotif)->GetContextualMenu();
   
       if ( NULL != pCntxMenu )
       {
          // Default Item Title 
          CATString StartString ("StartPoint");
          CATString MediumString("MediumPoint");
          CATString EndString ("EndPoint") ;
      
          // all these dialog objects are deleted when the contextual menu 
          // is deleted. The command does't delete them.
          CATDlgSeparatorItem *Separator = new CATDlgSeparatorItem(pCntxMenu,"separator");
          CATDlgPushItem * StartPoint    = new CATDlgPushItem(pCntxMenu,StartString) ;
          CATDlgPushItem * MediumPoint   = new CATDlgPushItem(pCntxMenu,MediumString) ;
          CATDlgPushItem * EndPoint      = new CATDlgPushItem(pCntxMenu,EndString) ;
          
          // Callbacks
          AddAnalyseNotificationCB(EndPoint,
                                   EndPoint->GetMenuIActivateNotification(),
                                   (CATCommandMethod) & CAADegAnalysisLogCmd::EndPoint, 
                                   (void*) pLine );
      
          AddAnalyseNotificationCB(MediumPoint,
                                   MediumPoint->GetMenuIActivateNotification(),
                                   (CATCommandMethod) & CAADegAnalysisLogCmd::MediumPoint, 
                                   (void*) pLine );

          AddAnalyseNotificationCB(StartPoint,
                                   StartPoint->GetMenuIActivateNotification(),
                                   (CATCommandMethod) & CAADegAnalysisLogCmd::StartPoint, 
                                   (void*) pLine );
       }
    }
  }
  return TRUE ;
}

//----------------------Contextual menu's PART ----------------------------

void CAADegAnalysisLogCmd::StartPoint(CATCommand           * iCmd , 
                                      CATNotification      * iNotif, 
                                      CATCommandClientData   iUsefulData)
{
  cout << "CAADegAnalysisLogCmd::StartPoint" << endl;

  CATBaseUnknown * pLine = (CATBaseUnknown *) iUsefulData;
  if ( NULL != pLine )
  {
    CAAISysLine * piSysLine = NULL;                
    HRESULT rc = pLine->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
    if (SUCCEEDED(rc))
    {
      CATMathPoint point ;
      piSysLine->GetStartPoint(point) ;

      ShowPoint(point);

      piSysLine-> Release();
      piSysLine=NULL;
    }
  }
}

//---------------------------------------------------------------------------

void CAADegAnalysisLogCmd::EndPoint(CATCommand           * iCmd,  
                                    CATNotification      * iNotif, 
                                    CATCommandClientData   iUsefulData)
{
  cout << "CAADegAnalysisLogCmd::EndPoint" << endl;

  CATBaseUnknown * pLine= (CATBaseUnknown *) iUsefulData;
  if ( NULL != pLine )
  {
    CAAISysLine * piSysLine = NULL;                
    HRESULT rc = pLine->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
    if (SUCCEEDED(rc))
    {
      CATMathPoint point ;
      piSysLine->GetEndPoint(point) ;


      ShowPoint(point);

      piSysLine-> Release();
      piSysLine=NULL;
    }
  }
}

//-----------------------------------------------------------------------------

void CAADegAnalysisLogCmd::MediumPoint(CATCommand           * iCmd , 	
                                       CATNotification      * iNotif, 
                                       CATCommandClientData   iUsefulData)
{
  cout << "CAADegAnalysisLogCmd::MediumdPoint" << endl;

  CATBaseUnknown * pLine = (CATBaseUnknown *) iUsefulData;
  if ( NULL != pLine )
  {
    CAAISysLine *piSysLine = NULL;                
    HRESULT rc = pLine->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
    if (SUCCEEDED(rc))
    {
      CATMathPoint point,point1,point2 ;

      piSysLine->GetStartPoint(point1) ;
      piSysLine->GetEndPoint(point2) ;

      point = (point1+point2)/2;

      ShowPoint(point);

      piSysLine -> Release();
      piSysLine=NULL;
    }
  }
}

//-----------------------------------------------------------------------------

void CAADegAnalysisLogCmd::ShowPoint(CATMathPoint & iPoint)
{   
  if ( NULL == _piTemporaryPoint ) 
  {
    CAAISysGeomFactory * piSysGeomFactory = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
    if (SUCCEEDED(rc))
    {
      piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                        (CATBaseUnknown**)&_piTemporaryPoint);
      _pISO->AddElement(_piTemporaryPoint);

      piSysGeomFactory -> Release();
      piSysGeomFactory=NULL;
    }
  }

  if (  NULL != _piTemporaryPoint )
  {
    _piTemporaryPoint->SetCoord((float) iPoint.GetX(),
                                (float) iPoint.GetY(), 
                                (float) iPoint.GetZ());
    _pISO->UpdateElement(_piTemporaryPoint) ;
  }
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegAnalysisLogCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisLogCmd::Activate" << endl;
  return (CATStatusChangeRCCompleted) ;
}

//------------------------------------------------------------------------------

CATStatusChangeRC CAADegAnalysisLogCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisLogCmd::Desactivate" << endl;
  return (CATStatusChangeRCCompleted) ;
}

//------------------------------------------------------------------------------

CATStatusChangeRC CAADegAnalysisLogCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisLogCmd::Cancel" << endl;

  if ( NULL != _piTemporaryPoint )
  {
    _pISO->RemoveElement(_piTemporaryPoint);
    _piTemporaryPoint->Release();
    _piTemporaryPoint= NULL ;
  }
  return (CATStatusChangeRCCompleted) ;
}

