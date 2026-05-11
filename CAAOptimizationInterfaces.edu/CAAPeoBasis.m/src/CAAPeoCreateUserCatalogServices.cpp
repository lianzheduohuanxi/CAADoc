// COPYRIGHT DASSAULT SYSTEMES  2002

// code commented the 17th of April 2012
// obsolete code : proper way to manage catalog has changed and don't uses C++ code but the executable CATfctEditorAssistant 

// CAAOptimizationInterfaces.edu headers
//#include "CAAPeoCreateUserCatalogServices.h"
//#include "CAAPeoUserAlgoFeatureDefines.h"	// catalog name, start up name, atributes name ...
//
//// C++ streams
//#include <iostream.h>
//
//// ObjectSpecsModeler headers
////#include "CATCatalogFactoryServices.h"   // Create, SaveCatalog
//#include "CATISpecObject.h"
//#include "CATISpecAttribute.h"
//
//
///**
//* This code was excuted to create the user catalog in the directory CAAOptimizationInterfaces\CNext\ressources\graphic.
//* This code is given for your information but it is not called in the different uses cases of this CAA framework
//* because we use the existing catalog stored here.
//* @param iStoragePathWithoutName
//* the path of the catalog without the name (ex: e:\myWorkSpace\CAAOptimizationInterfaces.edu\CNext\ressources\graphic\)
//*/
//HRESULT CAAPeoCreateUserCatalogServices::CAAPeoCreateFillAndSaveUserCatalog(const CATUnicodeString& iStoragePathWithoutName)
//{
//	CATICatalog* userCatalog = NULL;
//
//	if( CAAPeoCreateUserCatalog(&userCatalog,UserCatalogName) != CAAPeoOK )
//		return E_FAIL;
//
//	if( CAAPeoCreateUserAlgoStartUpInCatalog(userCatalog) != CAAPeoOK)
//	{
//		if(userCatalog != NULL)
//		{
//			userCatalog->Release();
//			userCatalog = NULL;
//		}
//		return E_FAIL;
//	}
//
//	CATUnicodeString iStoragePathAndName = iStoragePathWithoutName + UserCatalogName;
//
//	return ::SaveCatalog( &userCatalog,&iStoragePathAndName);
//}
//
//
///**
//* Creates the catalog of startups (does an AddRef if the operation succeeded,so
//* don't forget to release the catalog as soon as you don't need it anymore).
//*/
//CAAPeoReturnCodes CAAPeoCreateUserCatalogServices::CAAPeoCreateUserCatalog (CATICatalog** opCatalog, const char* iStorageName)
//{
//	HRESULT rc;
//	
//	CATUnicodeString catalogName( iStorageName );
//
//	// Create the Catalog that will contain StartUps	
//	cerr << "\n\nCreating user catalog ... ";
//	CATICatalog* piCatalog = NULL;	
//	rc = ::CreateCatalog(&catalogName, 
//		&piCatalog);
//	if ((FAILED(rc)) || NULL == piCatalog ) 
//	{
//		cerr << "KO (error occured while creating catalog)";
//		return CAAPeoKO;
//	}
//	
//	// Add a client identification to the catalog.  This is a mandatory step. 
//	CATUnicodeString clientId("SAMPLES");
//	rc = piCatalog -> SetClientId(&clientId);
//	if (FAILED(rc))
//	{
//		cerr << "KO (error occured while setting ClientID)";
//		piCatalog->Release();
//		piCatalog = NULL;
//		*opCatalog = NULL;
//		return CAAPeoKO;
//	}
//
//	*opCatalog = piCatalog;
//	cerr << "OK";
//	
//	return CAAPeoOK;	
//}
//
//
///**
//* Creates the startup of the user algorithm feature in the given start ups catalog
//* and saves the associated catalog.
//*/
//CAAPeoReturnCodes CAAPeoCreateUserCatalogServices::CAAPeoCreateUserAlgoStartUpInCatalog( CATICatalog* piCatalog )
//{
//	cerr << "\n\nCreating User Algorithm startup in catalog ... ";
//
//	if(!piCatalog)
//	{
//		cerr << "KO (no given catalog where creating the start up)";
//		return CAAPeoKO;
//	}
//
//	/*------------------------------------------ */
//	/* Creates the StartUp in the given catalog  */
//	/*------------------------------------------ */
//	CATBaseUnknown *pPeoUserAlgoSU = NULL;
//	CATUnicodeString peoUserAlgoSUName(UserAlgoSUName);
//	CATUnicodeString peoUserAlgoSUType(UserAlgoSUType);
//	
//	HRESULT rc  = piCatalog -> CreateSUInCatalog(&pPeoUserAlgoSU,
//												 &peoUserAlgoSUName,
//												 &peoUserAlgoSUType,
//												 "CATISpecObject");
//	
//	if ( (NULL == pPeoUserAlgoSU) || FAILED(rc) ) 
//	{
//		cerr << "KO (start up creation failed)";
//		return CAAPeoCreateUserAlgoSUInCatalogFailed;
//	} 
//
//
//	/*-----------------------------------------*/
//	/* Add attributes to the created Start Up  */
//	/*-----------------------------------------*/
//
//	CATISpecObject_var spPeoUserAlgoSUAsSO = pPeoUserAlgoSU;
//	if(!spPeoUserAlgoSUAsSO)
//	{
//		cerr << "KO (attributes initialization failed)";
//		return CAAPeoKO;
//	}
//
//	pPeoUserAlgoSU->Release();
//	pPeoUserAlgoSU = NULL;
//
//	CATISpecAttribute_var spSA = spPeoUserAlgoSUAsSO->AddAttribute(UserAlgoNbUpdatesMaxSetting, tk_integer);
//	if(!!spSA)
//		spSA->Release();
//
//	spSA = spPeoUserAlgoSUAsSO->AddAttribute(UserAlgoMaxTimeSetting, tk_integer); // minutes
//	if(!!spSA)
//		spSA->Release();
//
//	cerr << "OK";
//	return CAAPeoOK;
//	
//}
//


