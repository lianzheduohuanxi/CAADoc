#include "CAAPeoCreateAndRunOptimization.h"
#include "CATISpecObject.h" // Added by FRH on 07/30/2002
#include <iostream.h>

// ObjectModelerBase headers
#include "CATIContainer.h"
#include "CATIDocRoots.h"

// ObjectSpecsModeler headers
#include "CATISpecObject.h"

// CAAproductEngineeringOptimizer headers
#include "CAAPeoServices.h"
#include "CAAPeoReturnCodes.h"

// services headers
#include "CATCkeGlobalFunctions.h"

// LiteralFeatures interfaces 
#include "CATICkeParmFactory.h"
#include "CATICkeFunctionFactory.h"
#include "CATICkeParm.h"
#include "CATICkeRelation.h"
#include "CATICkeRelationExp.h"

// Optimization interfaces
#include "CATIOptFactory.h"
#include "CATIOptOptimization.h"
#include "CATIOptProblem.h"
#include "CATIOptGoal.h"
#include "CATIOptConstraint.h"
#include "CATIOptAlgorithm.h"
#include "CATIOptFreeParameter.h"
#include "CATIOptimizationLog.h"


int main (int argc, char** argv)
{
	CATIContainer_var spContainer = NULL_var;

	// Retrieve the mandatory arguments
	if(argc != 3)
	{
		cerr << "\n!! Wrong number of program argument : 2 mandatory arguments expected !!\n=> See the CAAPeoCreateAndRunOptimization.h file\n\n";
		return CAAPeoKO;
	}

	CATUnicodeString CATPartPath = "";
	CATUnicodeString optimResultsFilePath = "";

	// First argument : the .CATPart file path
	CATPartPath = argv[1];
	
	// Second argument : the path of the optimization log file
	optimResultsFilePath = argv[2];
	

	CAAPeoServices services;

	// Initialize the session
	if( FAILED(services.CAAPeoInitSession()) )
		return CAAPeoKO;


	// create a new document CATPart and get a pointer to the Root container of this document
	CATIContainer* piContainer = NULL;
	HRESULT hr = services.CAAPeoCreateInstanceContainer(&piContainer);
	if( FAILED(hr) )
		return CAAPeoDocumentCreationFailed;
	
	spContainer = piContainer;
	piContainer->Release();
	piContainer = NULL;

	// create parameter and relations that will be used in optimization
	// - get handler on parameters and function factory
	CATICkeParmFactory_var spParmFactory = spContainer;
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
	CATICkeParm_var spRadius = spParmFactory->CreateLength ("Radius",0.5);
	CATICkeParm_var spLength = spParmFactory->CreateLength ("Length",3);

	// - Create a Volume type parameter that will become the optimization goal
	CATICkeParm_var spVolume = spParmFactory->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),"Volume",0);


	// - Create a formula which calculates the cylinder volume (PI * Radius**2 * CylLength)
	CATCkeListOf(Parm) paramList;
	paramList.Append (spVolume);
	paramList.Append (spRadius);
	paramList.Append (spLength); 

	CATICkeRelation_var spFormula = spParmFactory->CreateFormula ("VolumeFormula",
															"",
															"", 
															spVolume,
															&paramList,
															"PI*(a2**2)*a3",
															NULL_var,
															CATCke::False);

	//#### Define the optimization ####
	//	  ==> get the optimization factory
	CATIOptFactory_var spOptFactory = spContainer;
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

	//			- and we want the volume to reach a target value (= 40m3)
	spOptGoal->SetGoalType(CATIOptGoal::TargetValue);
	spOptGoal->SetTargetValue(40);

	//			- BUT we want the length to be < 3.5m and the radius > 2m (=> 2 constraints)
	//		    => create contraints (using CATICkeParmFactory) and attach them to the problem
	CATLISTV(CATBaseUnknown_var) inputList;
	inputList.Append(spLength);
	CATIOptConstraint_var spOptLengthConstraint = spParmFactory->CreateOptimizationConstraint("LengthConstraint", "", 0.0, 0, 
																					   &inputList, "a1 < 3.5m", 
																					   NULL_var, CATCke::False);
	inputList.RemoveAll();
	inputList.Append(spRadius);
	CATIOptConstraint_var spOptRadiusConstraint = spParmFactory->CreateOptimizationConstraint("RadiusConstraint", "", 0.0, 0, 
																					   &inputList, "a1 > 2m", 
																					   NULL_var, CATCke::False);


	if(!spOptLengthConstraint || !spOptRadiusConstraint)
	{
		cerr << "\n!! Constraints creation failed !!\n";
		return CAAPeoCreateOptConstraintFailed;	
	}
	cerr << "\nConstraints created\n";
	
	spOptProblem->AddConstraint(spOptLengthConstraint);
	spOptProblem->AddConstraint(spOptRadiusConstraint);

	//	  ==> create algorithm and attach it to the optimization. Here we use an existing type of algorithm
	//		  later (we'll see how to create a "user" algorithm). 
	CATIOptAlgorithm_var spOptAlgorithm = spOptFactory->CreateSimulatedAnnealing();
	if(!spOptAlgorithm)
	{
		cerr << "\n!! Algorithm creation failed !!\n\n";
		return CAAPeoCreateOptAlgorithmFailed;	
	}
	cerr << "\nAlgorithm created\n";
	

	spOptim->SetAlgorithm(spOptAlgorithm);

	//	  ==> create free parameters and attach them to the optimization
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
	double radiusInfRange = 0.3;
	double radiusSupRange = 2.5;
	spLengthFreeParm->SetRanges(1, lengthInfRange , 1, lengthSupRange);
	spRadiusFreeParm->SetRanges(1, radiusInfRange , 1, radiusSupRange);

	//		- we attach it to the optimization
	spOptim->AddFreeParameter(spRadiusFreeParm);
	spOptim->AddFreeParameter(spLengthFreeParm);


	//	  ==> if you want to save optimization data : create solution and attach it to the  optimization
	CATUnicodeString StrEmpty = "";
	if(optimResultsFilePath != StrEmpty)
	{

		CATIOptimizationLog_var spOptLog = spOptFactory->CreateOptimizationLog();
		if(!spOptLog)
		{
			cerr << "\n!! Optimization log creation failed !!\n\n";
			return CAAPeoCreateOptimLogFailed;	
		}
		cerr << "\nOptimization log created\n";
		

		spOptim->SetOptimizationLog(spOptLog);

		//		  => create the optimization log file
		//			 - we need the list of all the parameters to be taken in account
		//			   in the historic
		CATLISTV(CATBaseUnknown_var) params;

		params.Append(spOptLengthConstraint->GetDistanceParameter()); // to see constraints evolution
		params.Append(spOptRadiusConstraint->GetDistanceParameter()); // in the optim log
		params.Append(spRadius);
		params.Append(spLength);
		params.Append(spVolume);		

		if ( FAILED(spOptLog->InitializeOptimLog(optimResultsFilePath, &params, 1)) )
		{
			cerr << "\n!! Creation of optimization log file failed !!\n\n";

			spOptim->SetOptimizationLog(NULL_var);
			spOptLog = NULL_var;
			return CAAPeoCreateOptimLogFileFailed;

		}
		cerr << "\nOptimization log file created\n";

	}


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
		 << "Optimization constraint(s) : " << ( (CATICkeRelationExp_var)spOptLengthConstraint)->Body().ConvertToChar() 
		 << " & " << ( (CATICkeRelationExp_var)spOptRadiusConstraint)->Body().ConvertToChar() << "\n"
		 << "Optimization results file : ";
	if(optimResultsFilePath != StrEmpty)
		cerr << optimResultsFilePath.ConvertToChar() << "\n";
	else
		cerr << " NONE\n";		 
	cerr << "=====================================================\n\n\n";

	//#### Run the optimization ####
	if( FAILED(spOptAlgorithm->CheckCompatibility(spOptim)) )
	{
		cout << "\n\n!! This algorithm is not compatible with the definition of the optimization problem !!";
		return CAAPeoCheckCompatibilityFailed;
	}
	cout << "\nChecking compatibility between algorithm and optimization problem succeeded\n\n";

	spOptAlgorithm->Run(spOptim);
	//#############################

	cerr << "\n\n\n#### AFTER optimization ###\nLength = " << spLength->Show().ConvertToChar()
		 << "\nRadius = " << spRadius->Show().ConvertToChar() 
		 << "\n=> Volume = " << spVolume->Show().ConvertToChar()
		 << "\n############################\n\n\n";

	// if CATPartPath was given, we attach all the created features to retrieve them while
	// re-opening the CATPart file.
	if(CATPartPath != StrEmpty)
	{
		CATIParmPublisher_var spParmPublisher = NULL_var;

		CATIParmPublisher* piDocPublisher=NULL;
		CATIParmPublisher_var spDocPublisher ; 
		services.CAAPeoRetrievePublisherFromCurrentDoc(&piDocPublisher);
		if(NULL != piDocPublisher)
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

			CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,spDocPublisher,CATCke::True);
			if (!!spRelationSet)
			{
				spParmPublisher = spRelationSet;
				if (!!spParmPublisher)
				{
					spParmPublisher->Append(spFormula);
					spParmPublisher->Append(spOptim);
				}
			}
		}
	}

	// Close the session and environment
	if(FAILED(services.CAAPeoCloseSession (CATPartPath)))
		return CAAPeoKO;

	return CAAPeoOK;
}


