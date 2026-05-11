#include "CAAPstAppliContProvider.h"

// ProductStructure Framework
#include "CATINavigateProvider.h"

// ObjectSpecsModeler Framework
#include "CATIProduct.h"
#include "CATISpecObject.h"
#include "CATDocument.h"
#include "CATAppliContServices.h"
#include "CATIClientContainer.h"
#include "CATILinkableObject.h"

#include "CATBaseUnknown.h"

// C++ Standard Library
#include "iostream.h"


 
#include "TIE_CATINavigateProvider.h"
TIEchain_CATINavigateProvider(CAAPstAppliContProvider);

CATImplementClass( CAAPstAppliContProvider,
                   Implementation, 
                   CATBaseUnknown,
                   CATNull );

//-----------------------------------------------------------------------------
// CAAPstAppliContProvider : constructor
//-----------------------------------------------------------------------------
CAAPstAppliContProvider::CAAPstAppliContProvider():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPstAppliContProvider : destructor
//-----------------------------------------------------------------------------
CAAPstAppliContProvider::~CAAPstAppliContProvider()
{

}
 
//-----------------------------------------------------------------------------
// CAAPstAppliContProvider : copy constructor
//-----------------------------------------------------------------------------
CAAPstAppliContProvider::CAAPstAppliContProvider(CAAPstAppliContProvider& original): CATBaseUnknown(original)
{
}
 
//-----------------------------------------------------------------------------
// CAAPstAppliContProvider : equal operator
//-----------------------------------------------------------------------------
CAAPstAppliContProvider& CAAPstAppliContProvider::operator=(CAAPstAppliContProvider& original)
{
   CATBaseUnknown::operator=(original);
   return *this;
}

HRESULT CAAPstAppliContProvider::GetChildren(CATBaseUnknown * pObj, CATLISTP(CATBaseUnknown) ** pListChildren) 
{
	cout << "***** CAAPstAppliContProvider::GetChildren" << endl << flush;

	// This provider returns the list of the children found in the applicative
	// container of the document only if the caller is the subproduct 
	// named "CAAPstProviderSubProduct1.1"

	// Retrieve a CATIProduct handle on the caller object
	CATIProduct *piProductOnObj = NULL;
	if (NULL == pObj) return E_FAIL;
	HRESULT rc = pObj -> QueryInterface (IID_CATIProduct, 
					     (void**) &piProductOnObj);
	if (SUCCEEDED(rc)) {
		// Retrieve the name of the product caller; if it is "CAAPstProviderSubProduct1.1"
		// then create and return the list of the children of the applicative container.
		CATUnicodeString productName;
		rc = piProductOnObj -> GetPrdInstanceName(productName);
		piProductOnObj -> Release();
		piProductOnObj = NULL;
		if (productName != "CAAPstProviderSubProduct1.1") {
			cout << "The caller is not the aggregating subproduct." << endl << flush;
			return S_OK;
		}

		// Retrieve a pointer to the applicative container.
		CATILinkableObject *piLinkableOnObj = NULL;
		rc = pObj -> QueryInterface (IID_CATILinkableObject,
					     (void**) &piLinkableOnObj);
		if (!SUCCEEDED(rc)) return E_FAIL;
		CATDocument* pDoc = piLinkableOnObj->GetDocument();
		piLinkableOnObj -> Release();
		piLinkableOnObj = NULL;
		
		CATUnicodeString appliContIdentifier("BaseFeatureContainer");
		CATBaseUnknown *pApplicativeContainer = NULL;

		rc = ::CATGetApplicativeContainer (&pApplicativeContainer,   
						   pDoc,                     
						   IID_CATIContainer,  
						   appliContIdentifier);     
		if (SUCCEEDED(rc)) 
			cout << "Applicative container retrieved OK" << endl << flush;
		else {
			cout << "ERROR in retrieving applicative container" << endl << flush;
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
			cout << "ERROR in retrieving container pointer" << endl << flush;
			return E_FAIL;
		}
		else cout << "CATIClientContainer pointer retrieved OK" << endl << flush;
	
		// Retrieve the list of features in the applicative container
		CATUnicodeString clientId("CAAOsmClientId"); 
		CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
		rc = piClientOnAppliCont -> ListMembers(IID_CATISpecObject,
							clientId,  
							&pMemberList);
		piClientOnAppliCont -> Release();
		piClientOnAppliCont = NULL;

		if (SUCCEEDED(rc)) 
			cout << "Member list retrieved OK" << endl << flush;
		else { 
			cout << "ERROR in retrieving member list" << endl << flush;
			return E_FAIL;
		}

		cout << "Number of members in applicative container: " << pMemberList->Size() << endl << flush;
      
		if (NULL == *pListChildren)
			*pListChildren = new CATLISTP(CATBaseUnknown);
		for(int i=1;i<=pMemberList->Size();i++) {
			(*pListChildren)->Append((*pMemberList)[i]);
		}
		delete pMemberList;
		pMemberList = NULL;
	}

	return S_OK;
}



