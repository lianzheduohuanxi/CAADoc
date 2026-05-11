// COPYRIGHT DASSAULT SYSTEMES  1994 2000

// Local Framework 
#include "CAALifExpressionVolatile.h"
#include <iostream.h>

// ObjectModelerBase
#include "CATIContainer.h"

// LiteralFeatures 
#include "CATCke.h"
#include "CATCkeBoolean.h"
#include "CATICkeParmFactory.h"

// Local Framework 
#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

// ===========================================================================
//
// ABSTRACT 
// --------
//
// Illustrates how to create and evaluate expressions. 
// Refer to the CAA articles below for more information:
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALifExpressionMain
//  
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================


int main (int argc, char** argv)
{
	  // Initialize the session
	  HRESULT rc = 0;
	  CAALifServices services;
	  CATCke::Boolean rcbool1;
	  
	  rc = services.CAALifInitSession ();
	  if (rc != CAALifOk )
			return rc;
	  
	  CATIContainer* piContainer = NULL;
	  rc = services.CAALifCreateInstanceContainer(&piContainer);
	  if( FAILED(rc) )
			return CAALifKO;	
	  
	  //Retrieves the parameters factory
	  CATICkeParmFactory* piFact = NULL;
	  rc = piContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);
	  if (FAILED(rc)) 
	  {
			cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
			piContainer->Release();
			return CAALifParmFactoryError;
	  }		
	  
	  // Create volatile parameters
	  rcbool1 = CAALifExpressionVolatile();
	  
	  piContainer->Release();
	  piFact->Release();
	  	  
	  cout << endl;
	  cout << " CAALifExpressionVolatile: " << rcbool1 << endl;

	  rc = services.CAALifCloseSession ();
	  
	  return rc;
}


