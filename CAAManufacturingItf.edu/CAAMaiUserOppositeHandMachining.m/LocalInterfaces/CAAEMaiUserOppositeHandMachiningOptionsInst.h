#ifndef CAAEMaiUserOppositeHandMachiningOptionsInst_H
#define CAAEMaiUserOppositeHandMachiningOptionsInst_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// CAAEMaiUserOppositeHandMachiningOptionsInst.h
// Provides implementation to interface CATICreateInstance
//=============================================================================

#include "CATBaseUnknown.h"

/**
 * Class extending the object "CAAEMaiUserOppositeHandMachiningOptions".
 * <br>
 * It implements the interface :
 *  <ol>
 *  <li>@see System.CATICreateInstance
 *  </ol>
 */
class CAAEMaiUserOppositeHandMachiningOptionsInst: public CATBaseUnknown
{
	CATDeclareClass;
	
public:
	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	CAAEMaiUserOppositeHandMachiningOptionsInst ();
	virtual ~CAAEMaiUserOppositeHandMachiningOptionsInst ();
	
    /**
	 * Implements a function from an interface.
	 * @see System.CATICreateInstance#CreateInstance
	 */
	HRESULT __stdcall CreateInstance (void ** oPPV ) ;
	
private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	CAAEMaiUserOppositeHandMachiningOptionsInst (const CAAEMaiUserOppositeHandMachiningOptionsInst &);
	CAAEMaiUserOppositeHandMachiningOptionsInst& operator=(const CAAEMaiUserOppositeHandMachiningOptionsInst&);
};
#endif
