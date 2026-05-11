// COPYRIGHT Dassault Systemes 2002

// Local Framework
#include "CAAEPstINFRoot.h"

// Visualization Framework
#include "CATIModelEvents.h"
#include "CATCreate.h"
#include "CATModify.h"

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"
#include "CATILinkableObject.h"
#include "CATIDocRoots.h"
#include "CATDocument.h"

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATISpecObject.h"

// ProductStructure Framework
#include "CATIProduct.h"

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Tie the implementation to its interface.
#include "TIE_CAAIPstINFRoot.h"
TIE_CAAIPstINFRoot(CAAEPstINFRoot);

// To declare that the class is a data extension of CAAPstINFRoot
//
CATImplementClass (CAAEPstINFRoot,
                   DataExtension,    
                   CATBaseUnknown,
                   CAAPstINFRoot);

// 
// To declare that CAAEPstINFRoot implements CAAIPstINFRoot for the CAAPstINFRoot
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFRoot CAAIPstINFRoot  libCAAINFModeler
//

//-----------------------------------------------------------------------------
// CAAEPstINFRoot : constructor
//-----------------------------------------------------------------------------
CAAEPstINFRoot::CAAEPstINFRoot():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEPstINFRoot : destructor
//-----------------------------------------------------------------------------
CAAEPstINFRoot::~CAAEPstINFRoot()
{
}
 
//-----------------------------------------------------------------------------
// Implements CAAIPstINFRoot::AddChild
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFRoot::AddChild (CATISpecObject *piFeature)
{
	cout << "**** CAAEPstINFRoot::Add Child" << endl;

	HRESULT rc = E_FAIL;

	CATISpecAttrAccess *piAttrAccess = NULL;
	rc = QueryInterface(IID_CATISpecAttrAccess, (void**) &piAttrAccess);
	if (FAILED(rc)) {
		cout << "CATISpecAttrAccess QI on root failed." << endl;
		return E_FAIL;
	}

	// Retrieve the attribute key in order to access
	// the list of aggregated features
	CATISpecAttrKey *piListKey =
		piAttrAccess->GetAttrKey("ListOfComponents");
	if (piListKey == NULL) {
		cout << "Retrieval of attribute key on component list failed."
		     << endl;
		piAttrAccess->Release();
		piAttrAccess = NULL;
		return E_FAIL;
	}

	// Add the new feature to the end of the list
	piAttrAccess->SetSpecObject (piListKey,
				     piFeature);
	cout << "New feature added under root OK" << endl;

	piAttrAccess -> Release();
	piAttrAccess = NULL;

	piListKey->Release();
	piListKey = NULL;
   
	// Refresh the navigation tree
	CATIRedrawEvent *piRedrawOnRoot = NULL;
	rc = QueryInterface(IID_CATIRedrawEvent, (void**) &piRedrawOnRoot);
	if (FAILED(rc))	{
		cout << "CATIRedrawEvent QI on root failed." << endl; 
		return E_FAIL;
	}

	piRedrawOnRoot->Redraw();
	cout << "Navigation tree refreshed OK" << endl;
  
	piRedrawOnRoot -> Release();
	piRedrawOnRoot = NULL;

	// Force the visualization of the new feature by sending an event
	// on the Product root
  
	// Retrieve a CATIModelEvents pointer on the product root
	// and connect the feature
	CATIModelEvents *piModelEventsOnRoot = NULL;
	rc = QueryInterface(IID_CATIModelEvents, (void**) &piModelEventsOnRoot);
	if (FAILED(rc)) {
		cout << "CATIModelEvents QI on root failed." << endl;
		return rc;
	}

	piModelEventsOnRoot->ConnectTo(piFeature);
  
	// Send a notification of the creation to the view
	CATCreate ntfCreate(piFeature, piModelEventsOnRoot);
	piModelEventsOnRoot->Dispatch(ntfCreate);
  
	piModelEventsOnRoot->Release();
	piModelEventsOnRoot = NULL;

	return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CAAIPstINFRoot::GetChildren
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFRoot::GetChildren (CATListValCATBaseUnknown_var **pList)
{
	cout << "***** CAAEPstINFRoot::GetChildren" << endl;

	CATISpecAttrAccess *piAttrAccessOnRoot = NULL;
	HRESULT rc = QueryInterface(IID_CATISpecAttrAccess,
				    (void**) &piAttrAccessOnRoot);
	if (FAILED(rc)) return rc;
  
	CATISpecAttrKey *piListComponentKey = NULL;
	piListComponentKey = piAttrAccessOnRoot->GetAttrKey ("ListOfComponents");
	if (!piListComponentKey) {
		piAttrAccessOnRoot->Release();
		piAttrAccessOnRoot = NULL;
		return rc;
	}
  
	CATISpecObject *piComponent = NULL;
	int n = piAttrAccessOnRoot->GetListSize(piListComponentKey);
	for (int i = 1; i <= n; i++) {
		piComponent = piAttrAccessOnRoot->GetSpecObject(piListComponentKey, i);
		if (NULL == piComponent) {
			cout << "Error in retrieving component" << endl;
			piAttrAccessOnRoot->Release();
			piAttrAccessOnRoot = NULL;
			piListComponentKey->Release();
			piListComponentKey = NULL;
			return E_FAIL;  
		}
      
		(*pList)->Append(piComponent);
		piComponent = NULL;
	}

	piAttrAccessOnRoot->Release();
	piAttrAccessOnRoot = NULL;
	piListComponentKey->Release();
	piListComponentKey = NULL;

	return S_OK;
}
		
