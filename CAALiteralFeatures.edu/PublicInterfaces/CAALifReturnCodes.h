// COPYRIGHT DASSAULT SYSTEMES  1994 2000
#ifndef CAALifReturnCodes_H
#define CAALifReturnCodes_H

// LiteralFeatures

// ==========================================================================
//
// ABSTRACT
//
//	CAALifKO = 1,
//	CAALifOk = 0,
//	CAALifInitSessionFailed = 2,
//	CAASessionNotInitialized = 3,
//	CAALifDeleteSessionFailed = 4,						
//	CAALifDocumentCreationFailed = 5,
//	CAALifCatalogCreationFailed = 6,
//	CAALifInterfaceImplementationNotFound = 7, 
//		- possible causes: Dictionnary not uptodate with feature name, MkCreateRuntimeView not done,
//		Implementation of the interface does not hold the startup name in the CATImplementClass macro.
//	CAALifContainerInitFailed = 8,
//	CAALifParmFactoryError = 9,
//
//	CAABadSampleArguments = 10
//
// ===========================================================================

enum CAALifReturnCodes {
	CAALifKO = 1,
	CAALifOk = 0,
	CAALifInitSessionFailed = 2,
	CAASessionNotInitialized = 3,
	CAALifDeleteSessionFailed = 4,						
	CAALifDocumentCreationFailed = 5,
	CAALifCatalogCreationFailed = 6,
	CAALifInterfaceImplementationNotFound = 7,
	CAALifContainerInitFailed = 8,
	CAALifParmFactoryError = 9,
	CAABadSampleArguments = 10,
	CAALifUnableToFindStartup = 11,
	CAALifOpenCatalogFailed = 12
};

#endif








































































