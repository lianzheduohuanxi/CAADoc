// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateRectangleCmd.h"

//DialogEngine Framework
#include "CATIndicationAgent.h"
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"

//Visualization Framework
#include "CATPathElement.h"   
#include "CATCreate.h"         
#include "CATIModelEvents.h"   
#include "CATCSO.h"

//CAASystem.edu Framework
#include "CAAISysPoint.h"        
#include "CAAISysPlane.h"        
#include "CAAISysPolyline.h"      
#include "CAAISysGeomFactory.h"   
#include "CAAISysCollection.h"   
#include "CAAISysAccess.h"  

// Application Framework
#include "CATFrmWindow.h"
#include "CATFrmLayout.h"
#include "CATI3DCamera.h"
#include "CATFrm3DCamera.h"
#include "CATFrmEditor.h" 
#include "CATISO.h" 

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 

//others
#include <iostream.h>

// Should be a data model 
#define EPSILON 10E-3

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateRectangleCmd);


//----------------------LifeCycle's PART -------------------------------------
CAADegCreateRectangleCmd::CAADegCreateRectangleCmd():CATStateCommand("CreateRectangleCmdId"),
           _daIndicationP1(NULL),_daIndicationP2(NULL),
           _daPathEltPlane(NULL),
           _piTemporaryPoint(NULL),_piTemporaryRect(NULL),
           _pUIActiveObject(NULL), _pContainer(NULL), _pISO(NULL)
                                        
