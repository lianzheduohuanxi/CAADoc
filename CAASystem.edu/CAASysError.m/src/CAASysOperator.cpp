// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAASysOperator.h"

// Local Framework
#include "CAASysError.h"

// Mathematics Framework
#include "CATMath.h"

// -----------------------------------------------------------------------

CAASysOperator::CAASysOperator() 
{
  printf("Operator class created\n");
}

// -----------------------------------------------------------------------

CAASysOperator::~CAASysOperator() 
{
  printf("Operator class destroyed\n");
}

// -----------------------------------------------------------------------

HRESULT CAASysOperator::Divide(float iDividend, float iDivisor, float * oResult)
{
  if ( 0.0 == iDivisor )
  {
    return(CATReturnFailure);
  } else 
  {
    *oResult = iDividend/iDivisor;
    return(CATReturnSuccess);
  };
}


// -----------------------------------------------------------------------

HRESULT CAASysOperator::SquareRoot(float iValue, float * oResult) 
{

  if ( iValue <0.0 ) 
  {
    // The square root is impossible

    // Instanciate an error class:
    //
    //   SquareRootERR_1001   :is the key of the message
    //   CAASysError          :is the name of the NLS message catalog
    //                          that you find in the CNext/resources/msgcatalog 
    //  
    CAASysError * pError = new CAASysError("SquareRootERR_1001", "CAASysError");
  
    // The english error message is: 
    //   "The square root of iValue is impossible "
    // So it contains one parameter that you give to the error.
    // 

    // The float parameter is translate in CATUnicodeString
    CATUnicodeString param;
    param.BuildFromNum(iValue);
  
    // Allows to construct a parametrizable NLS message
    int nbparameter = 1 ;
    pError->SetNLSParameters(nbparameter, &param);
  
    // The error is given to  the Error manager     
    return(CATReturnError(pError));
  
  } else 
  {
    *oResult= CATSqrt(iValue);
    return(CATReturnSuccess);
  };

}


HRESULT CAASysOperator::Subtraction(float iFirst, float iSecond, float * oResult) 
{
  if ( iSecond< iFirst ) 
  {
     *oResult= iFirst - iSecond ;
     return(CATReturnSuccess);    
  }else
  {
    // The subtraction is negative, it's an error

    // Instanciate an error class:
    //
    //   SubtractionERR_1002    :is the key of the message
    //   CAASysError            :is the name of the NLS message catalog
    //                          that you find in the CNext/resources/msgcatalog 
    //  
    CAASysError * pError = new CAASysError("SubtractionERR_1002","CAASysError");
  
    // For this error the message is composed of a 
    //  - Request message   : Describe the attempted action that fails
    //  - Diagnostic message: Describe the cause of the failure
    //  - Advice message    : Describe what to do for the attempted action to success
    //                         or give a by-pass.
    //

    // The english Request message is 
    //   "Subtraction 2 parameters, but the first parameter must be greater than 
    //    the second parameter, so the result is positiv"
    // So it contains zero parameter.
    // 
    // the following instruction is not necessary 
    // pError->SetNLSRequestParams(nbparameter, &param); 
    
    // The english Diagnostic message is 
    //   "The first parameter, /p1, is smaller than the second, /p2"
    // So it contains two parameter that you give to the error.
    // 
    int nbparameter = 2 ;
    CATUnicodeString param1, param2;
    param1.BuildFromNum(iFirst);
    param2.BuildFromNum(iSecond);
    pError->SetNLSDiagnosticParams(nbparameter, &param1, &param2);


    // The english Advice message is 
    //   "Inverse the 2 parameters and multiply the result by -1: that gives /p1"
    // So it contains one parameter that you give to the error.
    // 
    nbparameter = 1 ;
    CATUnicodeString param3 ;
    param3.BuildFromNum(iFirst - iSecond);
    pError->SetNLSAdviceParams(nbparameter, &param3);

    // The error is given to  the Error manager     
    return(CATReturnError(pError));
  }
}

