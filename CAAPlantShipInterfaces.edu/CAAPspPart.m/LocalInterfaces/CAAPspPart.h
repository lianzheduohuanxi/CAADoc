// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspPart
//
#ifndef CAAPspPart_H
#define CAAPspPart_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspPart : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspPart ();
    virtual ~CAAPspPart();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
};
#endif
