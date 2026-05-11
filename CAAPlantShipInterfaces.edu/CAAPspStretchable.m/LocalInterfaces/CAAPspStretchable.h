// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspStretchable
//
#ifndef CAAPspStretchable_H
#define CAAPspStretchable_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspStretchable : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspStretchable ();
    virtual ~CAAPspStretchable();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
};
#endif
