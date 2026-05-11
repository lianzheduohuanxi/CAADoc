#include "CAAPeoRunUserAlgorithmMain.h"
#include "CAAPeoUserAlgorithmNotif.h"
#include <iostream.h>

// system
#include "CATEventSubscriber.h"

// ObjectModelerBase headers
#include "CATIContainer.h"

// ObjectSpecsModeler headers
#include "CATISpecObject.h"

// CAAOptimizationInterfaces.edu headers
#include "CAAPeoServices.h"		// create session, open document ...
#include "CAAPeoReturnCodes.h"
#include "CAAPeoUserCmd.h"		// receive end iteration notification
#include "CAAPeoUserFactory.h"  // create user algorithm

// services headers
#include "CATCkeGlobalFunctions.h"

// LiteralFeatures interfaces 
#include "CATICkeParmFactory.h"
#include "CATICkeFunctionFactory.h"
#include "CATICkeParm.h"
#include "CATICkeRelation.h"
#include "CATICkeRelationExp.h"

#include "CATCkeGlobalFunctions.h"
#include "CATITypeDictionary.h"


// Optimization interfaces
#include "CATIOptFactory.h"
#include "CATIOptOptimization.h"
#include "CATIOptProblem.h"
#include "CATIOptGoal.h"
#include "CATIOptConstraint.h"
#include "CATIOptAlgorithm.h"
#include "CATIOptFreeParameter.h"
#include "CATIOptimizationLog.h"


//-----

CATIContainer_var _spContainer = NULL_var;

//-----

