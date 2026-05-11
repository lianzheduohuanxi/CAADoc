/**
 * @quickReview S1L 16:10:18    Migration of the startup’s ID syntax 
 */

// Copyright DASSAULT SYSTEMES
#include "CAAPstBookExtProvider.h"

// ProductStructure Framework
#include "CATINavigateProvider.h"

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATISpecObject.h"
#include "CATIOsmExtendable.h"

#include "CATBaseUnknown.h"

// C++ Standard Library
#include "iostream.h"
 
#include "TIE_CATINavigateProvider.h"
TIEchain_CATINavigateProvider(CAAPstBookExtProvider);

CATImplementClass( CAAPstBookExtProvider,
                   Implementation, 
                   CATBaseUnknown,
                   CATNull );

//-----------------------------------------------------------------------------
// CAAPstBookExtProvider : constructor
//-----------------------------------------------------------------------------
CAAPstBookExtProvider::CAAPstBookExtProvider():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPstBookExtProvider : destructor
//-----------------------------------------------------------------------------
CAAPstBookExtProvider::~CAAPstBookExtProvider()
{
}
 
//-----------------------------------------------------------------------------
// CAAPstBookExtProvider : copy constructor
//-----------------------------------------------------------------------------
CAAPstBookExtProvider::CAAPstBookExtProvider(CAAPstBookExtProvider& original): CATBaseUnknown(original)
{
}
 
//-----------------------------------------------------------------------------
// CAAPstBookExtProvider : equal operator
//-----------------------------------------------------------------------------
CAAPstBookExtProvider& CAAPstBookExtProvider::operator=(CAAPstBookExtProvider& original)
{
   CATBaseUnknown::operator=(original);
   return *this;
}

HRESULT CAAPstBookExtProvider::GetChildren(CATBaseUnknown * pObj, 
					   CATLISTP(CATBaseUnknown) ** pListChildren) 
{
	cout << "***** CAAPstBookExtProvider::GetChildren" << endl << flush;

	// This provider returns the children of the extension of the feature named
	// "CAAOsmBook1". If the caller object is not this feature, the provider
	// simply returns.

	// Retrieve a CATISpecObject pointer on the caller object.
	CATISpecObject *piSpecObjectOnExtFeature = NULL;
	if (NULL == pObj) return E_FAIL;
	HRESULT rc = pObj -> QueryInterface (IID_CATISpecObject,
					     (void**) &piSpecObjectOnExtFeature);

	if (!SUCCEEDED(rc)) return S_OK;

	CATUnicodeString specName = piSpecObjectOnExtFeature -> GetName();
	if (specName == "CAAOsmBook1") {     
		// Retrieve CATIOsmExtendable on the base feature
		CATIOsmExtendable *piExtendableOnExtFeature = NULL;
		rc = piSpecObjectOnExtFeature -> QueryInterface(IID_CATIOsmExtendable,
								(void**) &piExtendableOnExtFeature);
		piSpecObjectOnExtFeature -> Release();
		piSpecObjectOnExtFeature = NULL;
		if (FAILED(rc)) return E_FAIL;
         
		// Retrieve CATISpecAttrAccess on the extension
		//S1L : migration of the startup’s ID syntax 
		//const char *extensionName = "CAAPstHistoricalNovel";
		const char *extensionName = "`CAAPstHistoricalNovel`@`CAAPstExtCatalog.CATfct`";
		CATISpecAttrAccess *piAccessOnExtension = NULL;
		rc = piExtendableOnExtFeature->QueryExtension(extensionName,
							      IID_CATISpecAttrAccess,
							      (void**) &piAccessOnExtension);
		piExtendableOnExtFeature->Release();
		piExtendableOnExtFeature = NULL;
		if (FAILED(rc)) return E_FAIL;

		// Retrieve the attribute key for the extensions component attribute
		CATISpecAttrKey *piKeyNovelChapter = piAccessOnExtension -> 
			GetAttrKey("NovelChapter");
		if (NULL == piKeyNovelChapter) return E_FAIL; 
	   	
		// Retrieve the feature value of the attribute
		CATBaseUnknown *pChapter = NULL;
		pChapter = piAccessOnExtension -> GetSpecObject (piKeyNovelChapter, 1);

		piAccessOnExtension -> Release();
		piAccessOnExtension = NULL;

		piKeyNovelChapter -> Release();
		piKeyNovelChapter = NULL;

		// Add the feature to the list of children
		if (NULL != pChapter) {
			if (NULL == *pListChildren)
				*pListChildren = new CATLISTP(CATBaseUnknown);
			(*pListChildren)->Append(pChapter);
		} else 
			return E_FAIL;
	} else {
		piSpecObjectOnExtFeature -> Release();
		piSpecObjectOnExtFeature = NULL;
	}

	return S_OK;
}



