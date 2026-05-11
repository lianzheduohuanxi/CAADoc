// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAAPeoReturnCodes_H
#define CAAPeoReturnCodes_H


enum CAAPeoReturnCodes {
	CAAPeoKO = 1,
	CAAPeoOK = 0,
	CAAPeoInitSessionFailed = 2,
	CAALPeoDeleteSessionFailed = 3,						
	CAAPeoDocumentCreationFailed = 4,
	CAAPeoRetrieveParmFactoryFailed = 5,
	CAAPeoRetrieveOptFactoryFailed = 6,
	CAAPeoCreateOptimizationFailed = 7,
	CAAPeoCreateOptProblemFailed = 8,
	CAAPeoCreateOptGoalFailed = 9,
	CAAPeoCreateOptConstraintFailed = 10,
	CAAPeoCreateOptAlgorithmFailed = 11,
	CAAPeoCreateOptFreeParametersFailed = 12,
	CAAPeoCreateOptimLogFailed = 13,
	CAAPeoCreateOptimLogFileFailed = 14,
	CAAPeoRetrieveFctFactoryFailed = 15,
	CAAPeoOpenDocumentFailed = 16,
	CAAPeoCreateUserAlgoCatalogFailed = 17,
	CAAPeoCreateUserAlgoSUInCatalogFailed = 18,
	CAAPeoCheckCompatibilityFailed = 19
};

#endif



