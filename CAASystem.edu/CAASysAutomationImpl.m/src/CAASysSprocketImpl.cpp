#include "CAASysSprocketImpl.h"

// Declaration of the class as a CNext implementation class.
CATImplementClass(CAASysSprocketImpl, Implementation, CATBaseUnknown, CATnull);

// Implement the CAAIASysSprocket interface.
#include "TIE_CAAIASysSprocket.h"
TIE_CAAIASysSprocket(CAASysSprocketImpl);


CAASysSprocketImpl::CAASysSprocketImpl(
	const CATUnicodeString& iName) {

	_name = iName;
}

CAASysSprocketImpl::~CAASysSprocketImpl() {

}

HRESULT __stdcall CAASysSprocketImpl::CreateSprocket(
	const CATUnicodeString& iName,
	CAAIASysSprocket*& oCAAIASysSprocket) {

	HRESULT hr = E_FAIL;
	if (iName.GetLengthInChar() > 0) {
		CAASysSprocketImpl* SprocketImpl = new CAASysSprocketImpl(iName);
		hr = SprocketImpl->QueryInterface(IID_CAAIASysSprocket, (void**)&oCAAIASysSprocket);
		SprocketImpl->Release();
		SprocketImpl = NULL;
	}
	return hr;
}

HRESULT CAASysSprocketImpl::get_Name(
	CATBSTR & oNameBSTR) {

	_name.ConvertToBSTR(&oNameBSTR);
	return S_OK;
}




