// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAPstProductIconInit: CATInit implementation for container
//

#ifndef CAAPstProductIconInit_h
#define CAAPstProductIconInit_h

#include "CATBaseUnknown.h"
#include "CATBoolean.h"

class CAAPstProductIconInit : public CATBaseUnknown
{
	CATDeclareKindOf;

public:
 
	CAAPstProductIconInit();
	virtual ~CAAPstProductIconInit();

	/**
	 * Initializes data of this container.
	 * @param iDestroyExistingData
	 *         FALSE : Initialization is done only if there is no existing data.
	 *     <br>TRUE  :  Existing data is destroyed before new initialization.
	 */
	virtual void Init (CATBoolean iDestroyExistingData) ;

	/**
	 * Returns the root element of the given document.
	 * <br> Note that the return pointer type corresponds to the iInterfaceID
	 * argument. However, given the L1 exposition constraints, it is not possible
	 * to convert a CATIdent to an IID, which means that the only return possible
	 * is a CATBaseUnknown pointer which must then be cast to the proper interface
	 * handle.
	 * @param iInterfaceID
	 *        chosen interface to handle the root element.
	 */
	virtual CATBaseUnknown* GetRootContainer (const CATIdent iInterfaceID);

};

#endif
