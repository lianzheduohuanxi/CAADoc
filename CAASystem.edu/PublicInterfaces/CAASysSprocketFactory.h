#ifndef CAASysSprocketFactory_h
#define CAASysSprocketFactory_h

// COPYRIGHT DASSAULT SYSTEMES 2002

#include "CAASysAutomationImpl.h"
#include "CATUnicodeString.h"
class CAAIASysSprocket;
class CAAIASysSprockets;

/**
 * Implementation of the CAAIASysSprocket interface
 */
class ExportedByCAASysAutomationImpl CAASysSprocketFactory {
	public:
		/**
		 * Instantiates a new CAAIASysSprocket.
		 */
		static HRESULT __stdcall CreateSprocket(
			const CATUnicodeString& iName,
			CAAIASysSprocket*& oCAAIASysSprocket);

		/**
		 * Instantiates a new CAAIASysSprockets.
		 */
		static HRESULT __stdcall CreateSprockets(
			CAAIASysSprockets*& oCAAIASysSprockets);
};

#endif // CAASysSprocketFactory_h
