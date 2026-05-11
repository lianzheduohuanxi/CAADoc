// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAPstProductIconInit: CATInit implementation for container
//

// ObjectModelerBase Framework
#include "CATDocumentServices.h"
#include "CATDocument.h"
#include "CATAppliContServices.h"
#include "CATILinkableObject.h"
#include "CATInit.h"
#include "CATIDocRoots.h"
#include "CATIProduct.h"

// ObjectSpecsModeler Framework
#include "CATOsmExtensionServices.h"

// System Framework
#include "CATUnicodeString.h"

// C++ Standard library
#include <iostream.h>

#include "CAAPstProductIconInit.h"

#include "TIE_CATInit.h"
TIEchain_CATInit(CAAPstProductIconInit);

CATImplementClass (CAAPstProductIconInit,
		   DataExtension,
		   CATBaseUnknown,
		   CAAPstProductIconCont);

CAAPstProductIconInit::CAAPstProductIconInit()
{
}

CAAPstProductIconInit::~CAAPstProductIconInit()
{
}

//
// Initialize a CAAPstProductIconCont container
//
void CAAPstProductIconInit::Init (CATBoolean iDestroyExistingData)   
{
	cout << ">>>>> CAAPstIconInit::Init" << endl;
	//
	// Retrieve the current document
	//
	CATILinkableObject *piLinkableOnCont = NULL;
	HRESULT rc = QueryInterface(IID_CATILinkableObject,
				    (void**) &piLinkableOnCont);
	if (FAILED(rc) || NULL == piLinkableOnCont) {
		cout << "Failed to QI CATILinkableObject" << endl;
		return;
	}
	CATDocument *pDoc = piLinkableOnCont->GetDocument();
	piLinkableOnCont -> Release();
	piLinkableOnCont = NULL;
	if (NULL == pDoc) {
		cout << "Failed to GetDocument" << endl;
		return;
	}
	cout << "Document retrieved OK" << endl;
	
	//
	// Activate all extensions
	//
	const char *applContId = "PstProductIconContainer";
	rc =  CATOsmExtensionServices::CATActivateExtensions(pDoc, applContId);
}

CATBaseUnknown* CAAPstProductIconInit::GetRootContainer (const CATIdent iInterfaceID)
{
	cout << ">>>>> CAAPstIconInit::GetRootContainer" << endl;
	cout << "<<<<< CAAPstIconInit::GetRootContainer" << endl;
	return NULL;
}
