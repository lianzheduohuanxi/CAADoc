// COPYRIGHT DASSAULT SYSTEMES  2002

// CAAOptimizationInterfaces.edu headers
#include "CAAPeoUserFactory.h"
#include "CATOsmSUHandler.h"
#include "CAAPeoUserAlgoFeatureDefines.h" // catalog name, start up name, atributes name ...

// C++ streams
#include <iostream.h>

// ObjectSpecsModeler headers
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

CATIOptAlgorithm_var CAAPeoUserFactory::CreateUserAlgorithm(CATIContainer *iContainer)
{
	/*----------------------------*/
	/* Accessing the User catalog */
	/*----------------------------*/
	
	cerr << "\n\nInstanciating user algo start up ... ";
	
	CATUnicodeString clientId("SAMPLES");
	CATUnicodeString userCatalogName(UserCatalogName);
	CATUnicodeString peoUserAlgoSUType(UserAlgoSUType);
	CATOsmSUHandler CAAAlgoHandler(UserAlgoSUType, clientId, UserCatalogName);

	
	/*-------------------------------------*/
	/*  Instanciate the retrieved start up */
	/*-------------------------------------*/
	CATISpecObject_var spUserAlgoInst = NULL_var;
	CAAAlgoHandler.Instanciate(spUserAlgoInst, iContainer, NULL); 

	if(!!spUserAlgoInst)
	{
		/*-----------------------------------------------*/
		/*  Initialize the retrieved start up attributes */
		/*-----------------------------------------------*/

		CATISpecAttrAccess_var spSAA = spUserAlgoInst;
		if(!!spSAA)
		{
			// Valuates the NbUpdateMax attribute
			CATISpecAttrKey * piSpecAttrKeyOnNbUpdateMax = NULL;    
			piSpecAttrKeyOnNbUpdateMax = spSAA->GetAttrKey(UserAlgoNbUpdatesMaxSetting);

			if ( NULL != piSpecAttrKeyOnNbUpdateMax )
			{
				spSAA->SetInteger(piSpecAttrKeyOnNbUpdateMax,200);
				piSpecAttrKeyOnNbUpdateMax->Release();
				piSpecAttrKeyOnNbUpdateMax = NULL;
			}

			// Valuates the MaxTime attribute
			CATISpecAttrKey * piSpecAttrKeyOnMaxTime = NULL;    
			piSpecAttrKeyOnMaxTime = spSAA->GetAttrKey(UserAlgoMaxTimeSetting);

			if ( NULL != piSpecAttrKeyOnMaxTime)
			{
				spSAA->SetInteger(piSpecAttrKeyOnMaxTime,5);
				piSpecAttrKeyOnMaxTime->Release();
				piSpecAttrKeyOnMaxTime = NULL;
			}
		}

		CATIOptAlgorithm_var userAlgo = spUserAlgoInst;
		if(!!userAlgo)
		{
			return userAlgo;					
		}
		else
		{
			cerr << "\n\nError : start up instance does not have a CATIOptAlgorithm behaviour";
		}

	}
	else
	{
		cerr << "KO (instanciation of the start up failed)";
	}


	return NULL_var;

}