int main (int argc, char** argv)
{	

	// Retrieve the optionnal argument
	if(argc > 2)
	{
		cerr << "\n!! Wrong number of program argument : 1 optional argument !!\n";
		return CAAPeoKO;
	}

	// optionnal argument : output file path
	CATUnicodeString optimLogFilePath = "";
	if(argc == 2)
		optimLogFilePath = argv[1];	

	// Initialize the session
	CAAPeoServices services;
	if( FAILED(services.CAAPeoInitSession ()) )
		return CAAPeoKO;

	// create a new document CATPart and get a pointer to the Root container of this document
	CATIContainer* piContainer = NULL;
	HRESULT hr = services.CAAPeoCreateInstanceContainer(&piContainer);
	if( FAILED(hr) )
		return CAAPeoDocumentCreationFailed;	
	_spContainer = piContainer;
	piContainer->Release();
	piContainer = NULL;


									//------------------------------//


	// create parameter and relations that will be used in optimization
	// - get handler on parameters and function factory
	CATICkeParmFactory_var spParmFactory = _spContainer;
	if(!spParmFactory)
	{
		cerr << "\n!! Can't retrieve the parameters factory from the given container !!\n\n";
		return CAAPeoRetrieveParmFactoryFailed;
	}
	
	cerr << "\nParameters factory retrieved\n";

	CATICkeFunctionFactory_var spFctFactory = CATCkeGlobalFunctions::GetFunctionFactory();
	if(!spFctFactory)
	{
		cerr << "\n!! Can't retrieve the function factory from the given container !!\n\n";
		return CAAPeoRetrieveFctFactoryFailed;
	}

	cerr << "\nFunction factory retrieved\n";

	// - Create parameters that will become the optimization free parameters
	CATICkeParm_var spRadius = spParmFactory->CreateLength ("Radius",2);
	CATICkeParm_var spLength = spParmFactory->CreateLength ("Length",3);

	// - Create a Volume type parameter that will become the optimization goal
	CATICkeParm_var spVolume = spParmFactory->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),"Volume",0);
	CATIParmPublisher_var spParmPublisher = NULL_var;

	CATIParmPublisher* piDocPublisher=NULL;
	CATIParmPublisher_var spDocPublisher ; 
	services.CAAPeoRetrievePublisherFromCurrentDoc(&piDocPublisher);

	if ( NULL != piDocPublisher )
	{
		spDocPublisher = piDocPublisher;

		piDocPublisher->Release();

		CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,spDocPublisher,CATCke::True);
		if (!!spParameterSet)
		{
			spParmPublisher = spParameterSet;
			if (!!spParmPublisher)
			{
				spParmPublisher->Append(spRadius);
				spParmPublisher->Append(spLength);
				spParmPublisher->Append(spVolume);
			}
		}

		// - Create a formula which calculates the cylinder volume (PI * Radius**2 * CylLength)
		CATCkeListOf(Parm) paramList;
		paramList.Append (spVolume);
		paramList.Append (spRadius);
		paramList.Append (spLength); 

		CATICkeRelation_var spFormula = spParmFactory->CreateFormula (  "VolumeFormula",
			"",
			"", 
			spVolume,
			&paramList,
			"PI*(a2**2)*a3",
			NULL_var,
			CATCke::False);


		CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,spDocPublisher,CATCke::True);
		if (!!spRelationSet)
			spParmPublisher = spRelationSet;

		if (!!spParmPublisher)
			spParmPublisher->Append(spFormula);


		//------------------------------//


		//####### Define the optimization #######

		//	  ==> get the optimization factory
		CATIOptFactory_var spOptFactory = _spContainer;
		if(!spOptFactory)
		{
			cerr << "\n!! Can't retrieve the optimization factory from the given container !!\n\n";
			return CAAPeoRetrieveOptFactoryFailed;
		}

		cerr << "\nOptimization factory retrieved\n";

		//	  ==> create the optimization
		CATIOptOptimization_var spOptim = spOptFactory->CreateOptimization();
		if(!spOptim)
		{
			cerr << "\n!! Optimization creation failed !!\n\n";
			return CAAPeoCreateOptimizationFailed;	
		}

		cerr << "\nOptimization created\n";
		if (!!spRelationSet)
			spParmPublisher = spRelationSet;

		if (!!spParmPublisher)
			spParmPublisher->Append(spOptim);


		//	  ==> create problem and attach it to the optimization
		CATIOptProblem_var spOptProblem = spOptFactory->CreateProblem();
		if(!spOptProblem)
		{
			cerr << "\n!! Problem creation failed !!\n\n";
			return CAAPeoCreateOptProblemFailed;	
		}

		cerr << "\nProblem created\n";

		spOptim->SetProblemToSolve(spOptProblem);


		//		  => create goal and attach it to the problem 
		//			 (only one parameter to optimize because we'll use an algorithm
		//			 that supports only one)
		CATIOptGoal_var spOptGoal = spOptFactory->CreateGoal();
		if(!spOptGoal)
		{
			cerr << "\n!! Goal creation failed !!\n\n";
			return CAAPeoCreateOptGoalFailed;	
		}

		cerr << "\nGoal created\n";

		spOptProblem->AddGoal(spOptGoal);


		//			- we choose to optimize the cylinder volume
		spOptGoal->SetGoalParameter(spVolume);

		//			- and we want the volume to reach a target value (= 40m3) without 
		//			  any constraints on free parameters
		spOptGoal->SetGoalType(CATIOptGoal::TargetValue);
		spOptGoal->SetTargetValue(40);


		//	  ==> create algorithm and attach it to the optimization. Here we use an user type of algorithm.
		//		  The following method creates a catolog, create the user algo start up in the catalog
		//		  and returns an instance of this start up (See CAAPeoUserAlgoServices).
		//		  Notice that the catalog is not saved.
		CATIOptAlgorithm_var spOptAlgorithm = CAAPeoUserFactory::CreateUserAlgorithm(_spContainer);
		if(!spOptAlgorithm)
		{
			cerr << "\n!! User algorithm creation failed !!\n\n";
			return CAAPeoCreateOptAlgorithmFailed;	
		}

		cerr << "\nUser algorithm created\n";

		spOptim->SetAlgorithm(spOptAlgorithm);


		//	  ==> create free parameters (the ones that will be adjusted to reach the optimization goal)
		//		  and attach them to the optimization.
		//		  - to optimize the cylinder volume, we want to adjust the 2 parameters : Length and Radius
		CATIOptFreeParameter_var spLengthFreeParm = spOptFactory->CreateFreeParameter();
		CATIOptFreeParameter_var spRadiusFreeParm = spOptFactory->CreateFreeParameter();
		if(!spLengthFreeParm || !spRadiusFreeParm)
		{
			cerr << "\n!! Free parameters creation failed !!\n\n";
			return CAAPeoCreateOptFreeParametersFailed;	
		}

		cerr << "\nFree parameters created\n";

		spLengthFreeParm->SetParameter(spLength);
		spRadiusFreeParm->SetParameter(spRadius);

		//		 - we give ranges in which parameters will be adjusted (no steps given here)
		double lengthInfRange = 2.0;
		double lengthSupRange = 6.0;
		double radiusInfRange = 1.0;
		double radiusSupRange = 3.0;
		spLengthFreeParm->SetRanges(1, lengthInfRange , 1, lengthSupRange);
		spRadiusFreeParm->SetRanges(1, radiusInfRange , 1, radiusSupRange);

		//		- we attach it to the optimization
		spOptim->AddFreeParameter(spRadiusFreeParm);
		spOptim->AddFreeParameter(spLengthFreeParm);


		//	  ==> if you want to save optimization data : create solution and attach it to the  optimization
		CATIOptimizationLog_var spOptLog = NULL_var;
		CATUnicodeString StrEmpty = "";
		if(optimLogFilePath != StrEmpty)
		{

			spOptLog = spOptFactory->CreateOptimizationLog();
			if(!spOptLog)
			{
				cerr << "\n!! Optimizationlog creation failed !!\n\n";
				return CAAPeoCreateOptimLogFailed;	
			}

			cerr << "\nOptimization log created\n";

			spOptim->SetOptimizationLog(spOptLog);

			//		  => create the optimization log
			//			 - we need the list of all the parameters you want to appear
			//			   in the optimization log
			CATLISTV(CATBaseUnknown_var) params;
			params.Append(spRadius);
			params.Append(spLength);
			params.Append(spVolume);

			//			 - here we want to store historic in the model (we will export it
			//			   to a file at the end)
			if ( FAILED(spOptLog->InitializeOptimLog(/*optimLogFilePath*/ "", &params)) )
			{
				cerr << "\n!! Creation of optimization log file failed !!\n\n";

				spOptim->SetOptimizationLog(NULL_var);
				spOptLog = NULL_var;
				return CAAPeoCreateOptimLogFileFailed;
			}

			cerr << "\nOptimization log file created\n";

		}
		//#### END of optimization define ####


		//#### START of compatibility check ####
		cerr << "\nChecking compatibility between algorithm and optimization definition ... ";
		if( FAILED(spOptAlgorithm->CheckCompatibility(spOptim)) )
		{
			cerr << "KO\n\n";
			return CAAPeoCheckCompatibilityFailed;
		}
		cerr << "OK\n";
		//#### END of compatibility check  ####


		cerr << "\n\n\n#### BEFORE optimization ###\nLength = " << spLength->Show().ConvertToChar()
			<< "\nRadius = " << spRadius->Show().ConvertToChar() 
			<< "\n=> Volume = " << spVolume->Show().ConvertToChar()
			<< "\n############################\n\n";


		cerr << "\n\n=============== Running Optimization ===============\n"
			<< "Parameter to optimize : cylinder volume\n"
			<< "Optimization Type : Target Value = " << spOptGoal->GetTargetValue()->Show().ConvertToChar() << "\n"
			<< "Optimization free parameters : Length & Radius\n"
			<< "Variation range of cylinder length : [" << lengthInfRange << "m ; " <<lengthSupRange << "m]\n"
			<< "Variation range of cylinder radius: ["<< radiusInfRange << "m ; " <<radiusSupRange << "m]\n"
			<< "Optimization constraint(s) : NONE\n"
			<< "Optimization log file : ";

		if(optimLogFilePath != StrEmpty)
			cerr << optimLogFilePath.ConvertToChar() << "\n";
		else
			cerr << " NONE\n";		 
		cerr << "=====================================================\n\n\n";


		//-> [optional] put a callback to receive notification from the algorithm
		//	 (Notie that to put a callback, you have to give a suscriber that must be a CATCommand)
		CAAPeoUserCmd userCmd;
		CATCallback endIterationCB = AddCallback( &userCmd /*suscriber*/, spOptAlgorithm->GetCallbackManager()/*publisher*/, 
			spOptAlgorithm->GetEndIterationNotification()/*event*/, 
			(CATSubscriberMethod)&CAAPeoUserCmd::OnReceiveNotification/*method to call*/,NULL);


		//#### Run the optimization ####

		spOptAlgorithm->Run(spOptim);

		//#############################


		cerr << "\n\n\n#### AFTER optimization ###\nLength = " << spLength->Show().ConvertToChar()
			<< "\nRadius = " << spRadius->Show().ConvertToChar() 
			<< "\n=> Volume = " << spVolume->Show().ConvertToChar()
			<< "\n############################\n";

		//-> [Only if you put the callback before the run] Remove the callback
		RemoveCallback(&userCmd,spOptAlgorithm->GetCallbackManager(), endIterationCB);

		if(optimLogFilePath != StrEmpty)
		{
			cerr << "\nExporting optimization log to file ...";
			// to allow you to see the optimization log content, we export it to
			// a file.
			if( FAILED(spOptLog->ExportOptimLogToFile(optimLogFilePath,1)) )
			{
				cerr << "KO\n\n";
				return CAAPeoKO;
			}
			cerr << "OK\n\n";
		}

	}
	// Close the session and environment
	if(FAILED(services.CAAPeoCloseSession()) )
		return CAAPeoKO;

	return CAAPeoOK;
}



