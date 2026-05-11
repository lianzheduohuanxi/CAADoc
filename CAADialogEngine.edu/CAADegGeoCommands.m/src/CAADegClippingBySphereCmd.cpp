// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegClippingBySphereCmd.h"


//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"
#include "CATCommandGlobalUndo.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"

// Visualization Framework
#include "CATPathElement.h"    
#include "CATModify.h"              
#include "CATIModelEvents.h"  
#include "CAT3DRep.h"
#include "CATVisManager.h"
#include "CAT3DViewpoint.h"
#include "CATViewer.h"

//CAASystem.edu Framework
#include "CAAISysPoint.h"                 
#include "CAAISysCollection.h" 
#include "CAAISysAccess.h" 
     
// C++ Standard Library
#include <iostream.h>

// Should be a data model 
#define EPSILON 10E-6
#define DISTMIN 10E-1

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegClippingBySphereCmd);


//----------------------LifeCycle's PART -----------------------------------
CAADegClippingBySphereCmd::CAADegClippingBySphereCmd():
                   CATStateCommand("ClippingBySphereCmdId"),
                   _daCenterPathElement(NULL), _daRadiusPathElement(NULL),
                   _pListeForClippedElement(NULL),
                   _pICollectionModelContainer(NULL)  
 {
  cout << "CAADegClippingBySphereCmd constructor" << endl ;

  CATFrmEditor * pEditor   = GetEditor();
  CATBaseUnknown * pUIActiveObject = NULL ;
  if ( NULL != pEditor ) 
  {;
    CATPathElement path = pEditor->GetUIActiveObject();
    if ( 0 != path.GetSize() ) 
    {
      pUIActiveObject=path[path.GetSize()-1];
    }
  }

  if ( NULL != pUIActiveObject )
  {
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      // Retrieves the object which implements a factory to create 
      // geometrical object  ( point,line, circle,....)
	  CATBaseUnknown * pContainer = NULL ;
      piSysAccess->GetContainer(& pContainer);
    
      if ( NULL != pContainer )
	  {
		  pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&_pICollectionModelContainer);

		  pContainer->Release();
		  pContainer = NULL ;
	  }
      // Done with this pointer
      piSysAccess->Release();
      piSysAccess=NULL;
    }  
  }   

}

//-------------------------------------------------------------------------

CAADegClippingBySphereCmd::~CAADegClippingBySphereCmd()
{
   cout << "CAADegClippingBySphereCmd destructor" << endl ;

   if ( NULL != _daCenterPathElement )
   {
      _daCenterPathElement -> RequestDelayedDestruction();
      _daCenterPathElement  = NULL ;
   }

   if ( NULL != _daRadiusPathElement )
   {
      _daRadiusPathElement -> RequestDelayedDestruction();
      _daRadiusPathElement  = NULL ;
   }

   if ( NULL != _pICollectionModelContainer )
   {
     _pICollectionModelContainer->Release();
     _pICollectionModelContainer = NULL ;
   }

   // The life cycle of this data is managed by the Global Undo/Redo 
   _pListeForClippedElement = NULL ;
}

//----------------------BuildGraph PART -----------------------------------

