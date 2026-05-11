// ========================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ========================================================================================
// CAAMfgTPEUserCommandHeaders:
// ========================================================================================
// Jan 2002 : C.RIMBAUD :  Creation 
// ========================================================================================
//
#include "CAAMfgTPEUserCommandHeaders.h"

#include "CATCSO.h"
#include "CATCommandHeader.h"

#include "CATIMfgToolPathEditorUserHeader.h"
#include "CATListOfCATString.h"
#include "CATBooleanDef.h"

CATBeginImplementClass (CAAMfgTPEUserCommandHeaders,DataExtension,CATBaseUnknown ,MfgCompoundTraject);
CATAddExtendedImplementation (MfgTPMultipleMotion);
CATEndImplementClass (CAAMfgTPEUserCommandHeaders);

#include "TIE_CATIMfgToolPathEditorUserHeader.h"
TIEchain_CATIMfgToolPathEditorUserHeader(CAAMfgTPEUserCommandHeaders);

//===========================================================================
// Constructor
//===========================================================================
CAAMfgTPEUserCommandHeaders::CAAMfgTPEUserCommandHeaders() :
	CATBaseUnknown ()
{
}

//===========================================================================
// Destructor
//===========================================================================
CAAMfgTPEUserCommandHeaders::~CAAMfgTPEUserCommandHeaders()
{
}

//===========================================================================
// GetHeaders :
//===========================================================================
HRESULT CAAMfgTPEUserCommandHeaders::GetHeaders( CATListValCATString &ioHeadersList)
{
	HRESULT hRes= S_OK;

	// Default list of Headers of command in the Tool path Editor.
	// Each empty string is displayed as a separator in the menu.

	// R17 MODIFICATIONS :
    // TPEEdit
	// "" 
	// TPESplitToCopyTransformation
	// TPEToolLength
	// TPECreateGeometry

	CATIMfgToolPathEditorHeader_var spTPEHeaders = GetImpl();
	if (!!spTPEHeaders)
		spTPEHeaders->GetHeaders(ioHeadersList);

	int index=5;
	if ( ioHeadersList.Size() <= 1) index=1;
	ioHeadersList.InsertBefore(index,CATString("TPESplitToolPath"));

    index=3;
	if (ioHeadersList.Size() >= index) 
	    ioHeadersList.Replace ( index, CATString("TPEDisplayToolPath"));

	// User's list of Headers of command.
	ioHeadersList.Append(CATString("TPEDisplayDistance"));

	return hRes;
}

//===========================================================================
// IsHeadersAvailable
//===========================================================================
HRESULT CAAMfgTPEUserCommandHeaders::IsHeadersAvailable( CATListValCATString& ioHeadersList , CATCSO* iCSO )
{
	HRESULT hRes= S_OK;

	// Get the availabitiy of standards commands
	CATIMfgToolPathEditorHeader_var spTPEHeaders = GetImpl();
	if (!!spTPEHeaders)
		spTPEHeaders->IsHeadersAvailable(ioHeadersList,iCSO);
	
	// if several objects are selected, the contextual menu isn't the same.
	// Two items are disabled
	if (NULL == iCSO) return E_FAIL;
    int nbSelectedItems = iCSO->GetSize();
	if ( nbSelectedItems > 1 )
    {
		HeaderAvailability(CATString("TPEDisplayDistance"), CATFalse);
		HeaderAvailability(CATString("TPESplitToolPath"), CATFalse);
	}


	return hRes;
}

//===========================================================================
// HeaderAvailability
//===========================================================================
void CAAMfgTPEUserCommandHeaders::HeaderAvailability(const CATString& HeaderName, CATBoolean isON)
{
	CATCommandHeader *Header = CATCommandHeader::GetHeaderFromList(HeaderName);
	if ( Header )
    {
		if (isON)
            Header->BecomeAvailable();
		else 
			Header->BecomeUnavailable();
	}
}
