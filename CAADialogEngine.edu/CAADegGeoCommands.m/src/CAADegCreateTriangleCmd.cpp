
// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateTriangleCmd.h"
#include "CAADegPointErrorBox.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"
#include "CATCommandGlobalUndo.h"

// Visualization Framework
#include "CATCSO.h"
#include "CATPathElement.h"    
#include "CATCreate.h"        
#include "CATDelete.h"         
#include "CATIModelEvents.h"  

// ApplicationFrame Framework
#include "CATISO.h"
#include "CATFrmEditor.h"    
#include "CATApplicationFrame.h"  

//CAASystem.edu Framework
#include "CAAISysPoint.h"            
#include "CAAISysLine.h"             
#include "CAAISysGeomFactory.h"     
#include "CAAISysPolyline.h"         
#include "CAAISysCollection.h" 
#include "CAAISysAccess.h" 

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 
   
// C++ Standard Library
#include <iostream.h>

// Should be a data model 
#define EPSILON 10E-6

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateTriangleCmd);


//----------------------LifeCycle's PART -----------------------------------
CAADegCreateTriangleCmd::CAADegCreateTriangleCmd():
                   CATStateCommand("CreateTriangleCmdId")           
{
 // In this constructor the mode is the default mode exclusive
 cout << "CAADegCreateTriangleCmd constructor as main command" << endl ;
 Init() ;
}

CAADegCreateTriangleCmd::CAADegCreateTriangleCmd(const int iDummy):
                   CATStateCommand("CreateTriangleCmdId",CATCommandModeUndefined)
{
   // In this constructor the mode is undefined: CATCommandModeUndefined
   cout << "CAADegCreateTriangleCmd constructor as agent" << endl ;
   Init() ;
}
				   
void CAADegCreateTriangleCmd::Init()
{
  _daPathElement = NULL ;
  _piTemporaryLine = NULL;
  _piEltTriangle = NULL ;
  _pISO = NULL ;
  _pContainer = NULL ;
  _pUIActiveObject = NULL ;   
  _IsAgentValuated = FALSE ;
  
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

	  if ( NULL != _pUIActiveObject)
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
  }
}

//-------------------------------------------------------------------------

CAADegCreateTriangleCmd::~CAADegCreateTriangleCmd()
{
   cout << "CAADegCreateTriangleCmd destructor" << endl ;

   if ( NULL != _daPathElement )
   {
      _daPathElement -> RequestDelayedDestruction();
      _daPathElement  = NULL ;
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

   _pISO = NULL ;
   _piTemporaryLine = NULL ;

   if ( NULL != _piEltTriangle )
   { 
	   _piEltTriangle->Release();
	   _piEltTriangle = NULL ;
   }
}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreateTriangleCmd::BuildGraph()
{
  cout << "CAADegCreateTriangleCmd BuildGraph" << endl ;

  //1- Creates the PathElement Agent ( the same for the 3 points )

  // 1-1 element must be a point 
  _daPathElement = new CATPathElementAgent("SelStartPoint");
  _daPathElement->AddElementType(IID_CAAISysPoint);

  // 1-2 the selected point is hightlighted 
  _daPathElement->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

  //2- Creates the 3 states
  //  In the NLS file, with id=stxxxPointId, you note the message
  //  wich appears in the status bar to indicate how to give the xxx point
  CATDialogState *stStartState = GetInitialState("stFirstPointId");
  stStartState->AddDialogAgent(_daPathElement);

  CATDialogState *stSecondState = AddDialogState("stSecondPointId");
  stSecondState->AddDialogAgent(_daPathElement);
   
  CATDialogState *stEndState = AddDialogState("stThirdPointId");
  stEndState->AddDialogAgent(_daPathElement);

  //3-1 Defines transitions from Start to Second State
  CATDialogTransition *pFirstTransition = AddTransition
  (
     stStartState,
     stSecondState,
     AndCondition(IsOutputSetCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreateTriangleCmd::CheckPoint1)),
     Action((ActionMethod) & CAADegCreateTriangleCmd::CreatePoint,
            (ActionMethod) & CAADegCreateTriangleCmd::UndoCreatePoint,
            (ActionMethod) & CAADegCreateTriangleCmd::RedoCreatePoint)
  ) ;

  //3-2 Defines transitions from Second to End State
  CATDialogTransition *pSecondTransition = AddTransition
  (
     stSecondState,
     stEndState,
     AndCondition(IsOutputSetCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreateTriangleCmd::CheckPoint2)),
     Action((ActionMethod) & CAADegCreateTriangleCmd::CreateLine,
            (ActionMethod) & CAADegCreateTriangleCmd::UndoCreateLine,
            (ActionMethod) & CAADegCreateTriangleCmd::RedoCreateLine)
  ) ;

  // For the Edit/Undo-Redo Nls Message 
  pSecondTransition->SetResourceID("SecondTransition");

  //3-3 Defines a transition from End To Final State 
  CATDialogTransition *pThirdTransition =    AddTransition
  (
     stEndState,
     NULL,
     AndCondition(IsOutputSetCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreateTriangleCmd::CheckPoint3)),
     Action((ActionMethod) & CAADegCreateTriangleCmd::CreateTriangle)
  ) ;  
}