void CAADegClippingBySphereCmd::BuildGraph()
{
  cout << "CAADegClippingBySphereCmd BuildGraph" << endl ;

  //1- Creates the  agents 

  _daCenterPathElement = new CATPathElementAgent("SelCenterPoint");
  _daCenterPathElement->AddElementType(IID_CAAISysPoint);

  // The center point of the clipging sphere is hightlighted 
  // before and after the selection
  _daCenterPathElement->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

  _daRadiusPathElement = new CATPathElementAgent("SelRadiusPoint");
  _daRadiusPathElement->AddElementType(IID_CAAISysPoint);

  // The center point of the clipging sphere is hightlighted 
  // before and after the selection
  _daRadiusPathElement->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

  // Thanks this filter, the element selected is OK when the transition is done
  // compare to the CAADegCreateTriangleCmd, where no filter but check methods are
  // used. 
  CATAcquisitionFilter * pFilterForRadiusPoint = Filter((FilterMethod) & CAADegClippingBySphereCmd::TestRadiusPoint,
										   (void*)NULL);
										  
  _daRadiusPathElement->SetFilter(pFilterForRadiusPoint);

  //2- Creates the  states
  //  In the NLS file, with id=stxxxPointId, you note the message
  //  wich appears in the status bar to indicate how to give the xxx point
  //
  CATDialogState *stStartState = GetInitialState("stFirstPointId");
  stStartState->AddDialogAgent(_daCenterPathElement);

  CATDialogState *stSecondState = AddDialogState("stSecondPointId");
  stSecondState->AddDialogAgent(_daRadiusPathElement);
   

  //3-1 Defines transitions from Start to Second State
  CATDialogTransition *pFirstTransition = AddTransition
  (
     stStartState,
     stSecondState,
     IsOutputSetCondition(_daCenterPathElement),
	 NULL
  ) ;

  //3-1 Defines a transition from Second To Final State 
  CATDialogTransition *pThirdTransition =    AddTransition
  (
     stSecondState,
     NULL,
     IsOutputSetCondition(_daRadiusPathElement),
     Action((ActionMethod) & CAADegClippingBySphereCmd::ClippingBySphereTheModel)
  ) ;  
}



//---------------------Action method's PART-----------------------------------

CATBoolean CAADegClippingBySphereCmd::ClippingBySphereTheModel(void * iData)
{
  cout << "CAADegClippingBySphereCmd::ClippingBySphereTheModel" << endl ;

  CATBoolean rc = FALSE ;

  CATPathElement * pPathModelRadius = _daRadiusPathElement->GetValue();
  CATPathElement * pPathModelCenter = _daCenterPathElement->GetValue();

  if ( ( NULL != pPathModelCenter ) && ( NULL != pPathModelRadius ))
  {	  
	 // Get the center point
	 CATBaseUnknown * pObjectCenter = NULL ;
     if ( 0 != pPathModelCenter->GetSize())
	 {
         pObjectCenter = (*pPathModelCenter)[pPathModelCenter->GetSize()-1];
		 if (  NULL !=  pObjectCenter )
		 {
            CAAISysPoint * piSysPoint = NULL;                
            HRESULT hr =  pObjectCenter->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
            if ( SUCCEEDED(hr) )
			{
				CATMathPoint Center,Radius ;
				float x,y,z;

                piSysPoint->GetCoord(x,y,z);
                Center.SetX(x);
                Center.SetY(y);
                Center.SetZ(z);
                piSysPoint->Release();
				piSysPoint = NULL ;

				// Get the radius
	            CATBaseUnknown * pObjectRadius = NULL ;
                if ( 0 != pPathModelRadius->GetSize())
				{
                   pObjectRadius = (*pPathModelRadius)[pPathModelRadius->GetSize()-1];
	               if (  NULL !=  pObjectRadius )
				   {            
                      hr =  pObjectRadius->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
                      if ( SUCCEEDED(hr) )
					  {
                         piSysPoint->GetCoord(x,y,z);
						 Radius.SetX(x);
                         Radius.SetY(y);
                         Radius.SetZ(z);

                         piSysPoint->Release();
			             piSysPoint = NULL ;

						 rc = ClippingModel(Center,Radius);
					  }
				   }
				}
			}
		 }
	 }
  }
  return rc ;
}


//--------Global Undo/Redo method's PART ---------------------------------

CATCommandGlobalUndo * CAADegClippingBySphereCmd::GetGlobalUndo()
{
  cout << "CAADegClippingBySphereCmd::GetGlobalUndo"<< endl ;

  CATCommandGlobalUndo * command = NULL ;

  // _piEltTriangle  is the triangle created in the NewTriangle method
  // this value is kept (release +1) 
  //
  if ( NULL != _pListeForClippedElement )
  {
    command = new CATCommandGlobalUndo (
        (CATGlobalUndoMethod)& CAADegClippingBySphereCmd::UndoClippingBySphereTheModel,
        (CATGlobalUndoMethod)& CAADegClippingBySphereCmd::RedoClippingBySphereTheModel,
        (void *) _pListeForClippedElement ,
        (CATGlobalUndoMethod)& CAADegClippingBySphereCmd::DesallocatListOfDeletedElement);
  }

  return command  ;
}

