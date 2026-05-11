// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAPstINFVisuProviderRoot.h"

// ProductStructure Framework
#include "CATIProduct.h"
#include "CATI3DVisuProvider.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATIClientContainer.h"

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATAppliContServices.h"
#include "CATILinkableObject.h"

// System Framework
#include "CATBaseUnknown.h"

// Others
#include "iostream.h"

// Tie the implementation to its interface.
#include "TIE_CATI3DVisuProvider.h"
TIE_CATI3DVisuProvider(CAAPstINFVisuProviderRoot);

// To declare that the class is an simple implementation
//
CATImplementClass( CAAPstINFVisuProviderRoot,
                   Implementation, 
                   CATBaseUnknown,
                   CATNull );

// 
// To declare that CAAEPstINFVisuProviderRoot is an implementation of CATI3DVisuProvider, 
// insert the following line in the interface dictionary:
//
//    CAAPstINFVisuProviderRoot CATI3DVisuProvider  libCAAPstINFModeler
//

//-----------------------------------------------------------------------------
// CAAPstINFVisuProviderRoot : constructor
//-----------------------------------------------------------------------------
CAAPstINFVisuProviderRoot::CAAPstINFVisuProviderRoot():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPstINFVisuProviderRoot : destructor
//-----------------------------------------------------------------------------
CAAPstINFVisuProviderRoot::~CAAPstINFVisuProviderRoot()
{
}
 
//-----------------------------------------------------------------------------
// CAAPstINFVisuProviderRoot : copy constructor
//-----------------------------------------------------------------------------
CAAPstINFVisuProviderRoot::CAAPstINFVisuProviderRoot(CAAPstINFVisuProviderRoot& original): CATBaseUnknown(original)
{
}
 
//-----------------------------------------------------------------------------
// CAAPstINFVisuProviderRoot : equal operator
//-----------------------------------------------------------------------------
CAAPstINFVisuProviderRoot& CAAPstINFVisuProviderRoot::operator=(CAAPstINFVisuProviderRoot& original)
{
   CATBaseUnknown::operator=(original);
   return *this;
}

//-----------------------------------------------------------------------------
// CAAPstINFVisuProviderRoot : GetChildren
// If the caller is the Product root, this method returns a list of pointers to
// the features of type "CAAPstINFRoot" that serve as the root objects aggregating
// other features.	
//-----------------------------------------------------------------------------
HRESULT CAAPstINFVisuProviderRoot::GetChildren(CATBaseUnknown *pObj,
					       CATLISTP(CATBaseUnknown)
					       **pListChildren) 
{
	cout << "***** CAAPstINFVisuProviderRoot::GetChildren" << endl;

	HRESULT rc = E_FAIL;

	//------------------------------------------------------
	// Verify that the caller is actually the Product root.
	//------------------------------------------------------

	// Retrieve a CATIProduct handle on the caller object
	CATIProduct *piProductOnObj = NULL;
	if (NULL == pObj) return E_FAIL;
	rc = pObj -> QueryInterface (IID_CATIProduct, 
				     (void**) &piProductOnObj);
	if (SUCCEEDED(rc)) {
		// Retrieve the father of the product:
		// if it has none, this must be the root.
		CATIProduct *piFatherProd = piProductOnObj -> GetFatherProduct();
		piProductOnObj -> Release();
		piProductOnObj = NULL;
		if (NULL != piFatherProd) {
			cout << "The caller is not the aggregating root product." << endl;
			return S_OK;
		} else
			cout << "The caller is the aggregating root product: continue" << endl;
  
		//--------------------------------------------------------------
		// Retrieve the applicative container containing the features
		//--------------------------------------------------------------
		// Retrieve a pointer to the current document
		CATILinkableObject *piLinkableOnObj = NULL;
		rc = pObj -> QueryInterface (IID_CATILinkableObject,
					     (void**) &piLinkableOnObj);
		if (FAILED(rc))
			return E_FAIL;

		CATDocument* pDoc = piLinkableOnObj->GetDocument();
		piLinkableOnObj -> Release();
		piLinkableOnObj = NULL;
		
		// Retrieve a pointer to the applicative container
		CATUnicodeString appliContIdentifier("PstINFContainer");
		CATBaseUnknown *pApplicativeContainer = NULL;

		rc = ::CATGetApplicativeContainer (&pApplicativeContainer,   
						   pDoc,                     
						   IID_CATIContainer,  
						   appliContIdentifier);     
		if (SUCCEEDED(rc))
			cout << "Applicative container retrieved OK" << endl;
		else {
			cout << "ERROR in retrieving applicative container" << endl;
			return E_FAIL;
		}

		// Retrieve a pointer to CATIClientContainer in order to list the members
		// of the applicative container.
		CATIClientContainer *piClientOnAppliCont = NULL;
		rc = pApplicativeContainer -> QueryInterface(IID_CATIClientContainer,
							     (void**) &piClientOnAppliCont);

		pApplicativeContainer -> Release();
		pApplicativeContainer = NULL;

		if (NULL == piClientOnAppliCont) { 
			cout << "ERROR in retrieving container pointer" << endl;
			return E_FAIL;
		} else
			cout << "CATIClientContainer pointer retrieved OK" << endl;

		//------------------------------------------------------------
		// Retrieve the list of features in the applicative container
		//------------------------------------------------------------
		CATUnicodeString clientId("CAAPstINFClientId"); 
		CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
		rc = piClientOnAppliCont -> ListMembers(IID_CATISpecObject,
							clientId,  
							&pMemberList);
		piClientOnAppliCont -> Release();
		piClientOnAppliCont = NULL;

		if (SUCCEEDED(rc))
			cout << "Member list retrieved OK" << endl;
		else { 
			cout << "ERROR in retrieving member list" << endl;
			return E_FAIL;
		}

		cout << "Number of members in applicative container: "
		     << pMemberList->Size() << endl;
      
		//--------------------------------------------------------------
		// Scan the list to retrieve the "CAAPstINFRoot" feature and
		// return the features it aggregates through the
		// "ListOfComponents" attribute.
		//--------------------------------------------------------------
		CATUnicodeString rootType("");
		CATISpecObject *piSpecMember = NULL;
		for (int i = 1; i <= pMemberList->Size(); i++) {
			piSpecMember = (CATISpecObject *) (*pMemberList)[i];
			if (NULL == piSpecMember)
				return E_FAIL;
			rootType = piSpecMember -> GetType();
			if (rootType == "CAAPstINFRoot")
				(*pListChildren) -> Append(piSpecMember);
			else
				piSpecMember -> Release();
			piSpecMember = NULL;
		}
		delete pMemberList;
		pMemberList = NULL;	    
	}
	return S_OK;
}
