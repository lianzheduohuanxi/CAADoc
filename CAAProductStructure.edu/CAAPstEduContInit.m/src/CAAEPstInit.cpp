// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAEPstInit:
// Adhesion a CATInit du container du Base Feature 
//
// ObjectModelerBase Framework
#include "CATDocumentServices.h"
#include "CATDocument.h"
#include "CATAppliContServices.h"
#include "CATILinkableObject.h"
#include "CATInit.h"

// ProductStructure Framework
#include "CATIProviders.h"
#include "CATINavigateProvider.h"
#include "CATICtxMenuProvider.h"

// Local Framework
#include "CAAPstAppliContProvider.h"
#include "CAAPstCtxMenuProvider.h"
#include "CAAPstBookExtProvider.h"

// ObjectSpecsModeler Framework
#include "CATOsmExtensionServices.h"
#include "CATIClientContainer.h"
#include "CATIOsmExtendable.h"
#include "CATISpecObject.h"

// System Framework
#include "CATUnicodeString.h"

// YRC: Deprecated from V5R23
//#include "CATICatalog.h"
//#include "CATCatalogFactoryServices.h"

// C++ Standard library
#include <iostream.h>

#include "CAAEPstInit.h"

#include "TIE_CATInit.h"
TIEchain_CATInit(CAAEPstInit);

CATImplementClass (CAAEPstInit,
				   DataExtension,
				   CATBaseUnknown,
				   CAAPstBFCont);

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
CAAEPstInit::CAAEPstInit()
  {
  }
//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
CAAEPstInit::~CAAEPstInit()
  {
  }

//-----------------------------------------------------------------------------
// Implementationn de l'Interface de CATInit
//-----------------------------------------------------------------------------
void CAAEPstInit::Init (CATBoolean iDestroyExistingData)   
{
	cout << "***** CAAPstBFCont: CAAEPstInit::Init" << endl << flush;
	// Retrieve the current document
	CATILinkableObject *piLinkableOnCont = NULL;
	HRESULT rc = QueryInterface(IID_CATILinkableObject,
				    (void**) &piLinkableOnCont);
	if (!SUCCEEDED(rc)) return;
	CATDocument *pDoc = piLinkableOnCont -> GetDocument();
	piLinkableOnCont -> Release();
	piLinkableOnCont = NULL;
	if (NULL == pDoc) return;
	cout << "Document retrieved OK" << endl;
	
	
	// Retrieve a CATIProviders pointer on the current document
	CATIProviders *piProvidersOnDocument = NULL;
	rc = pDoc -> QueryInterface(IID_CATIProviders,
				    (void**) &piProvidersOnDocument);
	if (!SUCCEEDED(rc)) return;
	
	// Declare provider to list the children of the applicative container 
	CAAPstAppliContProvider *pAppliContProvider = new CAAPstAppliContProvider();
	rc = piProvidersOnDocument -> AddProvider (IID_CATINavigateProvider,
						   pAppliContProvider);
	pAppliContProvider -> Release();
	pAppliContProvider = NULL;
	if (!SUCCEEDED(rc))
		return;
	else
		cout << "Applicative container provider declared OK" << endl;
	
	// Declare provider for the contextual menu
	CAAPstCtxMenuProvider *pCtxMenuProvider = new CAAPstCtxMenuProvider();
	rc = piProvidersOnDocument -> AddProvider (IID_CATICtxMenuProvider,
						   pCtxMenuProvider);
	pCtxMenuProvider -> Release();
	pCtxMenuProvider = NULL;
	if (!SUCCEEDED(rc))
		return;
	else
		cout << "Applicative container provider declared OK" << endl;

	// Declare provider to list the children of an extended feature
	CAAPstBookExtProvider *pBookExtProvider = new CAAPstBookExtProvider();
	rc = piProvidersOnDocument -> AddProvider (IID_CATINavigateProvider,
						   pBookExtProvider);
	pBookExtProvider -> Release();
	pBookExtProvider = NULL;
	if (!SUCCEEDED(rc))
		return;
	else
		cout << "Extended feature provider declared OK" << endl;
	
	piProvidersOnDocument -> Release();
	piProvidersOnDocument = NULL;
	
	// Activate extensions (only required for former extensions)
	const char *appliContIdentifier = "ExtensionContainer";
	rc = CATOsmExtensionServices::CATActivateExtensions(pDoc,
							    appliContIdentifier);
	if (FAILED(rc)) { 
		cout << "ERROR activating extensions" << endl;
		return ;
	}
	else
		cout << "Extensions activated OK" << endl;
	
	return;
}


 
CATBaseUnknown* CAAEPstInit::GetRootContainer (const CATIdent iInterfaceID)
  {
	cout << "***** CAAPstBFCont: CAAEPstInit::GetRootContainer" << endl << flush;
    return 0;
  
  }

