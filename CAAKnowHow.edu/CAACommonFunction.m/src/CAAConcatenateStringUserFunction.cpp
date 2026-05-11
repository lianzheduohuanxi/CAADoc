// COPYRIGHT DASSAULT SYSTEMES 2001

//
// example : user function with variable argument
//

#include "CAAConcatenateStringUserFunction.h"

/*
// Evaluation

void CAAConcatenateString(CATCkeListOfParm l,const CATICkeParm_var &res,const CATCkeEvalContext *pevalcontext)
{
	int  size,i;

	if (!l || l->Size() == 0)
		return;

	CATICkeParm_var string1, arg;
	CATUnicodeString str1="", str2;

	string1 = (*l)[1];


	str1 = string1->Value()->AsString();

	size = l->Size();
	i = 2;

	CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();

	// Get the type descriptor corresponding to a real.
	CATICkeType_var spType = NULL_var;
	spType = spParmDictionary->GetStringType();


	while(i <= size)
	{
		if ( (CATICkeType_var) (*l)[i] == spType)
			str2 = ((CATICkeParm_var) (*l)[i])->Value()->AsString();
		else
			str2 = ((CATICkeParm_var) (*l)[i])->Show();
		str1.Append(str2);
		i++;
	}

	res->Valuate(str1);

}
*/

//-----------------------------------------------------------------------------
// CATIAddLibrary
//-----------------------------------------------------------------------------
CATImplementClass(CAAConcatenateStringUserFunction, Implementation, CATBaseUnknown, CATNull);

#include <TIE_CATIAddLibrary.h>
TIE_CATIAddLibrary(CAAConcatenateStringUserFunction);

// Add a function to the dictionary
void CAAConcatenateStringUserFunction::Add()
{
	/*

	// A user function is defined by:
	// 1 - its name: "CAAConcatenateString"
	// 2 - its return type: a Real    
	// 3 - its arguments the component and the name of parameter.
	// 4 - its evaluator i.e the function which computes the result
	CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();

	// Get the type descriptor corresponding to a real.
	CATICkeType_var spType = NULL_var;
	spType = spParmDictionary->GetStringType();

	CATICkeType_var spType2 = NULL_var;
	spType2 = spParmDictionary->FindType("Literal");
	//CATCkeContext::AtomType
	cout << " I will create my new user function. "<<endl;
	if( NULL_var != spType  && NULL_var !=spType2)
	{
		CATICkeFunctionFactory_var funcFactory = CATCkeGlobalFunctions::GetFunctionFactory();
		CATICkeSignature_var dtEval9 = funcFactory->CreateFunction("ConcatenateString", spType, CAAConcatenateString);
		dtEval9->AddArgument(funcFactory->CreateArg("concatenatestring", spType));
		dtEval9->AddArgument(funcFactory->CreateArg("argument", spType2));
		dtEval9->SetVariableArgNb (CATCke::True);

		// attention CATParmDictionary positionne les signatures comme etant externes 
		// or celles-ci sont internes

		//Once created this function can be put inside a package.
		//Packages are made for structuring USER FUNCTIONS and TYPES.
		//This name also is used to find the CATNls file containing the NLS name of this 
		// package (Only useful for interactive application).
		// CATUnicodeString packageName = ""; // "CAAKnowledgeExpert"      
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

			spTypeDic->AddMethodForPackage( dtEval9, packageName );
		}
	}
	*/

	return;
}

//-----------------------------------------------------------------------------
// CATICreateInstance
//-----------------------------------------------------------------------------
CATImplementClass(CAAConcatenateStringUserFunctionExt, CodeExtension, CATBaseUnknown, CAAConcatenateStringUserFunction);

#include <TIE_CATICreateInstance.h>
TIE_CATICreateInstance(CAAConcatenateStringUserFunctionExt);

HRESULT __stdcall CAAConcatenateStringUserFunctionExt::CreateInstance (void **oPPV)
{
	*oPPV = new CAAConcatenateStringUserFunction();
	return S_OK;
}
