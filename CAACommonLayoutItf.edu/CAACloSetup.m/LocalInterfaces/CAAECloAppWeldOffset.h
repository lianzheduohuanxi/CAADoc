#ifndef CAAECloAppWeldOffset_H
#define CAAECloAppWeldOffset_H

#include "CATBaseUnknown.h"

//-----------------------------------------------------------------------

/**
 * Interface to calculate the weld offset 
 */
class CAAECloAppWeldOffset: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
     CAAECloAppWeldOffset ();
     virtual ~CAAECloAppWeldOffset ();


  virtual HRESULT GetWeldOffset(  const wchar_t* iaWeldEndStyle,
                                  const double idRunInsideRadius,
                                  const double idRunOutsideRadius,
                                  const double idBranchInsideRadius,
                                  const double idBranchOutsideRadius,
                                  const double idWeldGap,
                                  double* odWeldOffset  );


};

//-----------------------------------------------------------------------

#endif
