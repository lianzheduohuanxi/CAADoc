#include "CAAFindAttributeRealUserFunction.h"
#include "CATIGenericRuleBaseComponent.h"
#include "CATICheckReport.h"
#include "CATCkeEvalContext.h"
#include "CATIParmDictionary.h"
#include "CATCkeGlobalFunctions.h"
#include "CATListOfCATUnicodeString.h"
#include "CATITypeDictionary.h"

#include "iostream.h"
// Evaluation

void CAAFindAttributeReal(				   CATCkeListOfParm ipArguments,
				   const CATICkeParm_var &ispReturnValue,
				   const CATCkeEvalContext *iEvaluationContext )
{
	// Retrieve parameters (inputs and output)
	CATICkeParm_var spParameterA =  (*ipArguments)[1];
	CATICkeParm_var spParameterB =  (*ipArguments)[2];
		
	// Retrieve the parameter input values
	CATIGenericRuleBaseComponent_var genericrulebasecomponent = spParameterA->Value()->AsObject ();
	CATUnicodeString parametername = spParameterB->Value()->AsString ();

	CATIInstance_var instance = genericrulebasecomponent;

	// We suppose that parmeter was added with parameterexplorer or with Rules or Checks panel definition.
	// So the parameter wad added with an attribute.
	if (!!instance)
	{
		CATIValue* val = instance->GetValue(parametername);
		if (val)
		{
			double toto = 0.0;
			val->AsReal(toto);
			val->Release();
			ispReturnValue->Valuate(toto);
		}
	}
}
  


//-----------------------------------------------------------------------------
// CATIAddLibrary
//-----------------------------------------------------------------------------
CATImplementClass(CAAFindAttributeRealUserFunction, Implementation, CATBaseUnknown, CATNull);

#include <TIE_CATIAddLibrary.h>
TIE_CATIAddLibrary(CAAFindAttributeRealUserFunction);

// Add a function to the dictionary
void CAAFindAttributeRealUserFunction::Add()
{
	// A user function is defined by:
	// 1 - its name: "CAAFindAttributeReal"
	// 2 - its return type: a Real    
	// 3 - its arguments the component and the name of parameter.
	// 4 - its evaluator i.e the function which computes the result
	cout<<" I add my function "<<endl;
	CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();
	
	// Get the type descriptor corresponding to a real.
	CATICkeType_var spType = NULL_var;
	spType = spParmDictionary->GetRealType();
	if( NULL_var != spType )
	{
		CATICkeFunctionFactory_var funcFactory = CATCkeGlobalFunctions::GetFunctionFactory();
		CATICkeSignature_var spSign = funcFactory->CreateFunction ("FindAttributeReal",
			spType,
			CAAFindAttributeReal);		
		
		spSign->AddArgument (funcFactory->CreateArg ("iComponent",spParmDictionary->GetFeatureType()));		
		spSign->AddArgument (funcFactory->CreateArg ("iParameterName",spParmDictionary->GetStringType()));		
		
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
CATImplementClass(CAAFindAttributeRealUserFunctionExt, CodeExtension, CATBaseUnknown, CAAFindAttributeRealUserFunction);

#include <TIE_CATICreateInstance.h>
TIE_CATICreateInstance(CAAFindAttributeRealUserFunctionExt);

HRESULT __stdcall CAAFindAttributeRealUserFunctionExt::CreateInstance (void **oPPV)
{
	*oPPV = new CAAFindAttributeRealUserFunction();
	return S_OK;
}

