// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreatePolylineBy2TrianglesCmd.h"

//DialogEngine Framework
#include "CAADegCreateTriangleCmd.h"
#include "CATDialogTransition.h"
#include "CATCommandGlobalUndo.h"
#include "CATStateCancelNotification.h"

// Visualization Framework
#include "CATCSO.h"
#include "CATPathElement.h"    
#include "CATCreate.h"        
#include "CATDelete.h"         
#include "CATIModelEvents.h"  

// ApplicationFrame Framework
#include "CATFrmEditor.h"    
#include "CATApplicationFrame.h"  
#include "CATListOfCATBaseUnknown.h"  // for _pListeForUndoRedoElement

//CAASystem.edu Framework          
#include "CAAISysGeomFactory.h"     
#include "CAAISysPolyline.h"         
#include "CAAISysCollection.h" 
#include "CAAISysAccess.h" 

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 
     
// C++ Standard Library
#include <iostream.h>


//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreatePolylineBy2TrianglesCmd);


//----------------------LifeCycle's PART -----------------------------------
CAADegCreatePolylineBy2TrianglesCmd::CAADegCreatePolylineBy2TrianglesCmd():
                   CATStateCommand("CreatePolylineBy2TrianglesId"),
                   _pCmdTr1(NULL), _pCmdTr2(NULL),
                   _pContainer(NULL), _pUIActiveObject(NULL),
				   _pListeForUndoRedoElement(NULL)
{
  cout << "CAADegCreatePolylineBy2TrianglesCmd constructor" << endl ;

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
      // geometrical object  ( point,line, circle,....)
      piSysAccess->GetContainer(&_pContainer);

      // Done with this pointer
      piSysAccess->Release();
      piSysAccess=NULL;
    }  
  }   

}

//-------------------------------------------------------------------------

