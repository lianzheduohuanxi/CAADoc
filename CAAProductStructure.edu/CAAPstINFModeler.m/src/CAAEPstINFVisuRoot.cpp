// COPYRIGHT DASSAULT SYSTEMES 2002

//Local Framework
#include "CAAEPstINFVisuRoot.h"

// Local Framework
#include "CAAIPstINFRoot.h"

// Visualization Framework 
#include "CAT3DBagRep.h"
#include "CATVisManager.h"
#include "CATI3DGeoVisu.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATIClientContainer.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATIModelEvents.h"

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Tie the implementation to its interface
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEPstINFVisuRoot);

// To declare that the class is a data extension of CAASysRoot
//
CATImplementClass(CAAEPstINFVisuRoot, DataExtension, CATBaseUnknown, CAAPstINFRoot);
// 
// To declare that CAAEPstINFVisuRoot implements CATI3DGeoVisu for the CAAPstINFRoot
// component, insert the following Root in the interface dictionary:
//
//    CAAPstINFRoot CATI3DGeoVisu  libCAAIntegrateNewFeaturesImpl
//

//-----------------------------------------------------------------------------

CAAEPstINFVisuRoot::CAAEPstINFVisuRoot()
{
  cout << "*****CAAEPstINFVisuRoot::CAAEPstINFVisuRoot" << endl;
}

CAAEPstINFVisuRoot::~CAAEPstINFVisuRoot()
{
  cout << "*****CAAEPstINFVisuRoot::~CAAEPstINFVisuRoot" << endl;
}

CATRep * CAAEPstINFVisuRoot::BuildRep()
{
  cout << "*****CAAEPstINFVisuRoot::BuildRep" << endl;

  // Initialize pointer for bag of representations
  CAT3DBagRep * pRepRoot = NULL;

  CATIModelEvents * piModelEventsOnRoot = NULL ;
  HRESULT rc = QueryInterface(IID_CATIModelEvents,
	                          (void**) & piModelEventsOnRoot);
  if (FAILED(rc)) return pRepRoot;
  
  // Create bag of representations
  pRepRoot = new CAT3DBagRep();

  // Retrieve attribute key for list of features aggregated to root
  CATISpecAttrAccess *piAttrAccessOnRoot = NULL;
  rc = QueryInterface(IID_CATISpecAttrAccess,
                      (void**) &piAttrAccessOnRoot);
	                                            
  if (SUCCEEDED(rc) )
  {
     CATISpecAttrKey *piListComponentKey = NULL;
	 piListComponentKey = piAttrAccessOnRoot -> GetAttrKey ("ListOfComponents");
	 if ( NULL != piListComponentKey) 
     {
	    CATISpecObject *piComponent = NULL;
	       int n = piAttrAccessOnRoot -> GetListSize(piListComponentKey);
	       for (int i = 1; i <= n; i++)
		{
		   piComponent = piAttrAccessOnRoot -> GetSpecObject(piListComponentKey, i);
           if ( NULL != piComponent )
           {
              // Computes or retrieves its graphic representation
              CATVisManager * pVisuManager = CATVisManager::GetVisManager();
                 
              CATModelIdentificator Ident(piComponent);
              CAT3DRep * pRepChild = (CAT3DRep *) pVisuManager->BuildRep(Ident);
   
              if ( NULL != pRepChild )
              {
                 pRepRoot->AddChild(*pRepChild) ;
              }
                    
              // Done with the pointer
	      piComponent -> Release();
              piComponent = NULL ;
           }
        }
 
	    piListComponentKey -> Release();
		piListComponentKey = NULL;

     }
     piAttrAccessOnRoot -> Release();
	 piAttrAccessOnRoot = NULL;
  }

  piModelEventsOnRoot -> Release();
  piModelEventsOnRoot = NULL;
  return pRepRoot;
} 

