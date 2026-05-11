// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreatePlaneCmd.h"
#include "CAADegPointErrorBox.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"

// Visualization Framework
#include "CATCSO.h"
#include "CATPathElement.h"   
#include "CATCreate.h"        
#include "CATIModelEvents.h"  

//CAASystem.edu Framework
#include "CAAISysAccess.h"    
#include "CAAISysPoint.h"        
#include "CAAISysPlane.h"        
#include "CAAISysGeomFactory.h" 
#include "CAAISysCollection.h"   

//ApplicationFrame Framework
#include "CATFrmEditor.h"   
#include "CATApplicationFrame.h"

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 
  
//Standard Library
#include <iostream.h>

// Should be a data model 
#define EPSILON 10E-6

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreatePlaneCmd);

//----------------------LifeCycle's PART --------------------------------------

CAADegCreatePlaneCmd::CAADegCreatePlaneCmd():CATStateCommand("CreatePlaneCmdId"),
                   _daPathElement(NULL), _pUIActiveObject(NULL),
                   _pContainer(NULL)                
{
  cout << "CAADegCreatePlaneCmd constructor" << endl ;
 
  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor ) 
  {
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
      // geometrical object  ( point,line, ellipse,....)
      piSysAccess->GetContainer(&_pContainer);

      // Done with this pointer
      piSysAccess->Release();
      piSysAccess=NULL;
    }  
  }   

}

//------------------------------------------------------------------------
 
CAADegCreatePlaneCmd::~CAADegCreatePlaneCmd()
{
   cout << "CAADegCreatePlaneCmd destructor" << endl ;

   if ( NULL != _daPathElement ) 
   {
      _daPathElement->RequestDelayedDestruction() ;
      _daPathElement = NULL ;
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
}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreatePlaneCmd::BuildGraph()
{
  cout << "CAADegCreatePlaneCmd BuildGraph" << endl ;

  //1- Creates the PathElement Agent 
  //.................................

  //  Element must be a point 
  _daPathElement = new CATPathElementAgent("SelStartPoint");
  _daPathElement->AddElementType(IID_CAAISysPoint);

  //  The point selected is hightlighted and pre-highlighted and 
  //  no Undo step is recorded with this agent 
  _daPathElement->SetBehavior(CATDlgEngWithPSOHSO | 
	                CATDlgEngWithPrevaluation | CATDlgEngWithUndo);

  //2- Create the 3 states
  //.......................

  //  In the NLS file, with id=stxxxPointId, you define the message
  //  wich appears in the status bar to indicate how get the xxx point
  CATDialogState *stStartState = GetInitialState("stFirstPointId");
  stStartState->AddDialogAgent(_daPathElement);

  CATDialogState *stSecondState = AddDialogState("stSecondPointId");
  stSecondState->AddDialogAgent(_daPathElement);
   
  CATDialogState *stEndState = AddDialogState("stThirdPointId");
  stEndState->AddDialogAgent(_daPathElement);

  //3-1 Defines transitions from Start to Second State
  //..................................................
  CATDialogTransition *pFirstTransition = AddTransition
  (
     stStartState,
     stSecondState,
     AndCondition(IsOutputSetCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreatePlaneCmd::CheckPoint1)),		  
     Action((ActionMethod) & CAADegCreatePlaneCmd::CreatePoint,NULL,NULL, (void *) 1) 
  ) ;

  //3-2 Defines transitions from Second to End State
  //..................................................
  CATDialogTransition *pSecondTransition = AddTransition
  (
     stSecondState,
     stEndState,
     AndCondition(IsOutputSetCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreatePlaneCmd::CheckPoint2)),
     Action((ActionMethod) & CAADegCreatePlaneCmd::CreatePoint,NULL,NULL, (void *) 2) 
  ) ;

  //3-3 Defines a transition from End To Final State 
  //..................................................
  CATDialogTransition *pThirdTransition =    AddTransition
  (
     stEndState,
     NULL,
     AndCondition(IsOutputSetCondition(_daPathElement) ,
                  Condition((ConditionMethod) & CAADegCreatePlaneCmd::CheckPoint3)),
     Action((ActionMethod) & CAADegCreatePlaneCmd::CreatePlane)
  ) ;  

}

//----------------------Condition methods's PART -----------------------------

