#include <string.h>
#include "iostream.h"
#include "CATMathInterval.h"
#include "CAAMyFract.h"

//-----------------------------------------------------------------
//- Object Management
//-----------------------------------------------------------------
CAAMyFract::CAAMyFract(const CATMathFunctionX * P,
                       const CATMathFunctionX * Q)
{ _P = P; _Q = Q; }

CATMathClassId CAAMyFract::IsA() const
{ return "CAAMyFract";} 

CATMathFunctionX * CAAMyFract::Duplicate() const
{ return new CAAMyFract(*this); }

CATMathFunctionX * CAAMyFract::DeepDuplicate() const
{ 
    if (_P == NULL ) return NULL;
    if (_Q == NULL ) return NULL;
    CATMathFunctionX* P = _P->Duplicate();
    CATMathFunctionX* Q = _Q->Duplicate();
    return new CAAMyFract(P, Q); 
 
    // return (this)->Duplicate(); // would result in a throw
    
}

const CATMathFunctionX * CAAMyFract::GetNumerator () const {
	return _P;
}

const CATMathFunctionX * CAAMyFract::GetDenominator () const {
	return _Q;
}
//-----------------------------------------------------------------
//- Evaluators on doubles
//-----------------------------------------------------------------
double CAAMyFract::Eval(const double & t) const
{ 
  if ( (_Q == NULL ) ||  (_P == NULL) ) 
  {
	  cout << "WARNING: one operand is NULL" << endl;
	  return 0;
  }
  double q = _Q->Eval(t); 
  if (q == 0.)
  {
    cout << "q == 0 " << endl;
    return CATMathInfinite;
  }
  return _P->Eval(t) / q;
}
