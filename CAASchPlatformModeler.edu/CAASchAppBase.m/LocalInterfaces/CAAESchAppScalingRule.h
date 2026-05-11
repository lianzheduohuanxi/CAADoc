// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAESchAppScalingRule
// Implements CATISchAppScalingRule
//
//=============================================================================
#ifndef CAAESchAppScalingRule_H
#define CAAESchAppScalingRule_H

#include "CATEASchAppScalingRule.h"

// System
#include "CATBaseUnknown.h"

class CAAESchAppScalingRule : public CATEASchAppScalingRule
{
  public:
  CATDeclareClass;

  CAAESchAppScalingRule();
  virtual ~CAAESchAppScalingRule();
  
  /**
  * Get a priority number to indicate the adjustment (moving)
  * priority of this object during scaling.  
  * @param oPriority
  *   1 to 99.  The lower the number, the higher the processing
  *   priority. For example, an object with priority 1 is processed
  *   first and will not move while connected objects adjust. 
  */
  virtual HRESULT AppGetScalingPriority (int *oPriority);

  private:

  // do not implement
  CAAESchAppScalingRule (const CAAESchAppScalingRule &);
  CAAESchAppScalingRule &operator = (const CAAESchAppScalingRule &);
};
#endif
