// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspServices
//
#ifndef CAAPspServices_H
#define CAAPspServices_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspServices : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspServices ();
    virtual ~CAAPspServices();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
};
#endif
