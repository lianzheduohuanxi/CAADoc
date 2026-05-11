// COPYRIGHT DASSAULT SYSTEMES  2000

#include <CAALifFormula.h>
#include <CAALifRuleCheck.h>
#include <iostream.h>

// ObjectModelerBase
#include "CATIContainer.h"

// LietralFeatures
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATICkeType.h"
#include "CATICkeInst.h"
#include "CATICkeMagnitude.h"
#include "CATCke.h"

#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

// ===========================================================================
//
// ABSTRACT 
// --------
//
// Illustrates how to create and manage relations 
// Refer to the CAA article "Creating relations" for more information
//
// ===========================================================================

int main (int argc, char** argv)
{
	  CAALifServices services;
	  
	  // Initialize the session
	  int rc = 0;
	  rc = services.CAALifInitSession ();
	  if( rc != CAALifOk )
			return rc;

	  CATIContainer* piContainer = NULL;
	  HRESULT hr = services.CAALifCreateInstanceContainer(&piContainer);
      if( FAILED(hr) )
          return CAALifKO;
	  
	  CATIParmPublisher* piRoot = NULL;
	   hr = services.CAALifRetrievePublisherFromCurrentDoc(&piRoot);
      if( FAILED(hr) )
          return CAALifKO;
	  
	  
	  // you can create a formula under relationset
	  CAALifFormula(piRoot);
	  // you can create rules & checks under relationset
	  CAALifRuleCheck(piRoot);
		
	  piRoot->Release();	
	  piContainer->Release();
	
	  rc = services.CAALifCloseSession ();
	  
	  return rc;
}


