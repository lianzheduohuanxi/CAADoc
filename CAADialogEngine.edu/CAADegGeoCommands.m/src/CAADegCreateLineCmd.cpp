// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateLineCmd.h" 

//DialogEngine Framework
#include "CATIndicationAgent.h"
#include "CATDialogTransition.h"
#include "CATStateActivateNotification.h"

//Visualization Framework
#include "CATCreate.h"        
#include "CATIModelEvents.h"  
#include "CATPathElement.h"

//CAASystem.edu Framework
#include "CAAISysAccess.h"       
#include "CAAISysPoint.h"        
#include "CAAISysLine.h"
#include "CAAISysGeomFactory.h"
#include "CAAISysCollection.h"

//ApplicationFrame Framework
#include "CATISO.h"    
#include "CATFrmEditor.h"         

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree        

// Mathematics Framework
#include "CATMathPlane.h" 

// Should be a data model 
#define EPSILON 10E-6

//others
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateLineCmd);

//----------------------LifeCycle's PART ----------------------------------
CAADegCreateLineCmd::CAADegCreateLineCmd():CATStateCommand("CreateLineCmdId"),
          _daIndication(NULL), _piFirstPoint(NULL) ,
          _pUIActiveObject(NULL), _pContainer(NULL), _pISO(NULL)
				   
{
  cout << "CAADegCreateLineCmd constructor" << endl ;

  // 1- The root object and the root container are stored as
  // data members
  //.....................................................                                           

  CATFrmEditor * editor   = GetEditor();
  if ( NULL != editor ) 
  {
    _pISO = editor->GetISO() ;
    CATPathElement path = editor->GetUIActiveObject();
    if ( 0 != path.GetSize() ) 
    {
      _pUIActiveObject=path[path.GetSize()-1];

      // Keep a interface pointer = AddRef to do
      _pUIActiveObject->AddRef();
    }
  }
  if ( NULL != _pUIActiveObject )
  {
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      // Retrieves the object which implements a factory to create 
      // geometrical object  ( point,line, circle,....)
      piSysAccess->GetContainer(&_pContainer);

      // Done with this pointer
      piSysAccess->Release();
      piSysAccess=NULL;
    }  
  }   

}

//-------------------------------------------------------------------------------------

CAADegCreateLineCmd::~CAADegCreateLineCmd()
{
  cout << "CAADegCreateLineCmd destructor" << endl ;

  if ( NULL != _daIndication )  
  {
     _daIndication ->RequestDelayedDestruction();
     _daIndication = NULL ;
  }
  if ( NULL != _pContainer )
  {
     _pContainer->Release();
     _pContainer = NULL ;
  }
  if ( NULL != _pUIActiveObject  ) 
  {
     _pUIActiveObject ->Release();
     _pUIActiveObject = NULL ;
  }

  _pISO        = NULL ;
  _piFirstPoint = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreateLineCmd::BuildGraph()
{
   cout << "CAADegCreateLineCmd BuildGraph" << endl ;

   //1- Create the indication agent ( the same for the 2 points )
   //.............................................................
      
   _daIndication = new CATIndicationAgent("StartPointIndication");
   // The plane of projection is not explicitly set with the SetMathPlane
   // method: a plane perpendicular to the sight
   // direction of the current viewpoint will be used for the projection.

   // No Undo with this agent 
   _daIndication->SetBehavior(CATDlgEngWithUndo);


   //2- Created the Start state
   //..........................
   //  In the NLS file, with id=stStartPointId, you note the message
   //  wich appears in the status bar to indicate how to get the first 
   //  point
   CATDialogState *stStartState = GetInitialState("stStartPointId");
   stStartState->AddDialogAgent(_daIndication);


   //3- Creates the End state
   //........................
   //  In the NLS file, with id=stEndPointId, you note the message
   //  wich appears in the status bar to indicate how to get the 
   //  second point
   CATDialogState *stEndState = AddDialogState("stEndPointId");
   stEndState->AddDialogAgent(_daIndication);


   //4-Defines a transition from Start to End State
   //...............................................

   CATDialogTransition *pFirstTransition = AddTransition
   (
      stStartState,
      stEndState,
      AndCondition(IsOutputSetCondition(_daIndication),
                   Condition((ConditionMethod) & CAADegCreateLineCmd::CheckStartPoint)),
      Action((ActionMethod) & CAADegCreateLineCmd::CreatePoint)
   );


   //5-Defines a transition from End To Final State 
   //...............................................
   CATDialogTransition *pSecondTransition =    AddTransition
   (
      stEndState,
      NULL,
      AndCondition(IsOutputSetCondition(_daIndication), 
                   Condition((ConditionMethod) & CAADegCreateLineCmd::CheckEndPoint)),		  
      Action((ActionMethod) & CAADegCreateLineCmd::CreateLine)
   );  
}

//----------------------Condition methods's PART -----------------------------

CATBoolean CAADegCreateLineCmd::CheckStartPoint(void *iDummy)
{
  cout << "CAADegCreateLineCmd::CheckStartPoint" << endl ;

  CATBoolean rc = TRUE ;

  // If no Root Object, it's impossible to create element
  if ( NULL == _pUIActiveObject || NULL == _pContainer ) rc = FALSE ;

  return rc ;
}

//-------------------------------------------------------------------------------

CATBoolean CAADegCreateLineCmd::CheckEndPoint(void *iDummy)
{
  cout << "CAADegCreateLineCmd::CheckEndPoint" << endl ;

  CATBoolean rc = TRUE ;

  // Tests if the second point is not equal to the first
  if (  NULL != _piFirstPoint ) 
  {
    // End Point 
    CATMathPoint2D point2D = _daIndication->GetValue();
    CATMathPoint EndPoint;

    // Retrieve the plane automatically defined
    CATMathPlane Plane =   _daIndication->GetMathPlane();
    Plane.EvalPoint(point2D.GetX(),point2D.GetY(), EndPoint);

    // Start Point
    float x,y,z ;
    _piFirstPoint->GetCoord(x,y,z);
    CATMathPoint StartPoint(x,y,z);

    // EPSILON should be a data model 
    if ( EndPoint.DistanceTo(StartPoint) < EPSILON ) 
    { 
      rc = FALSE ;
      // to get back the end point
      _daIndication->InitializeAcquisition();
    }
  }
  else rc = FALSE;

  return rc ;
}

//----------------------Action methods's PART -----------------------------

CATBoolean CAADegCreateLineCmd::CreatePoint(void *iDummy)
{

  cout << "CAADegCreateLineCmd::CreatePoint" << endl ;

  // Creation of the first 3D point 
  CATMathPoint2D point2D = _daIndication->GetValue();
  CATMathPoint Point3D;

  // Projection of the 2D point in the 3D space
  CATMathPlane Plane =   _daIndication->GetMathPlane();
  Plane.EvalPoint(point2D.GetX(),point2D.GetY(),Point3D);

  // Creates a temporary point 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                           (CATBaseUnknown**)&_piFirstPoint);
    
    // Done with the factory pointer
    piSysGeomFactory -> Release();
    piSysGeomFactory=NULL;
    
    if  (SUCCEEDED(rc))
    {   
       float x = (float) Point3D.GetX();
       float y = (float) Point3D.GetY();
       float z = (float) Point3D.GetZ();
      _piFirstPoint->SetCoord(x,y,z);
      _pISO->AddElement(_piFirstPoint);
    }

  }

  // We use the same agent for all the states. So you must reinitialize
  // it beetween each state, otherwise you go directly to the End state. 
  _daIndication->InitializeAcquisition(); 

  return TRUE ;
}

