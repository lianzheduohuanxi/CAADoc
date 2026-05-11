#include "CAAPeoAddTypeLibrary.h"

// Files containing the defines (for user and for optimization package)
#include "CAAPeoAddTypeLibraryDefines.h"
#include "CATOptAddTypeLibraryDefines.h"


#include "CATITypeDictionary.h"
#include "CATMsgCatalog.h"


// the CAAPeoAddTypeLibrary class is an implementation of the CATIAddTypeLibaryInterface
#include "TIE_CATIAddTypeLibrary.h"
TIE_CATIAddTypeLibrary(CAAPeoAddTypeLibrary);
CATImplementClass(CAAPeoAddTypeLibrary, Implementation, CATBaseUnknown, CATNull);

//--------------------------------
//  CATIAddLibrary Implemenation  |
//--------------------------------
void CAAPeoAddTypeLibrary::Add()
{
	// we get the dictionnary of types
	CATITypeDictionary_var dico = CATGlobalFunctions::GetTypeDictionary();
	
	if (!!dico)
	{
		// we get a list of all the loaded packages
		HRESULT rc;
		CATListOfCATUnicodeString listPackages;
		rc = dico->ListPackages(listPackages);
		if (FAILED(rc))
			return;
		
		int packageExists;
		
		// if package doesn't exist, it will be added to the types dictionary
		packageExists = listPackages.Locate(CAAPeoPackageName);
		if (packageExists == 0)
		{
			CATListOfCATUnicodeString iListOfPrerequisites;
			// Here we want to add user algorithm types for optimization
			// then, the optimization package is a prerequisite
			iListOfPrerequisites.Append(CATOptOptimizationPackageName /* in CATOptAddTypeLibraryDefines.h */);
			rc = dico->AddPackage( CAAPeoPackageName /* in CAAPeoAddTypeLibraryDefines.h */, iListOfPrerequisites );

			// According to the instructions given in the CATITypeDictionnary.h, we create a CATPackageCAAPeoPackage.CATRsc
			// file to be able to force the package loading in CATIA (by using to the Tools->Options).
		}
		
		if (FAILED(rc))
			return;

		// To be retrieved by the Optimizer UI, the user algorithm type HAS TO DERIVE
		// from the generic optimization algorithm feature type
		// => try to get this generic optimization algorithm type
		CATIType_var genericOptimAlgorithmFeature = NULL_var;
		rc = dico->FindType(CATOptGenericOptimAlgorithmCATIType /* in CATOptAddTypeLibraryDefines.h */, genericOptimAlgorithmFeature);
		if (FAILED(rc))
			return;		

		// if the user algorithm type doesn't exist, it will be added to the types dictionnary
		CATIType_var userAlgorithmType = NULL_var;
		rc = dico->FindType(CAAPeoUserAlgorithmCATIType /* in CAAPeoAddTypeLibraryDefines.h */, userAlgorithmType);
		if (FAILED(rc))
		{
			CATListValCATAttributeInfos listAttributesInfo;

			// we get the NLS name of the user algo from an NLS file
			CATUnicodeString userAlgoNLSName = CATMsgCatalog::BuildMessage(CAAPeoNLSFileName,"UserAlgorithm");
			
			// we create the user algorithm type
			rc = dico->CreateType(CAAPeoUserAlgorithmCATIType	  /* internal type name defined in CAAPeoAddTypeLibraryDefines.h */, 
								  userAlgoNLSName				  /* NLS name defined in the CAAPeoNLSFileName file */,
								  genericOptimAlgorithmFeature	  /* the father type i.e. the type from which derives the created one */, 
								  userAlgorithmType				  /* the created type*/, 
								  &listAttributesInfo			  /* list of created type attributes - empty here */, 
								  CAAPeoDelegateInstanciationName /* defined in CAAPeoAddTypeLibraryDefines.h - gives the name 
																	 of the class that implement CATIDelegateInstanciation
																	 and whose method Instanciate() will be implicitly
																	 called to get an instance of this new type */);
			if (SUCCEEDED(rc))
			{
				// we add the new algorithm type in the CAAPeoPackageName of the types dictionary
				rc = dico->AddTypeForPackage(userAlgorithmType, CAAPeoPackageName);
			}
		}

	}

}

//-------------------------------------
//  CATICreateInstance implementation  |
//-------------------------------------
// the CAAPeoAddTypeLibraryExt class is a code extension for CAAPeoAddTypeLibrary, that implements
// the CATICreateInstance interface
CATImplementClass(CAAPeoAddTypeLibraryExt, CodeExtension, CATBaseUnknown, CAAPeoAddTypeLibrary);

#include <TIE_CATICreateInstance.h>
TIE_CATICreateInstance(CAAPeoAddTypeLibraryExt);

HRESULT __stdcall CAAPeoAddTypeLibraryExt::CreateInstance (void **oPPV)
{
	*oPPV = new CAAPeoAddTypeLibrary();
	return S_OK;
}
