// COPYRIGHT DASSAULT SYSTEMES  2000

#ifndef CAAPeoUserAlgoServices_H
#define CAAPeoUserAlgoServices_H
// =============================================================
// ABSTRACT
// --------
//
// Provide services :
//  to create the user algorithm by instanciating the user 
//	algo start up stored in the user catalog located in
//	CAAOptimizationInterfaces.edu\CNext\ressources\graphic\
//  and named CAAPeoUserCatalog.CATfct.
//=============================================================================
#include "CAAPeoCreateUserAlgorithm.h"
#include "CAAPeoReturnCodes.h"

// ObjectSpecsModeler headers
#include "CATIContainer.h"

// OptimizationInterfaces headers
#include "CATIOptAlgorithm.h"


class ExportedByCAAPeoCreateUserAlgorithm CAAPeoUserFactory
{
public:

	/**
	* Access the current catalog, retrieve the user algo start up and returns 
	* an instance of it.
	* @return
	* NULL_var if operation failed.
	*/
	static CATIOptAlgorithm_var CreateUserAlgorithm(CATIContainer *iContainer);

};

#endif








































































