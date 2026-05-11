//------------------------------------------------------------------------------
// Copyright Dassault Systemes 2003
//------------------------------------------------------------------------------
// Command Header Implementation
//------------------------------------------------------------------------------
#include "CAAPuiPrsConfigAddinHeader.h"

// ApplicationFrame
#include "CATFrmEditor.h"

// ObjectModelerBase
#include "CATILinkableObject.h"
#include "CATDocument.h"

// ProductStructure
#include "CATIProduct.h"

// ProductStructureInterfaces
#include "CATIPrdPLMPersistency.h"

CATImplementHeaderResources(CAAPuiPrsConfigAddinHeader,
			    CATCommandHeader,
			    CAAPuiPrsConfigAddinHeader);

CATImplementKindOf(CAAPuiPrsConfigAddinHeader,
		   Implementation,
		   CATCommandHeader,
		   CATNull);

//===========================================================================
CAAPuiPrsConfigAddinHeader::CAAPuiPrsConfigAddinHeader(const CATString &headerID,
						       const CATString &loadName,
						       const CATString &className,
						       void * argument,
						       int state)
		: CATCommandHeader(headerID, loadName, className, argument, state)
{
	// setup callback
	_FrmEditor = CATFrmEditor::GetCurrentEditor();
	_UIActivatedCallback = NULL;
	AddUIActivatedCallback();
	UpdateAvailability();
}

//===========================================================================
CAAPuiPrsConfigAddinHeader::CAAPuiPrsConfigAddinHeader(CATCommandHeader *header)
	: CATCommandHeader(header)
{
	// setup callback
	_FrmEditor = CATFrmEditor::GetCurrentEditor();
	_UIActivatedCallback = NULL;
	AddUIActivatedCallback();
	UpdateAvailability();
}

//===========================================================================
CAAPuiPrsConfigAddinHeader::~CAAPuiPrsConfigAddinHeader()
{
	// Remove callback
	RemoveUIActivatedCallback();
	_UIActivatedCallback = NULL;
	_FrmEditor = NULL;
}

//===========================================================================
CATCommandHeader *CAAPuiPrsConfigAddinHeader::Clone()
{
	return new CAAPuiPrsConfigAddinHeader(this);
}

//===========================================================================
void CAAPuiPrsConfigAddinHeader::AddUIActivatedCallback()
{
	if (NULL == _FrmEditor)
		return;
	// Add our callback for UI activated
	_UIActivatedCallback = AddCallback
		(_FrmEditor,
		 CATFrmEditor::UIACTIVEOBJECT_CHANGECOMPLETED(),
		 (CATSubscriberMethod) &CAAPuiPrsConfigAddinHeader::UIActivated);
}

//===========================================================================
void CAAPuiPrsConfigAddinHeader::RemoveUIActivatedCallback()
{
	// Remove callback
	if (NULL != _FrmEditor && NULL != _UIActivatedCallback ) {
		RemoveCallback(_Editor, _UIActivatedCallback);
		_UIActivatedCallback = NULL;
	}
}

//===========================================================================
// This is called when UI has been activated
void CAAPuiPrsConfigAddinHeader::UIActivated(CATCallbackEvent,
					     void *,
					     CATNotification *,
					     CATSubscriberData,
					     CATCallback)
{
	// Enable/Disable command
	UpdateAvailability();
}

//===========================================================================
// Enable/Disable command depending on document storage mode
void CAAPuiPrsConfigAddinHeader::UpdateAvailability()
{
	if (NULL == _FrmEditor)
		return;

	//
	// Get current active product
	//
	CATPathElement activePath = _FrmEditor->GetUIActiveObject();
	CATIProduct *activeProduct = (CATIProduct *)
		activePath.SearchObject(CATIProduct::ClassName());
	if (NULL == activeProduct) return;

	//
	// Query its PersistencyMode
	//
	CATIProduct_var spRefProd = activeProduct->GetReferenceProduct();
	activeProduct->Release();
	activeProduct = NULL;
	if (NULL_var == spRefProd) return;

	CATILinkableObject_var spLink(spRefProd);
	if (NULL_var == spLink) return;

	CATDocument *pDoc = spLink->GetDocument();
	if (NULL == pDoc) return;

	CATIPrdPLMPersistency_var spPrdPLMPers(pDoc);
	CATIPrdPLMPersistency::PersistencyMode mode;
	if (NULL_var != spPrdPLMPers &&
	    SUCCEEDED(spPrdPLMPers->get_PersistencyMode(mode)) &&
	    mode == CATIPrdPLMPersistency::WorkpackageOrFile) {
		//
		// Enable only if workpackage/file mode
		//
		BecomeAvailable();
	} else {
		//
		// Disable otherwise
		//
		BecomeUnavailable();
	}
}
