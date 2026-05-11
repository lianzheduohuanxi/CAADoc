// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateCircleCmd.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATIndicationAgent.h"
#include "CATDialogTransition.h"

// Visualization Framework
#include "CATCSO.h"
#include "CATPathElement.h"   
#include "CATCreate.h"        
#include "CATIModelEvents.h"  

//CAASystem.edu Framework
#include "CAAISysPlane.h"          
#include "CAAISysCircle.h"         
#include "CAAISysPoint.h"          
#include "CAAISysGeomFactory.h"    
#include "CAAISysCollection.h" 
#include "CAAISysAccess.h"       

// ApplicationFrame Framework
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

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateCircleCmd);


//----------------------LifeCycle's PART ------------------------------------

CAADegCreateCircleCmd::CAADegCreateCircleCmd():
                   CATStateCommand("CreateCircleCmdId"),
           _daPathEltPlane (NULL), _daIndicCircleCenter (NULL) ,
           _daIndicRadius(NULL), _Radius(0.f),
           _piTemporaryPoint(NULL),_piTemporaryCircle(NULL),
           _pUIActiveObject(NULL), _pContainer(NULL), _pISO(NULL)
{
  cout << "CAADegCreateCircleCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor ) 
  {
    _pISO = pEditor->GetISO() ;
    CATPathElement path = pEditor->GetUIActiveObject();
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

//-------------------------------------------------------------------------

CAADegCreateCircleCmd::~CAADegCreateCircleCmd()
{
   cout << "CAADegCreateCircleCmd destructor" << endl ;

   if ( NULL != _daPathEltPlane )    
   {
      _daPathEltPlane ->RequestDelayedDestruction();
      _daPathEltPlane = NULL ;
   }
   if ( NULL != _daIndicCircleCenter ) 
   {
      _daIndicCircleCenter ->RequestDelayedDestruction();
      _daIndicCircleCenter = NULL ;
   }
   if ( NULL != _daIndicRadius )       
   {
      _daIndicRadius ->RequestDelayedDestruction();
      _daIndicRadius = NULL ;
   }

   if ( NULL != _pContainer )   
   {
      _pContainer->Release();
      _pContainer = NULL ;
   }
   if ( NULL != _pUIActiveObject )       
   {
      _pUIActiveObject ->Release();
      _pUIActiveObject = NULL ;
   }

   _pISO = NULL ;
   _piTemporaryCircle = NULL ;
   _piTemporaryPoint  = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreateCircleCmd::BuildGraph()
{
  cout << "CAADegCreateCircleCmd BuildGraph" << endl ;

  // 1- Creates dialog agents 
  //.........................


  //  1-1 to select the plane 
  //.........................

  _daPathEltPlane = new CATPathElementAgent("SelPlane");
  _daPathEltPlane->AddElementType(IID_CAAISysPlane);

  // To be in Highlight after the selection + Prehighlight +
  // no Undo step recorded with this agent 
  _daPathEltPlane->SetBehavior(CATDlgEngWithPSOHSO | 
                               CATDlgEngWithPrevaluation | 
                               CATDlgEngWithUndo ); 
  // Reads the cso  
  AddCSOClient(_daPathEltPlane); 


  //  1-2 To indicate the circle center
  //...................................

  _daIndicCircleCenter = new CATIndicationAgent("GetCircleCenter");
  // No Undo step recorded for this agent 
  _daIndicCircleCenter->SetBehavior(CATDlgEngWithUndo);


  //  1-3 To indicate the point ended 
  //.................................

  _daIndicRadius = new CATIndicationAgent("GetRadiusPoint");
  _daIndicRadius->SetBehavior(CATDlgEngAcceptOnPrevaluate | 
	         CATDlgEngWithPrevaluation | CATDlgEngWithUndo );



  // 2- Creates states. See NLS file to display messages in the status bar  
  //......................................................................

  CATDialogState *stGetPlane = GetInitialState("stGetPlaneId");
  stGetPlane->AddDialogAgent(_daPathEltPlane);

  CATDialogState *stGetCircleCenter = AddDialogState("stGetCircleCenterId");
  stGetCircleCenter->AddDialogAgent(_daIndicCircleCenter);

  CATDialogState *stGetRadius = AddDialogState("stGetRadiusId");
  stGetRadius->AddDialogAgent(_daIndicRadius);
   

  // 3- Defines transitions 
  //......................

  CATDialogTransition *pFirstTransition = AddTransition
  (
     stGetPlane,
     stGetCircleCenter,
     IsOutputSetCondition(_daPathEltPlane),		   
     Action((ActionMethod) & CAADegCreateCircleCmd::CreateCamera)
  );

  CATDialogTransition *pSecondTransition = AddTransition
  (
     stGetCircleCenter,
     stGetRadius,
     AndCondition(IsOutputSetCondition(_daIndicCircleCenter),
                  Condition((ConditionMethod) & CAADegCreateCircleCmd::CheckCircleCenter)),
     Action((ActionMethod) & CAADegCreateCircleCmd::CreateCircleCenter)
  );

  CATDialogTransition *pThirdTransition = AddTransition
  (
     stGetRadius,
     NULL,
     IsOutputSetCondition(_daIndicRadius),
     Action((ActionMethod) & CAADegCreateCircleCmd::NewCircle)
  );

  CATDialogTransition *pRubberTransition = AddTransition
  (
     stGetRadius,
     stGetRadius,
     IsLastModifiedAgentCondition(_daIndicRadius),
     Action((ActionMethod) & CAADegCreateCircleCmd::UpdateCircle)
  );
}

//----------------------Condition's Method PART -------------------------------

CATBoolean CAADegCreateCircleCmd::CheckCircleCenter(void * iDummy)
{
  cout << "CAADegCreateCircleCmd::CheckCircleCenter" << endl ;
    
  CATBoolean rc = TRUE ;

  // If no Root Object, it's impossible to create an element 
  // If No Iso, no need to see the temporary point and circle
  if ( NULL == _pUIActiveObject || NULL == _pISO || NULL == _pContainer ) rc = FALSE ;

  return rc ;
}

//----------------------Action's Method PART ----------------------------------

CATBoolean CAADegCreateCircleCmd::CreateCamera(void *iDummy)
{
  cout << "CAADegCreateCircleCmd::CreateCamera" << endl ;

  CATBoolean rc = FALSE ;

  CATPathElement * pPathModel = _daPathEltPlane->GetValue();
  CATBaseUnknown * obj = NULL ;
  if ( (NULL != pPathModel) && (0 != pPathModel->GetSize()) )
  {
     // Retrieves the leaf of the path
     obj = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if ( NULL != obj )
  {
    CAAISysPlane * piSysPlane = NULL;                
    HRESULT hr = obj->QueryInterface(IID_CAAISysPlane, (void**)&piSysPlane);
    if (SUCCEEDED(hr))
    {
      // Gets the values from the selected plane
      CATMathPoint           OriginPlane   ;        
      CATMathVector       UPlane,VPlane ;
      piSysPlane->GetOrigin(OriginPlane )  ;
      piSysPlane->GetPlane(UPlane,VPlane)  ;
          
      // Sets the plane for the 2d indication  agents 
      _ProjPlane.SetOrigin(OriginPlane)      ;
      _ProjPlane.SetVectors(UPlane,VPlane) ;
      _daIndicCircleCenter->SetMathPlane(_ProjPlane);
      _daIndicRadius->SetMathPlane(_ProjPlane);

      // Sets the current window plane with the selected plane
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

            // Creates the implementation of the camera
            CATFrm3DCamera * pCameraImpl = NULL ;
            pCameraImpl = new CATFrm3DCamera("cam3d", OriginCamera, direction, VPlane);

            // Retrieves the interface CATI3DCamera
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
      }	  
      rc = TRUE ;

      // Done with this pointer
      piSysPlane -> Release();
      piSysPlane=NULL;
    }
  }

  return rc ;
}

//-------------------------------------------------------------------------

CATBoolean CAADegCreateCircleCmd::CreateCircleCenter(void * iData)
{
  cout << "CAADegCreateCircleCmd::CreateCircleCenter" << endl ;

  // Gets the indicated center  
  CATMathPoint2D point2D = _daIndicCircleCenter->GetValue();

  // Projection of the 2D point in 3D space
  _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),_CircleCenter);

  // Retrives the object which implements a factory to create a circle
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates the temporary point 
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
			(CATBaseUnknown**)&_piTemporaryPoint);
	
    if (SUCCEEDED(rc))
    {
       // Sets the Location to the new point
       float x= (float) _CircleCenter.GetX() ; 
       float y= (float) _CircleCenter.GetY() ;
       float z= (float) _CircleCenter.GetZ() ;
       _piTemporaryPoint->SetCoord(x,y,z);
       _pISO->AddElement(_piTemporaryPoint);
   
       // Creates the temporary circle ( r=0 ) and add in the ISO 
       rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Circle, IID_CAAISysCircle, 
   			(CATBaseUnknown**)&_piTemporaryCircle);
   
       if (SUCCEEDED(rc))
       {
          // Modifies the temporary circle with current value
          CATMathVector  UPlane,VPlane ;
          _ProjPlane.GetDirections(UPlane,VPlane);
          CATMathVector normal = UPlane ^ VPlane ;
          CATMathVector axis = UPlane ;
      
          _piTemporaryCircle->SetCenter(_CircleCenter);
          _piTemporaryCircle->SetPlanar(normal,axis);
          _piTemporaryCircle->SetRadius(_Radius);
      
          // Adds temporary circle in the the ISO
          _pISO->AddElement(_piTemporaryCircle);
       }
    }

    // Done with this pointer
    piSysGeomFactory -> Release();
    piSysGeomFactory=NULL;
  }
  return TRUE ;
}
//-------------------------------------------------------------------------

