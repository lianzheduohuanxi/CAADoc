#include "CAAGenerateResultsUserFunction.h"
#include "CATICheckReport.h"
#include "CATCkeEvalContext.h"
#include "CATIParmDictionary.h"
#include "CATCkeGlobalFunctions.h"
#include "CATListOfCATUnicodeString.h"
#include "CATITypeDictionary.h"

#include "iostream.h"
// Evaluation

void GenerateResults(				   CATCkeListOfParm ipArguments,
				   const CATICkeParm_var &ispReturnValue,
				   const CATCkeEvalContext *iEvaluationContext )
{
	// Retrieve parameters (inputs and output)
	CATICkeParm_var spParameterA =  (*ipArguments)[1];
	CATICkeParm_var spParameterB =  (*ipArguments)[2];
		
	// Retrieve the parameter input values
	CATICheckReport_var checkreport = spParameterA->Value()->AsObject ();
	CATISpecObject_var hole = spParameterB->Value()->AsObject ();

	if (!!hole)
	{
		// I simulate an algorithm : here I find the father of Hole (PartBody)
		CATISpecObject_var father = hole->GetFather();
		CATListValCATIInstance_var listoftuple;
		if (!! father)
		{
			CATIInstance_var partbody = father;
			if (NULL_var != partbody)
				listoftuple.Append (partbody);
			father->Release();
			father = NULL_var;
		}

	
		if (NULL_var != checkreport)
		{
			// I Stop to generate automatically the tuple
			checkreport->StopGenerateTuple();
			// I fill the report with father
			checkreport->AddTupleFailed(listoftuple);
			ispReturnValue->Valuate(CATCke::True);
		
		}
		else
			ispReturnValue->Valuate(CATCke::False);
	}
}
  


//-----------------------------------------------------------------------------
// CATIAddLibrary
//-----------------------------------------------------------------------------
CATImplementClass(CAAGenerateResultsUserFunction, Implementation, CATBaseUnknown, CATNull);

#include <TIE_CATIAddLibrary.h>
TIE_CATIAddLibrary(CAAGenerateResultsUserFunction);

// Add a function to the dictionary
void CAAGenerateResultsUserFunction::Add()
{
	// A user function is defined by:
	// 1 - its name: "GenerateResults"
	// 2 - its return type: a boolean    
	// 3 - its arguments the check and Hole
	// 4 - its evaluator i.e the function which computes the result
	
	CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();
	
	// Get the type descriptor corresponding to a real.
	CATICkeType_var spType = NULL_var;
	spType = spParmDictionary->GetBooleanType();
	if( NULL_var != spType )
	{
		CATICkeFunctionFactory_var funcFactory = CATCkeGlobalFunctions::GetFunctionFactory();
		CATICkeSignature_var spSign = funcFactory->CreateFunction ("GenerateResults",
			spType,
			GenerateResults);		
		
		spSign->AddArgument (funcFactory->CreateArg ("iCheck",spParmDictionary->GetFeatureType()));		
		spSign->AddArgument (funcFactory->CreateArg ("iHole",spParmDictionary->GetFeatureType()));		
		
		//Once created this function can be put inside a package.
		//Packages are made for structuring USER FUNCTIONS and TYPES.
		//This name also is used to find the CATNls file containing the NLS name of this 
		// package (Only useful for interactive application).
		CATUnicodeString packageName = "CAAKnowledgeExpert";        
		CATITypeDictionary_var spTypeDic = CATGlobalFunctions::GetTypeDictionary();
		
		if( spTypeDic == NULL_var)
			return;
		
		HRESULT rc;
		CATListOfCATUnicodeString listPackages;
		rc = spTypeDic->ListPackages(listPackages);
		if (SUCCEEDED(rc))
		{
			CATUnicodeString translation;
			int packageExists;
			
			packageExists = listPackages.Locate(packageName);
			if (packageExists == 0)
			{
				CATListOfCATUnicodeString iListOfPrerequisites;
				if (SUCCEEDED(rc))
					rc = spTypeDic->AddPackage( packageName, iListOfPrerequisites );
			}
			
			spTypeDic->AddMethodForPackage( spSign, packageName );
		}
	}    
	return;
}

//-----------------------------------------------------------------------------
// CATICreateInstance
//-----------------------------------------------------------------------------
CATImplementClass(CAAGenerateResultsUserFunctionExt, CodeExtension, CATBaseUnknown, CAAGenerateResultsUserFunction);

#include <TIE_CATICreateInstance.h>
TIE_CATICreateInstance(CAAGenerateResultsUserFunctionExt);

HRESULT __stdcall CAAGenerateResultsUserFunctionExt::CreateInstance (void **oPPV)
{
	*oPPV = new CAAGenerateResultsUserFunction();
	return S_OK;
}