//---------------------Condition method's PART---------------------------------
CATBoolean CAADegCreateTriangleCmd::CheckPoint1(void *iUsefulData)
{
  cout << "CAADegCreateTriangleCmd::CheckPoint1"<<  endl ;
    
  CATBoolean rc = TRUE ;

  // If no Root Object, it's impossible to create element
  if ( (NULL == _pUIActiveObject) || (NULL == _pContainer) ) rc = FALSE ;
	 
  return rc ;
}

//------------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::CheckPoint2(void *iUsefulData)
{
  cout << "CAADegCreateTriangleCmd::CheckPoint2"<<  endl ;
    
  CATBoolean rc = FALSE ;

  // Tests if the first two points are not equal 
  if (  (NULL != _pUIActiveObject) && (NULL != _pContainer) ) 
  {
    //Gets the second point coordinates 
    CATPathElement * pPathModel = _daPathElement->GetValue();
    CATBaseUnknown * pObject = NULL ;
    if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()) )
    {
      pObject = (*pPathModel)[pPathModel->GetSize()-1];
    }

    if (  NULL != pObject )
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
           // The dialog box will be deleted when the end user 
           // selects the OK button.
		   CATApplicationFrame *pFrame = NULL ;
           pFrame = CATApplicationFrame::GetFrame();
           if ( NULL != pFrame )
           {
              CATDialog * pParent = pFrame->GetMainWindow();
              if ( NULL != pParent )
              {
                 CAADegPointErrorBox * pBoxError = new CAADegPointErrorBox(pParent,1,2);
                 pBoxError->Build();
                 pBoxError->SetVisibility(CATDlgShow);
			  }
		   }

          // to get back the second point
          _daPathElement->InitializeAcquisition();
        }
        else rc = TRUE ;

        piSysPoint-> Release();
        piSysPoint=NULL;
      }
    } 
  } 
  return rc ;
}

//-------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::CheckPoint3(void *iUsefulData)
{
  cout << "CAADegCreateTriangleCmd::CheckPoint3"<<  endl ;
    
  CATBoolean rc = FALSE ;

  // Tests points equality
  if (  (NULL != _pUIActiveObject) && (NULL != _pContainer) ) 
  {
    //Get the third point coordinates 
    CATPathElement * pPathModel = _daPathElement->GetValue();
    CATBaseUnknown * pObject = NULL ;
    if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()) )
    {
      pObject = (*pPathModel)[pPathModel->GetSize()-1];
    }

    if (  NULL != pObject )
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
           // The dialog box will be deleted when the end user 
           // selects the OK button.
			
           CATApplicationFrame *pFrame = NULL ;
           pFrame = CATApplicationFrame::GetFrame();
           if ( NULL != pFrame )
           {
              CATDialog * pParent = pFrame->GetMainWindow();
              if ( NULL != pParent )
              {
                 CAADegPointErrorBox * pBoxError = new CAADegPointErrorBox(pParent,first,3);
                 pBoxError->Build();
                 pBoxError->SetVisibility(CATDlgShow);
			  }
		   }

           // to reset the third point
           _daPathElement->InitializeAcquisition();
        }
        else rc= TRUE;

        piSysPoint -> Release();
        piSysPoint=NULL ;
      }
    } 
  } 
  return rc ;
}

//---------------------Action method's PART-----------------------------------

