#include "CAAPstCtxMenuProvider.h"

// ProductStructure Framework
#include "CATIProduct.h"
#include "TIE_CATICtxMenuProvider.h"

// ApplicationFrame Framework
#include "CATCmdContainer.h"
#include "CATCmdStarter.h"
#include "CATCreateWorkshop.h"
#include "CATCommandHeader.h"
MacDeclareHeader(CAAPstCtxMenuCmdHeader);

TIE_CATICtxMenuProvider(CAAPstCtxMenuProvider);

CATImplementClass(CAAPstCtxMenuProvider,
		  Implementation,
		  CATBaseUnknown,
		  CATNull);

CAAPstCtxMenuProvider::CAAPstCtxMenuProvider() : CATBaseUnknown()
{
	_command_created = FALSE;
}

CAAPstCtxMenuProvider::~CAAPstCtxMenuProvider()
{
}

HRESULT CAAPstCtxMenuProvider::GetContextualMenu(CATBaseUnknown *iObj,
						 CATCmdContainer *oCtxMenu)
{
	// Create the command header
	CreateCommand();

	// Retrieve a CATIProduct handle on the caller object
	CATIProduct *piProductOnObj = NULL;
	if (NULL == iObj) return E_FAIL;
	HRESULT rc = iObj -> QueryInterface (IID_CATIProduct, 
					     (void**) &piProductOnObj);
	if (SUCCEEDED(rc)) {
		// Retrieve the name of the product caller
		// If it is "CAAPstProviderSubProduct1.1"
		// then create a entry in the contextual menu
		CATUnicodeString productName;
		rc = piProductOnObj->GetPrdInstanceName(productName);
		piProductOnObj->Release();
		piProductOnObj = NULL;
		if (productName == "CAAPstProviderSubProduct1.1") {
			NewAccess(CATCmdStarter, pStarter, CAACtxMenuStarter);
			SetAccessCommand(pStarter, "CAACtxMenuCmd");
			SetAccessChild(oCtxMenu, pStarter);
			return S_OK;
		}
	}
	return E_FAIL;
}

void CAAPstCtxMenuProvider::CreateCommand()
{
	if (! _command_created) {
		new CAAPstCtxMenuCmdHeader("CAACtxMenuCmd",
					   "CAAPstCtxMenuProvider",
					   "CAAPstCtxMenuCmd",
					   (void *) NULL);
		_command_created = TRUE;
	}
}
