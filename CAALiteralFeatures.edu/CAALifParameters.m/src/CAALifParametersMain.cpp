// COPYRIGHT DASSAULT SYSTEMES  1994 2000

// Local Framework 
#include "CAALifParametersPersistent.h"
#include "CAALifParametersVolatile.h"
#include "CAALifParametersRights.h"
#include "CAALifParametersMani.h"
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
// Illustrates how to create and manage all types of parameters as well as 
// manipulators. 
// Refer to the CAA articles below for more information:
//   * CAALifParametersPersistent.cpp -> "Using Persistent Parameters"
//   * CAALifParametersVolatile.cpp -> Using Volatile Parameters"
//   * CAALifParametersRights.cpp -> "Specifying Parameter Access Rights"
//   * CAALifParametersMani.cpp -> "Using Manipulators"
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALitParametersMain
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
	  CATCke::Boolean rcbool1, rcbool2, rcbool3, rcbool4, rcbool5;
	  
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
	  
	  // Create persistent parameters
	  rcbool1 = CAALifParametersPersistent(piFact, services);
	  
	  // Create volatile parameters
	  rcbool2 = CAALifParametersVolatile();
	  
	  // Manage parameter rights
	  rcbool3 = CAALifParametersRights(piFact, services);
	  
	  // Using manipulators
	  rcbool4 = CAALifParametersMani(piFact, services);

      rcbool5 = CAALifParametersPersistentMani(piFact, services);
	  
	  piContainer->Release();
	  piFact->Release();
	  	  
	  cout << endl;
	  cout << " CAALifParametersPersistent: " << rcbool1 << endl;
	  cout << " CAALifParametersVolatile: " << rcbool2 << endl;
	  cout << " CAALifParametersRights: " << rcbool3 << endl;
	  cout << " CAALifParametersMani: " << rcbool4 << endl;
	  cout << " CAALifParametersPersistentMani: " << rcbool5 << endl;

	  rc = services.CAALifCloseSession ();
	  
	  return rc;
}


