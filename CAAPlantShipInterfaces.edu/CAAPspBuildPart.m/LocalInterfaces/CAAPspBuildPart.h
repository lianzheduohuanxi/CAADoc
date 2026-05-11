// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspBuildPart
//
#ifndef CAAPspBuildPart_H
#define CAAPspBuildPart_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspBuildPart : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspBuildPart ();
    virtual ~CAAPspBuildPart();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
};
#endif