CATBoolean CAADegCreateTriangleCmd::CreatePoint(void *iPointIndice)
{ 
  cout << "CAADegCreateTriangleCmd::CreatePoint" <<  endl ;

  CATPathElement * pPathModel = _daPathElement->GetValue();

  CATBaseUnknown * pObject = NULL ;
  if ( (NULL != pPathModel) &&  (0 != pPathModel->GetSize()) )
  {
     pObject = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if (  NULL !=  pObject )
  {
    CAAISysPoint * piSysPoint = NULL;                
    HRESULT rc =  pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
    if (SUCCEEDED(rc))
    {
      // Gets x,y,z from the point selected
      float x,y,z ;

      piSysPoint->GetCoord(x,y,z);
      _aPoint[0].SetX(x);
      _aPoint[0].SetY(y);
      _aPoint[0].SetZ(z);

      piSysPoint-> Release();
      piSysPoint=NULL;
    }
  }

  // We use the same agent for all states, so between each, you must
  // reinitialize it, else you go directly to the end state. 
  _daPathElement->InitializeAcquisition(); 

  return TRUE ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::CreateLine(void *iPointIndice)
{

  cout << "CAADegCreateTriangleCmd::CreateLine" <<  endl ;

  CATPathElement * pPathModel = _daPathElement->GetValue();

  CATBaseUnknown * pObject = NULL ;
  if ( (NULL != pPathModel) &&  (0 != pPathModel->GetSize()) )
  {
    pObject = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if ( NULL != pObject )
  {
    CAAISysPoint * piSysPoint = NULL;                
    HRESULT rc = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
    if (SUCCEEDED(rc))
    {
      // Gets x,y,z from the point selected
      float x,y,z ;

      piSysPoint->GetCoord(x,y,z);
      _aPoint[1].SetX(x);
      _aPoint[1].SetY(y);
      _aPoint[1].SetZ(z);

      piSysPoint-> Release();
      piSysPoint=NULL;
    }
  }

 // Draws an temporary line beetween p0 and p1 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    rc = piSysGeomFactory->Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                                    (CATBaseUnknown**)&_piTemporaryLine);
    piSysGeomFactory->Release();
    piSysGeomFactory= NULL ;

    if ( SUCCEEDED(rc) )
    {
       _piTemporaryLine->SetStartPoint(_aPoint[0]);
       _piTemporaryLine->SetEndPoint(_aPoint[1]);
       _pISO->AddElement(_piTemporaryLine);
    }
  }

  // The same agent is used for all states, so between each, you must
  // reinitialize it, else you go directly to the end state. 
  _daPathElement->InitializeAcquisition(); 

  return TRUE ;
}

//---------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::CreateTriangle(void * iData)
{
  cout << "CAADegCreateTriangleCmd::CreatePlane" << endl ;

  CATPathElement * pPathModel = _daPathElement->GetValue();

  CATBaseUnknown * pObject = NULL ;
  if ( (NULL != pPathModel) &&  (0 != pPathModel->GetSize()) )
  {
    pObject = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if ( NULL != pObject )
  {
    CAAISysPoint * piSysPoint = NULL;                
    HRESULT rc = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
    if (SUCCEEDED(rc))
    {
      // Gets x,y,z for the last 3D point
      float x,y,z ;

      piSysPoint->GetCoord(x,y,z);
      _aPoint[2].SetX(x);
      _aPoint[2].SetY(y);
      _aPoint[2].SetZ(z);

      piSysPoint->Release();
      piSysPoint=NULL;
    }
  }
    
  // Updates ISO
  if ( NULL != _piTemporaryLine )
  {
    _pISO->RemoveElement(_piTemporaryLine);
    _piTemporaryLine->Release();
    _piTemporaryLine= NULL ;
  }
  
  // Creates a new triangle in the document and updates the display
  NewTriangle();

  return TRUE ;
}

//---------Local Undo/Redo method's PART -----------------------------------

CATBoolean CAADegCreateTriangleCmd::UndoCreateLine(void *iPointIndice)
{
  cout << "CAADegCreateTriangleCmd::UndoCreateLine" <<  endl ;

  if ( NULL != _piTemporaryLine )
  {
    _pISO->RemoveElement(_piTemporaryLine);
    _piTemporaryLine->Release();
    _piTemporaryLine= NULL ;
  }
  return TRUE ;
}

//---------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::RedoCreateLine(void *iPointIndice)
{
  cout << "CAADegCreateTriangleCmd::RedoCreateLine" <<  endl ;
 
  if ( NULL == _piTemporaryLine ) 
  {
    // P1 and P0 are always valid
    CAAISysGeomFactory * piSysFactory = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysFactory);
    if (SUCCEEDED(rc))
    {
      rc = piSysFactory -> Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                        (CATBaseUnknown**)&_piTemporaryLine);
      piSysFactory -> Release();
      piSysFactory = NULL ;
      if ( SUCCEEDED(rc) )
      {
         _piTemporaryLine->SetStartPoint(_aPoint[0]);
         _piTemporaryLine->SetEndPoint(_aPoint[1]);
         _pISO->AddElement(_piTemporaryLine);
      }
    }
  }

  // Required 
  _daPathElement->InitializeAcquisition(); 

  return TRUE ;
}


//-----------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::UndoCreatePoint(void *iPointIndice)
{
  cout << "CAADegCreateTriangleCmd::UndoCreatePoint" <<  endl ;
  return TRUE ;
}

//------------------------------------------------------------------------------

CATBoolean CAADegCreateTriangleCmd::RedoCreatePoint(void *iPointIndice)
{
  cout << "CAADegCreateTriangleCmd::RedoCreatePoint" <<  endl ;

  // Required to get back the first point
  _daPathElement->InitializeAcquisition(); 

  return TRUE ;
}
//--------Global Undo/Redo method's PART ---------------------------------

CATCommandGlobalUndo * CAADegCreateTriangleCmd::GetGlobalUndo()
{
  cout << "CAADegCreateTriangleCmd::GetGlobalUndo"<< endl ;

  CATCommandGlobalUndo * command = NULL ;

  // _piEltTriangle  is the triangle created in the NewTriangle method
  // this value is kept (release +1) 
  //
  if ( NULL != _piEltTriangle )
  {
    
	_piEltTriangle->AddRef();

    command = new CATCommandGlobalUndo (
        (CATGlobalUndoMethod)& CAADegCreateTriangleCmd::UndoCreateTriangle,
        (CATGlobalUndoMethod)& CAADegCreateTriangleCmd::RedoCreateTriangle,
        (void *) _piEltTriangle ,
        (CATGlobalUndoMethod)& CAADegCreateTriangleCmd::DesallocatTriangle);
  }

  return command  ;
}

//------------------------------------------------------------------------

void CAADegCreateTriangleCmd::UndoCreateTriangle(void *iData)
{
  // iData is the Triangle created in the CreateTriangle 
  CAAISysPolyline * piSysPolyline  = (CAAISysPolyline *) iData ;
  cout << "CAADegCreateTriangleCmd::UndoCreateTriangle"<< piSysPolyline << endl ;

  if ( NULL != piSysPolyline )
  {
    // Retrieves the container which contains Elt
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = piSysPolyline->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      CATBaseUnknown * pContainer = NULL ;
      piSysAccess->GetContainer(&pContainer);
        
      if ( NULL != pContainer )
      {
        // Updates Display 
        CATIModelEvents * piModelEvents = NULL;                
        rc = piSysPolyline->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
        if (SUCCEEDED(rc))
        {
          CATDelete  notif (piSysPolyline);
          piModelEvents->Dispatch(notif);
          
          piModelEvents->Release();
          piModelEvents = NULL ;
        }
      
        // Updates the container's collector
        CAAISysCollection * piSysCollection = NULL;                
        rc = pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
        if (SUCCEEDED(rc))
        {
           piSysCollection->RemoveObject(piSysPolyline); 

           // retrieves the UI Active object 
           CATBaseUnknown * UIAObject = NULL ;
           piSysCollection->GetObject(1,&UIAObject);

           // Updates the specification tree
           if ( NULL != UIAObject )
           {
              CATIRedrawEvent * piRedrawEvent= NULL;                
              rc =UIAObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
              if (SUCCEEDED(rc))
              {
                 piRedrawEvent->Redraw();
        
                 piRedrawEvent->Release();
                 piRedrawEvent = NULL ;
              }
              UIAObject->Release();
              UIAObject = NULL ;
           }

           piSysCollection->Release(); 
           piSysCollection= NULL ;
        }
        
        // Necessary for the Redo 
        piSysAccess->SetContainer(pContainer);

        pContainer->Release(); 
        pContainer = NULL ;
      }

      piSysAccess -> Release();
      piSysAccess = NULL ;
    }
  }	
}