//------------------------------------------------------------------------

void CAADegClippingBySphereCmd::UndoClippingBySphereTheModel(void *iData)
{
  // iData is the list of element removed  
 
  if ( NULL != iData )
  {
	  // iData is a list of object
	  CATLISTP(CATBaseUnknown) * pListRemovedElement = (CATLISTP(CATBaseUnknown) *) iData ;

	  // Clipped element are readded in the model
	  for ( int i=1 ; i <= pListRemovedElement->Size() ; i++ )
	  {
	  }

  }	
}

//------------------------------------------------------------------------

void  CAADegClippingBySphereCmd::RedoClippingBySphereTheModel(void *iData)
{
  //iData is the list of element removed  
 

  if ( NULL != iData )
  {
	  // iData is a list of object
	  CATLISTP(CATBaseUnknown) * pListRemovedElement = (CATLISTP(CATBaseUnknown)* ) iData ;

  }
}

//-------------------------------------------------------------------------------

void  CAADegClippingBySphereCmd::DesallocatListOfDeletedElement(void *iData)
{
  cout << "CAADegClippingBySphereCmd::DesallocatListOfDeletedElement"<< endl ;
	
  if ( NULL != iData )
  {
      // iData is a list of object
	  CATLISTP(CATBaseUnknown) * pListRemovedElement = (CATLISTP(CATBaseUnknown) *) iData ;

	  // Release each object 
	  CATBaseUnknown * pCurrentObject = NULL ;
	  for ( int j= 1 ; j <= pListRemovedElement->Size() ; j++ )
	  {
         pCurrentObject = (*pListRemovedElement)[j] ;
		 if ( NULL != pCurrentObject )
		 {
            pCurrentObject->Release();
			pCurrentObject = NULL ;
		 }
	  }

	  // Delete the list
      delete pListRemovedElement;
      pListRemovedElement = NULL ;
  }
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegClippingBySphereCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegClippingBySphereCmd::Activate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//----------------------------------------------------------------------------------

CATStatusChangeRC CAADegClippingBySphereCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegClippingBySphereCmd::Desactivate" << endl;
  // Nothing to do here, just to see cout when you launch the command
  // and note order of method 
  return (CATStatusChangeRCCompleted) ;
}

//-----------------------------------------------------------------------------------

CATStatusChangeRC CAADegClippingBySphereCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegClippingBySphereCmd::Cancel" << endl;

  return (CATStatusChangeRCCompleted) ;
}

//----------------------MODEL 's PART ----------------------------------------

