#ifndef CAASysError_H
#define CAASysError_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// ==================================================================================
// Abstract class
// -------------
//
// An error class 
// 
// ==================================================================================

// System Framework
#include "CATInputError.h"


class CAASysError: public CATInputError 
{
  public:
   
    // Declare that the class CAASysError is an error class which derives
    // from CATInpuError.
    CATDeclareError(CAASysError, CATIntputError)
  
};

#endif