//------------------------------------------------------------------------

void  CAADegCreateTriangleCmd::RedoCreateTriangle(void *iData)
{
  // iData is the Triangle created in the CreateTriangle
  // and given in the GetGlobalUndo to the dialog engine
  //
  CAAISysPolyline * piSysPolyline  = (CAAISysPolyline *) iData ;

  cout << "CAADegCreateTriangleCmd::RedoCreateTriangle"<< piSysPolyline << endl ;

  if ( NULL != piSysPolyline )
  {
    // Retrieves  the container
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = piSysPolyline->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      CATBaseUnknown * pContainer = NULL ;
      piSysAccess->GetContainer(&pContainer);
      piSysAccess->Release();
      piSysAccess=NULL;
        
      if ( NULL != pContainer )
      {
        // Updates the container's collector
        CAAISysCollection * piSysCollection = NULL;                
        rc = pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);

        pContainer->Release();
        pContainer= NULL ;

        if (SUCCEEDED(rc))
        {
           piSysCollection->AddObject(piSysPolyline); 

           //Updates display
           CATIModelEvents * piModelEvents = NULL;                
           rc = piSysPolyline->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
           if (SUCCEEDED(rc))
           {
              // retrieves the UI Active object 
              CATBaseUnknown * UIAObject = NULL ;
              piSysCollection->GetObject(1,&UIAObject);

              if ( NULL != UIAObject )
              {
                 CATCreate notif (piSysPolyline,UIAObject);
                 piModelEvents->Dispatch(notif);
              
                 CATIRedrawEvent * piRedrawEvent= NULL;                
                 rc =UIAObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
                 if (SUCCEEDED(rc))
                 {
                     piRedrawEvent->Redraw();
        
                     piRedrawEvent->Release();
                     piRedrawEvent = NULL ;
                 }

                 UIAObject->Release();
                 UIAObject= NULL ;
              }
              piModelEvents->Release();
              piModelEvents = NULL ;
           }

           piSysCollection->Release(); 
           piSysCollection= NULL ;
        }
      }
    }	
  }
}

