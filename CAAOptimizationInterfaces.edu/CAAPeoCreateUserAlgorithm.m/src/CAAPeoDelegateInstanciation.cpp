// COPYRIGHT Dassault Systemes 2002
#include "CAAPeoDelegateInstanciation.h"

// ObjectModelerBase
#include "CATIContainer.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// KnowledgeInterfaces
#include "CATIInstance.h"

// OptimizationInterfaces
#include "CATIOptOptimization.h"
#include "CATIOptAlgorithm.h"

// CAAOptimizationInterfaces
#include "CAAPeoUserFactory.h"
#include "CAAPeoAddTypeLibraryDefines.h"


//------------------------------------------
// CATIDelegateInstanciation implementation |
//------------------------------------------
#include "TIE_CATIDelegateInstanciation.h"
TIE_CATIDelegateInstanciation(CAAPeoDelegateInstanciation);

CATImplementKindOf(CAAPeoDelegateInstanciation,
				   Implementation,
				   CATBaseUnknown,
				   CATNull);

//-------------------------------------------------------------
CAAPeoDelegateInstanciation::CAAPeoDelegateInstanciation()
{
}

CAAPeoDelegateInstanciation::~CAAPeoDelegateInstanciation()
{
}

//-------------------------------------------------------------
HRESULT CAAPeoDelegateInstanciation::Instanciate(const CATIInstance_var& iOwner,
												 const CATUnicodeString& iKey,
												 const CATUnicodeString& typeName,
												 CATIInstance_var& oInstanciated,
												 const CATInstanciationContext *iContext)
{

	if (typeName == CAAPeoUserAlgorithmCATIType)
	{

		// get the optimization feature
		CATIOptOptimization_var spOptim = iOwner;
		if(!spOptim)
			return E_FAIL;

		// algorithm creation
		CATISpecObject_var specOpt = iOwner;
		if(!specOpt)
			return E_FAIL;

		CATIContainer_var container = specOpt->GetFeatContainer();
		if(!container)
			return E_FAIL;

		CATIOptAlgorithm_var spUserAlgo = CAAPeoUserFactory::CreateUserAlgorithm(container);
		if(!spUserAlgo)
			return E_FAIL;

		// the algorithm is aggregated to the optimization feature
		spOptim->SetAlgorithm(spUserAlgo);

		// get a CATIInstance handler from the algorithm (CAAPeoUserAlgo feature adheres to the CATIInstance interface)
		CATIInstance_var instance = spUserAlgo;
		if(!instance)
			return E_FAIL;

		// get the instance to be returned
		oInstanciated = instance;
	}
	else
	{// if we had created an other type of algorithm in CAAPeoAddTypeLibrary, we should have provided
	 // a instanciation mechanism here
		return E_FAIL;
	}

	return S_OK;
}

//-----------------------------------
// CATICreateInstance implementation |
//-----------------------------------
CATImplementClass(CAAPeoDelegateInstanciationExt, CodeExtension, CATBaseUnknown, CAAPeoDelegateInstanciation);

#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAPeoDelegateInstanciationExt);

HRESULT __stdcall CAAPeoDelegateInstanciationExt::CreateInstance (void **oPPV)
{
	*oPPV = new CAAPeoDelegateInstanciation();
	return S_OK;
}
