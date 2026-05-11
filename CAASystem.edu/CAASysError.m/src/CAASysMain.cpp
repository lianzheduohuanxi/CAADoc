// COPYRIGHT DASSAULT SYSTEMES 2000

//======================================================================================
//  Abstract of the sample
//  -----------------------
//  
//  This sample shows how to create, instantiate, retrieve and decode an error.
//
//       - The CAASysError    class is the  error class
//       - The CAASysOperator class instanciate error 
//       - The main program shows how retrieve and decode an error. 
//         
//     
//          1- Use FAILED method 
//          2- Use SUCCEEDED method
//          3- Retrieve and Decode an error with a simple NLS Message
//          4- Retrieve and Decode an error with a composite NLS Message
//
//=====================================================================
//  How to launch the sample :
//  -------------------------
//
//  Type:
//    CAASysError
//
//  Return Code:
//     0 : OK  
    
//=====================================================================

// Object which instantiates an error instance
#include "CAASysOperator.h"

// the local class error
#include "CAASysError.h"

//C++ standard library
#include <iostream.h>

int main() 
{
  cout << endl << "The CAASysError program begins ...."<< endl << endl;
  
  CAASysOperator MyOperator ;

  // -----------------
  // Use FAILED method
  // -----------------
  cout << endl << "Try to divide 10 by 0: " << endl;
  
  float result ;
  HRESULT status = MyOperator.Divide(10.f, 0.f, &result);

  if ( FAILED(status) ) 
  {
    cout <<"Cannot divise by Zero"<< endl;
  } else 
  {
    cout << "The operator is very Strange"<<  endl;  
  }

  // --------------------
  // Use SUCCEEDED method
  // --------------------
  cout << endl << "Try to divide 10 by 2 :" << endl;

  float result1 ;
  status = MyOperator.Divide(10.f, 2.f, &result1);

  if ( SUCCEEDED(status) ) 
  {
    cout << "10/2="<< result1 << endl;  
  } else 
  {
    cout << "The operator is very Strange"<< endl; 
  }


  // -------------------------------------------------------
  // Retrieve and Decode an error class with a simple message
  // -------------------------------------------------------
  cout << endl << "Try to have the square root of -9" << endl;
  
  float SquareRoot = 0;
  status = MyOperator.SquareRoot(-9, &SquareRoot);
  if (SUCCEEDED(status)) 
  {
     cout << "The operator is very Strange"<< endl; 
  }else
  {
     CATError * pError = CATError::CATGetLastError(status);
     if ( NULL != pError )
     {
        HRESULT rc = pError->GetReturnCode();
        
        cout <<"  HRESULT   : "<<  rc << endl;
        
        // The name of the NLS message catalog
        if ( NULL != pError->GetMsgCatalog() )
        {
           cout <<"  Catalogue : "<<  pError->GetMsgCatalog() << endl;
        }

        // The key of the  NLS message: SquareRootERR_1001 
        if ( NULL != pError->GetMsgId() )
        {
           cout <<"  Key       : "<<  pError->GetMsgId() << endl;
        }

        // The error identifier (an integer) : 1001
        cout <<"  GetId     : "<<  pError->GetId() << endl;

        // Retrieves the NLS Message 
        CATUnicodeString ErrorMessage = pError->GetNLSMessage() ;
        cout <<"  Message   : "<<  ErrorMessage.ConvertToChar() << endl;
        
        pError->Release();
     } else
     {
        cout << "No error class instantiate "<< endl;
     }
  }

  // -------------------------------------------------------
  // Retrieve and Decode an error class with 
  //   a Request,Diagnostic,Advice message
  // -------------------------------------------------------
 
  cout << endl << "Try to substract 7 to 10 " << endl;
  
  float PositiveSubtraction = 0;
  status = MyOperator.Subtraction(7.f,10.f, &PositiveSubtraction);
  if (SUCCEEDED(status)) 
  {
     cout << "The operator doesn't follow the specifications "<< endl; 
  }else
  {
     CATError * pError = CATError::CATGetLastError(status);
     if ( NULL != pError )
     {
        HRESULT rc = pError->GetReturnCode();
        
        cout <<"  HRESULT   : "<<  rc << endl;
        
        // The name of the NLS message catalog
        if ( NULL != pError->GetMsgCatalog() )
        {
           cout <<"  Catalogue : "<<  pError->GetMsgCatalog() << endl;
        }

        // The key of the  NLS message: SubtractionERR_1001 
        if ( NULL != pError->GetMsgId() )
        {
           cout <<"  Key       : "<<  pError->GetMsgId() << endl;
        }

        // The error identifier ( an integer ): 1001
        cout <<"  GetId     : "<<  pError->GetId() << endl;

        // Retrieves the NLS Message: wich is the concatenation of the
        // request, Diagnostic and Advice messages
        CATUnicodeString ErrorMessage = pError->GetNLSMessage() ;
        cout <<"  Complete Message   : "<<  endl << ErrorMessage.ConvertToChar()<<endl<<endl;
        
        // Retrieves the Request message
        CATUnicodeString RequestMessage = pError->GetNLSRequest() ;
        cout <<"  Request Message    : "<<  RequestMessage.ConvertToChar() << endl;
        
        // Retrieves the Diagnostic message
        CATUnicodeString DiagnosticMessage = pError->GetNLSDiagnostic() ;
        cout <<"  Diagnostic Message : "<<  DiagnosticMessage.ConvertToChar() << endl;

        // Retrieves the Advice message
        CATUnicodeString AdviceMessage = pError->GetNLSAdvice() ;
        cout <<"  Advice Message     : "<<  AdviceMessage.ConvertToChar() << endl;

        pError->Release();
        
     } else
     {
        cout << "No error class instantiate "<< endl;
     }
  }

  cout << endl << "The CAASysError program is finished ...."<< endl << endl;
  
  return(0);
}