//------------------------------------------------------------------------------

CATBoolean CAADegCreateLineCmd::CreateLine(void * iData)
{
  cout << "COCreateLineCmd::CreateLine" << endl ;

  // Creation of the second 3D point
  CATMathPoint2D point2D = _daIndication->GetValue();
  CATMathPoint SecondPoint ;
  CATMathPlane Plane =   _daIndication->GetMathPlane();
  Plane.EvalPoint(point2D.GetX(),point2D.GetY(),SecondPoint);

  // Creates a new line in the document and updates the display
  NewLine(SecondPoint);

  return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreateLineCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method

  if ( NULL != iNotif ) 
  {
     if (((CATStateActivateNotification *) iNotif) -> GetType() 
                 ==  CATStateActivateNotification::Begin)
     {
       cout << " CAADegCreateLineCmd::Activate Begin " << endl;   
     }   
     else if (((CATStateActivateNotification *) iNotif) -> GetType() 
                 ==  CATStateActivateNotification::Resume)
     { 
       cout << "CAADegCreateLineCmd::Activate  Resume " << endl;
     }

  }  
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateLineCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateLineCmd::Desactivate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method  
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateLineCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateLineCmd::Cancel" << endl;

  if (  NULL != _piFirstPoint ) 
  {
    _pISO->RemoveElement(_piFirstPoint);
    _piFirstPoint->Release();
    _piFirstPoint = NULL ;
  }

  return (CATStatusChangeRCCompleted) ;
}

//-----------------Model's PART -----------------------------------------------

void CAADegCreateLineCmd::NewLine(const CATMathPoint &iSecondPoint)
{
  // Creation of the line by the container factory 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creation of the line 
    CAAISysLine * piSysLine = NULL ;
    HRESULT rc = piSysGeomFactory->Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                                          (CATBaseUnknown**)&piSysLine);
    // Done with the factory pointer
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Adds the line into the Container's collection
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
 	piSysCollection->AddObject(piSysLine);
        piSysCollection->Release();
        piSysCollection=NULL;
      }

      // Line location
      float x,y,z ;
      _piFirstPoint->GetCoord(x,y,z);
      CATMathPoint TemporaryPoint(x,y,z);

      piSysLine->SetStartPoint(TemporaryPoint);
      piSysLine->SetEndPoint(iSecondPoint);

      // Updates the display
      CATIModelEvents * piModelEventLine = NULL;                
      rc =piSysLine->QueryInterface(IID_CATIModelEvents, (void**)&piModelEventLine);
      if (SUCCEEDED(rc))
      {
        CATCreate notif (piSysLine,_pUIActiveObject);		 
        piModelEventLine->Dispatch(notif);
        
        piModelEventLine->Release();
        piModelEventLine=NULL;
      }

      // Updates the specification tree
      CATIRedrawEvent * piRedrawEventLine = NULL;                
      rc =_pUIActiveObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEventLine);
      if (SUCCEEDED(rc))
      {
        piRedrawEventLine->Redraw();
        
        piRedrawEventLine->Release();
        piRedrawEventLine = NULL ;
      }

      // Done with the Line pointer
      piSysLine->Release();
      piSysLine=NULL;
    }
  }
}

