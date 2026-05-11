#include "CAASysSprocketFactory.h"
#include "CAASysSprocketImpl.h"
#include "CAASysSprocketsImpl.h"

HRESULT __stdcall CAASysSprocketFactory::CreateSprocket(
	const CATUnicodeString& iName,
	CAAIASysSprocket*& oCAAIASysSprocket) {

	return CAASysSprocketImpl::CreateSprocket(iName, oCAAIASysSprocket);
}

HRESULT __stdcall CAASysSprocketFactory::CreateSprockets(
	CAAIASysSprockets*& oCAAIASysSprockets) {

	return CAASysSprocketsImpl::CreateSprockets(oCAAIASysSprockets);
}