//-------------------------------------------------------------------------------

void  CAADegCreateTriangleCmd::DesallocatTriangle(void *iData)
{
  cout << "CAADegCreateTriangleCmd::DesallocatTriangle"<< endl ;
	
  if ( iData )
  {
    // iData is the Triangle created in the CreateTriangle
    CAAISysPolyline * piSysPolyline  = (CAAISysPolyline *) iData ;

    if ( NULL != piSysPolyline) 
    {
      piSysPolyline->Release();
      piSysPolyline = NULL ;
    }
  }
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreateTriangleCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateTriangleCmd::Activate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateTriangleCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateTriangleCmd::Desactivate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateTriangleCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateTriangleCmd::Cancel" << endl;
  if (NULL != _piTemporaryLine)
  {
    _pISO->RemoveElement(_piTemporaryLine);
    _piTemporaryLine->Release();
    _piTemporaryLine= NULL ;
  }
  return (CATStatusChangeRCCompleted) ;
}

//----------------------MODEL 's PART ----------------------------------------
void CAADegCreateTriangleCmd::NewTriangle()
{
  // Creation of the triangle by the container factory 
  CAAISysGeomFactory * piSysFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysFactory);
  if (SUCCEEDED(rc))
  {
    CAAISysPolyline * piSysPolyline = NULL ;
    rc = piSysFactory ->Create(CAAISysGeomFactory::Polyline, IID_CAAISysPolyline, 
			(CATBaseUnknown**)&piSysPolyline);
    
    piSysFactory -> Release();
    piSysFactory=NULL;
    
    if (SUCCEEDED(rc))
    {      
      // Triangle Location
      CATMathPoint * list = new CATMathPoint[3];
      list[0] = _aPoint[0] ;
      list[1] = _aPoint[1] ;
      list[2] = _aPoint[2] ;
      piSysPolyline->SetListPoint(3,list) ;
      piSysPolyline->SetCloseStatus(1) ;
      delete [] list ;

      // Adds the triangle in the Container's collection 
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
        piSysCollection->AddObject(piSysPolyline);
        piSysCollection->Release();
        piSysCollection=NULL;
      }
      
      //Updates display
      CATIModelEvents * piModelEvents = NULL;                
      rc = piSysPolyline->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
      if (SUCCEEDED(rc))
      {
         CATCreate notif (piSysPolyline,_pUIActiveObject);	
         piModelEvents->Dispatch(notif);
       
         piModelEvents->Release();
         piModelEvents=NULL;
      }

      // Updates the specification tree
      CATIRedrawEvent * piRedrawEvent = NULL;                
      rc =_pUIActiveObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
      if (SUCCEEDED(rc))
      {
        piRedrawEvent->Redraw();
        
        piRedrawEvent->Release();
        piRedrawEvent = NULL ;
      }

	  // The interface pointer is kept for the global Undo/Redo
      _piEltTriangle = piSysPolyline ;

	  // We can get the triangle as value of agent
	  _IsAgentValuated = TRUE ;

      // Triangle in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the CAADegCreateRectangleCmd::BuildGraph method.
	  // 
      CATFrmEditor * pEditor = GetEditor();
      if ( NULL != pEditor )
      {
         CATCSO * pCso = pEditor->GetCSO();

         if ( NULL != pCso )
         {
            // Creates the path from the root object to the object
            CATPathElement RootPath = pEditor->GetUIActiveObject();
            CATPathElement *pPathTriangle = new CATPathElement(RootPath);
            pPathTriangle->AddChildElement(piSysPolyline);

            // completes path in the cso
            pCso->AddElement(pPathTriangle);

            // AddElement has AddRef'ed
            pPathTriangle->Release();
            pPathTriangle=NULL;
         }
      }
     
    }

  } 
}