CATBoolean CAADegClippingBySphereCmd::TestRadiusPoint( CATDialogAgent * iAgent, void * iUsefulData)
{
  cout << " CAADegClippingBySphereCmd::TestRadiusPoint" << endl;

  CATBoolean rc = FALSE ;

  if ( NULL == iAgent ) return rc ;

  // Retrieves the center
  CATPathElement * pPathModelCenter = _daCenterPathElement->GetValue();
  CATPathElement * pPathModelRadius = ((CATPathElementAgent*) iAgent)->GetValue();

  if ( (pPathModelRadius != pPathModelCenter) && ( NULL != pPathModelRadius ) &&
       ( NULL != pPathModelCenter) )
  {
     // the radius point is none equal to the center point
	  
	 // Now, we test that the distance between the 2 points are enought
	 CATBaseUnknown * pObjectCenter = NULL ;
     if ( 0 != pPathModelCenter->GetSize())
	 {
         pObjectCenter = (*pPathModelCenter)[pPathModelCenter->GetSize()-1];
		 if (  NULL !=  pObjectCenter )
		 {
            CAAISysPoint * piSysPoint = NULL;                
            HRESULT hr =  pObjectCenter->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
            if ( SUCCEEDED(hr) )
			{
				CATMathPoint Center,Radius ;
				float x,y,z;

                piSysPoint->GetCoord(x,y,z);
                Center.SetX(x);
                Center.SetY(y);
                Center.SetZ(z);
                piSysPoint->Release();
				piSysPoint = NULL ;

	            CATBaseUnknown * pObjectRadius = NULL ;
                if ( 0 != pPathModelRadius->GetSize())
				{
                   pObjectRadius = (*pPathModelRadius)[pPathModelRadius->GetSize()-1];
	               if (  NULL !=  pObjectRadius )
				   {            
                      hr =  pObjectRadius->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
                      if ( SUCCEEDED(hr) )
					  {
                         piSysPoint->GetCoord(x,y,z);
						 Radius.SetX(x);
                         Radius.SetY(y);
                         Radius.SetZ(z);

                         piSysPoint->Release();
			             piSysPoint = NULL ;

						 // test if 
						 double d = Center.DistanceTo(Radius);
						 if ( d > DISTMIN) 
                         {
							 rc = TRUE ;
						 }
						 
                      }
				   }
				}
			}
         }
	 }
  }
  return (rc) ;
}

//-----------------------------------------------------------------------------

CATBoolean CAADegClippingBySphereCmd::ClippingModel(CATMathPoint & iCenter,
													CATMathPoint & iRadius )
{
	CATBoolean rc = FALSE ;
    
	double RadiusClippingSphere = iCenter.DistanceTo(iRadius);

	cout << " RadiusClippingSphere=" << RadiusClippingSphere << endl;

	// we test each element of the model
    _pListeForClippedElement = new CATLISTP(CATBaseUnknown);

	if ( NULL != _pICollectionModelContainer )
	{

		int NbElementInTheModel = 0 ;
		_pICollectionModelContainer->GetNumberOfObjects(&NbElementInTheModel);
		cout << " GetNumberOfObjects" << NbElementInTheModel << endl ;
		// The first elt in the model container is the UI active object, it's not
		// a geometrical object. 
		//
		CAT3DBoundingSphere ElementSphere ; 
		CATBaseUnknown * pCurrentObject = NULL ;

		for (int i= 2 ; i <= NbElementInTheModel ; i++ )
		{
			// Gets the current geometrical element
            _pICollectionModelContainer->GetObject(i,&pCurrentObject);
			if ( NULL != pCurrentObject )
			{
                // Gets the Bounding Sphere of the current element
                CAT3DRep * pRep = NULL ;
                HRESULT hr = Get3DRep(pCurrentObject,&pRep);
                if ( SUCCEEDED(hr) )
				{
                   ElementSphere = pRep->GetBoundingElement();
				 
		  	       // If the element is not complety inside the bounding sphere given by 
			       // the current command, the element is set in the list of element to be remove
			       // from the model

			   	   if ( FALSE == IsElementInSphere(iCenter,RadiusClippingSphere,ElementSphere) )
				   {
                      _pListeForClippedElement->Append(pCurrentObject);

				      // we add a reference because the object is kept in the list
                      pCurrentObject->AddRef();
				   }
				}
                pCurrentObject->Release();
				pCurrentObject = NULL ;
            }
		}

		// If all element of the model are completly inside the sphere
		// the collection is deleted else all element outside the sphere are
		// removed from the model.
		if ( 0 == _pListeForClippedElement->Size() )
		{
            delete _pListeForClippedElement ;
			_pListeForClippedElement = NULL ;
		}else
		{
		   for ( int j= 1 ; j <= _pListeForClippedElement->Size() ; j++ )
		   {
              pCurrentObject = (*_pListeForClippedElement)[j] ;
              _pICollectionModelContainer->RemoveObject(pCurrentObject);
		   }

	       // An display event is sent to refresh all views
		   CATBaseUnknown * pUIActveObject = NULL ;
           _pICollectionModelContainer->GetObject(1,&pUIActveObject);
		   if ( NULL != pUIActveObject )
		   {
               CATIModelEvents * piModelEvents = NULL;                
               HRESULT hr = pUIActveObject->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
               if (SUCCEEDED(hr))
			   {
                  CATModify notif (pUIActveObject);
                  piModelEvents->Dispatch(notif);
          
                  piModelEvents->Release();
                  piModelEvents = NULL ;
			   }

			   pUIActveObject->Release();
			   pUIActveObject = NULL ;
		   }
		}
	}
	return rc ;
}


