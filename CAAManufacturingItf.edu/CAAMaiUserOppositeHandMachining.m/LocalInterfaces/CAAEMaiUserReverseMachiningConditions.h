#ifndef CAAEMaiUserReverseMachiningConditions_h
#define CAAEMaiUserReverseMachiningConditions_h
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// CAAEMaiUserReverseMachiningConditions.h
// Provides implementation to interface CATIMfgUserReverseMachiningConditions
//=============================================================================

#include "CATBaseUnknown.h"

/**
 * Class extending the "ProfileContouring" late type.
 * <br>
 * It implements the interface :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgUserReverseMachiningConditions
 *  </ol>
 */
class CAAEMaiUserReverseMachiningConditions : public CATBaseUnknown
{
	CATDeclareClass;
	
public:
	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
    CAAEMaiUserReverseMachiningConditions();
    virtual ~CAAEMaiUserReverseMachiningConditions();
	
    /**
	 * Implements a function from an interface.
	 * @see ManufacturingInterfaces.CATIMfgUserReverseMachiningConditions#ReverseMachiningConditions
	 */
	HRESULT ReverseMachiningConditions();

private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
    CAAEMaiUserReverseMachiningConditions(const CAAEMaiUserReverseMachiningConditions &iObjectToCopy);
    CAAEMaiUserReverseMachiningConditions & operator  = (const CAAEMaiUserReverseMachiningConditions &iObjectToCopy);
};
#endif

