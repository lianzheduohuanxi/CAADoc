#ifndef CAASysOperator_H
#define CAASysOperator_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
// ==================================================================================
// Abstract class
// -------------
//
// Operator class definition for demonstrate error mechanism usage
// 
// ==================================================================================

// System Framework
#include "IUnknown.h"  // for HRESULT

class CAASysOperator 
{
  public:

    CAASysOperator();
    virtual ~CAASysOperator();

    // Divide 
    // -------
    // This method returns CATReturnSuccess if the division is possible
    // (ie iDivisor is not null), else CATReturnFailure
    //
    HRESULT Divide    (float iDividend, float iDivisor, float * oResult);

    // SquareRoot
    // ----------
    // This method returns a CATSysError if iValue is negatif else
    // return CATReturnSuccess. 
    //
    // The error contains a non-composite NLS message 
    //
    HRESULT SquareRoot(float iValue, float * oResult);

    // Subtraction
    // ----------
    // This method returns a CATSysError if iFirst is smaller that iSecond 
    // else return CATReturnSuccess. 
    //
    // The Error contains a composite NLS Message: A request, Diagnostic and 
    // Advice messages.
    //
    HRESULT Subtraction(float iFirst, float iSecond, float * oResult);
  
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysOperator(const CAASysOperator &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysOperator & operator = (const CAASysOperator &iObjectToCopy);
};

#endif
