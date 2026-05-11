// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAArrRunMngt
//
#ifndef CAAArrRunMngt_H
#define CAAArrRunMngt_H

#include "CAAArrBaseEnv.h"

class CAAArrRunMngt : public CAAArrBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAArrRunMngt ();
    virtual ~CAAArrRunMngt();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //        iPathToOutputFile - path to save the file in 
    //-------------------------------------------------------------------------
    int DoSample(const CATUnicodeString &iFileToBeLoaded);

  private:


};
#endif
