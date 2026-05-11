// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAPstINFNavigProviderRoot.h"

// ProductStructure Framework
#include "CATIProduct.h"
#include "CATINavigateProvider.h"

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

// Tie the implementation to its interface
#include "TIE_CATINavigateProvider.h"
TIE_CATINavigateProvider(CAAPstINFNavigProviderRoot);

// To declare that the class is an simple implementation
//
CATImplementClass( CAAPstINFNavigProviderRoot,
                  Implementation, 
                  CATBaseUnknown,
                  CATNull );

// To declare that CAAEPstINFNavigProviderRoot is an implementation of CATINavigateProvider, 
// insert the following line in the interface dictionary:
//
//    CAAPstINFNavigProviderRoot CATINavigateProvider  libCAAPstINFModeler
//

//-----------------------------------------------------------------------------
// CAAPstINFNavigProviderRoot : constructor
//-----------------------------------------------------------------------------
CAAPstINFNavigProviderRoot::CAAPstINFNavigProviderRoot():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPstINFNavigProviderRoot : destructor
//-----------------------------------------------------------------------------
CAAPstINFNavigProviderRoot::~CAAPstINFNavigProviderRoot()
{
}

//-----------------------------------------------------------------------------
// CAAPstINFNavigProviderRoot : copy constructor
//-----------------------------------------------------------------------------
CAAPstINFNavigProviderRoot::CAAPstINFNavigProviderRoot(CAAPstINFNavigProviderRoot& original): CATBaseUnknown(original)
{
}

//-----------------------------------------------------------------------------
// CAAPstINFNavigProviderRoot : equal operator
//-----------------------------------------------------------------------------
CAAPstINFNavigProviderRoot& CAAPstINFNavigProviderRoot::operator=(CAAPstINFNavigProviderRoot& original)
{
  CATBaseUnknown::operator=(original);
  return *this;
}

//-----------------------------------------------------------------------------
// CAAPstINFNavigateProviderRoot : GetChildren
// Returns a pointer to the "CAAPstINFRoot" feature found in the applicative
// container of type "CAAPstINFCont" if the caller is the Product root	
//-----------------------------------------------------------------------------
HRESULT CAAPstINFNavigProviderRoot::GetChildren(CATBaseUnknown *pObj, CATLISTP(CATBaseUnknown) **pListChildren) 
{
  cout << "***** CAAPstINFNavigProviderRoot::GetChildren" << endl << flush;

  // Retrieve a CATIProduct handle on the caller object
  CATIProduct *piProductOnObj = NULL;
  if (NULL == pObj) return E_FAIL;
  HRESULT rc = pObj -> QueryInterface (IID_CATIProduct, 
    (void**) &piProductOnObj);
  if (SUCCEEDED(rc)) {
    // Retrieve the father of the product: if it has none, this must be the root.
    CATIProduct *piFatherProd = piProductOnObj -> GetFatherProduct();
    piProductOnObj -> Release();
    piProductOnObj = NULL;
    if (piFatherProd != NULL) {
      cout << "The caller is not the aggregating root product." << endl << flush;
      return S_OK;
    } else 
      cout << "The caller is the aggregating root product: continue" << endl;

    // Retrieve a pointer to the applicative container.
    CATILinkableObject *piLinkableOnObj = NULL;
    rc = pObj -> QueryInterface (IID_CATILinkableObject,
      (void**) &piLinkableOnObj);
    if (!SUCCEEDED(rc)) return E_FAIL;
    CATDocument* pDoc = piLinkableOnObj->GetDocument();
    piLinkableOnObj -> Release();
    piLinkableOnObj = NULL;

    CATUnicodeString appliContIdentifier("PstINFContainer");
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
    else 
      cout << "CATIClientContainer pointer retrieved OK" << endl << flush;

    // Retrieve the list of features in the applicative container
    CATUnicodeString clientId("CAAPstINFClientId"); 
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

    CATUnicodeString rootType("");
    CATISpecObject *piSpecMember = NULL;
    if (NULL == *pListChildren)
      *pListChildren = new CATLISTP(CATBaseUnknown);
    for(int i=1;i<=pMemberList->Size();i++) {
      piSpecMember = (CATISpecObject *) (*pMemberList)[i];
      if (NULL == piSpecMember) return E_FAIL;
      rootType = piSpecMember -> GetType();
      if (rootType == "CAAPstINFRoot")
        (*pListChildren)->Append((*pMemberList)[i]);
      else
        piSpecMember -> Release();
      piSpecMember = NULL;
    }
    delete pMemberList;
    pMemberList = NULL;
  }

  return S_OK;
}