CATBoolean CAADegCreatePlaneCmd::CheckPoint1(void * iUsefulData)
{
  cout << "CAADegCreatePlaneCmd::CheckPoint1"<<  endl ;
    
  CATBoolean rc = TRUE ;

  // If no Root Object, it's impossible to create element
  if ( (NULL == _pUIActiveObject) ||  (NULL == _pContainer) ) rc = FALSE ;

  return rc ;
}

//--------------------------------------------------------------------------

CATBoolean CAADegCreatePlaneCmd::CheckPoint2(void * iUsefulData)
{
  cout << "CAADegCreatePlaneCmd::CheckPoint2"<<  endl ;
    
  CATBoolean rc = TRUE ;

  // Tests if the first two points are not equal  
  if (  (NULL != _pUIActiveObject) && (NULL != _pContainer) ) 
  {
    //Gets the second point coordinates 
    CATPathElement * pPathModel = _daPathElement->GetValue();
    CATBaseUnknown * pObject = NULL ;
    if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()) )
    {
       // Retrieves the leaf of the path
       pObject = (*pPathModel)[pPathModel->GetSize()-1];
    }

    if ( NULL != pObject )
    {
      CAAISysPoint * piSysPoint = NULL;                
      HRESULT rc1 = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
      if (SUCCEEDED(rc1))
      {
        float x,y,z ;
        piSysPoint->GetCoord(x,y,z);
        CATMathPoint SecondPoint(x,y,z);

        // Tests the distance between the two points
        if ( SecondPoint.DistanceTo(_aPoint[0]) < EPSILON ) 
        {
           rc = FALSE ;

           CATApplicationFrame *pFrame = NULL ;
           pFrame = CATApplicationFrame::GetFrame();
           if ( NULL != pFrame )
           {
              CATDialog * pParent = pFrame->GetMainWindow();
              if ( NULL != pParent )
              {
                 // The dialog box will be deleted when the end user 
                 // selects the OK button.
                 CAADegPointErrorBox * pBoxError = new CAADegPointErrorBox(pParent,1,2);
                 pBoxError->Build();
                 pBoxError->SetVisibility(CATDlgShow);
              }
           }

           // to get back the second point
           _daPathElement->InitializeAcquisition();
        }
        
        // Done with the point interface
        piSysPoint -> Release();
        piSysPoint=NULL;
      }
    }else
    {
       rc = FALSE ;
    }
  }else 
  {
     rc = FALSE ;
  }

  return rc ;
}

//--------------------------------------------------------------------------

CATBoolean CAADegCreatePlaneCmd::CheckPoint3(void * iUsefulData)
{
  cout << "CAADegCreatePlaneCmd::CheckPoint3"<<  endl ;
    
  CATBoolean rc = TRUE ;

  // Tests points equality
  if (  (NULL != _pUIActiveObject) && (NULL != _pContainer) ) 
  {
    //Gets the third point coordinates 
    CATPathElement * pPathModel = _daPathElement->GetValue();
    CATBaseUnknown * pObject = NULL ;
    if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()) )
    {
       // Retrieves the leaf of the path
       pObject = (*pPathModel)[pPathModel->GetSize()-1];
    }

    if ( NULL != pObject )
    {
      CAAISysPoint * piSysPoint = NULL;                
      HRESULT rc1 = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
      if (SUCCEEDED(rc1))
      {
        float x,y,z ;
        piSysPoint->GetCoord(x,y,z);
        CATMathPoint ThirdPoint(x,y,z);

        int first(0) ;
        if ( ThirdPoint.DistanceTo(_aPoint[0]) < EPSILON ) 
            first = 1 ;
        else if ( ThirdPoint.DistanceTo(_aPoint[1]) < EPSILON )
            first = 2 ;
		
        if ( 0 != first )
        {
           rc = FALSE ;

           CATApplicationFrame *pFrame = NULL ;
           pFrame = CATApplicationFrame::GetFrame();
           if ( NULL != pFrame )
           {
              CATDialog * pParent = pFrame->GetMainWindow();
              if ( NULL != pParent )
              {
                 // The dialog box will be deleted when the end user 
                 // selects the OK button.
                 CAADegPointErrorBox * pBoxError = new CAADegPointErrorBox(pParent,first,3);
                 pBoxError->Build();
                 pBoxError->SetVisibility(CATDlgShow);
              }
           }
	   // to reset the agent
           _daPathElement->InitializeAcquisition();
        }

        // Done with the point 
        piSysPoint -> Release();
        piSysPoint=NULL;
      }
    }else
    {
       rc = FALSE ;
    }
  }else 
  {
     rc = FALSE ;
  }

  return rc ;
}