//------------------------------------------------------------------------

void CAADegCreateTriangleCmd::BeforeUndo()
{
	cout << " CAADegCreateTriangleCmd::BeforeUndo" << endl ;

  if ( NULL != _piEltTriangle )
  {
	_IsAgentValuated = FALSE ;

    // Updates Display 
    CATIModelEvents * piModelEvents = NULL;                
    HRESULT rc = _piEltTriangle->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
    if ( SUCCEEDED(rc) )
    {
          CATDelete  notif (_piEltTriangle);
          piModelEvents->Dispatch(notif);
          
          piModelEvents->Release();
          piModelEvents = NULL ;
    }

    // Updates the container's collector
    CAAISysCollection * piSysCollection = NULL;                
    rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
    if (SUCCEEDED(rc))
    {
       piSysCollection->RemoveObject(_piEltTriangle); 

       piSysCollection->Release(); 
       piSysCollection= NULL ;
    }

  }	
}
//------------------------------------------------------------------------
void CAADegCreateTriangleCmd::BeforeRedo()
{
  cout << " CAADegCreateTriangleCmd::BeforeRedo" << endl ;
  
  if ( NULL != _piEltTriangle )
  {
	_IsAgentValuated = TRUE ;

    // Updates the container's collector
    CAAISysCollection * piSysCollection = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection) ;

    if (SUCCEEDED(rc))
    {
       piSysCollection->AddObject(_piEltTriangle); 
       piSysCollection->Release(); 
       piSysCollection= NULL ;
       
	   //Updates display
       CATIModelEvents * piModelEvents = NULL;                
       rc = _piEltTriangle->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
       if (SUCCEEDED(rc))
       {
          CATCreate notif (_piEltTriangle,_pUIActiveObject);
          piModelEvents->Dispatch(notif);

          piModelEvents->Release();
          piModelEvents = NULL ;
       }    
    }	
  }

}

//------------------------------------------------------------------------

HRESULT CAADegCreateTriangleCmd::GetValue(CAAISysPolyline ** oTriangle)
{
	HRESULT rc = E_FAIL ;
	if ( (TRUE == _IsAgentValuated) && ( NULL !=oTriangle) )
	{
        rc = S_OK ;
        *oTriangle = _piEltTriangle ;

		// Release to do by the caller
		(*oTriangle)->AddRef();
	}

	return rc ;
}

//------------------------------------------------------------------------

