//COPYRIGHT DASSAULT SYSTEMES  1994 2000
// =============================================================================
//
// ABSTRACT
// --------
// This class is the factory that allows the creation of a feature that behaves like a measure.
//
// =============================================================================
//  Usage:
//  ------
//	CAALifValuatorFeatureDef::Start(...), creates the Startup of the feature.
//  CAALifValuatorFeatureDef::GetInstance(...) returns an instance of the CAALifFeature
// feature and sets its attributes.
// CAALifValuatorFeatureDef::End(...), cleans the class.
//   
// 	
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================
//  Main Method:
//  ------------
//				None
//
//===========================================================================
/** @quickReview tvq 2001:06:25 */


#include "CAALifValuatorFeatureDef.h"

// ObjectSpecsLegacy
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATOsmSUHandler.h"

#include "iostream.h" 


CATOsmSUHandler *CAALifValuatorFeatureDef::_spSUHandler = NULL;
CATISpecObject_var CAALifValuatorFeatureDef::_spCAAFeature;


int CAALifValuatorFeatureDef::Start (CATIContainer* ipiContainer, 
		const char* iCatalogName)
{
	CATUnicodeString startupType( "CAALifFeature" );	

		// the object that encapsulates a startup
	_spSUHandler = new CATOsmSUHandler(startupType, "SAMPLES", iCatalogName);


	CATISpecObject_var hStartupFeat;

		// let's retrieve the startup
	_spSUHandler->RetrieveSU(hStartupFeat);

	if (!hStartupFeat)
		return CAALifKO;

	_spCAAFeature = hStartupFeat;

	return CAALifOk;
}

void CAALifValuatorFeatureDef::End() 
{
	_spCAAFeature = NULL_var;
	if (_spSUHandler)
		delete _spSUHandler;
	_spSUHandler = NULL;
}


CATISpecObject_var CAALifValuatorFeatureDef::GetStartUp() 
{
  return _spCAAFeature;
}

CATISpecObject_var CAALifValuatorFeatureDef::GetInstance
(const CATICkeParmFactory_var &ispFact,
 const CATICkeParm_var &iInParameter,
 const CATICkeParm_var &iOutParameter)
{
	//Instance Creation and setting the parameters in the input and output attributes.
	//--------------------------------------------------------------------------------
	CATISpecObject_var spInst = GetStartUp()->Instanciate("CAALifValuatorFeature",ispFact);
	spInst->Release();

	if( NULL_var != spInst )
	{
		// Valuates the InAttribute
		CATISpecAttrAccess * piSpecAttrAccessOnIn = NULL; 
		HRESULT rc = spInst->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnIn);
		if ( SUCCEEDED(rc) ) 
		{ 
			if (NULL != piSpecAttrAccessOnIn)
			{
				// Gets a pointer on the in attribute
				CATISpecAttrKey * piSpecAttrKeyOnIn = NULL;    
				piSpecAttrKeyOnIn = piSpecAttrAccessOnIn->GetAttrKey("InAttribute");
       
				if ( NULL != piSpecAttrKeyOnIn )
				{
					piSpecAttrAccessOnIn->SetSpecObject(piSpecAttrKeyOnIn,iInParameter);
					piSpecAttrKeyOnIn->Release();
					piSpecAttrKeyOnIn = NULL;
				}

				piSpecAttrAccessOnIn->Release();
				piSpecAttrAccessOnIn = NULL;

			}
		}
		
		//Valuates the OutAttribute
		CATISpecAttrAccess * piSpecAttrAccessOnOut = NULL; 
		rc = spInst->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnOut);
		if ( SUCCEEDED(rc) ) 
		{ 
			if (NULL != piSpecAttrAccessOnOut)
			{
				// Gets a pointer on the out attribute
				CATISpecAttrKey * piSpecAttrKeyOnOut = NULL;    
				piSpecAttrKeyOnOut = piSpecAttrAccessOnOut->GetAttrKey("OutAttribute");
       
				if ( NULL != piSpecAttrKeyOnOut )
				{
					piSpecAttrAccessOnOut->SetSpecObject(piSpecAttrKeyOnOut,iOutParameter);
					piSpecAttrKeyOnOut->Release();
					piSpecAttrKeyOnOut = NULL;
				}

				piSpecAttrAccessOnOut->Release();
				piSpecAttrAccessOnOut = NULL;

			}
		}

		// Now we create the inverse 
		CATIParmValuator_var spValuator = spInst;
		if( NULL_var == spValuator)
		{
			  cout << " Error : unable to retrieve the interface CATIParmValuator on the current feature." << endl;
		}
		else
		{
			  //The output parameter is valuated by the feature viewed as a
			  //valuator.
			  //If you want a persistent link update between the parameter iOutParameter and its valuator,
			  //put the 2nd argument to 1.
			  iOutParameter->SetRelation (spValuator,1);
		}
	}


	return spInst;
}


