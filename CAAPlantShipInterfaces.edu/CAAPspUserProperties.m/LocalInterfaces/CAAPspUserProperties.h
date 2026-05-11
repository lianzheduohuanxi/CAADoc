// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspUserProperties
//
#ifndef CAAPspUserProperties_H
#define CAAPspUserProperties_H

#include "CAAPspBaseEnv.h"


class CATListValCATUnicodeString;
//-----------------------------------------------------------------------------

class CAAPspUserProperties : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspUserProperties ();
    virtual ~CAAPspUserProperties();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);
		
};
#endif
