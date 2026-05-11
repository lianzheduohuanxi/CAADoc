// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateEllipseCmd.h"
#include "CAADegRadiusEllipseEditor.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATIndicationAgent.h"
#include "CATDialogAgent.h"
#include "CATDialogTransition.h"

//ApplicationFrame Framework      
#include "CATFrmEditor.h"     
#include "CATApplicationFrame.h"    

//Visualization Framework
#include "CATPathElement.h"   
#include "CATCreate.h"        
#include "CATIModelEvents.h" 
#include "CATCSO.h"

//CAASystem.edu Framework
#include "CAAISysPlane.h"          
#include "CAAISysEllipse.h"        
#include "CAAISysGeomFactory.h"    
#include "CAAISysCollection.h" 
#include "CAAISysAccess.h"       

// To set the current window plane with the selected  plane
// ApplicationFrame Framework
#include "CATFrmWindow.h"
#include "CATFrmLayout.h"
#include "CATI3DCamera.h"
#include "CATFrm3DCamera.h"

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 

//others
#include <iostream.h>

//-------------------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateEllipseCmd);
//
//----------------------LifeCycle's PART -----------------------------------------------

CAADegCreateEllipseCmd::CAADegCreateEllipseCmd(): CATStateCommand("CreateEllipseCmdId"),
        _daPathEltPlane (NULL), _daIndicEllipseCenter (NULL) ,
        _pRadiusEditor(NULL), _pUIActiveObject(NULL), 
        _pContainer(NULL)
{
  cout << "CAADegCreateEllipseCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor ) 
  {
    CATPathElement path = pEditor->GetUIActiveObject();
    if ( 0 != path.GetSize() ) 
    {
      // Retrieves the leaf of the path 
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
      // geometrical object  ( point,line, ellipse,....)
      piSysAccess->GetContainer(&_pContainer);

      // Done with this pointer
      piSysAccess->Release();
      piSysAccess=NULL;
    }  
  }   
}      

//-------------------------------------------------------------------------------------

CAADegCreateEllipseCmd::~CAADegCreateEllipseCmd()
{
  cout << "CAADegCreateEllipseCmd destructor" << endl ;

  if ( NULL != _daPathEltPlane ) 
  {
     _daPathEltPlane ->RequestDelayedDestruction();
     _daPathEltPlane = NULL ;
  }
  if ( NULL != _daIndicEllipseCenter )  
  {
     _daIndicEllipseCenter->RequestDelayedDestruction() ;
     _daIndicEllipseCenter = NULL ;
  }
  if ( NULL != _pRadiusEditor )
  {
     _pRadiusEditor->RequestDelayedDestruction() ;
     _pRadiusEditor = NULL ;
  }

  if ( NULL != _pContainer )
  {
    _pContainer->Release();
    _pContainer = NULL ;
  }

  if ( NULL != _pUIActiveObject ) 
  {
     _pUIActiveObject ->Release();
     _pUIActiveObject  = NULL ;
  }

}

//-------------------------------------------------------------------------

void CAADegCreateEllipseCmd::BuildGraph()
{
  cout << "CAADegCreateEllipseCmd BuildGraph" << endl ;

  //1- Create Dialog Agent 
  //......................

  //  1-1 To select the plane ( You can change several time the plane ) 
  //...................................................................

  _daPathEltPlane = new CATPathElementAgent("SelPlane");
  _daPathEltPlane->AddElementType(IID_CAAISysPlane);

  //  To be in Highlight after the selection + Prehighlight
  _daPathEltPlane->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation); 

  //  Read the cso  
  AddCSOClient(_daPathEltPlane); 


  //  1-2 To select the ellipse center
  // ..................................

  _daIndicEllipseCenter = new CATIndicationAgent("GetEllipseCenter");


  //  1-3 To select the ellipse radius ( repeat mode ) 
  //  No need of an agent. 
  // .................................................

  CATApplicationFrame * pFrame = NULL ;
  pFrame = CATApplicationFrame::GetFrame() ;
  if ( NULL != pFrame )
  {
	   // pParent is the Dialog object dedicated to the current document. 
       //
       CATDialog * pParent = pFrame->GetMainWindow() ;
       
       if ( NULL != pParent )
       {
          _pRadiusEditor = new CAADegRadiusEllipseEditor(pParent);
          _pRadiusEditor->Build();
	   }
  }


  //2- Creates states. See NLS file to display messages in the status bar  
  //.....................................................................

  CATDialogState *stGetPlane = GetInitialState("stGetPlaneId");
  stGetPlane->AddDialogAgent(_daPathEltPlane);

  CATDialogState *stGetEllipse = AddDialogState("stGetEllipseId");
  stGetEllipse->AddDialogAgent(_daIndicEllipseCenter);

   
  //3- Defines transitions
  //.......................
   
  CATDialogTransition *pFirstTransition = AddTransition
  (
     stGetPlane,
     stGetEllipse,
     IsOutputSetCondition(_daPathEltPlane),			  
     Action((ActionMethod) & CAADegCreateEllipseCmd::CreateCamera)
  ) ;

  CATDialogTransition *pSecondTransition = AddTransition
  (
     stGetEllipse,
     NULL,
     IsOutputSetCondition(_daIndicEllipseCenter),
     Action((ActionMethod) & CAADegCreateEllipseCmd::CreateEllipse)
  ) ;

}

