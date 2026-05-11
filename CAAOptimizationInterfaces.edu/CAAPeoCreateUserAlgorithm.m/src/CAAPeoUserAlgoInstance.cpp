#include "CAAPeoUserAlgoInstance.h"

#include "CAAPeoAddTypeLibraryDefines.h"
#include "CAAPeoUserAlgoFeatureDefines.h"

#include "CATITypeDictionary.h"
#include "CATIType.h"

#include "TIE_CATIInstance.h"
TIEchain_CATIInstance(CAAPeoUserAlgoInstance);

CATImplementKindOf(CAAPeoUserAlgoInstance, DataExtension, CATBaseUnknown, CAAPeoUserAlgo);

//------------------------------
//  CATIInstance implementation |
//------------------------------
CATIType* CAAPeoUserAlgoInstance::Type()
{

	// get the types dictionnary
	CATITypeDictionary_var dico = CATGlobalFunctions::GetTypeDictionary();
	if (!dico)
		return NULL;

	// get the type from its internal name in the dictionnary
	CATIType_var typeInDico;
	HRESULT hr = dico->FindTypeSafe(CAAPeoUserAlgorithmCATIType, CAAPeoPackageName, typeInDico);

	if (!!typeInDico)
		typeInDico->AddRef();
	else
	{
		// if type not found in the types dictionnary, get a generic type that is "Feature Type"
		typeInDico = CATKweInstanceAdapter::Type();
	}

	return typeInDico;
}
