// COPYRIGHT DASSAULT SYSTEMES  2015
//=============================================================================
//
// CAACloTransferElements
//

#ifndef CAACloTransferElements_H
#define CAACloTransferElements_H

#include "CAAPspBaseEnvProtected.h"

//class Declarations
class CATListValCATUnicodeString;

//-----------------------------------------------------------------------

class CATUnicodeString;

/**
 * Interface to calculate the weld offset 
 */
class CAACloTransferElements: public CAAPspBaseEnvProtected
{
  public:

  // Standard constructors and destructors
  // -------------------------------------
     CAACloTransferElements ();
     virtual ~CAACloTransferElements ();

	 int DoSample(const CATUnicodeString &iuFileToBeLoaded);
};

//-----------------------------------------------------------------------

#endif
