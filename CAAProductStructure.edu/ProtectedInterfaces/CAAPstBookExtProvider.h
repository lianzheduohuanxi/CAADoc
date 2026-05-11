// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================
//

#ifndef CAAPstBookExtProvider_H
#define CAAPstBookExtProvider_H

#include "CATBaseUnknown.h"
#include "CATListOfCATBaseUnknown.h"

#include "CAAPstEduNavigExtProv.h"

//-----------------------------------------------------------------------

class ExportedByCAAPstEduNavigExtProv CAAPstBookExtProvider: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
  CAAPstBookExtProvider ();
  virtual ~CAAPstBookExtProvider ();

  // Copy constructor and equal operator
  // -----------------------------------
  CAAPstBookExtProvider (CAAPstBookExtProvider &);
  CAAPstBookExtProvider& operator=(CAAPstBookExtProvider&);
	
  HRESULT GetChildren(CATBaseUnknown * iObj, CATLISTP(CATBaseUnknown) ** oListChildren); 

};

//-----------------------------------------------------------------------

#endif

