// COPYRIGHT DASSAULT SYSTEMES 2002

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATILinkableObject.h"
#include "CATIDocRoots.h"
#include "CATAppliContServices.h"

// ProductStructure Framework
#include "CATIProviders.h"
#include "CATINavigateProvider.h"
#include "CATI3DVisuProvider.h"
#include "CATIUpdateProvider.h"
#include "CATIProduct.h"

// Local Framework
#include "CAAEPstINFInitCont.h"
#include "CAAPstINFNavigProviderRoot.h"
#include "CAAPstINFVisuProviderRoot.h"
#include "CAAPstINFUpdateProvider.h"

// ObjectSpecsModeler Framework
#include "SpecBindNativeFormat.h"
#include "CATIClientContainer.h"
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

// Visualization Framework
#include "CATIModelEvents.h"

// Others
#include <iostream.h>

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATInit.h"
TIE_CATInit(CAAEPstINFInitCont);


// To declare that the class is a data extension of "CAAPstINFCont" 
//
CATImplementClass (CAAEPstINFInitCont,
				   DataExtension,
				   CATBaseUnknown,
				   CAAPstINFCont);

// To declare that CAAEPstINFCont implements CATInit for the CAAIPstINFCont
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFCont   CATInit  libCAAINFModeler

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
CAAEPstINFInitCont::CAAEPstINFInitCont()
{
}
//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
CAAEPstINFInitCont::~CAAEPstINFInitCont()
{
}