//----------------------Action methods's PART -----------------------------

CATBoolean CAADegCreateEllipseCmd::CreateCamera(void *iDummy)
{
  cout << "CAADegCreateEllipseCmd::CreateCamera" << endl ;

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
      _ProjPlane.SetVectors(UPlane,VPlane);
      _daIndicEllipseCenter->SetMathPlane(_ProjPlane);

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
               pi3DCamera = NULL;
            }
            pCameraImpl->Release();
            pCameraImpl = NULL;
         }
      }	  
      rc = TRUE ;

      // Done with this pointer
      piSysPlane -> Release();
      piSysPlane= NULL ;
    }
  }

  return rc ;

}

//---------------------------------------------------------------------------

CATBoolean CAADegCreateEllipseCmd::CreateEllipse(void * iData)
{
  cout << "CAADegCreateEllipseCmd::CreateEllipse" << endl ;

  // Gets the Center  
  CATMathPoint2D point2D = _daIndicEllipseCenter->GetValue();
  CATMathPoint Center ;
  _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),Center);

  // Gets the radius from the  editor
  float Uradius (1.f);
  float Vradius (1.f);

  if ( NULL != _pRadiusEditor )
  {
     _pRadiusEditor->GetValues(&Uradius,&Vradius);
  }

  // Creates a new ellipse and updates the display
  NewEllipse(Center,Uradius,Vradius);

  return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreateEllipseCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateEllipseCmd::Activate" << endl;

  if ( NULL != _pRadiusEditor )
  {
     _pRadiusEditor->SetVisibility(CATDlgShow);
  }
  
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateEllipseCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateEllipseCmd::Desactivate" << endl;

  if ( NULL != _pRadiusEditor )
  {
     _pRadiusEditor->SetVisibility(CATDlgHide);
  }
  
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateEllipseCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateEllipseCmd::Cancel" << endl;

  if ( NULL != _pRadiusEditor )
  {
     _pRadiusEditor->SetVisibility(CATDlgHide);
  }

  return (CATStatusChangeRCCompleted) ;
}

//----------------------MODEL 's PART ---------------------------------------

void CAADegCreateEllipseCmd::NewEllipse(const CATMathPoint iCenter, 
                                        const float        iUradius, 
                                        const float        iVradius)
{
  // Creation of the ellipse by the pContainer factory 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates the new Ellipse
    CAAISysEllipse * piSysEllipse = NULL ;
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Ellipse, IID_CAAISysEllipse, 
			              (CATBaseUnknown**)&piSysEllipse);
    
    // Done with this pointer
    piSysGeomFactory -> Release();
    piSysGeomFactory= NULL;

    if (SUCCEEDED(rc))
    {      
      // Adds the ellipse in the pContainer's collection 
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);

      if (SUCCEEDED(rc))
      {
         piSysCollection ->AddObject(piSysEllipse);
         piSysCollection->Release();
         piSysCollection=NULL;
      }

      // Ellipse Location
      piSysEllipse->SetCenter(iCenter);
      piSysEllipse->SetRadius(iUradius,iVradius);

      CATMathVector UPlane , VPlane ;
      _ProjPlane.GetDirections(UPlane , VPlane);
      CATMathVector normal = UPlane ^ VPlane ;
      CATMathVector axis ;
      if ( iUradius > iVradius )
         axis = UPlane ;
      else
         axis = VPlane ;
      piSysEllipse->SetPlanar(normal,axis);

      // Updates display
      CATIModelEvents * piModelEventEllipse = NULL;                
      rc =piSysEllipse->QueryInterface(IID_CATIModelEvents, (void**)&piModelEventEllipse);
      if (SUCCEEDED(rc))
      {
         CATCreate notif (piSysEllipse,_pUIActiveObject);		
         piModelEventEllipse->Dispatch(notif);
         
         piModelEventEllipse->Release();
         piModelEventEllipse=NULL;
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

      // Ellipse in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the current BuildGraph method.
	  // 
      CATFrmEditor *pEditor = GetEditor();
      if ( NULL != pEditor) 
      {
         CATCSO * pCso = pEditor->GetCSO() ;
         if ( NULL != pCso)
         {
            // Creation of the path from the root to the Ellipse
            CATPathElement  RootPath = pEditor->GetUIActiveObject();
            CATPathElement *pPathEllipse = new CATPathElement(RootPath);
            pPathEllipse->AddChildElement(piSysEllipse);

            // Adds the complete path into the cso
            pCso->AddElement(pPathEllipse);

            pPathEllipse->Release();
            pPathEllipse = NULL;
         }
      }
      piSysEllipse->Release();
      piSysEllipse= NULL;
    }
    
  }
}