CAADegCreatePolylineBy2TrianglesCmd::~CAADegCreatePolylineBy2TrianglesCmd()
{
   cout << "CAADegCreatePolylineBy2TrianglesCmd destructor" << endl ;

   if ( NULL != _pCmdTr1 )
   {
      ((CATDialogAgent*)_pCmdTr1)-> RequestDelayedDestruction();
      _pCmdTr1  = NULL ;
   }

   if ( NULL != _pCmdTr2 )
   {
      ((CATDialogAgent*)_pCmdTr2) -> RequestDelayedDestruction();
      _pCmdTr2  = NULL ;
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

   _pListeForUndoRedoElement = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreatePolylineBy2TrianglesCmd::BuildGraph()
{
  cout << "CAADegCreatePolylineBy2TrianglesCmd BuildGraph" << endl ;
 
  // The agent associated with the first state is a CATStateCommand
  _pCmdTr1 = new CAADegCreateTriangleCmd(1);

  // The agent associated with the second state is a CATStateCommand
  _pCmdTr2 = new CAADegCreateTriangleCmd(1);
 
  //2- Creates the 2 states

  CATDialogState *stTR1State = GetInitialState("stGetTriangle1Id");
  stTR1State->AddDialogAgent(_pCmdTr1);

  CATDialogState *stTR2State = AddDialogState("stGetTriangle2Id");
  stTR2State->AddDialogAgent(_pCmdTr2);
   

  //3 Defines transitions from Start to Second State
  CATDialogTransition *pFirstTransition = AddTransition
  (
     stTR1State,
     stTR2State,
     IsOutputSetCondition(_pCmdTr1),
	 NULL
  ) ;

  //3-2 Defines transitions from Second to End State
  CATDialogTransition *pSecondTransition = AddTransition
  (
     stTR2State,
     NULL,
     IsOutputSetCondition(_pCmdTr2),
     Action((ActionMethod) & CAADegCreatePolylineBy2TrianglesCmd::CreatePolyline)
  ) ;


}

//---------------------------------------------------------------------------

CATBoolean CAADegCreatePolylineBy2TrianglesCmd::CreatePolyline(void *iDummy)
{

  cout << "CAADegCreatePolylineBy2TrianglesCmd::CreatePolyline" <<  endl ;

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

	// This list will contain the polyline and the 2 triangles
	_pListeForUndoRedoElement = new CATLISTP(CATBaseUnknown);

	// Done with the factory
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {    
      // Retrieve the first triangle
	  CAAISysPolyline * piSysPolylineTriangle = NULL ;
      rc = ((CAADegCreateTriangleCmd*)_pCmdTr1)->GetValue(&piSysPolylineTriangle);

	  if ( SUCCEEDED(rc) )
	  {
	     AddPoints(piSysPolyline,piSysPolylineTriangle) ;

         _pListeForUndoRedoElement->Append(piSysPolylineTriangle);
         piSysPolylineTriangle = NULL ;
	  }

	  // Retrieve the second triangle
	  rc = ((CAADegCreateTriangleCmd*)_pCmdTr2)->GetValue(&piSysPolylineTriangle);
	  if ( SUCCEEDED(rc) )
	  {
	     AddPoints(piSysPolyline,piSysPolylineTriangle) ;

         _pListeForUndoRedoElement->Append(piSysPolylineTriangle);
		 piSysPolylineTriangle = NULL ;
	  }

	  // it's an open polyline
      piSysPolyline->SetCloseStatus(0) ;

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

      _pListeForUndoRedoElement->Append(piSysPolyline);
	  piSysPolyline = NULL ;
    }
    
  }
  return TRUE ;
  return TRUE ;
}

//---------------------------------------------------------------------------



//--------Global Undo/Redo method's PART ---------------------------------

CATCommandGlobalUndo * CAADegCreatePolylineBy2TrianglesCmd::GetGlobalUndo()
{
  cout << "CAADegCreatePolylineBy2TrianglesCmd::GetGlobalUndo"<< endl ;

  CATCommandGlobalUndo * command = NULL ;

  // _piEltParent  is the Parent created in the NewParent method
  // this value is kept (release +1) 
  //
  if ( NULL != _pListeForUndoRedoElement )
  {

    command = new CATCommandGlobalUndo (
        (CATGlobalUndoMethod)& CAADegCreatePolylineBy2TrianglesCmd::UndoCreatePolyline,
        (CATGlobalUndoMethod)& CAADegCreatePolylineBy2TrianglesCmd::RedoCreatePolyline,
        (void *) _pListeForUndoRedoElement ,
        (CATGlobalUndoMethod)& CAADegCreatePolylineBy2TrianglesCmd::DesallocatPolyline);
  }

  return command  ;
}

//------------------------------------------------------------------------

void CAADegCreatePolylineBy2TrianglesCmd::UndoCreatePolyline(void *iData)
{
   cout << "CAADegCreatePolylineBy2TrianglesCmd::UndoCreatePolyline"<< endl ;
	
  // iData is a list which contains the polyline and the 2 triangles
  CATLISTP(CATBaseUnknown) * pList  = (CATLISTP(CATBaseUnknown) *) iData ;

  if ( NULL != pList )
  {
    for ( int i= 1 ; i <= pList->Size() ; i++ )
    {
       CATBaseUnknown * pObject = (*pList)[i] ;
 
       if ( NULL != pObject )
       { 
          CAAISysAccess * piSysAccess = NULL;                
          HRESULT rc = pObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
          if (SUCCEEDED(rc))
          {
             CATBaseUnknown * pContainer = NULL ;
             piSysAccess->GetContainer(&pContainer); 
       
             if ( NULL != pContainer )
	     {
                // Updates Display 
                CATIModelEvents * piModelEvents = NULL;                
                HRESULT rc =pObject->QueryInterface(IID_CATIModelEvents,
                                          (void**)&piModelEvents);
                if (SUCCEEDED(rc))
                {
                   CATDelete  notif (pObject);
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
                   piSysCollection ->RemoveObject(pObject);

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
  }  
}

//------------------------------------------------------------------------

void  CAADegCreatePolylineBy2TrianglesCmd::RedoCreatePolyline(void *iData)
{
  cout << "CAADegCreatePolylineBy2TrianglesCmd::RedoCreatePolyline"<< endl ;

  // iData is a list which contains the polyline and the 2 triangles
  CATLISTP(CATBaseUnknown) * pList  = (CATLISTP(CATBaseUnknown) *) iData ;

  if ( NULL != pList )
  {
    for ( int i= 1 ; i <= pList->Size() ; i++ )
    {
        CATBaseUnknown * pObject = (*pList)[i] ;
	
        if ( NULL != pObject )
        {
           CAAISysAccess * piSysAccess = NULL;                
           HRESULT rc = pObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
           if (SUCCEEDED(rc))
           {
              CATBaseUnknown * pContainer = NULL ;
              piSysAccess->GetContainer(&pContainer);
      
              if ( NULL != pContainer )
              {
                 // Updates the container's collector
                 CAAISysCollection * piSysCollection = NULL;                
                 rc = pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);

                 if (SUCCEEDED(rc))
                 {
                    piSysCollection->AddObject(pObject);
 
                    //Updates display

                    // retrieves the UI Active object 
                    CATBaseUnknown * UIAObject = NULL ;
                    piSysCollection->GetObject(1,&UIAObject);

                    if ( NULL != UIAObject)
                    {
                       CATIModelEvents * piModelEvents = NULL;                 
                       rc = UIAObject->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
                       if (SUCCEEDED(rc))
                       {
                          CATCreate notif (pObject,UIAObject);
                          piModelEvents->Dispatch(notif);

                          piModelEvents->Release();
                          piModelEvents = NULL ;
                       }

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
                    piSysCollection->Release(); 
                    piSysCollection= NULL ;
                 }

                 pContainer->Release();
                 pContainer = NULL ;
              }

              piSysAccess->Release();
              piSysAccess=NULL;
   	  }
	}
     }
  }
  
}

//-------------------------------------------------------------------------------

void  CAADegCreatePolylineBy2TrianglesCmd::DesallocatPolyline(void *iData)
{
  cout << "CAADegCreatePolylineBy2TrianglesCmd::DesallocatPolyline"<< endl ;

  CATLISTP(CATBaseUnknown) * pList  = (CATLISTP(CATBaseUnknown) *) iData ;

  if ( NULL != pList )
  {
    // iData is a list which contains the polyline and the 2 triangles
    CATBaseUnknown * pCurrentObject = NULL ;
	for ( int i=1 ; i<= pList->Size() ; i++)
	{
        pCurrentObject = (*pList)[i] ;
		if ( NULL != pCurrentObject )
		{
			pCurrentObject->Release();
			pCurrentObject = NULL ;
		}
	}

	// Here _pListeForUndoRedoElement is deleted 
    delete pList ;
	pList = NULL ;
    
  }
  
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreatePolylineBy2TrianglesCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePolylineBy2TrianglesCmd::Activate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreatePolylineBy2TrianglesCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePolylineBy2TrianglesCmd::Desactivate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreatePolylineBy2TrianglesCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreatePolylineBy2TrianglesCmd::Cancel" << endl;

  if ( ( NULL != iNotif) && ( ((CATStateCancelNotification *) iNotif) -> GetType() 
                 ==  CATStateCancelNotification::Interrupt) )
  {
	  
     cout << " CAADegCreatePolylineBy2TrianglesCmd has been interrupted by an exclusive command" << endl;   
     // If the Triangle1 has been accepted, it means created and no local undo on this
	 // agent, the triangle must be removed from the model

     if ( NULL != _pCmdTr1 )
	 {
	     CAAISysPolyline * piSysTriangle1 = NULL ;
         HRESULT rc = ((CAADegCreateTriangleCmd*)_pCmdTr1)->GetValue(&piSysTriangle1);
         if ( SUCCEEDED(rc) )
		 {
			// the triangle must be removed from the CSO 
            CATFrmEditor * pEditor = GetEditor() ;
            if ( NULL != pEditor )
			{
                CATCSO *pCso = pEditor->GetCSO();
                if ( NULL != pCso )
				{
					pCso->Empty();
				}
			}
			// update the model
            CATIModelEvents * piModelEvents = NULL;                
            rc = piSysTriangle1->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
            if ( SUCCEEDED(rc) )
			{
               CATDelete  notif (piSysTriangle1);
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
               piSysCollection->RemoveObject(piSysTriangle1); 

               piSysCollection->Release(); 
               piSysCollection= NULL ;
			}   

			piSysTriangle1->Release();
			piSysTriangle1 = NULL ;
		 }
	 } 

  }


  // Nothing to do here, just to see cout when you launch the command
  // and note order of method
    
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------------

void CAADegCreatePolylineBy2TrianglesCmd::AddPoints(CAAISysPolyline * piPolylineToCreate, 
                                      CAAISysPolyline * piTriangle)
{
	if ( (NULL != piPolylineToCreate) && (NULL != piTriangle ) )
	{
		// Retrieves the point of the polyline
		CATMathPoint *listein = NULL ;
	    int nbpointin = 0 ;
        piPolylineToCreate->GetListPoint(&nbpointin,&listein);

		// Retrieves the point of the current triangle
		CATMathPoint *listetriangle = NULL ;
		int nbpointtriangle = 0 ;
        piTriangle->GetListPoint(&nbpointtriangle,&listetriangle);

		// Set the point of the polyline into the listeout list 
		int nbpointout = nbpointtriangle+nbpointin ;
        CATMathPoint * listeout = new CATMathPoint[nbpointout];
		int i = 0;
  for ( ; i < nbpointin ; i++ )
		{
            listeout[i] = listein[i] ;
		}
		// Add the point of the current triangle into the listeout list
		for ( i= 0 ; i < nbpointtriangle ; i++ )
		{
            listeout[i+nbpointin] = listetriangle[i] ;
		}

        piPolylineToCreate->SetListPoint(nbpointout,listeout) ;

		delete [] listeout ;
        listeout = NULL ;
	
	}
}