//----------------------Action methods's PART -----------------------------

CATBoolean CAADegCreatePlaneCmd::CreatePoint(void *iPointIndice)
{
  int indice = CATPtrToINT32(iPointIndice) -1 ;
  cout << "CAADegCreatePlaneCmd::CreatePoint=" << indice << endl ;

  CATPathElement * pPathModel = _daPathElement->GetValue();
  CATBaseUnknown * pObject = NULL ;
  if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()) )
  {
     // Retrieves the leaf of the path
     pObject = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if ( NULL != pObject )
  {
    CAAISysPoint * piSysPoint = NULL;                
    HRESULT rc = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
    if (SUCCEEDED(rc))
    {
      float x,y,z ;
      piSysPoint->GetCoord(x,y,z);
      _aPoint[indice].SetX(x);
      _aPoint[indice].SetY(y);
      _aPoint[indice].SetZ(z);
      piSysPoint->Release();
      piSysPoint=NULL;
    }
  }

  // The same agent is used in all the states, so between each, you must
  // reinitialize it, else you go directly to the end state. 
  _daPathElement->InitializeAcquisition(); 

  return TRUE ;
}

//--------------------------------------------------------------------------

CATBoolean CAADegCreatePlaneCmd::CreatePlane(void * iData)
{
  cout << "CAADegCreatePlaneCmd::CreatePlane" << endl ;

  CATPathElement * pPathModel = _daPathElement->GetValue();
  CATBaseUnknown * pObject = NULL ;
  if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()) )
  {
     // Retrieves the leaf of the path
     pObject = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if ( NULL != pObject )
  {

    CAAISysPoint * piSysPoint = NULL;                
    HRESULT rc = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
    if (SUCCEEDED(rc))
    {
       float x,y,z ;
       piSysPoint->GetCoord(x,y,z);
       _aPoint[2].SetX(x);
       _aPoint[2].SetY(y);
       _aPoint[2].SetZ(z);

       piSysPoint->Release();
       piSysPoint=NULL;
  
       // Creates a new plane in the document and updates the display
       NewPlane();
    }
  }
  return TRUE ;
}

//----------------------MODEL 's PART -----------------------------------------

void CAADegCreatePlaneCmd::NewPlane()
{
  // Creation of the plane by the container factory 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates the new Plane
    CAAISysPlane * piSysPlane = NULL ;
    rc = piSysGeomFactory ->Create(CAAISysGeomFactory::Plane, IID_CAAISysPlane, 
                           (CATBaseUnknown**)&piSysPlane);
    
    // Done with this pointer
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Adds the plane into the Container's collection
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection,(void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
         piSysCollection ->AddObject(piSysPlane);
         piSysCollection ->Release();
         piSysCollection =NULL;
      }

      // Plane Location
      piSysPlane->SetOrigin(_aPoint[0]);
      CATMathVector U = _aPoint[1] - _aPoint[0];
      CATMathVector V = _aPoint[2] - _aPoint[0];
      piSysPlane->SetPlane(U,V);

      // Updates the display
      CATIModelEvents * piModelEventPlane = NULL;                
      rc = piSysPlane->QueryInterface(IID_CATIModelEvents, (void**)&piModelEventPlane);
      if (SUCCEEDED(rc))
      {
         CATCreate notif (piSysPlane,_pUIActiveObject);	
    	 piModelEventPlane->Dispatch(notif);
        
         piModelEventPlane->Release();
         piModelEventPlane=NULL;
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

      // Plane in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the CAADegCreateRectangleCmd::BuildGraph method.
	  //
      CATFrmEditor *pEditor = GetEditor();
      if ( NULL != pEditor )
      {
         CATCSO * pCso = pEditor->GetCSO();
         if ( NULL != pCso)
         {
            // Creation of the path from the root object to the plane
            CATPathElement RootPath = pEditor->GetUIActiveObject();
            CATPathElement * pPathPlane = new CATPathElement(RootPath);			
            pPathPlane->AddChildElement(piSysPlane);

            // adds the path into the cso
            pCso->AddElement(pPathPlane);

            pPathPlane->Release();
            pPathPlane=NULL;
         }
      }
      piSysPlane->Release();
      piSysPlane=NULL;
    }
    
  } 
}


