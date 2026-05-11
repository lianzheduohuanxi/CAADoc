// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspLogicalLine
//
#ifndef CAAPspLogicalLine_H
#define CAAPspLogicalLine_H

#include "CAAPspBaseEnv.h"

//-----------------------------------------------------------------------------

class CAAPspLogicalLine : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspLogicalLine ();
    virtual ~CAAPspLogicalLine();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
};
#endif
