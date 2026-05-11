// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspLightPart
//
#ifndef CAAPspLightPart_H
#define CAAPspLightPart_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspLightPart : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspLightPart ();
    virtual ~CAAPspLightPart();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
};
#endif
