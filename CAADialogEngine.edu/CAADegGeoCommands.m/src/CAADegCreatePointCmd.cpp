// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreatePointCmd.h"
#include "CAADegPointEditor.h" 

//DialogEngine Framework
#include "CATIndicationAgent.h"
#include "CATDialogTransition.h"
#include "CATPanelState.h"
#include "CATCustomizableTransition.h"

//Visualization Framework 
#include "CATPathElement.h"   
#include "CATCreate.h"   
#include "CATModify.h"      
#include "CATIModelEvents.h" 
#include "CATCSO.h"  

//CAASystem.edu Framework
#include "CAAISysAccess.h"       
#include "CAAISysPoint.h"        
#include "CAAISysGeomFactory.h"  
#include "CAAISysCollection.h"   

//ApplicationFrame Framework
#include "CATFrmEditor.h"    
#include "CATApplicationFrame.h"    

// Mathematics Framework
#include "CATMathPlane.h" 

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 

//others
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreatePointCmd);

//----------------------LifeCycle's PART ----------------------------------
CAADegCreatePointCmd::CAADegCreatePointCmd():CATStateCommand("CreatePointCmdId"),
                        _daIndication(NULL),
                        _pPointEditor(NULL),
                        _pUIActiveObject(NULL), _pContainer(NULL)            
{
  cout << "CAADegCreatePointCmd constructor" << endl ;

  // 1- We keep the root object 
  // 
  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor )
  {
    CATPathElement path = pEditor->GetUIActiveObject();
    if ( path.GetSize() > 0 )
    {
      _pUIActiveObject = path[path.GetSize()-1];
      _pUIActiveObject->AddRef();
    }
  }

  if ( NULL != _pUIActiveObject )
  {
    // Point will be created by this container and added inside
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      piSysAccess->GetContainer(&_pContainer);
      piSysAccess->Release();
      piSysAccess=NULL;
    }
  }
  
}

//-----------------------------------------------------------------------

CAADegCreatePointCmd::~CAADegCreatePointCmd()
{
  cout << "CAADegCreatePointCmd destructor" << endl ;

  if ( NULL != _daIndication ) 
  {
     _daIndication -> RequestDelayedDestruction() ;
     _daIndication = NULL ;
  }

  if ( NULL != _pPointEditor ) 
  {
     _pPointEditor->RequestDelayedDestruction() ;
     _pPointEditor = NULL ;
  }

  if ( NULL != _pUIActiveObject )
  {
     _pUIActiveObject ->Release();
     _pUIActiveObject = NULL ;
  }

  if ( NULL != _pContainer ) 
  {
     _pContainer->Release(); 
     _pContainer = NULL ;
  }
}


//----------------------BuildGraph PART -----------------------------------

void CAADegCreatePointCmd::BuildGraph()
{
  cout << "CAADegCreatePointCmd BuildGraph" << endl ;
  
  // Retrieves the Dialog Object to attach the Point Editor Box
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

     //1- Creates the indication agent 
     //.................................
    
     _daIndication = new CATIndicationAgent("Indication");
     // The plane of projection is not explicitly set with the SetMathPlane
     // method: a plane perpendicular to the sight
     // direction of the current viewpoint will be used for the projection.

     //2- Creates the dialog box to input xyz 
     //......................................
  
     _pPointEditor = new CAADegPointEditor(pParent);
     _pPointEditor->Build();

  
     //3- Creates the State associated with the dialog box and containing the 
     // Indication Agent.
     // In the NLS file, with id=GetPointId, you have the message
     // which appears in the status bar 
     //........................................................................

     CATPanelState * stState = new CATPanelState (this, "GetPointId", _pPointEditor);
     SetInitialState(stState);
     stState->AddDialogAgent(_daIndication);
   

     //4-Defines the transition triggered by the Indication Agent
     //..........................................................

     CATDialogTransition *pFirstTransition = AddTransition
     (
        stState,
        stState,
        AndCondition(IsOutputSetCondition(_daIndication) ,
                  Condition((ConditionMethod) & CAADegCreatePointCmd::CheckPoint)),
        Action((ActionMethod) & CAADegCreatePointCmd::CreatePointByIndication)
     );
  
     //5- Completes the Apply transition
     //..................................

     // Sets a condition to the Apply transition
     CATCustomizableTransition * pCustoTransition = stState->GetApplyTransition() ;
     if ( NULL != pCustoTransition )
     {
	    CATDialogTransition *pDiaApplyTransition = pCustoTransition;
        pDiaApplyTransition-> SetCondition(Condition((ActionMethod)&CAADegCreatePointCmd::CheckPoint));

        // Sets an action to the Apply transition
        pDiaApplyTransition-> SetAction(Action((ActionMethod)&CAADegCreatePointCmd::CreatePointByBox));
     }

     //6- Completes the Ok transition
     //..............................

     // Sets a condition to the Ok transition
     CATCustomizableTransition * pOkTransition = stState->GetOkTransition() ;
     if ( NULL != pOkTransition )
     {
 	    CATDialogTransition *pDiaOkTransition = pOkTransition;

        pDiaOkTransition-> SetCondition(Condition((ActionMethod)&CAADegCreatePointCmd::CheckPoint));

        // Sets an action to the Ok transition
        pDiaOkTransition-> SetAction(Action((ActionMethod)&CAADegCreatePointCmd::CreatePointByBox));
     }
   
     // As the state was created explicitely by "new" instead of the 
     // GetInitialState method, it must be released.
     stState -> Release();
     stState=NULL;
  }
}

