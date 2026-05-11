// COPYRIGHT Dassault Systemes 2008
//===================================================================
//
// CAAPDMUEResId.h
//
// Implement the CATIPDMUEResId interface
//
//===================================================================
//   EXTENSION: CATIPDMUEResId
//   TIE: CATIPDMUEResId
//===================================================================
#ifndef CAAPDMUEResId_H
#define CAAPDMUEResId_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class CATDbBinary;

//-----------------------------------------------------------------------

/**
 * Class extending the object "CATUEPDMResId".
 * <br>
 * It implements the interface:
 *  <ol>
 *  <li>@see CATIPDMUEResId
 *  </ol>
 */
class CAAPDMUEResId : public CATBaseUnknown
{
	CATDeclareClass;

public:

	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	CAAPDMUEResId();
	virtual ~CAAPDMUEResId();


  virtual CATDbBinary CreateId();

};

//-----------------------------------------------------------------------

#endif

