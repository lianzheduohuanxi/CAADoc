// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspFunctionPhysical
//
#ifndef CAAPspFunctionPhysical_H
#define CAAPspFunctionPhysical_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspFunctionPhysical : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspFunctionPhysical ();
    virtual ~CAAPspFunctionPhysical();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample(const CATUnicodeString &iFileToBeLoaded);
};
#endif