//----------------------Condition methods's PART -----------------------------

CATBoolean CAADegCreatePointCmd::CheckPoint(void *iDummy)
{  
  cout << "CAADegCreatePointCmd::CheckPosition" << endl ;
    
  CATBoolean rc = TRUE ;

  // If no Root Object, it's impossible to create element
  if ( (NULL == _pUIActiveObject) || (NULL == _pContainer) ) rc = FALSE ;
  return rc ;
}

//----------------------Action methods's PART -----------------------------
CATBoolean CAADegCreatePointCmd::CreatePointByIndication(void *iDummy)
{
  cout << "CAADegCreatePointCmd::CreatePointByIndication" << endl ;

  // Computes a CATMathPoint from the dialog agent
  CATMathPoint Point ;
  CATMathPoint2D point2D = _daIndication->GetValue();

  // Retrieve the plane automatically defined
  CATMathPlane Plane =   _daIndication->GetMathPlane();
  Plane.EvalPoint(point2D.GetX(),point2D.GetY(),Point);

  // Creates a new point in the document and updates the display
  NewPoint(Point);

  // recycles the agent
  _daIndication->InitializeAcquisition(); 
  return TRUE ;
}

//-----------------------------------------------------------------------------

CATBoolean CAADegCreatePointCmd::CreatePointByBox(void *iDummy)
{
  cout << "CAADegCreatePointCmd::CreatePointByIndication" << endl ;

  // Creates a new point in the document and updates the display
  NewPoint(_pPointEditor->GetValue());
  return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreatePointCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePointCmd::Activate" << endl;

  if ( NULL != _pPointEditor )
  {
     _pPointEditor->SetVisibility(CATDlgShow);
  }

  // This command does't use the cso as entry. 
  // so here we empty it. If your command uses the AddCSOClient method in its 
  // BuildGraph Method, don't empty the CSO (see CAADegCreateCircleCmd)
  //

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

CATStatusChangeRC CAADegCreatePointCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePointCmd::Desactivate" << endl;

  _pPointEditor->SetVisibility(CATDlgHide);

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreatePointCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePointCmd::Cancel" << endl;

  if ( NULL != _pPointEditor )
  {
     _pPointEditor->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}

//----------------------MODEL 's PART -----------------------------------------------

void CAADegCreatePointCmd::NewPoint(const CATMathPoint &iPoint)
{

  // Retrieves the factory to create the new point
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creation of the point by a factory 
    CAAISysPoint * piSysPoint = NULL ;
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                           (CATBaseUnknown**)&piSysPoint);

    // Done with the factory
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Adds the point in the container's collection
      //
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
         piSysCollection->AddObject(piSysPoint); 
         piSysCollection-> Release();
         piSysCollection=NULL;
      }
      
      // Point location
      float x,y,z ;
      x = (float)iPoint.GetX() ;
      y = (float)iPoint.GetY() ;
      z = (float)iPoint.GetZ() ;
      piSysPoint->SetCoord(x,y,z);

      // Updates Display 
      CATIModelEvents * piModelEvent = NULL;                
      rc = piSysPoint->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
      if (SUCCEEDED(rc))
      {
		 CATBoolean WindowHistogram = TRUE ;
		 if ( TRUE == WindowHistogram ) 
		 {
            CATModify notif(_pUIActiveObject);
            piModelEvent->Dispatch(notif);
         }else
		 {
			CATCreate notif(piSysPoint,_pUIActiveObject);
            piModelEvent->Dispatch(notif);
		 }
         piModelEvent->Release();
         piModelEvent=NULL;
      }	 
      
      // Updates the specification tree
      CATIRedrawEvent * piRedrawEvent = NULL;                
      rc =_pUIActiveObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
      if (SUCCEEDED(rc))
      {
        piRedrawEvent->Redraw();
        
        piRedrawEvent->Release();
        piRedrawEvent= NULL ;
      }

      // Done with the point 
      piSysPoint->Release();
      piSysPoint=NULL;
    }

  }
}
