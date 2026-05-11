// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================
//

#ifndef CAAPstAppliContProvider_H
#define CAAPstAppliContProvider_H

#include "CATBaseUnknown.h"
#include "CATListOfCATBaseUnknown.h"

#include "CAAPstEduNavigFeatProv.h"

//-----------------------------------------------------------------------

class ExportedByCAAPstEduNavigFeatProv CAAPstAppliContProvider: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
  CAAPstAppliContProvider ();
  virtual ~CAAPstAppliContProvider ();

  // Copy constructor and equal operator
  // -----------------------------------
  CAAPstAppliContProvider (CAAPstAppliContProvider &);
  CAAPstAppliContProvider& operator=(CAAPstAppliContProvider&);
	
  HRESULT GetChildren(CATBaseUnknown * iObj, CATLISTP(CATBaseUnknown) ** oListChildren); 

};

//-----------------------------------------------------------------------

#endif

