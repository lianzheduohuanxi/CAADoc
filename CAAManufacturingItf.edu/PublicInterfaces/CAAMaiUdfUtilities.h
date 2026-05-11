//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2003
//-----------------------------------------------------------------------------
// class CAAMaiUdfUtilities
// 
// This class is dedicated to Udf methods 
//-----------------------------------------------------------------------------
// Usage Notes:
//
//-----------------------------------------------------------------------------
// 2003/01/21 V5R11 Creation                                                DCN
//-----------------------------------------------------------------------------

#ifndef CAAMaiUdfUtilities_H
#define CAAMaiUdfUtilities_H

#include "CAAMaiUdfEnv.h"

#include "CATBaseUnknown.h"

//-----------------------------------------------------------------------------

class ExportedByCAAMaiUdfEnv CAAMaiUdfUtilities 
 {
 public :
                                  CAAMaiUdfUtilities ();
  virtual                        ~CAAMaiUdfUtilities ();
  
  //-----------------------------------------------------------------------------
  // GetUdfGeometry: Generic method to get a User Feature geometry from its role name
  //-----------------------------------------------------------------------------

  static HRESULT GetUdfGeometry (CATBaseUnknown * iUdf, CATUnicodeString iGeometryName, CATBaseUnknown_var &oGeometry);

 private :

    CAAMaiUdfUtilities (CAAMaiUdfUtilities &);
    CAAMaiUdfUtilities& operator=(CAAMaiUdfUtilities&);   


};

#endif
