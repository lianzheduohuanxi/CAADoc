// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegAnalysisEltTypeCmd.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogAgent.h"
#include "CATDialogTransition.h"

//CAASystem.edu Framework
#include "CAAISysCollection.h"   
#include "CAAISysLine.h"         
#include "CAAISysPoint.h"        
#include "CAAISysCircle.h"       
#include "CAAISysEllipse.h"      
#include "CAAISysPlane.h"  
#include "CAAISysAccess.h"      

//ApplicationFrame Framework
#include "CATFrmEditor.h"     //To get the editor- the PSO - the Active path
#include "CATPSO.h"  

// Dialog Framework 
#include "CATDlgPushItem.h"
#include "CATDlgContextualMenu.h"
#include "CATContext.h"

//other
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegAnalysisEltTypeCmd);
//
//----------------------LifeCycle's PART ----------------------------------

CAADegAnalysisEltTypeCmd::CAADegAnalysisEltTypeCmd():CATStateCommand("AnalysisEltTypeCmdId"),
                _daPathElement(NULL),_daDialog(NULL),
                _pContainer(NULL), _pPSO(NULL)
                                   
{
  cout << "CAADegAnalysisEltTypeCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor ) 
  {
    // Retrieves PSO 
    _pPSO = pEditor->GetPSO() ;

    //Retrieves the container 
    _UIActivePath = pEditor->GetUIActiveObject();
	   
    if ( 0 != _UIActivePath.GetSize() )
    {
      // Retrieves the root object which implements CAAISysAccess
      // This interface allows to retrieves the object which implements
      // objects factory (point, line,.....) 
      CATBaseUnknown * pUIActiveObject = NULL ;
      pUIActiveObject = _UIActivePath[_UIActivePath.GetSize()-1];
      if ( NULL != pUIActiveObject )
      {
        CAAISysAccess * piSysAccess = NULL;                
        HRESULT rc = pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
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

//----------------------------------------------------------------------------------

CAADegAnalysisEltTypeCmd::~CAADegAnalysisEltTypeCmd()
{
  cout << "CAADegAnalysisEltTypeCmd destructor" << endl ;

  if ( NULL != _daPathElement  )  
  {
     _daPathElement -> RequestDelayedDestruction()  ;
     _daPathElement = NULL ;
  }

  if ( NULL != _daDialog ) 
  { 
     _daDialog -> RequestDelayedDestruction() ;
     _daDialog = NULL ;
  }

  if ( NULL != _pContainer )
  {
     _pContainer->Release();
     _pContainer = NULL ;
  }

  _pPSO = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAADegAnalysisEltTypeCmd::BuildGraph()
{
   cout << "CAADegAnalysisEltTypeCmd BuildGraph" << endl ;

   //1- Creates the dialog agents 
   //   they have the same behavior: they react on right clicks and are
   //   repeatable.
   //
   //    -  This agent catches all right clicks on any component representation.
   //       this agent is valued when you select any element of the document
   //       with a right click. 
   //
   _daPathElement = new CATPathElementAgent("pathelt");
   _daPathElement->SetBehavior( CATDlgEngWithContext | 
                       CATDlgEngRepeat );
								
   //
   //    -  This agent catches remaining right clicks in the viewer background.
   //       This agent is repeatable, with the InitializeAcquisition done 
   //       in the CreateCntxMenu method 
   //       No Undo step recorded for this agent 
   //
   _daDialog = new CATDialogAgent("dialoagent");
   _daDialog->SetBehavior(CATDlgEngWithUndo );
   _daDialog->AcceptOnNotify(NULL,"CATContext");

   //2- Creates the state. See NLS file for the message in the status bar.
   //  The two dialog agents are added to the dialog state in the appropriate 
   //  order to get only filter clicks from the background in the
   //  _daDialog agent.
   //
   CATDialogState *stBackGroundState = GetInitialState("stBackGroundStateId");
   stBackGroundState->AddDialogAgent(_daPathElement);
   stBackGroundState->AddDialogAgent(_daDialog);

   // 3- The transition loops on the state pCntxMenuTransition
   //    The CreateCntxMenu action is actived when the _daDialog is valued
   //    so when you click on the backgound viewer. If you click on an element
   //    this action method is not actived while the test condition is 
   //    not ok.
   //
   CATDialogTransition *pCntxMenuTransition =    AddTransition
   (
      stBackGroundState,
      stBackGroundState,
      IsOutputSetCondition(_daDialog), 
      Action((ActionMethod) & CAADegAnalysisEltTypeCmd::CreateCntxMenu)
   ) ;  

}

//----------------------Action methods's PART -----------------------------

CATBoolean CAADegAnalysisEltTypeCmd::CreateCntxMenu(void * iData)
{
  cout << "CAADegAnalysisEltTypeCmd::CreateCntxMenu"  << endl ;

  // Retrieves the contextual menu
  CATNotification      *pNotif    = GetLastNotification();

  if ( NULL != pNotif )
  {
     CATDlgContextualMenu *pCntxMenu = ((CATContext*)pNotif)->GetContextualMenu();

     if ( NULL != pCntxMenu)
     {
   
       // All these Dialog objects are deleted when the contextual menu
       // is deleted so this command does't delete them.
       CATDlgPushItem * Point   = new CATDlgPushItem(pCntxMenu,CATString("Point")) ;
       CATDlgPushItem * Line    = new CATDlgPushItem(pCntxMenu,CATString("Line")) ;
       CATDlgPushItem * Circle  = new CATDlgPushItem(pCntxMenu,CATString("Circle")) ;
       CATDlgPushItem * Ellipse = new CATDlgPushItem(pCntxMenu,CATString("Ellipse")) ;
       CATDlgPushItem * Plane   = new CATDlgPushItem(pCntxMenu,CATString("Plane")) ;
     
       // Callbacks
       AddAnalyseNotificationCB( Point,Point->GetMenuIActivateNotification(),
                                (CATCommandMethod) & CAADegAnalysisEltTypeCmd::ShowPoint, 
                                (void*) NULL);
     
       AddAnalyseNotificationCB( Line,Line->GetMenuIActivateNotification(),
                                (CATCommandMethod) & CAADegAnalysisEltTypeCmd::ShowLine, 
                                (void*) NULL);
     
       AddAnalyseNotificationCB( Circle,Circle->GetMenuIActivateNotification(),
                                (CATCommandMethod) & CAADegAnalysisEltTypeCmd::ShowCircle, 
                                (void*) NULL);
     
       AddAnalyseNotificationCB( Ellipse,Ellipse->GetMenuIActivateNotification(),
                                (CATCommandMethod) & CAADegAnalysisEltTypeCmd::ShowEllipse, 
                                (void*) NULL);
   
       AddAnalyseNotificationCB( Plane,Plane->GetMenuIActivateNotification(),
                                (CATCommandMethod) & CAADegAnalysisEltTypeCmd::ShowPlane, 
                                (void*) NULL);
   	
     }
  }
  // Required to reuse this agent in the loop transition. 
  _daDialog->InitializeAcquisition();

  return TRUE ;
}

//----------------------Contextual menu's PART ----------------------------

void CAADegAnalysisEltTypeCmd::ShowPoint(CATCommand          *iPublishingCommand, 
                          CATNotification     *iNotification, 
                          CATCommandClientData iUsefulData)
{
  cout << "CAADegAnalysisEltTypeCmd::ShowPoint"<<  endl;

  // finds all points belonging to the piSysCollection
  if ( NULL != _pContainer )	    
  {
    _pPSO->Empty();

    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      int nbelt(0)  ;
      piSysCollection->GetNumberOfObjects(&nbelt);

      for ( int i=1 ; i <= nbelt ; i++ )
      { 
        CATPathElement * PathPSO = new CATPathElement(_UIActivePath);

        CATBaseUnknown * obj = NULL ;
        rc = piSysCollection->GetObject(i,&obj);

        if (SUCCEEDED(rc))
        {
           CAAISysPoint * piSysPoint = NULL;                
           rc = obj->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
           if (SUCCEEDED(rc))
           {
             PathPSO ->AddChildElement(piSysPoint) ;
             _pPSO->AddElement(PathPSO);

             piSysPoint ->Release();
             piSysPoint=NULL;
           }

           obj-> Release();
           obj = NULL ;
        }

        // AddElement AddRef'ed 
        PathPSO ->Release();
        PathPSO=NULL;
      }
      piSysCollection->Release();
      piSysCollection=NULL;
    }
  }
}

//----------------------------------------------------------------------------------

void CAADegAnalysisEltTypeCmd::ShowLine(CATCommand          *iPublishingCommand, 
                          CATNotification     *iNotification, 
                          CATCommandClientData iUsefulData)
{
  cout << "CAADegAnalysisEltTypeCmd::ShowLine"<<  endl;

  // finds all lines contained in the piSysCollection
  if ( NULL != _pContainer )	    
  {
    _pPSO->Empty();

    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      int nbelt(0)  ;
      piSysCollection->GetNumberOfObjects(&nbelt);

      for ( int i=1 ; i <= nbelt ; i++ )
      {
        CATPathElement * PathPSO = new CATPathElement(_UIActivePath);

        CATBaseUnknown * obj = NULL ;
        rc = piSysCollection->GetObject(i,&obj);

        if (SUCCEEDED(rc))
        {
           CAAISysLine * piSysLine = NULL;                
           rc = obj->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
           if (SUCCEEDED(rc))
           {
              PathPSO ->AddChildElement(piSysLine) ;
              _pPSO->AddElement(PathPSO);

              piSysLine ->Release();
              piSysLine=NULL;
           }
           obj-> Release();
           obj= NULL ;
        }

        // AddElement AddRef'ed 
        PathPSO ->Release();
        PathPSO=NULL;
      }
      piSysCollection->Release();
      piSysCollection=NULL;
    }
  }
}

//----------------------------------------------------------------------------------

void CAADegAnalysisEltTypeCmd::ShowCircle(CATCommand          *iPublishingCommand, 
                          CATNotification     *iNotification, 
                          CATCommandClientData iUsefulData)
{
  cout << "CAADegAnalysisEltTypeCmd::ShowCircle"<<  endl;

  // finds all circles contained in the  piSysCollection
  if ( NULL != _pContainer )	    
  {
    _pPSO->Empty();

    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      int nbelt(0)  ;
      piSysCollection->GetNumberOfObjects(&nbelt);

      for ( int i=1 ; i <= nbelt ; i++ )
      {
        CATPathElement * PathPSO = new CATPathElement(_UIActivePath);

        CATBaseUnknown * obj = NULL ;
        rc = piSysCollection->GetObject(i,&obj);

        if (SUCCEEDED(rc))
        {
           CAAISysCircle * piSysCircle = NULL;                
           rc = obj->QueryInterface(IID_CAAISysCircle, (void**)&piSysCircle);
           if (SUCCEEDED(rc))
           {
             PathPSO ->AddChildElement(piSysCircle) ;
             _pPSO->AddElement(PathPSO);

             piSysCircle ->Release();
             piSysCircle=NULL;
           }
           obj-> Release();
           obj = NULL ;
        }

        // AddElement AddRef'ed 
        PathPSO ->Release();
        PathPSO=NULL;
      }
      piSysCollection->Release();
      piSysCollection=NULL ;
    }
  }
}

//----------------------------------------------------------------------------------

void CAADegAnalysisEltTypeCmd::ShowEllipse(CATCommand          *iPublishingCommand, 
                          CATNotification     *iNotification, 
                          CATCommandClientData iUsefulData)
{
  cout << "CAADegAnalysisEltTypeCmd::ShowLine"<<  endl;

  // finds all the ellipses contained in the piSysCollection
  if ( NULL != _pContainer )	    
  {
    _pPSO->Empty();
    
    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      int nbelt(0)  ;
      piSysCollection->GetNumberOfObjects(&nbelt);

      for ( int i=1 ; i <= nbelt ; i++ )
      {
        CATPathElement * PathPSO = new CATPathElement(_UIActivePath);

        CATBaseUnknown * obj = NULL;
        rc = piSysCollection->GetObject(i,&obj);

        if (SUCCEEDED(rc))
        {
           CAAISysEllipse * piSysEllipse = NULL;                
           rc = obj->QueryInterface(IID_CAAISysEllipse, (void**)&piSysEllipse);
           if (SUCCEEDED(rc))
           {
             PathPSO ->AddChildElement(piSysEllipse) ;
             _pPSO->AddElement(PathPSO);

             piSysEllipse ->Release();
             piSysEllipse=NULL;
           }
           obj-> Release();
           obj = NULL ;
        }

        // AddElement AddRef'ed 
        PathPSO ->Release();
        PathPSO=NULL;
      }
      piSysCollection->Release();
      piSysCollection=NULL;
    }
  }
}

//--------------------------------------------------------------------------------

void CAADegAnalysisEltTypeCmd::ShowPlane(CATCommand          *iPublishingCommand, 
                          CATNotification     *iNotification, 
                          CATCommandClientData iUsefulData)
{
  cout << "CAADegAnalysisEltTypeCmd::ShowLine"<<  endl;

  // finds all the planes contained in the piSysCollection
  if ( NULL != _pContainer )	    
  {
    _pPSO->Empty();

    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
      int nbelt(0)  ;
      piSysCollection->GetNumberOfObjects(&nbelt);

      for ( int i=1 ; i <= nbelt ; i++ )
      {
        CATPathElement * PathPSO = new CATPathElement(_UIActivePath);

        CATBaseUnknown * obj = NULL ;
        rc = piSysCollection->GetObject(i,&obj);

        if (SUCCEEDED(rc))
        {
           CAAISysPlane * piSysPlane = NULL;                
           rc = obj->QueryInterface(IID_CAAISysPlane, (void**)&piSysPlane);
           if (SUCCEEDED(rc))
           {
             PathPSO ->AddChildElement(piSysPlane) ;
             _pPSO->AddElement(PathPSO);

             piSysPlane ->Release();
             piSysPlane=NULL;
           }
           obj-> Release();
           obj = NULL ;
        }

        // AddElement AddRef'ed 
        PathPSO ->Release();
        PathPSO=NULL;
      }
      piSysCollection->Release();
      piSysCollection=NULL;
    }
  }
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegAnalysisEltTypeCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisEltTypeCmd::Activate" << endl;

  _pPSO->Empty();
  return (CATStatusChangeRCCompleted) ;
}

//--------------------------------------------------------------------------------

CATStatusChangeRC CAADegAnalysisEltTypeCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
   cout << " CAADegAnalysisEltTypeCmd::Desactivate" << endl;

  _pPSO->Empty();
  return (CATStatusChangeRCCompleted) ;
}

//--------------------------------------------------------------------------------

CATStatusChangeRC CAADegAnalysisEltTypeCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegAnalysisEltTypeCmd::Cancel" << endl;

  _pPSO->Empty();
  return (CATStatusChangeRCCompleted) ;
}

