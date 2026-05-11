//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2003
//-----------------------------------------------------------------------------
// class CAAPmiUdfUtilities
// 
// This class is dedicated to Udf methods 
//-----------------------------------------------------------------------------
// Usage Notes:
//
//-----------------------------------------------------------------------------
// 2003/01/21 V5R11 Creation                                                DCN
//-----------------------------------------------------------------------------

#ifndef CAAPmiUdfUtilities_H
#define CAAPmiUdfUtilities_H

#include "CAAPmiUdfEnv.h"

#include "CATBaseUnknown.h"

//-----------------------------------------------------------------------------

class ExportedByCAAPmiUdfEnv CAAPmiUdfUtilities 
 {
 public :
                                  CAAPmiUdfUtilities ();
  virtual                        ~CAAPmiUdfUtilities ();
  
  //-----------------------------------------------------------------------------
  // GetUdfGeometry: Generic method to get a User Feature geometry from its role name
  //-----------------------------------------------------------------------------

  static HRESULT GetUdfGeometry (CATBaseUnknown * iUdf, CATUnicodeString iGeometryName, CATBaseUnknown_var &oGeometry);

 private :

    CAAPmiUdfUtilities (CAAPmiUdfUtilities &);
    CAAPmiUdfUtilities& operator=(CAAPmiUdfUtilities&);   


};

#endif
