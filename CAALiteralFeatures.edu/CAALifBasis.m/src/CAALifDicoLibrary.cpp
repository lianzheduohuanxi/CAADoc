// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#include <iostream.h>

//CAALiteralFeatures headers
#include "CAALifDicoLibrary.h"

// LiteralFeatures headers
#include "CATCkeGlobalFunctions.h"
#include "CAALifEval.h"
#include "CATICkeSignature.h"
#include "CATICkeArg.h"

#include "CATListOfCATUnicodeString.h"

//KnowledgeInterfaces
#include "CATITypeDictionary.h"

// C++ implementation
CATImplementClass(CAALifDicoLibrary, Implementation, CATBaseUnknown, CATNull);

// CATIAddLibrary implementation
#include <TIE_CATIAddLibrary.h>
TIE_CATIAddLibrary(CAALifDicoLibrary);

// Add a function to the dictionary
void CAALifDicoLibrary::Add () 
{
    // A user function is defined by:
    // 1 - its name: "Hypotenuse"
    // 2 - its return type: a real    
    // 3 - its arguments
    // 4 - its evaluator i.e the function which computes the result
    
    CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();
    
    // Get the type descriptor corresponding to a real.
    CATICkeType_var spType = NULL_var;
    spType = spParmDictionary->GetRealType();
    if( NULL_var != spType )
    {
        CATICkeFunctionFactory_var funcFactory = CATCkeGlobalFunctions::GetFunctionFactory();
        CATICkeSignature_var spSign = funcFactory->CreateFunction ("CAAHypothenuse",
            spType,
            _caalifeval0);

        //Two arguments are defined
        // "iA", "iB" are input arguments 
        spSign->AddArgument (funcFactory->CreateArg ("iA",spParmDictionary->GetLengthType()));
        spSign->AddArgument (funcFactory->CreateArg ("iB",spParmDictionary->GetLengthType()));
        

        //Once created this function can be put inside a package.
        //Packages are made for structuring USER FUNCTIONS and TYPES.
        //This name also is used to find the CATNls file containing the NLS name of this 
        // package (Only useful for interactive application).
        CATUnicodeString packageName = "CATPackageMethodCAALif";        
        CATITypeDictionary_var spTypeDic = CATGlobalFunctions::GetTypeDictionary();
        
        if( spTypeDic == NULL_var)
        {
            cout << " Unable to retrieve the type dictionary. " << endl;
            return;
        }
        
        HRESULT hr;

		CATListOfCATUnicodeString iListOfPackages;
		hr = spTypeDic->ListPackages(iListOfPackages);
		if (iListOfPackages.Locate(packageName) == 0)
		{
			CATListOfCATUnicodeString iListOfPrerequisites;
			hr = spTypeDic->AddPackage( packageName, iListOfPrerequisites );
		}
		else
			hr = S_OK;

        if (SUCCEEDED(hr))
        {
            spTypeDic->AddMethodForPackage( spSign, packageName );
        }
    }    
    return;
}



























