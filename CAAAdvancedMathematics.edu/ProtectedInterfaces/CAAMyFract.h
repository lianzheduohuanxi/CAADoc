#ifndef MyFraction_h
#define MyFraction_h

// COPYRIGHT DASSAULT SYSTEMES 2004

#include "CAAMyFraction.h"
#include "CATMathFunctionX.h"

class ExportedByCAAMyFraction CAAMyFract : public CATMathFunctionX
{
 public:
  //-----------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------
  CAAMyFract(const CATMathFunctionX *P, const CATMathFunctionX *Q);
  
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
  const CATMathFunctionX *GetNumerator   () const;
  const CATMathFunctionX *GetDenominator () const;

  CATMathClassId IsA() const;  
  double Eval(const double & t) const;
 
  private:

  const CATMathFunctionX *_P, *_Q;
};
#endif