CATBoolean CAADegCreateCircleCmd::UpdateCircle(void * iData)
{
  cout << "CAADegCreateCircleCmd::UpdateCircle" << endl ;

  // Gets the current Point  
  CATMathPoint2D point2D = _daIndicRadius->GetValue();

  // Projection of the 2D point in 3D space
  CATMathPoint Mouse ;
  _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),Mouse);

  // Computes the radius 
  _Radius = (float) _CircleCenter.DistanceTo( Mouse);

  // Modification of the temporary circle
  _piTemporaryCircle->SetRadius(_Radius);

  _pISO->UpdateElement(_piTemporaryCircle);

  // Required to continue the rubber bending
  _daIndicRadius->InitializeAcquisition();

  return TRUE ;
}

//-------------------------------------------------------------------------

CATBoolean CAADegCreateCircleCmd::NewCircle(void * iData)
{
  // Creation of the circle  by a factory 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates the new Circle 
    CAAISysCircle * piSysCircle = NULL ;
    rc = piSysGeomFactory->Create(CAAISysGeomFactory::Circle, IID_CAAISysCircle, 
			                    (CATBaseUnknown**)&piSysCircle);
    // Done with this pointer
    piSysGeomFactory ->Release();	
    piSysGeomFactory=NULL;
    
    if (SUCCEEDED(rc))
    {   	 
      // Adds the circle in the Container's collection 
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
        piSysCollection ->AddObject(piSysCircle);
        piSysCollection->Release();
        piSysCollection=NULL;
      }

      // Circle Location
      piSysCircle->SetCenter(_CircleCenter);
      piSysCircle->SetRadius(_Radius);

      CATMathVector  UPlane,VPlane ;
      _ProjPlane.GetDirections(UPlane,VPlane);
      CATMathVector normal = UPlane ^ VPlane ;
      CATMathVector axis = UPlane ;
      piSysCircle->SetPlanar(normal,axis);

      // Updates the display
      CATIModelEvents * piModelEventCircle = NULL;                
      rc = piSysCircle->QueryInterface(IID_CATIModelEvents, (void**)&piModelEventCircle);
      if (SUCCEEDED(rc))
      {
         CATCreate Notif (piSysCircle,_pUIActiveObject);
         piModelEventCircle ->Dispatch(Notif);
         
         piModelEventCircle->Release();
         piModelEventCircle=NULL;
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

      // Circle in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the current BuildGraph method.
	  // 
      CATFrmEditor * pEditor = GetEditor();
      if ( NULL != pEditor) 
      {
        
         CATCSO * pCso = pEditor->GetCSO()  ;
         if ( NULL != pCso)
         {
            // Creation of the path from the root to the Circle
            CATPathElement RootPath     = pEditor->GetUIActiveObject();
            CATPathElement *pPathCircle = new CATPathElement(RootPath);
            pPathCircle->AddChildElement(piSysCircle);

            // Adds the path into the cso
            pCso->AddElement(pPathCircle);

            //AddElement AddRef'ed
            pPathCircle->Release();
            pPathCircle=NULL;
         }
      }
      // Done with this pointer
      piSysCircle->Release();
      piSysCircle=NULL;
    }

  }
  return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreateCircleCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateCircleCmd::Activate" << endl ;
  // This command uses the cso as entry so we don't empty it. 
  // But see CATDegCreateCylinder1.cpp to see the contrary
  // 

  // Nothing to do here, just to see cout when you launch the command
  // and note order of method  
  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateCircleCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateCircleCmd::Desactivate" << endl; 
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method  
  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------
CATStatusChangeRC CAADegCreateCircleCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateCircleCmd::Cancel" << endl;

  if (  NULL != _piTemporaryPoint)
  {
    _pISO->RemoveElement(_piTemporaryPoint);
    _piTemporaryPoint->Release();
    _piTemporaryPoint = NULL ;
  }
  if (  NULL != _piTemporaryCircle)
  {
    _pISO->RemoveElement(_piTemporaryCircle);
    _piTemporaryCircle->Release();
    _piTemporaryCircle = NULL ;
  }
  return (CATStatusChangeRCCompleted) ;
}
