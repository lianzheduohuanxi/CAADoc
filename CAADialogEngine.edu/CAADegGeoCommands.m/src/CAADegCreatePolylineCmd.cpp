// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreatePolylineCmd.h"
#include "CAADegPointErrorBox.h"
#include "CAADegPointEditor.h" 

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"
#include "CATDialogAgent.h"
#include "CATIndicationAgent.h"
#include "CATCommandGlobalUndo.h"

// Visualization Framework 
#include "CATCSO.h"
#include "CATPathElement.h"   
#include "CATCreate.h"        
#include "CATDelete.h"       
#include "CATIModelEvents.h" 

//CAASystem.edu Framework
#include "CAAISysAccess.h" 
#include "CAAISysPoint.h"            
#include "CAAISysLine.h"             
#include "CAAISysGeomFactory.h"      
#include "CAAISysPolyline.h"         
#include "CAAISysCollection.h"       

//ApplicationFrame Framework
#include "CATFrmWindow.h"
#include "CATFrmLayout.h"
#include "CATI3DCamera.h"
#include "CATICamera.h"
#include "CATFrmEditor.h"  
#include "CATISO.h"
#include "CATApplicationFrame.h"

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree        

//others
#include <iostream.h>

// Should be a data model 
#define EPSILON 10E-6

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreatePolylineCmd);

//----------------------LifeCycle's PART --------------------------------------

CAADegCreatePolylineCmd::CAADegCreatePolylineCmd():CATStateCommand("CreateTriangleCmdId"),
                     _daPathElement(NULL),_daIndicationP(NULL),
                     _daIndicationP1(NULL),_daEditor(NULL),_daDialogEnd(NULL),
                     _piEltPolyline(NULL),_pPointEditor(NULL),
                    _nbPoint(0),_maxPoint(0),_piMouseLine(NULL),
                    _pISO(NULL), _pUIActiveObject(NULL), _pContainer(NULL)
{
  cout << "CAADegCreatePolylineCmd constructor" << endl ; 
 
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

  // The plane of the projection is the screen
  // Note: If you do not set the plane by using the SetMathPlane
  // on the indication agent, you have the same result. We have kept
  // this code only to show how to use the CATI3DCamera interface.
  //
  CATMathVector dir1(1,0,0) ;
  CATMathVector dir2(0,1,0) ;
  CATMathPoint origin (0,0,0);
   
  CATFrmLayout * pCurrentLayout = CATFrmLayout::GetCurrentLayout();
  if ( NULL != pCurrentLayout )
  {
    CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
    if ( NULL != pCurrentWindow )
    {
      CATICamera * piICamera = NULL ;
      piICamera = pCurrentWindow->GetCurrentCamera();
      
      if (NULL != piICamera) 
      {
          CATI3DCamera * pi3DCamera = NULL;
          HRESULT rc = piICamera->QueryInterface(IID_CATI3DCamera,(void **)& pi3DCamera);

          if ( SUCCEEDED(rc) )
          {
	     // The plane must be in front of the eye
             origin = pi3DCamera->GetTarget();
             dir2   = pi3DCamera->GetZenith();
             dir1   = pi3DCamera->GetDirection() ^ dir2 ;

             pi3DCamera->Release(); 
             pi3DCamera=NULL;
	  }
          piICamera->Release();
	  piICamera= NULL ;
      }
    }
  }
   
  _ProjPlane.SetOrigin(origin);
  _ProjPlane.SetVectors(dir1,dir2) ;
}

//--------------------------------------------------------------------------

CAADegCreatePolylineCmd::~CAADegCreatePolylineCmd()
{
  cout << "CAADegCreatePolylineCmd destructor" << endl ;

  if ( NULL != _daPathElement ) 
  {
     _daPathElement->RequestDelayedDestruction() ;
     _daPathElement = NULL ;
  }
  if ( NULL != _daEditor)  
  {
     _daEditor->RequestDelayedDestruction() ;
     _daEditor = NULL ;
  }

  if ( NULL != _daDialogEnd)  
  {
     _daDialogEnd->RequestDelayedDestruction() ;
     _daDialogEnd = NULL ;
  }

  if ( NULL != _daIndicationP1)
  {
     _daIndicationP1->RequestDelayedDestruction() ;
     _daIndicationP1 = NULL ;
  }

  if ( NULL != _daIndicationP)
  {
     _daIndicationP->RequestDelayedDestruction() ;
     _daIndicationP = NULL ;
  }

  if ( NULL != _pContainer  )
  {
     _pContainer->Release();
     _pContainer = NULL ;
  }

  if ( NULL != _pUIActiveObject )
  {
     _pUIActiveObject->Release();
     _pUIActiveObject = NULL ;
  }

  if ( NULL != _pPointEditor ) 
  {
     _pPointEditor->RequestDelayedDestruction() ;
     _pPointEditor = NULL ;
  }

  _pISO = NULL ;
  _piEltPolyline = NULL ;
  _piMouseLine   = NULL ;
}


