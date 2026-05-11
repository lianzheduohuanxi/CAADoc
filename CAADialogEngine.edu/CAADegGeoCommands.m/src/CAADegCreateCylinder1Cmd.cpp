// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateCylinder1Cmd.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATOtherDocumentAgent.h"

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
#include "CAAISysCylinder.h"   
#include "CAAISysLine.h" 
#include "CAAISysCircle.h"   

//ApplicationFrame Framework
#include "CATFrmEditor.h"      
#include "CATFrmWindow.h" 

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 

// C++ Standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateCylinder1Cmd);

//----------------------LifeCycle's PART ----------------------------------
CAADegCreateCylinder1Cmd::CAADegCreateCylinder1Cmd():CATStateCommand("CreateCylinder1CmdId"),
                        _daSelectionLine(NULL),
                        _daSelectionCircle(NULL),
                        _pUIActiveObject(NULL), _pContainer(NULL)            
{
  cout << "CAADegCreateCylinder1Cmd constructor" << endl ;

  //
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

  //
  // 2- Retrieves the container which can create a cuboid in the model 
  // 

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

CAADegCreateCylinder1Cmd::~CAADegCreateCylinder1Cmd()
{
  cout << "CAADegCreateCylinder1Cmd destructor" << endl ;

  if ( NULL != _daSelectionLine ) 
  {
     _daSelectionLine -> RequestDelayedDestruction() ;
     _daSelectionLine = NULL ;
  }

  if ( NULL != _daSelectionCircle ) 
  {
     _daSelectionCircle->RequestDelayedDestruction() ;
     _daSelectionCircle = NULL ;
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

void CAADegCreateCylinder1Cmd::BuildGraph()
{
  cout << "CAADegCreateCylinder1Cmd BuildGraph" << endl ;

  // -----------------------
  // 1- Creates Dialog Agent
  // -----------------------
    
  // The agent to get the line
  _daSelectionLine = new CATPathElementAgent("SelectionLineId");

  // The cylinder is along this line
  _daSelectionLine->AddElementType(IID_CAAISysLine);

  // The selection is highlighted when you pre-select it, and when it is
  // selected. ( CATDlgEngWithPSOHSO/CATDlgEngWithPrevaluation)
  // This agent can be reused (CATDlgEngRepeat)
  // Just the last selection is set in the HSO (CATDlgEngNewHSOManager)
  //
  _daSelectionLine->SetBehavior(CATDlgEngWithPSOHSO | 
	                               CATDlgEngWithPrevaluation | CATDlgEngRepeat |
								   CATDlgEngNewHSOManager) ;

  // The agent allows you to select the circle in an another editor.
  // 
  // SelectionRadiusId            it's its identificator ( For NlS )
  // CATBasicMultiDocumentCommand is the command launched in another editors
  // CATDialogEngine              this command is exported by this module
  // 
  _daSelectionCircle = new CATOtherDocumentAgent("SelectionCircleId",
	   "CATBasicMultiDocumentCommand","CATDialogEngine");

  // The radius of the circle is the radius of the cylinder
  _daSelectionCircle->AddElementType(IID_CAAISysCircle);

  // The selection is highlighted when you pre-select it, and when it is
  // selected. ( CATDlgEngWithPSOHSO/CATDlgEngWithPrevaluation)
  // This agent can be reused (CATDlgEngRepeat)
  // Just the last selection is set in the HSO (CATDlgEngNewHSOManager)
  //
  _daSelectionCircle->SetBehavior(CATDlgEngWithPSOHSO | 
	                               CATDlgEngWithPrevaluation| CATDlgEngRepeat |
								   CATDlgEngNewHSOManager) ;
  
  // -----------------------
  // 2- Creates State
  // -----------------------

   CATDialogState *stCylinder = GetInitialState("stCylinderId");
   stCylinder->AddDialogAgent(_daSelectionLine);
   stCylinder->AddDialogAgent(_daSelectionCircle);
   
  // -----------------------
  // 2- Creates Transition
  // -----------------------

  CATDialogTransition *pTransition1 = AddTransition
  (
     stCylinder,
     NULL,
     AndCondition(IsOutputSetCondition(_daSelectionLine) ,
                  IsOutputSetCondition(_daSelectionCircle) ),
     Action((ActionMethod) & CAADegCreateCylinder1Cmd::CreateCylinder)
  );
  
}


//----------------------Action methods's PART -----------------------------

CATBoolean CAADegCreateCylinder1Cmd::CreateCylinder(void *iDummy)
{
  cout << "CAADegCreateCylinder1Cmd::CreateCylinder"<< endl;
	
  // Retrieves the factory to create the new cylinder
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {

    // Creation of the cylinder by a factory 
    CAAISysCylinder * piSysCylinder = NULL ;
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Cylinder, IID_CAAISysCylinder, 
                           (CATBaseUnknown**)&piSysCylinder);

    // Done with the factory
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Adds the cylinder in the container's collection
      //
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
         piSysCollection->AddObject(piSysCylinder); 
         piSysCollection-> Release();
         piSysCollection=NULL;
      }
      
      // Valuation of the new cylinder
	  CATMathPoint BasePoint,TopPoint ;
	  float Radius = 0.f ;
	  GetValuation(BasePoint,TopPoint,Radius);

      piSysCylinder->SetBasePoint(BasePoint);      
	  piSysCylinder->SetTopPoint(TopPoint);
      piSysCylinder->SetRadius(Radius);

      // Updates Display 
      CATIModelEvents * piModelEvent = NULL;                
      rc = piSysCylinder->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
      if (SUCCEEDED(rc))
      {
		 CATBoolean WindowHistogram = TRUE ;
		 if ( TRUE == WindowHistogram ) 
		 {
            CATModify notif(_pUIActiveObject);
            piModelEvent->Dispatch(notif);
         }else
		 {
			CATCreate notif(piSysCylinder,_pUIActiveObject);
            piModelEvent->Dispatch(notif);
		 }
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

      // Cylinder in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the CAADegCreateRectangleCmd::BuildGraph method.
	  // 
      CATFrmEditor * pEditor = GetEditor();
      if ( NULL != pEditor) 
      {
        
         CATCSO * pCso = pEditor->GetCSO()  ;
         if ( NULL != pCso)
         {
            // Creation of the path from the root to the Circle
            CATPathElement RootPath     = pEditor->GetUIActiveObject();
            CATPathElement *pPathCylinder= new CATPathElement(RootPath);
            pPathCylinder->AddChildElement(piSysCylinder);

            // Adds the path into the cso
            pCso->AddElement(pPathCylinder);

            //AddElement AddRef'ed
            pPathCylinder->Release();
            pPathCylinder=NULL;
         }
      }

      // Done with the point 
      piSysCylinder->Release();
      piSysCylinder=NULL;
    }

  }
  
	return TRUE ;
}

//----------------------Focus management PART ---------------------------------
CATStatusChangeRC CAADegCreateCylinder1Cmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateCylinder1Cmd::Activate" << endl;

  // This command does't use the cso as entry. 
  // so here we empty it. If your command uses the AddCSOClient method in its 
  // BuildGraph Method, don't empty the CSO (see CAADegCreateCircleCmd)
  // 
/*
  CATFrmEditor * pEditor =GetEditor();
  
  if ( NULL != pEditor )
  {
     CATCSO * pCso = pEditor->GetCSO() ;
     if ( NULL != pCso ) 
     {
       pCso->Empty();
     }
  }
*/
  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

void CAADegCreateCylinder1Cmd::GetValuation   (CATMathPoint & oBasePoint,
                          CATMathPoint & oTopPoint, 
                          float & oRadius)
{
	// Radius 
    CATPathElement * pPathModel = _daSelectionCircle->GetValue();
    CAAISysCircle * piSysCircle = NULL;  
    if ( (NULL != pPathModel) && (0 != pPathModel->GetSize()) )
	{
        // Retrieves the leaf of the path
        CATBaseUnknown * pObject = NULL ;
        pObject = (*pPathModel)[pPathModel->GetSize()-1];
	    if ( NULL != pObject )
		{
            HRESULT rc = pObject->QueryInterface(IID_CAAISysCircle, (void**)&piSysCircle);
            if ( SUCCEEDED(rc) )
			{
                piSysCircle->GetRadius(oRadius);
                piSysCircle->Release();
				piSysCircle= NULL ;
			}
		}
	}

	// Base And Top Point
    pPathModel = _daSelectionLine->GetValue();
    CAAISysLine * piSysLine = NULL;  
    if ( (NULL != pPathModel) && (0 != pPathModel->GetSize()) )
	{
        // Retrieves the leaf of the path
        CATBaseUnknown * pObject = NULL ;
        pObject = (*pPathModel)[pPathModel->GetSize()-1];
	    if ( NULL != pObject )
		{
            HRESULT rc = pObject->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
            if ( SUCCEEDED(rc) )
			{
                piSysLine->GetStartPoint(oBasePoint);
                piSysLine->GetEndPoint(oTopPoint);
                piSysLine->Release();
				piSysLine= NULL ;
			}
		}
	}
}