CATBoolean CAADegClippingBySphereCmd::IsElementInSphere(CATMathPoint & iClippingSphereCenter,
														double iClippingSphereRadius,
														CAT3DBoundingSphere & iElementBoundingSphere)											  
{
   CATBoolean rc = FALSE ;

   CATMathPointf Center = iElementBoundingSphere.GetCenter();
   CATMathPoint ElementClippingSphereCenter ;
   // Initialize a  CATMathPoint with value of the CATMathPointf
   Center.GetValue(ElementClippingSphereCenter) ;

   cout << " Center X =" << ElementClippingSphereCenter.GetX() << " y=" << ElementClippingSphereCenter.GetY() << " z=" << ElementClippingSphereCenter.GetZ()  << endl;
   float ElementClippingSphereRadius = iElementBoundingSphere.GetRadius();
 
   int DistanceBetweenToCenter = iClippingSphereCenter.DistanceTo(ElementClippingSphereCenter);

   cout << " distance entre le centre de la sphere de clipping et de l'object=" << DistanceBetweenToCenter << endl ;
   cout << " ElementClippingSphereRadius" << ElementClippingSphereRadius << endl ;

   if ( (DistanceBetweenToCenter + ElementClippingSphereRadius) <=  iClippingSphereRadius )
   {
	   rc = TRUE ;
   }

   return rc ;
}

//---------------------------------------------------------------------------

HRESULT CAADegClippingBySphereCmd::Get3DRep(CATBaseUnknown *iObject, CAT3DRep ** oRep)
{
   HRESULT rc = E_FAIL ;

   if ( NULL == oRep ) return rc ;

   CATVisManager * pVisManager = CATVisManager::GetVisManager();

   CATViewpoint * pViewpoint = NULL ;

   CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
   if ( NULL !=  pLayout )
   {
      CATFrmWindow * pWindow = pLayout->GetCurrentWindow();
      if ( NULL !=  pWindow )
      {
         CATViewer * pViewer = pWindow->GetViewer();
              
         if ( NULL != pViewer )
         {
            CAT3DViewpoint & Main3DViewpoint = pViewer->GetMain3DViewpoint();
            pViewpoint = (CATViewpoint*)(& Main3DViewpoint);
         }
      }
   }

   CATFrmEditor * pEditor   = GetEditor();
   CATBaseUnknown * pUIActiveObject = NULL ;
   if ( NULL != pEditor ) 
   {
      CATPathElement path = pEditor->GetUIActiveObject();
      if ( 0 != path.GetSize() ) 
	  {
         pUIActiveObject=path[path.GetSize()-1];
	  }
   }

   if ( (NULL != pVisManager) && (NULL != pViewpoint) && (NULL != pUIActiveObject) )
   {
      // Create a path with the Root object
      
      CATPathElement Path ;

      Path.AddChildElement( pUIActiveObject );
      if ( NULL != iObject )
      {
        Path.AddChildElement( iObject );
      }
           
      // The returned path 
      CATRepPath RepPath  ;

      // Generation of the rep
      pVisManager->GenerateRepPathFromPathElement(Path,pViewpoint,RepPath);

      if ( RepPath.Size() >= 1 )
      {                   
         *oRep = (CAT3DRep*) RepPath[RepPath.Size()-1];
         if ( NULL != *oRep )
         {
            rc = S_OK ;
         }
       }
    }
    return rc ;
}
