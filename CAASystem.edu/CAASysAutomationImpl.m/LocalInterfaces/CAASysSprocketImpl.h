#ifndef CAASysSprocketImpl_h
#define CAASysSprocketImpl_h

// COPYRIGHT DASSAULT SYSTEMES 2002

#include "CATBaseObject.h"
#include "CATBSTR.h"
#include "CATUnicodeString.h"
class CAAIASysSprocket;

/**
 * Implementation of the CAAIASysSprocket interface
 */
class CAASysSprocketImpl : public CATBaseObject {
	public:
		CATDeclareClass;

		/**
		 * Destructor.
		 */
		virtual ~CAASysSprocketImpl();


		/**
		 * Instantiates a new CAASysSprocketImpl.
		 */
		static HRESULT __stdcall CreateSprocket(
			const CATUnicodeString& iName,
			CAAIASysSprocket*& oCAAIASysSprocket);

		// Implementation of the CAAIASysSprocket interface
		virtual HRESULT get_Name(
			CATBSTR & oNameBSTR);

	private:
		/**
		 * Constructor.
		 */
		CAASysSprocketImpl(
			const CATUnicodeString& iName);

	private:
		/**
		 * The sprocket name.
		 */
		CATUnicodeString _name;
};

#endif // CAASysSprocketImpl_h
