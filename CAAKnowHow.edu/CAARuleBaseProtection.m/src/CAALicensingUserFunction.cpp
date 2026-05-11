#include "CAALicensingUserFunction.h"
#include "CATCkeEvalContext.h"
#include "CATIParmDictionary.h"
#include "CATCkeGlobalFunctions.h"
#include "CATListOfCATUnicodeString.h"
#include "CATITypeDictionary.h"


// Evaluation

void TestLicensing(
				   CATCkeListOfParm ipArguments,
				   const CATICkeParm_var &ispReturnValue,
				   const CATCkeEvalContext *iEvaluationContext )
{	
	// Simulation of Licensing Test
	//if (!License is OK)
	//{
		// Send an error with a comment and a severity
		if (iEvaluationContext)
			iEvaluationContext->SendError("You must Install License",CATKWEErrorSeverity::Information);
	    // Valuate False to forbide use of check or rule which included this user function
		if (!!ispReturnValue)
			ispReturnValue->Valuate(CATCke::False);
	//}
	//else
	if (!!ispReturnValue)
		ispReturnValue->Valuate(CATCke::True);

}
  


//-----------------------------------------------------------------------------
// CATIAddLibrary
//-----------------------------------------------------------------------------
CATImplementClass(CAALicensingUserFunction, Implementation, CATBaseUnknown, CATNull);

#include <TIE_CATIAddLibrary.h>
TIE_CATIAddLibrary(CAALicensingUserFunction);

// Add a function to the dictionary
void CAALicensingUserFunction::Add()
{
	// A user function is defined by:
	// 1 - its name: "Hypotenuse"
	// 2 - its return type: a real    
	// 3 - its arguments
	// 4 - its evaluator i.e the function which computes the result
	
	CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();
	
	// Get the type descriptor corresponding to a real.
	CATICkeType_var spType = NULL_var;
	spType = spParmDictionary->GetBooleanType();
	if( NULL_var != spType )
	{
		CATICkeFunctionFactory_var funcFactory = CATCkeGlobalFunctions::GetFunctionFactory();
		CATICkeSignature_var spSign = funcFactory->CreateFunction ("LicensingTest",
			spType,
			TestLicensing);		
		
		//Once created this function can be put inside a package.
		//Packages are made for structuring USER FUNCTIONS and TYPES.
		//This name also is used to find the CATNls file containing the NLS name of this 
		// package (Only useful for interactive application).
		CATUnicodeString packageName = "CATPackageMethodCAAKhw";        
		CATITypeDictionary_var spTypeDic = CATGlobalFunctions::GetTypeDictionary();
		
		if( spTypeDic == NULL_var)
			return;
		
		HRESULT hr;
		CATListOfCATUnicodeString iListOfPrerequisites;
		hr = spTypeDic->AddPackage( packageName, iListOfPrerequisites );
		if(SUCCEEDED(hr) )
		{
			spTypeDic->AddMethodForPackage( spSign, packageName );
		}
	}    
	return;
}

//-----------------------------------------------------------------------------
// CATICreateInstance
//-----------------------------------------------------------------------------
CATImplementClass(CAALicensingUserFunctionExt, CodeExtension, CATBaseUnknown, CAALicensingUserFunction);

#include <TIE_CATICreateInstance.h>
TIE_CATICreateInstance(CAALicensingUserFunctionExt);

HRESULT __stdcall CAALicensingUserFunctionExt::CreateInstance (void **oPPV)
{
	*oPPV = new CAALicensingUserFunction();
	return S_OK;
}

