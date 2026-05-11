// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspGroup
//
#ifndef CAAPspGroup_H
#define CAAPspGroup_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspGroup : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspGroup ();
    virtual ~CAAPspGroup();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);

};
#endif
