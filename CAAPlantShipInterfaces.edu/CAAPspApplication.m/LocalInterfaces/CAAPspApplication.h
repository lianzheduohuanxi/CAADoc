// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspApplication
//
#ifndef CAAPspApplication_H
#define CAAPspApplication_H

#include "CAAPspBaseEnv.h"

class CAAPspApplication : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspApplication ();
    virtual ~CAAPspApplication();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //        iPathToOutputFile - path to save the file in 
    //-------------------------------------------------------------------------
    int DoSample(const CATUnicodeString &iFileToBeLoaded);

};
#endif