{
  cout << "CAADegCreateRectangleCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor )
  {
    _pISO = pEditor->GetISO() ;
    
    CATPathElement path = pEditor->GetUIActiveObject();
    if ( path.GetSize() > 0  )
    {
      _pUIActiveObject = path[path.GetSize()-1];
      _pUIActiveObject->AddRef();
    }
  }

  if ( NULL != _pUIActiveObject )
  {
    // Rectangle will be created by this container and added inside
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

//------------------------------------------------------------------------
 
CAADegCreateRectangleCmd::~CAADegCreateRectangleCmd()
{
  cout << "CAADegCreateRectangleCmd destructor" << endl ;

  if ( NULL != _daIndicationP1 )
  {
     _daIndicationP1 ->RequestDelayedDestruction();  
     _daIndicationP1 = NULL ;
  }
  if ( NULL != _daIndicationP2 ) 
  {
     _daIndicationP2 ->RequestDelayedDestruction();
     _daIndicationP2 = NULL ;
  }
  if ( NULL != _daPathEltPlane )
  {
     _daPathEltPlane ->RequestDelayedDestruction();
     _daPathEltPlane = NULL ;
  }

  if ( NULL != _pContainer )
  {
     _pContainer->Release();
     _pContainer = NULL ;
  }
  if ( NULL != _pUIActiveObject )
  {
     _pUIActiveObject->Release();
     _pUIActiveObject = NULL ;
  }

  _piTemporaryPoint = NULL ;
  _piTemporaryRect  = NULL ;
  _pISO = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreateRectangleCmd::BuildGraph()
{
  cout << "CAADegCreateRectangleCmd BuildGraph" << endl ;

  //1- Creates the dialog agents 
  //............................

  //1-1 Agent to select the projection plane 
  _daPathEltPlane = new CATPathElementAgent("SelPlane");
  _daPathEltPlane->AddElementType(IID_CAAISysPlane);

  // To be in Highlight after the selection + PreHighlight 
  // No Undo step recorded for this agent
  //
  _daPathEltPlane->SetBehavior(CATDlgEngWithPSOHSO | 
	                   CATDlgEngWithPrevaluation |
			   CATDlgEngWithUndo); 
  // Reads the cso  
  AddCSOClient(_daPathEltPlane); 

  //1-2 Agent to indicate the first point
  //    No Undo for this agent 
  _daIndicationP1 = new CATIndicationAgent("IndicationP1");
  _daIndicationP1->SetBehavior(CATDlgEngWithUndo);


  //1-3 Agent to indicate the second point
  _daIndicationP2 = new CATIndicationAgent("IndicationP2");
  // to have direct manipulation and No Undo step 
  _daIndicationP2->SetBehavior(CATDlgEngWithPrevaluation | 
	      CATDlgEngAcceptOnPrevaluate |
	      CATDlgEngWithUndo);

  //2- Creates states. See Nls file 
  //................................

  CATDialogState *stPlaneState = GetInitialState("stPlaneStateId");
  stPlaneState->AddDialogAgent(_daPathEltPlane);

  CATDialogState *stGetFirstPointState = AddDialogState("stGetFirstPointStateId");
  stGetFirstPointState->AddDialogAgent(_daIndicationP1);

  CATDialogState *stGetLastPointState = AddDialogState("stGetLastPointStateId");
  stGetLastPointState->AddDialogAgent(_daIndicationP2);

  //3-Define transitions 
  //.....................

  CATDialogTransition *pFirstTransition = AddTransition
  (
     stPlaneState,
     stGetFirstPointState,
     IsOutputSetCondition(_daPathEltPlane) ,
     Action((ActionMethod) & CAADegCreateRectangleCmd::CreateCamera)
  ) ;  

  CATDialogTransition *pSecondTransition = AddTransition
  (
     stGetFirstPointState,
     stGetLastPointState,
     AndCondition(IsOutputSetCondition(_daIndicationP1),
                  Condition((ConditionMethod)& CAADegCreateRectangleCmd::TestPoint1)),
     Action((ActionMethod) & CAADegCreateRectangleCmd::CreatePoint)
  ) ;  

  CATDialogTransition *pRubberTransition = AddTransition
  (
     stGetLastPointState,
     stGetLastPointState,
     AndCondition(IsLastModifiedAgentCondition(_daIndicationP2),
                  Condition((ConditionMethod)& CAADegCreateRectangleCmd::TestPoint2)),
     Action( (ActionMethod) & CAADegCreateRectangleCmd::UpdateRectangle)
  ) ;  

  CATDialogTransition *pFinalTransition = AddTransition
  (
     stGetLastPointState,
     NULL,
     AndCondition(IsOutputSetCondition(_daIndicationP2),
                  Condition((ConditionMethod)& CAADegCreateRectangleCmd::TestPoint2)),
     Action( (ActionMethod) & CAADegCreateRectangleCmd::NewRectangle)
  ) ; 
}

//-----------------------Condition Method's PART-------------------------------
CATBoolean CAADegCreateRectangleCmd::TestPoint1(void *iUsefulData)
{
  cout << "CAADegCreateRectangleCmd::TestPoint1" << endl ;
    
  CATBoolean rc = TRUE ;

  // If no Root Object, it's impossible to create an element
  // in the document
  if ( (NULL == _pUIActiveObject) ||
       (NULL == _pISO )|| 
       (NULL == _pContainer)  ) rc = FALSE ;
	 
  return rc ;
}

//-------------------------------------------------------------------------

CATBoolean CAADegCreateRectangleCmd::TestPoint2(void *iUsefulData)
{
  cout << "CAADegCreateRectangleCmd::TestPoint2" << endl ;
    
  CATBoolean rc = TRUE ;

  // Points in the plane 
  CATMathPoint2D P2D_2= _daIndicationP2->GetValue();
  CATMathPoint2D P2D_1= _daIndicationP1->GetValue();

  // test U and V distance 
  double du = CATFabs( P2D_2.GetX() - P2D_1.GetX() );
  double dv = CATFabs( P2D_2.GetY() - P2D_1.GetY() );

  if ( (du < EPSILON ) || (dv < EPSILON ) )
  {
    rc = FALSE ;
  }
  return rc ;
}

//-----------------------Action Method's PART-------------------------------

CATBoolean CAADegCreateRectangleCmd::CreateCamera(void *iUsefulData)
{
  cout << "CAADegCreateRectangleCmd::CreateCamera" << endl ;

  CATBoolean rc = FALSE ;

  CATPathElement * pathmodel = _daPathEltPlane->GetValue();
  CATBaseUnknown *obj = NULL ;
  if ( ( NULL != pathmodel) && (pathmodel->GetSize()> 0) )
  {
    obj = (*pathmodel)[pathmodel->GetSize()-1];
  }

  if ( NULL != obj )
  {
    CAAISysPlane * piSysPlane = NULL;                
    HRESULT hr = obj->QueryInterface(IID_CAAISysPlane, (void**)&piSysPlane);
    if (SUCCEEDED(hr))
    {
      // Retrieves the values from the selected plane
      CATMathPoint OriginPlane;
      CATMathVector UPlane,VPlane ;
      piSysPlane->GetOrigin(OriginPlane);
      piSysPlane->GetPlane(UPlane,VPlane);
          
      // sets the plane for the 2d indications agent 
      _ProjPlane.SetOrigin(OriginPlane);
      _ProjPlane.SetVectors(UPlane,VPlane);
      _daIndicationP1->SetMathPlane(_ProjPlane);
      _daIndicationP2->SetMathPlane(_ProjPlane);
          
      // Sets the current window plane with the selected  plane
      CATFrmLayout * pCurrentLayout = CATFrmLayout::GetCurrentLayout();
      if ( NULL != pCurrentLayout )
      {
         CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
         if ( NULL != pCurrentWindow )
         {
            CATMathVector direction = VPlane ^ UPlane ;

            // The plane origin must be in the viewport 
            float targetdist = 4.2f ;
            CATMathPoint OriginCamera = OriginPlane - targetdist * direction ;

            CATFrm3DCamera * pCameraImpl = NULL ;
            pCameraImpl = new CATFrm3DCamera("cam3d", OriginCamera, direction, VPlane);

            CATI3DCamera * pi3DCamera = NULL;                
            hr = pCameraImpl->QueryInterface(IID_CATI3DCamera, (void**)&pi3DCamera);
            if (SUCCEEDED(hr))
            {
               pCurrentWindow->SetCurrentCamera(pi3DCamera);
               pi3DCamera->Release();
               pi3DCamera=NULL;
            }
            pCameraImpl->Release();
            pCameraImpl=NULL;
        }
        rc = TRUE ;
      }
      piSysPlane -> Release();
      piSysPlane=NULL;
    }
  }
  return rc ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegCreateRectangleCmd::CreatePoint(void *iUsefulData)
{
  cout << "CAADegCreateRectangleCmd::CreatePoint " << endl ;

  // Gets The Point 
  CATMathPoint2D P2D ;
  P2D= _daIndicationP1->GetValue();
  _ProjPlane.EvalPoint(P2D.GetX(),P2D.GetY(),_P1);

  // Retrieves the factory from the container 	
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates a temporary point
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                               (CATBaseUnknown**)&_piTemporaryPoint);

    if ( SUCCEEDED(rc) )
    {
       float x= (float) _P1.GetX() ; 
       float y= (float) _P1.GetY() ;
       float z= (float) _P1.GetZ() ;
       _piTemporaryPoint->SetCoord(x,y,z);
       // Adds the temporary point in the ISO 	
       _pISO->AddElement(_piTemporaryPoint);
    }

    // Computes the second point to create a temporary polygone
    _ProjPlane.EvalPoint(P2D.GetX()+1.f, P2D.GetY()+1.f, _P2);
    _ProjPlane.EvalPoint(P2D.GetX()+1.f, P2D.GetY()    , _P3);
    _ProjPlane.EvalPoint(P2D.GetX()    , P2D.GetY()+1.f, _P4);

    // Creates the Temporary Rectangle 
    rc = piSysGeomFactory->Create(CAAISysGeomFactory::Polyline, IID_CAAISysPolyline, 
                             (CATBaseUnknown**)&_piTemporaryRect);
    if ( SUCCEEDED(rc) )
    {
       CATMathPoint * list = new CATMathPoint[4];
       list[0] = _P1 ;
       list[1] = _P3 ;
       list[2] = _P2 ;
       list[3] = _P4;
   
       _piTemporaryRect->SetListPoint(4,list);
       _piTemporaryRect->SetCloseStatus(1);
   
       delete [] list ;
   
       _pISO->AddElement(_piTemporaryRect);
    }

    piSysGeomFactory -> Release();
    piSysGeomFactory=NULL;
  }
  return TRUE ;
}

//----------------------------------------------------------------------------------

CATBoolean CAADegCreateRectangleCmd::UpdateRectangle(void *iUsefulData)
{
  cout << "CAADegCreateRectangleCmd::UpdateRectangle " << endl ;

  // Gets the second indicated point  
  CATMathPoint2D P2D_2= _daIndicationP2->GetValue();
  _ProjPlane.EvalPoint(P2D_2.GetX(),P2D_2.GetY(),_P2);

  //Retrieves the first indicated point 
  CATMathPoint2D P2D_1 ;
  P2D_1 = _daIndicationP1->GetValue();

  // Computes the others points 
  _ProjPlane.EvalPoint(P2D_1.GetX(), P2D_2.GetY(), _P4);
  _ProjPlane.EvalPoint(P2D_2.GetX(), P2D_1.GetY(), _P3);

  // Updates the temporary rectangle
  CATMathPoint * list = new CATMathPoint[4];
  list[0] = _P1 ;
  list[1] = _P3 ;
  list[2] = _P2 ;
  list[3] = _P4;
  _piTemporaryRect->SetListPoint(4,list);
  delete [] list ;

  _pISO->UpdateElement(_piTemporaryRect);

  return TRUE ;
}

//-------------------------------------------------------------------------------

CATBoolean CAADegCreateRectangleCmd::NewRectangle(void *iUsefulData)
{
  // Creation of the rectangle by the container factory 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates the new Rectangle
    CAAISysPolyline * piSysPolyline = NULL ;
    rc = piSysGeomFactory->Create(CAAISysGeomFactory::Polyline, IID_CAAISysPolyline, 
                                  (CATBaseUnknown**)&piSysPolyline);

    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Rectangle definition
      CATMathPoint * list = new CATMathPoint[4];
      list[0] = _P1 ;
      list[1] = _P3 ;
      list[2] = _P2 ;
      list[3] = _P4;
      piSysPolyline->SetListPoint(4,list);
      piSysPolyline->SetCloseStatus(1);
      delete [] list ;

      // Adds the rectangle in the Container's collection 
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
  	piSysCollection ->AddObject(piSysPolyline);
        piSysCollection->Release();
        piSysCollection=NULL;
      }

      // Updates Display 
      CATIModelEvents * piModelEvents = NULL;                
      rc =piSysPolyline->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
      if (SUCCEEDED(rc))
      {
         CATCreate notif (piSysPolyline,_pUIActiveObject);		   
         piModelEvents->Dispatch(notif);
        
         piModelEvents->Release();
         piModelEvents=NULL;
      }

      // Updates the specification tree
      CATIRedrawEvent * piRedrawEvent= NULL;                
      rc =_pUIActiveObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
      if (SUCCEEDED(rc))
      {
        piRedrawEvent->Redraw();
        
        piRedrawEvent->Release();
        piRedrawEvent= NULL ;
      }

      // Rectangle in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the current BuildGraph method.
	  // 
      CATFrmEditor * pEditor = GetEditor();
      if ( NULL != pEditor )
      {
        CATCSO * pCso = pEditor->GetCSO();
        if ( NULL != pCso )
        {
           // Creates the path from the root to the object
           CATPathElement RootPath = pEditor->GetUIActiveObject();
           CATPathElement * pPathRectangle = new CATPathElement(RootPath);
           pPathRectangle->AddChildElement(piSysPolyline);

           // Adds the path into the cso
           pCso->AddElement(pPathRectangle);

           //AddElement has AddRef'ed
           pPathRectangle->Release();
           pPathRectangle=NULL;
        }
      }
      piSysPolyline->Release();
      piSysPolyline=NULL;
    }
    
  }
  return TRUE ;
}

//--------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreateRectangleCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateRectangleCmd::Activate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//------------------------------------------------------------------------------ 

CATStatusChangeRC CAADegCreateRectangleCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateRectangleCmd::Desactivate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateRectangleCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateRectangleCmd::Cancel" << endl;

  if ( NULL != _piTemporaryPoint)
  {
    _pISO->RemoveElement(_piTemporaryPoint);
    _piTemporaryPoint->Release();
    _piTemporaryPoint = NULL ;
  }
  if ( NULL != _piTemporaryRect)
  {
    _pISO->RemoveElement(_piTemporaryRect);
    _piTemporaryRect->Release();
    _piTemporaryRect = NULL ;
  }
  return (CATStatusChangeRCCompleted) ;
}