//-----------------------------------------------------------------------------
// Implementationn de l'Interface de CATInit
//-----------------------------------------------------------------------------
void CAAEPstINFInitCont::Init (CATBoolean destroyExistingData)   
{
    cout << "***** CAAPstINFCont: CAAEPstINFInitCont::Init" << endl;

    // Retrieve the current document
    CATILinkableObject *piLinkableOnCont = NULL;
    HRESULT rc = this -> QueryInterface(IID_CATILinkableObject,
                                        (void**) &piLinkableOnCont);
    if (!SUCCEEDED(rc)) return;

    CATDocument *pDoc = piLinkableOnCont -> GetDocument();
    piLinkableOnCont -> Release();
    piLinkableOnCont = NULL;
    if (NULL == pDoc) return;
    cout << "Document retrieved OK" << endl << flush;


    // Retrieve a CATIProviders pointer on the current document
    CATIProviders *piProvidersOnDocument = NULL;
    rc = pDoc -> QueryInterface(IID_CATIProviders,
                                (void**) &piProvidersOnDocument);
    if (!SUCCEEDED(rc)) return;

    // Declare the navigation provider to list the feature root(s) 
    CAAPstINFNavigProviderRoot *pNavigProviderRoot = new CAAPstINFNavigProviderRoot();
    rc = piProvidersOnDocument -> AddProvider (CATINavigateProvider::ClassId(),
					       pNavigProviderRoot);
    pNavigProviderRoot -> Release();
    pNavigProviderRoot = NULL;

    if (!SUCCEEDED(rc)) return;
    else cout << "Navigation provider for root declared OK" << endl << flush; 

    // Declare the visualization provider to list the children of the applicative container 
    CAAPstINFVisuProviderRoot *pVisuProviderRoot = new CAAPstINFVisuProviderRoot();
    rc = piProvidersOnDocument -> AddProvider (CATI3DVisuProvider::ClassId(),
					       pVisuProviderRoot);
    pVisuProviderRoot -> Release();
    pVisuProviderRoot = NULL;

    if (!SUCCEEDED(rc)) return;
    else cout << "Visualization provider declared OK" << endl << flush; 

    // Declare the update provider to re-build line or wire after modification
    // of points 
    CAAPstINFUpdateProvider *pUpdateProvider = new CAAPstINFUpdateProvider();
    rc = piProvidersOnDocument -> AddProvider (CATIUpdateProvider::ClassId(),
					       pUpdateProvider);
    pUpdateProvider -> Release();
    pUpdateProvider = NULL;

    piProvidersOnDocument -> Release();
    piProvidersOnDocument = NULL;

    if (!SUCCEEDED(rc)) return;
    else cout << "Update provider declared OK" << endl << flush; 

    //--------------------------------------------------------------------------------------
    // Connect the Feature root to the Product root and each aggregated feature to its root.
    //--------------------------------------------------------------------------------------

    // Retrieve the Product root

    CATIProduct *piRootProduct = NULL;
	
    CATIDocRoots* piDocRootsOnDoc = NULL;
    rc = pDoc -> QueryInterface(IID_CATIDocRoots,
                                (void**) &piDocRootsOnDoc);
    if (SUCCEEDED(rc))
	{
	    // Retrieve the root product which is the first element of root elements
	    CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc -> GiveDocRoots();
	    piDocRootsOnDoc -> Release();
	    piDocRootsOnDoc = NULL;
	    CATBaseUnknown *pBaseRootProduct = NULL;
	   
	    if (pRootProducts && pRootProducts->Size())
		{  
		    pBaseRootProduct = (*pRootProducts)[1];
		    delete pRootProducts;
		    pRootProducts = NULL;
		    if (NULL == pBaseRootProduct) return;
		    rc = pBaseRootProduct -> QueryInterface(IID_CATIProduct,
							    (void**) &piRootProduct);
		    if (FAILED(rc)) return;
		}
	}
    else return;

    // Scan the applicative container to retrieve the Feature roots and connect them to the
    // Product root.

    CATUnicodeString appliContIdentifier("PstINFContainer");
    CATBaseUnknown *pApplicativeContainer = NULL;

    rc = ::CATGetApplicativeContainer (&pApplicativeContainer,   
                                       pDoc,                     
				       IID_CATIClientContainer,  
                                       appliContIdentifier);     
    if (SUCCEEDED(rc)) cout << "Applicative container retrieved OK" << endl << flush;
    else
	{
	    cout << "ERROR in retrieving applicative container" << endl << flush;
	    return;
	}

    // Retrieve a pointer to CATIClientContainer in order to list the members
    // of the applicative container.

    CATIClientContainer *piClientOnAppliCont = (CATIClientContainer *) pApplicativeContainer;
    
    // Retrieve the list of features in the applicative container
    CATUnicodeString clientId("CAAPstINFClientId"); 
    CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
    rc = piClientOnAppliCont -> ListMembers(IID_CATISpecObject,
                                            clientId,  
                                            &pMemberList);
    pApplicativeContainer -> Release();
    pApplicativeContainer = NULL;

    if (SUCCEEDED(rc)) cout << "Member list retrieved OK" << endl << flush;
    else
	{ 
	    cout << "ERROR in retrieving member list" << endl << flush;
	    return;
	}

    cout << "Number of members in applicative container: " << pMemberList->Size() << endl << flush;
      
    // Retrieve a CATIModelEvents pointer to the Product root
    CATIModelEvents *piModelEventsOnProductRoot = NULL;
    rc = piRootProduct -> QueryInterface(IID_CATIModelEvents,
                                         (void**) &piModelEventsOnProductRoot);
    if (FAILED(rc)) return;
	
    piRootProduct -> Release();
    piRootProduct = NULL;

    // Scan through the list of features in the applicative container and
    // when find a feature root, connect it to the Product root.
    // Then, for each feature root, retrieve the features it aggregates (or references) in 
    // order to connect them to their root (feature root) as well.
    CATUnicodeString rootType("");
    CATISpecObject *piSpecMember = NULL;
    for(int i=1;i<=pMemberList->Size();i++)
	{
	    piSpecMember = (CATISpecObject *) (*pMemberList)[i];
	    if (NULL == piSpecMember) return;
	    rootType = piSpecMember -> GetType();
	    if (rootType == "CAAPstINFRoot")
		{
		    // Connect the feature root to the Product root
		    piModelEventsOnProductRoot -> ConnectTo((*pMemberList)[i]);       

		    // Retrieve the list of aggregated or referenced features
		    CATISpecAttrAccess *piSpecAttrAccessOnFeatureRoot = NULL;
		    rc = piSpecMember -> QueryInterface(IID_CATISpecAttrAccess,
							(void**) &piSpecAttrAccessOnFeatureRoot);
		    if (FAILED(rc)) return;

		    CATUnicodeString keyName = "ListOfComponents";
	
		    if (NULL == piSpecAttrAccessOnFeatureRoot) return;
		    CATISpecAttrKey *piComponentKey = piSpecAttrAccessOnFeatureRoot -> GetAttrKey (keyName);
		    if (NULL == piComponentKey) return;
	      	  
		    CATIModelEvents *piModelEventsOnFeatureRoot = NULL;
		    rc = piSpecMember -> QueryInterface(IID_CATIModelEvents,
							(void**) &piModelEventsOnFeatureRoot);
		    if (FAILED(rc)) return;
          
		    CATISpecObject *piFeatureComponent = NULL;
		    int n = piSpecAttrAccessOnFeatureRoot -> GetListSize(piComponentKey);
		    for (int j = 1; j <= n; j++)
			{
			    // Connect each feature to its root
			    piFeatureComponent = piSpecAttrAccessOnFeatureRoot -> GetSpecObject(piComponentKey, j);	
			    if (NULL == piModelEventsOnFeatureRoot ||
				NULL == piFeatureComponent) return;
			    piModelEventsOnFeatureRoot -> ConnectTo((CATBaseUnknown *)piFeatureComponent);
			    piFeatureComponent -> Release();
			    piFeatureComponent = NULL;
			}

		    piSpecAttrAccessOnFeatureRoot -> Release();
		    piSpecAttrAccessOnFeatureRoot = NULL;

		    piComponentKey -> Release();
		    piComponentKey = NULL;

		    piModelEventsOnFeatureRoot -> Release();
		    piModelEventsOnFeatureRoot = NULL;
		}
	    piSpecMember -> Release();
	    piSpecMember = NULL;
	}
    piModelEventsOnProductRoot -> Release();
    piModelEventsOnProductRoot = NULL;
    delete pMemberList;
    pMemberList = NULL;

    // Declare the CCP Format
    ::SpecBindNativeFormat("CAAPstINFCont");

    return;
} 

CATBaseUnknown* CAAEPstINFInitCont::GetRootContainer (const CATIdent interfaceID)
{
	cout << "***** CAAPstINFCont: CAAEPstINFInitCont::GetRootContainer" << endl;
    return 0;
}
