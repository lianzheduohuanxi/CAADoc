//COPYRIGHT DASSAULT SYSTEMES  1994 2000
// =============================================================================
//
// ABSTRACT
// --------
//	Creates a feature which holds an input and an output parameter.
//	The value of the output parameter is recomputed whenever the 
// feature is updated (with method Update()). This computation is done
// in the implementation of the interface CATIBuild (file CAALifBasis.m/src/CAAExtensionForMeasure.cpp)
//
// =============================================================================
//  Usage:
//  ------
//  	
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================
//  Main Method:
//  ------------
//			main()
//
//===========================================================================

#include <iostream.h>
#include "CATSession.h"
#include "CATLib.h"

//CAALiteralFeatures
#include "CAALifServices.h"
#include "CAALifReturnCodes.h"
#include "CAALifValuatorFeatureDef.h"

//LiteralFeatures
#include "CATIParmPublisher.h"
#include "CATIParmValuator.h"
#include "CATICkeInst.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"

//ObjectModelerBase
#include "CATIAlias.h"

void MeasureUpdate (CATICkeParmFactory* ipFact, CATIParmPublisher_var piPublisher)
{
  if(ipFact != NULL)
    {
	CATICkeParm_var spInParam = ipFact->CreateInteger("x",2);
	CATICkeParm_var spOutParam = ipFact->CreateInteger("y",3);

	// It is important (but not necessary) to aggregate those parameters especially in part context
    // Note that they could have been aggregated by the feature itself, but this is not the case yet
	CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,piPublisher,CATCke::True);
	if (!!spParameterSet)
	{
		CATIParmPublisher_var spParmPublisher = spParameterSet;
		if (!!spParmPublisher)
		{
			spParmPublisher->Append(spInParam);
			spParmPublisher->Append(spOutParam);
		}
	}    
 
	//Creation of the feature.
	CATISpecObject_var inst = CAALifValuatorFeatureDef::GetInstance (ipFact,spInParam,spOutParam);
	
		  //Retrieves the parameters factory
	  CATIParmValuator* piValuator = NULL;
	  HRESULT rc1 = inst->QueryInterface(IID_CATIParmValuator, (void**) &piValuator);
	  if (FAILED(rc1)) 
	  {
			cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
			return;
	  }



	if( NULL == piValuator)
	{
		  cout << " Error : unable to retrieve the interface CATIParmValuator on the current feature." << endl;
	}
	else
	{		  
		  //The input parameter is valuated with an odd number.
		  spInParam->Valuate(3);
		  
		  // Update of the CAAFeature
		  CATTry
		  {
				inst->Update();
		  }
		  CATCatch(CATError,error) 
		  {
				cout << "Update Error" <<endl;
				piValuator->Release();
				return;
		  }
		  CATEndTry;
		  
		  //Verification that the output value is really updated.
		  //Output expected : 99
		  CATICkeInst_var spInstParam = spOutParam->Value();
		  int outValue = spInstParam->AsInteger();
		  cout << " Output parameter value is: " << outValue << endl;
		  
		//The input parameter is valuated with an even number.
		spInParam->Valuate(4);
		
		// Now we update the CAAFeature
		  CATTry
		  {
				inst->Update();
		  }
		  CATCatch(CATError,error) 
		  {
				cout << "Update Error" <<endl;
				piValuator->Release();
				return;
		  }
		  CATEndTry;		
		// And we verify that the output value is really updated.
		//Output expected : 100	
		spInstParam = spOutParam->Value();
		outValue = spInstParam->AsInteger();
		cout << " Output parameter value is: " << outValue << endl;
		
		piValuator->Release();
	}
    }
}


int main (int argc, char** argv)
{
	int rc = 0;
	if( argc <= 1 )
	{
		cout << " Catalog absolute name is expected in input of this program " <<
				endl;
	}
	cout << " *******************************" << endl; 
	cout << " * Measure implementation example *" << endl;
	cout << " *******************************" << endl; 
	
	CAALifServices services;
	
	// Initialize the session
	rc = services.CAALifInitSession ();
	if( rc != CAALifOk )
		return rc;

	// Retrieve the parameter factory 
	CATIContainer* piContainer = NULL;		
	HRESULT hr = services.CAALifCreateInstanceContainer( &piContainer );
    if( FAILED(hr) )
        return CAALifKO;	
    
	  //Retrieves the parameters factory
	  CATICkeParmFactory* piFact = NULL;
	  HRESULT rc1 = piContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);
	  if (FAILED(rc1)) 
	  {
			cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
			piContainer->Release();
			return CAALifParmFactoryError;
	  }

	if( argc == 2 )
	  rc = CAALifValuatorFeatureDef::Start (piContainer, argv[1]);
	if( argc <=1)
	  rc = CAALifValuatorFeatureDef::Start (piContainer, "CAA2_CAALifFeatCatalog.CATfct");
	
	if( rc != CAALifOk )
			return rc;
	
    CATIParmPublisher* piPublisher = NULL;
    rc = services.CAALifRetrievePublisherFromCurrentDoc( &piPublisher );
    if (FAILED(rc) || !piPublisher)
      {
        cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
        return CATCke::False;
      }

	MeasureUpdate( piFact, piPublisher );

	CAALifValuatorFeatureDef::End ();
	
	piPublisher->Release();
	piFact->Release();
	piContainer->Release();

	// Close the session and environment
	rc = services.CAALifCloseSession ();
	
	return rc;
};