//----------------------BuildGraph PART -----------------------------------

void CAADegCreatePolylineCmd::BuildGraph()
{
  cout << "CAADegCreatePolylineCmd BuildGraph" << endl ;

  //1- Creates agents
  //-----------------

  // 1-1 Point acquisition by selection 
  // ----------------------------------

  // This agent selects only the points
  _daPathElement = new CATPathElementAgent("PathElementAgentId");
  _daPathElement->AddElementType(IID_CAAISysPoint);
   
  // Agent behavior:
  // - CATDlgEngWithPSO + CATDlgEngWithPrevaluation: 
  //   Points are prehighlighted when the mouse is near them 
  //
  // - CATDlgEngRepeat
  //   After each point selection this agent is always useable and the 
  //   IsLastModifiedAgentCondition method will return true when the 
  //   end user selects another or the same point. Do not use 
  //   the IsOutputSetCondition method because after the first selection 
  //   this agent remains valued.
  //
  _daPathElement->SetBehavior(CATDlgEngWithPSO          |  
	                           CATDlgEngWithPrevaluation |
							   CATDlgEngRepeat );  
							        

  // 1-2 Point acquisition by indication 
  // -----------------------------------

  // Indication agent specific to the first point
  _daIndicationP1 = new CATIndicationAgent("IndicationP1Id");
  _daIndicationP1->SetMathPlane(_ProjPlane);

  // Indication agent for all another points
  _daIndicationP = new CATIndicationAgent("IndicationPNId");
  _daIndicationP->SetMathPlane(_ProjPlane);

  // Agent (_daIndicationP) behavior:
  // - CATDlgEngAcceptOnPrevaluate + CATDlgEngWithPrevaluation: 
  //   When the mouse moves, the agent is prevalued.(Useful for 
  //   the rubber banding effect.) This agent is valued when the end 
  //   user left clicks.
  //    
  // To reuse this agent for several points, recycle it:
  //   - after each left click (See CreateLineByIndic)
  //   - after a redo operation (See RedoCreateLine ) 
  //   - after a bad indication (See CheckPointByIndic )
  //   - after each prevaluation (See Rubber Banding ) 
  //
  _daIndicationP->SetBehavior(CATDlgEngAcceptOnPrevaluate | 
	                           CATDlgEngWithPrevaluation   ); 
							    	                           
  // 1-3 Point acquisition by dialog box
  // -----------------------------------
							   	                           
  CATApplicationFrame * pFrame = NULL ;
  pFrame = CATApplicationFrame::GetFrame() ;
  if ( NULL != pFrame )
  {
     // pParent is the Dialog object dedicated to the current document. 
     //
     CATDialog * pParent = pFrame->GetMainWindow() ;
     if ( NULL != pParent )
     {
        // Dialog agent for all points enter by dialog box
        _daEditor = new CATDialogAgent("PointEditorId");

        // Agent behavior :
        // - CATDlgEngRepeat:
        //   After each OK in the _pPointEditor dialog box, the agent is always
        //   usable and the condition method IsLastModifiedAgentCondition 
        //   will be true when the end user reclicks OK.
        //  
        _daEditor->SetBehavior(CATDlgEngRepeat); 

        _pPointEditor = new CAADegPointEditor(pParent);
        _pPointEditor->Build();   
    
        _daEditor->AcceptOnNotify(_pPointEditor,_pPointEditor->GetDiaOKNotification());
     }
  }
 


  // 1-4 Dialog agent to test the end: click right 
  // ---------------------------------------------

  _daDialogEnd = new CATDialogAgent("PointFinalId");
  _daDialogEnd->AcceptOnNotify(NULL,"CATContext");

	                         
  //2- Create states
  //-----------------

  CATDialogState *stStartState = GetInitialState("stFirstPointId");
  // order is important between _daPathElement and _daIndicationP1
  stStartState->AddDialogAgent(_daPathElement);
  stStartState->AddDialogAgent(_daIndicationP1);

  if (NULL != _daEditor )
  {
     stStartState->AddDialogAgent(_daEditor);
  }
   
  CATDialogState *stRepeatState = AddDialogState("stRepeatPointId");
  // order is important between _daPathElement and _daIndicationP 
  stRepeatState->AddDialogAgent(_daPathElement);
  stRepeatState->AddDialogAgent(_daIndicationP);
  stRepeatState->AddDialogAgent(_daDialogEnd);
  if (NULL != _daEditor )
  {
     stRepeatState->AddDialogAgent(_daEditor);
  }

  //3- Create transitions 
  //---------------------
    
  CATDialogTransition *pFirstTransitionSelect = AddTransition
  (
     stStartState,
     stRepeatState,
     AndCondition(IsLastModifiedAgentCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckFirstPoint)),
     Action((ActionMethod) & CAADegCreatePolylineCmd::CreateFirstPointBySelect,
            (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateFirstPoint,
            (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateFirstPoint)
  ) ;


  CATDialogTransition *pFirstTransitionIndic = AddTransition
  (
     stStartState,
     stRepeatState,
     AndCondition(IsOutputSetCondition(_daIndicationP1),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckFirstPoint)),
     Action( (ActionMethod) & CAADegCreatePolylineCmd::CreateFirstPointByIndic,
             (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateFirstPoint,
             (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateFirstPoint)
  ) ;

  if ( NULL != _daEditor )
  {
     CATDialogTransition *pFirstTransitionBox = AddTransition
     (
     stStartState,
     stRepeatState,
     AndCondition(IsLastModifiedAgentCondition(_daEditor),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckFirstPoint)),
     Action( (ActionMethod) & CAADegCreatePolylineCmd::CreateFirstPointByBox,
             (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateFirstPoint,
             (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateFirstPoint)
     ) ;
  }

  CATDialogTransition *pRepeatTransitionIndic =    AddTransition
  (
     stRepeatState,
     stRepeatState,
     AndCondition(IsOutputSetCondition(_daIndicationP),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointByIndic)),
     Action( (ActionMethod) & CAADegCreatePolylineCmd::CreateLineByIndic,
             (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateLine,
             (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateLine )
  ) ;
   
  CATDialogTransition *pRubberTransitionIndic =    AddTransition
  (
     stRepeatState,
     stRepeatState,
     IsLastModifiedAgentCondition(_daIndicationP),
     Action((ActionMethod) & CAADegCreatePolylineCmd::RubberLine)			
  ) ; 

  CATDialogTransition *pRepeatTransitionSelect =    AddTransition
  (
     stRepeatState,
     stRepeatState,
     AndCondition(IsLastModifiedAgentCondition(_daPathElement),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointBySelect)),
     Action( (ActionMethod) & CAADegCreatePolylineCmd::CreateLineBySelect,
             (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateLine,
             (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateLine )
  ) ;  

  if ( NULL != _daEditor )
  {
     CATDialogTransition *pRepeatTransitionBox =    AddTransition
     (
     stRepeatState,
     stRepeatState,
     AndCondition(IsLastModifiedAgentCondition(_daEditor),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointByBox)),
     Action( (ActionMethod) & CAADegCreatePolylineCmd::CreateLineByBox,
             (ActionMethod) & CAADegCreatePolylineCmd::UndoCreateLine,
             (ActionMethod) & CAADegCreatePolylineCmd::RedoCreateLine )
     ) ;
  }


  CATDialogTransition *pLastTransition =    AddTransition
  (
     stRepeatState,
     NULL,
     AndCondition(IsOutputSetCondition(_daDialogEnd),
                  Condition((ConditionMethod) & CAADegCreatePolylineCmd::CheckPointNumber)),
     Action((ActionMethod) & CAADegCreatePolylineCmd::CreatePolyline)
  ) ; 
   

}

//---------------------Condition method's PART---------------------------------

CATBoolean CAADegCreatePolylineCmd::CheckPointNumber(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::CheckPointNumber"<<  endl ;
    
  CATBoolean rc = TRUE ;

  // The end user has clicked the right button to indicate the end 
  // polyline, but it must contain at least 3 points
  if ( _nbPoint < 3 ) 
  {
    rc = FALSE ;

    // This agent must be reseted otherwise the next point will finish 
    // the command  
    _daDialogEnd->InitializeAcquisition(); 
  } 
  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CheckFirstPoint(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::CheckFirstPoint"<<  endl ;
    
  CATBoolean rc = TRUE ;

  // If no UI active Object, it's impossible to create element
  if ( (NULL == _pUIActiveObject) || (NULL == _pContainer) ) rc = FALSE ;

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CheckPointByIndic(void *iUsefulData)
{

  cout << "CAADegCreatePolylineCmd::CheckPointByIndic"<<  endl ;
    
  CATBoolean rc = FALSE ;

  //  If no UI active, it's impossible to create element
  if ( (NULL != _pUIActiveObject) && ( NULL != _pContainer) ) 
  {
    // Tests that's two points are not equal 
    CATMathPoint2D point2D = _daIndicationP->GetValue();
    CATMathPoint CurrentPoint ;
    _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),CurrentPoint);

    rc = TestAllPoints(CurrentPoint) ;

    if ( FALSE == rc ) 
    {
      // The point already exists, Agent is revaluable , to reselect a point
      _daIndicationP->InitializeAcquisition();
    }
  }
  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CheckPointByBox(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::CheckPointByBox"<<  endl ;
    
  CATBoolean rc = FALSE ;

  // If no UI active object, it's impossible to create element
  if ( (NULL != _pUIActiveObject) && ( NULL != _pContainer) ) 
  {
    // Tests that's two points are not equal 
    CATMathPoint CurrentPoint = _pPointEditor->GetValue();
    rc = TestAllPoints(CurrentPoint) ;
  }
  return rc ;
}

//------------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CheckPointBySelect(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::CheckPointBySelect"<<  endl ;
    
  CATBoolean rc = FALSE;

  //  If no UI active object, it's impossible to create element
  if ( (NULL != _pUIActiveObject) && ( NULL != _pContainer) ) 
  {
    // Tests that's two points are not equal 
    CATMathPoint CurrentPoint ;
	
    if ( TRUE == GetValuePathElement(CurrentPoint) )
    {
       rc = TestAllPoints(CurrentPoint) ;
    }
  }
  return rc ;
}

//---------------------Action method's PART-----------------------------------

CATBoolean CAADegCreatePolylineCmd::CreateFirstPointBySelect(void *iUsefulData)
{ 
  cout << "CAADegCreatePolylineCmd::CreateFirstPointBySelect" <<  endl ;

  CATBoolean rc = FALSE;

  CATMathPoint Point ;

  // Gets x,y,z from the selected point model
  if ( TRUE == GetValuePathElement(Point) )
  {
    rc = NewTemporaryFirstPoint(Point);
  }		
  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CreateFirstPointByIndic(void *iUsefulData)
{ 
  cout << "CAADegCreatePolylineCmd::CreateFirstPointByIndic" <<  endl ;

  // Gets x,y,z from the 2D point projected in the plane 
	
  CATBoolean rc = FALSE;

  CATMathPoint2D point2D = _daIndicationP1->GetValue();
  CATMathPoint Point ;
  _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),Point);

  rc = NewTemporaryFirstPoint(Point);

 return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CreateFirstPointByBox(void *iUsefulData)
{ 
  cout << "CAADegCreatePolylineCmd::CreateFirstPointByBox" <<  endl ;

  // Gets x,y,z from the point dialog box
	
  CATBoolean rc = FALSE;

  CATMathPoint point = _pPointEditor->GetValue();
  rc = NewTemporaryFirstPoint(point);

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::RubberLine(void *iUsefulData)
{ 
  cout << "CAADegCreatePolylineCmd::RubberLine" <<  endl ;

  CATBoolean rc = TRUE;

  int first = 0 ;

  // A temporary line when the  mouse moves
  if ( NULL ==  _piMouseLine )
  {
    first = 1 ;
    CAAISysGeomFactory * piSysGeomFactory = NULL;                
    HRESULT rc1 = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
    if (SUCCEEDED(rc1))
    {
      piSysGeomFactory->Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                         (CATBaseUnknown**)&_piMouseLine);
      piSysGeomFactory->Release();
      piSysGeomFactory=NULL;
    }
  }

  if ( NULL != _piMouseLine )
  {
    float x,y,z ; 
    _piTemporaryPoint[_nbPoint-1]->GetCoord(x,y,z);
    CATMathPoint P1(x,y,z);
    _piMouseLine->SetStartPoint(P1);

    // The end point is the point indicated by the mouse position 
    CATMathPoint2D point2D = _daIndicationP->GetValue();
    CATMathPoint P2 ;
    _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),P2);

    _piMouseLine->SetEndPoint(P2);

    if ( 1 == first ) 
      _pISO->AddElement(_piMouseLine);
    else
       _pISO->UpdateElement(_piMouseLine);
  }

  // Required to be reusable 	
  _daIndicationP->InitializeAcquisition();

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CreateLineBySelect(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::CreateLineBySelect" <<  endl ;

  CATBoolean rc = FALSE ;

  CATMathPoint Point ;
  // Gets x,y,z from the selected point model
  if ( TRUE == GetValuePathElement(Point) )
  {
    rc = NewTemporaryLine(Point);
  }

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CreateLineByBox(void *iUsefulData)
{
  cout << " CAADegCreatePolylineCmd::CreateLineByBox"<< endl;

  // Gets x,y,z from the dialog box
	
  CATBoolean rc = FALSE;

  CATMathPoint point = _pPointEditor->GetValue();
  rc = NewTemporaryLine(point);

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CreateLineByIndic(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::CreateLineByIndic" <<  endl ;

  CATBoolean rc = FALSE ;

  // Gets x,y,z from the 2D point projected in the plane 
  CATMathPoint2D point2D = _daIndicationP->GetValue();
  CATMathPoint Point ;

  // Projection of the 2D point in the 3D space
  _ProjPlane.EvalPoint(point2D.GetX(),point2D.GetY(),Point);

  rc = NewTemporaryLine(Point);

  // Reusable agent: The IsOutputSetCondition method will be true 
  // when the end user left clicks one more time.
  //
  _daIndicationP->InitializeAcquisition();

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::CreatePolyline(void *iUsefulData)
{
  // Creation of the polyline by the container factory 
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates the new Polyline
    CAAISysPolyline * piSysPolyline = NULL ;
    HRESULT rc = piSysGeomFactory->Create(CAAISysGeomFactory::Polyline, IID_CAAISysPolyline, 
                                          (CATBaseUnknown**)&piSysPolyline);

    // Done with the factory
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Polyline Location
      CATMathPoint * list = new  CATMathPoint[_nbPoint];
      float x,y,z ;
      for ( int i=0 ; i <_nbPoint ;i++)
      {
        _piTemporaryPoint[i]->GetCoord(x,y,z);
        list[i].SetCoord(x,y,z);
      }
      piSysPolyline->SetListPoint(_nbPoint,list) ;
      piSysPolyline->SetCloseStatus(0) ;
      delete [] list ;

      // Adds the polyline in the Container's collection 
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
        piSysCollection->AddObject(piSysPolyline);
        piSysCollection->Release();
        piSysCollection=NULL;
      }

      // Updates  display 
      CATIModelEvents * piModelEvent = NULL;                
      rc =piSysPolyline->QueryInterface(IID_CATIModelEvents,
                                          (void**)&piModelEvent);
      if (SUCCEEDED(rc))
      {
        CATCreate notif (piSysPolyline,_pUIActiveObject);		      
        piModelEvent->Dispatch(notif);
       
        piModelEvent->Release();
        piModelEvent=NULL;
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

      // Polyline in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the CAADegCreateRectangleCmd::BuildGraph method.
	  // 
      CATFrmEditor * pEditor = GetEditor();
      
      if ( NULL != pEditor )
      {
         CATCSO *pCso = pEditor->GetCSO();
         if ( NULL != pCso )
         {
            // Creation of the path from the root object to the object
            CATPathElement RootPath = pEditor->GetUIActiveObject(); 
            CATPathElement *pPathPolyline = new CATPathElement(RootPath);
            pPathPolyline->AddChildElement(piSysPolyline);

            // Adds the complete path into the cso
            pCso->AddElement(pPathPolyline);
            pPathPolyline->Release();
            pPathPolyline=NULL;
        }
      }
         
      // The interface pointer is kept for the Undo/Redo global
      _piEltPolyline = piSysPolyline ;
    }
    
  }
  return TRUE ;
}

//----------Local Undo/Redo method's PART ----------------------------------

CATBoolean CAADegCreatePolylineCmd::UndoCreateLine(void *iUsefulData)
{

  cout << "CAADegCreatePolylineCmd::UndoCreateLine" <<  endl ;
    
  _pISO->RemoveElement(_piTemporaryLine[_nbPoint-2]);
  _pISO->RemoveElement(_piTemporaryPoint[_nbPoint-1]);
  _nbPoint -- ;

  //Avoids having a temporary line when the end user clicks undo
  // 
  if ( NULL != _piMouseLine ) 
  {
    _pISO->RemoveElement(_piMouseLine);
    _piMouseLine->Release() ;
    _piMouseLine = NULL ;
  }

  return TRUE ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::RedoCreateLine(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::RedoCreateLine" <<  endl ;
  
  _nbPoint ++;
  _pISO->AddElement(_piTemporaryLine[_nbPoint-2]);
  _pISO->AddElement(_piTemporaryPoint[_nbPoint-1]);
 
  // Resets the agent
  _daIndicationP->InitializeAcquisition();

  return TRUE ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::UndoCreateFirstPoint(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::UndoCreateFirstPoint" <<  endl ;

  _nbPoint-- ;
  _pISO->RemoveElement(_piTemporaryPoint[_nbPoint]);

  //Avoids having a temporary line when the end user clicks undo
  // 
  if ( NULL != _piMouseLine ) 
  {
    _pISO->RemoveElement(_piMouseLine);
    _piMouseLine->Release() ;
    _piMouseLine = NULL ;
  }

  return TRUE ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::RedoCreateFirstPoint(void *iUsefulData)
{
  cout << "CAADegCreatePolylineCmd::RedoCreateFirstPoint" <<  endl ;

  _nbPoint++ ;
  _pISO->AddElement(_piTemporaryPoint[_nbPoint-1]);

  // Resets the agent
  _daIndicationP1->InitializeAcquisition();

  return TRUE ;
}

//-------------Global Undo/Redo method's PART ---------------------------------

CATCommandGlobalUndo * CAADegCreatePolylineCmd::GetGlobalUndo()
{
  cout << "CAADegCreatePolylineCmd::GetGlobalUndo"<< endl ;

  CATCommandGlobalUndo * command = NULL ;

  // _piEltPolyline  is the polyline created in the NewPolyline method
  // this value is kept (release +1) 
  //
  if ( NULL != _piEltPolyline )
  {
     command = new CATCommandGlobalUndo (
         (CATGlobalUndoMethod) & CAADegCreatePolylineCmd::UndoCreatePolyline,
         (CATGlobalUndoMethod)& CAADegCreatePolylineCmd::RedoCreatePolyline,
         (void *) _piEltPolyline ,
         (CATGlobalUndoMethod)& CAADegCreatePolylineCmd::DesallocatPolyline);
  }

  return command  ;
}

//----------------------------------------------------------------------------

void CAADegCreatePolylineCmd::UndoCreatePolyline(void *iData)
{
  // iData is the Triangle created in the CreateTriangle 
  CAAISysPolyline * piSysPolyline  = (CAAISysPolyline *) iData ;

  cout << "CAADegCreatePolylineCmd::UndoCreatePolyline"<< piSysPolyline << endl ;

  if ( NULL != piSysPolyline )
  {
    // Retrieves the container which contains piSysPolyline
    //
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
        HRESULT rc =piSysPolyline->QueryInterface(IID_CATIModelEvents,
                                          (void**)&piModelEvents);
        if (SUCCEEDED(rc))
        {
           CATDelete  notif (piSysPolyline);
           piModelEvents->Dispatch(notif);
          
           piModelEvents->Release();
           piModelEvents=NULL;
        }

        // Updates the container's collector
        CAAISysCollection * piSysCollection = NULL;                
        rc = pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
        if (SUCCEEDED(rc))
        {
          piSysCollection ->RemoveObject(piSysPolyline);

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
          piSysCollection=NULL;
        }

        // Necessary for the Redo 
        piSysAccess->SetContainer(pContainer);
        
        // No more need of the container
        pContainer->Release(); 
        pContainer=NULL;
      }
      // No more need of the Access pointer
      piSysAccess->Release();
      piSysAccess=NULL;
      
    }
  }
}

//----------------------------------------------------------------------------

void  CAADegCreatePolylineCmd::RedoCreatePolyline(void *iData)
{
  // iData is the Polyline created in the CreatePolyline method
  CAAISysPolyline * piSysPolyline  = (CAAISysPolyline *) iData ;

  cout << "CAADegCreatePolylineCmd::RedoCreatePolyline"<< piSysPolyline << endl ;

  if ( NULL != piSysPolyline )
  {
    // Retrieves  the container
    //
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
        // Updates container's collector 
        CAAISysCollection * piSysCollection = NULL;                
        rc = pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
        pContainer->Release();
        pContainer=NULL;
        
        if (SUCCEEDED(rc))
        {
  	      piSysCollection ->AddObject(piSysPolyline);

          //Updates the visu
          CATIModelEvents * piModelEvent = NULL;                
          rc =piSysPolyline->QueryInterface(IID_CATIModelEvents,
                                          (void**)&piModelEvent);
          if (SUCCEEDED(rc))
          {
             // retrieves the UI Active object 
             CATBaseUnknown * UIAObject = NULL ;
             piSysCollection->GetObject(1,&UIAObject);

             if ( NULL != UIAObject )
             {
                CATCreate  notif (piSysPolyline,UIAObject);
                piModelEvent->Dispatch(notif);
                
                CATIRedrawEvent * piRedrawEvent= NULL;                
                rc =UIAObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
                if (SUCCEEDED(rc))
                {
                    piRedrawEvent->Redraw();
        
                    piRedrawEvent->Release();
                    piRedrawEvent = NULL ;
                }
 
                UIAObject->Release();
                UIAObject=NULL;
             }
                      
             piModelEvent->Release();
             piModelEvent=NULL;

          }
          piSysCollection->Release();
          piSysCollection=NULL;
        }
        
      }
      
    }
  }	
}

//-----------------------------------------------------------------------------

void  CAADegCreatePolylineCmd::DesallocatPolyline( void * iData)
{
  cout << "CAADegCreatePolylineCmd::DesallocatPolyline"<< endl ;
	
  if ( NULL != iData )
  {
    // iData is the Polyline created in the CreatePolyline method
    CAAISysPolyline * piSysPolyline  = (CAAISysPolyline *) iData ;

    // The polyline is deleted
    if ( piSysPolyline) piSysPolyline->Release();
    piSysPolyline=NULL;
    
  }
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreatePolylineCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePolylineCmd::Activate" << endl;
  
  if ( NULL != _pPointEditor ) 
  {
     _pPointEditor->SetVisibility(CATDlgShow);
  }

  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAADegCreatePolylineCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePolylineCmd::Desactivate" << endl;

  if ( NULL != _pPointEditor ) 
  {
     _pPointEditor->SetVisibility(CATDlgHide);
  }

  if ( NULL != _piMouseLine ) 
  {
    _pISO->RemoveElement(_piMouseLine);
    _piMouseLine->Release() ;
    _piMouseLine = NULL ;
  }

  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------

CATStatusChangeRC CAADegCreatePolylineCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePolylineCmd::Cancel" << endl;

  if ( NULL != _pPointEditor ) 
  {
     _pPointEditor->SetVisibility(CATDlgHide);
  }

  for ( int i=0 ; i < _maxPoint-1 ; i++ )
  {
    _pISO->RemoveElement(_piTemporaryLine[i]);
    _piTemporaryLine[i]->Release();
    _piTemporaryLine[i]= NULL ;
    _pISO->RemoveElement(_piTemporaryPoint[i]);
    _piTemporaryPoint[i]->Release();
    _piTemporaryPoint[i]= NULL ;
  }
  if ( 0 != _maxPoint )
  {
    _pISO->RemoveElement(_piTemporaryPoint[_maxPoint-1]);
    _piTemporaryPoint[_maxPoint-1]->Release();
    _piTemporaryPoint[_maxPoint-1]= NULL ;
  }

  //Removes the last temporary line seen when the mouse moves 
  if ( NULL != _piMouseLine ) 
  {
    _pISO->RemoveElement(_piMouseLine);
    _piMouseLine->Release() ;
    _piMouseLine = NULL ;
  }

   return (CATStatusChangeRCCompleted) ;
}

//------------------------ Private methods ---------------------------------------------

CATBoolean CAADegCreatePolylineCmd::NewTemporaryFirstPoint(CATMathPoint & iPoint)
{
  // Cleaning Between MaxPoint and nbpoint
  // _bPoint can change in the local Undo/Redo methods 
  //
  if ( _maxPoint > _nbPoint )
  {
    for ( int i=1 ; i < _maxPoint ; i++ )
    {
      _piTemporaryPoint[i] ->Release();
      _piTemporaryPoint[i]=NULL;
      _piTemporaryLine[i-1]->Release();
      _piTemporaryLine[i-1]=NULL;
    }
    _piTemporaryPoint[0]->Release();
    _piTemporaryPoint[0]=NULL;
  }

  //Create a temporary point
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
			(CATBaseUnknown**)& _piTemporaryPoint[_nbPoint]);
    piSysGeomFactory -> Release();
    piSysGeomFactory=NULL;
  }  
   
  float x = (float) iPoint.GetX() ;
  float y = (float) iPoint.GetY() ;
  float z = (float) iPoint.GetZ() ;
  _piTemporaryPoint[_nbPoint]->SetCoord(x,y,z);

  _pISO->AddElement(_piTemporaryPoint[_nbPoint]);
 
  _nbPoint  = 1 ;
  _maxPoint = 1 ;

  return TRUE;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::NewTemporaryLine(CATMathPoint & iPoint)
{
  // Cleaning Between MaxPoint and nbpoint
  // _bPoint can change in the local Undo/Redo methods 
  if ( _maxPoint > _nbPoint )
  {
    for ( int i=_nbPoint ; i < _maxPoint ; i++ )
    {
      _piTemporaryPoint[i] ->Release();
      _piTemporaryPoint[i]=NULL;
      _piTemporaryLine[i-1]->Release();
      _piTemporaryLine[i-1]=NULL;
    }
    _maxPoint = _nbPoint ;
  }

  // Removes the temporary line seen when the mouse moves 
  if ( NULL != _piMouseLine ) 
  {
    _pISO->RemoveElement(_piMouseLine);
    _piMouseLine->Release() ;
    _piMouseLine = NULL ;
  }

  // Retrieves the factory from the container
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creates a new temporary point
    piSysGeomFactory -> Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
			(CATBaseUnknown**)& _piTemporaryPoint[_nbPoint]);
   
    float x = (float) iPoint.GetX() ;
    float y = (float) iPoint.GetY() ;
    float z = (float) iPoint.GetZ() ;
    _piTemporaryPoint[_nbPoint]->SetCoord(x,y,z);

    _pISO->AddElement(_piTemporaryPoint[_nbPoint]);

    _nbPoint ++ ; 

    _maxPoint++ ;

    // Creates a new temporary line
    piSysGeomFactory -> Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
			(CATBaseUnknown**)& _piTemporaryLine[_nbPoint-2]);

    _piTemporaryPoint[_nbPoint-2]->GetCoord(x,y,z);
    CATMathPoint P1(x,y,z);
    _piTemporaryPoint[_nbPoint-1]->GetCoord(x,y,z);
    CATMathPoint P2(x,y,z);

    _piTemporaryLine[_nbPoint-2]->SetStartPoint(P1);
    _piTemporaryLine[_nbPoint-2]->SetEndPoint(P2);

    _pISO->AddElement(_piTemporaryLine[_nbPoint-2]);

    piSysGeomFactory -> Release();
    piSysGeomFactory=NULL;
  }  
  return TRUE;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::GetValuePathElement(CATMathPoint & ioPoint)
{
  CATBoolean rc = FALSE ;

  CATPathElement * pPathModel = _daPathElement->GetValue();

  CATBaseUnknown * pObject = NULL ;
  if ( (NULL != pPathModel) && ( 0 != pPathModel->GetSize()))
  {
    pObject = (*pPathModel)[pPathModel->GetSize()-1];
  }

  if ( NULL !=  pObject )
  {
    CAAISysPoint * piSysPoint = NULL;                
    HRESULT rc1 = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
    if (SUCCEEDED(rc1))
    {
      float x,y,z ;
      piSysPoint->GetCoord(x,y,z);

      ioPoint.SetCoord(x,y,z);
		   
      piSysPoint->Release();
      piSysPoint=NULL ;

      rc = TRUE ;
    }
  }

  return rc ;
}

//----------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineCmd::TestAllPoints(CATMathPoint & iCurrentPoint)
{
  CATBoolean rc = TRUE ;

  int i = 0 ;
  CATMathPoint point ;
  float x,y,z;
  
  while ( ( TRUE == rc) && ( i < _nbPoint ) )
  {
    _piTemporaryPoint[i]->GetCoord(x,y,z);
    point.SetCoord(x,y,z);

    if ( point.DistanceTo(iCurrentPoint) < EPSILON )
	rc = FALSE ;
    i ++ ;
  }

  if ( FALSE == rc )
  {
    // this dialog box is deleted when the end user clicks OK 
    // 
	CATApplicationFrame *pFrame = NULL ;
    pFrame = CATApplicationFrame::GetFrame();
    if ( NULL != pFrame )
    {
       CATDialog * pParent = pFrame->GetMainWindow();
       if ( NULL != pParent )
       {
          CAADegPointErrorBox * pBox = new CAADegPointErrorBox(pParent,i,_nbPoint+1) ;
          pBox->Build();
          pBox->SetVisibility(CATDlgShow);
	   }
	}
  }

  return rc ;
}

