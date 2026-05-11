// COPYRIGHT DASSAULT SYSTEMES  2000

#ifndef CAAPeoCreateUserCatalogServices_H
#define CAAPeoCreateUserCatalogServices_H
// =============================================================
// ABSTRACT
// --------
//
// Provide services :
//  - to create a catalog of features
//  - to create your own algorithm start up in the catalog
//=============================================================================
// WARNING: NO USAGE HERE
//  This code is given in order to show you how the user catalog
//	containing the user algo start up has been created.
// =============================================================

#include "CAAPeoBasis.h"
#include "CAAPeoReturnCodes.h"

// ObjectSpecsModeler headers
//#include "CATICatalog.h"
#include "CATIContainer.h"

// OptimizationInterfaces headers
#include "CATIOptAlgorithm.h"


class ExportedByCAAPeoBasis CAAPeoCreateUserCatalogServices
{
public:


	//---- Methods used to create and fill the user catalog with our algorithm start up ---
	/**
	* This code was excuted to create the user catalog in the directory CAAOptimizationInterfaces\CNext\ressources\graphic.
	* This code is given for your information but it is not called in the different uses cases of this CAA framework
	* because we use the existing catalog stored here.
	* @param iStoragePathWithoutName
	* the path of the catalog without the name (ex: e:\myWorkSpace\CAAOptimizationInterfaces\CNext\ressources\graphic\)
	* @return
	* S_OK if catalog creation succeded and E_FAIL else.
	*/
	static HRESULT CAAPeoCreateFillAndSaveUserCatalog(const CATUnicodeString& iStoragePathWithoutName);


	/**
	* Method called by CAAPeoCreateFillAndSaveUserCatalog() so that it is given for your information
	* by it is never called in the different uses cases of this CAA framework.
	* Creates a user catalog (start ups container)
	* Notice that the catalog is not saved.
	* @param opCatalog
	* pointer to the created catalog
	* @return
	* CAAPeoReturnCoded::CAAPeoOK if the operation succeeded.
	*/
	static CAAPeoReturnCodes CAAPeoCreateUserCatalog (CATICatalog** opCatalog, const char* iStorageName);

	/**
	* Method called by CAAPeoCreateFillAndSaveUserCatalog() so that it is given for your information
	* by it is never called in the different uses cases of this CAA framework.
	* Creates a user algorithm start up in the user catalog
	* @param piCatalog
	* the catalog where the user algo start up has to be created.
	* @return
	* CAAPeoReturnCoded::CAAPeoOK if the operation succeeded.
	*/
	static CAAPeoReturnCodes CAAPeoCreateUserAlgoStartUpInCatalog( CATICatalog* piCatalog );
	//----------------------------------------------------------------------------------------


};

#endif








































































