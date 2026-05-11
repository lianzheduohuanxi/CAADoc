#include "CAAPeoUserAlgorithm.h"
#include "CATIContainer.h" // Added by FRG on 07/30/2002
#include "CATISpecObject.h" // Added by FRG on 07/30/2002
#include <iostream.h>
#include <math.h>
#include "CATTime.h"
#include "CATTimeSpan.h"

// system
#include "CATListOfDouble.h"
#include "CATListPV.h" // list of void* pointers
#include "CATListOfInt.h"

// ObjectModeler
#include "CATIContainer.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"

// Optimization Interfaces
#include "CATIOptFreeParameter.h"
#include "CATIOptProblem.h"
#include "CATIOptGoal.h"

// LiteralFeatures
#include "CATICkeParmFactory.h"
#include "CATICkeMagnitude.h"
#include "CATCkeGlobalFunctions.h"
#include "CATITypeDictionary.h"

// local headers
#include "CAAPeoUserAlgorithmNotif.h"
#include "CAAPeoUserAlgoFeatureDefines.h"
#include "CAAPeoServices.h"



class CATListValCATBaseUnknown_var;

// extension of CATOptAlgorithmAdapter for the feature named "CAAPeoUserAlgo" (see CAAPeoUserAlgoServices
// where the start up is created)
CATImplementClass(CAAPeoUserAlgorithm, DataExtension, CATOptAlgorithmAdapter, CAAPeoUserAlgo);

// adhesion to CATIOptAlgorithm interface
#include "TIE_CATIOptAlgorithm.h"
TIEchain_CATIOptAlgorithm(CAAPeoUserAlgorithm);


CAAPeoUserAlgorithm::CAAPeoUserAlgorithm() : CATOptAlgorithmAdapter()
{
	_spOptGoal = NULL_var;
	_spUserRelation = NULL_var;
	_spParmToMinimize = NULL_var;
	_spUserAlgoOptimLog = NULL_var;
}

CAAPeoUserAlgorithm::~CAAPeoUserAlgorithm()
{
	_spOptGoal = NULL_var;
	_spUserRelation = NULL_var;
	_spParmToMinimize = NULL_var;
	_spUserAlgoOptimLog = NULL_var;
}

/*
* Here is a algorithm whose target is to minimize the
* parameter "spParmToMinimize". The resolution is made
* by dichotomy and does not take in account the eventual constraints.
* For example with 3 free parameters P1, P2, and P3 which all have defined
* ranges R1p1, R1p2, R1p3 at the iteration 1 (that defines a space part):
* - we divide R1p1, R1p2 and R1p3 in two equal distances, and we choose
*   two points = the middles of each two distances
*   => there are 2^ParmNb points (4 points in 2D, 8 points in 3D etc ...).
* - we compute the value of spParmToMinimize for all these points, and
*   we keep the point that gives the minimum value. This point
*   defines a part of the initial domain. This part of space becomes
*   the new study domain definied by R2p1, R2p2,R2p3 (iteration 2).
* - we divide R2p1, R2p2 and R2p3 in two equal distances, and we choose
*   two points = the middles of each two distances etc ...
* The algorithm stops as soon as  
*/
HRESULT CAAPeoUserAlgorithm::Run(CATIOptOptimization_var & spiOptim)
{

	// ** Initialize algorithm	
	//  -> get the optimization data
	if( FAILED(GetOptimizationData(spiOptim)) )
		return E_FAIL;

	int freeParmNb = _freeParmsList.Size();
	if(!freeParmNb)
		return E_FAIL;

	//  -> get the list of input parameters (those which will be modified
	//     and which have to be set as update engine inputs because their
	//     configuration changes may lead to better output(s) value(s)).
	//	-> get initial inf. and sup. ranges of free parameters
	CATLISTV(CATBaseUnknown_var) inputsList;
	CATListOfDouble infRangesList, supRangesList;
	CATICkeParm_var spParm;
	int i = 1;
 for(; i <= freeParmNb; i++)
	{
		CATIOptFreeParameter_var spFreeParm = _freeParmsList[i];
		if(!spFreeParm)
			return E_FAIL;

		spParm = spFreeParm->GetParameter();
		if(!spParm)
			return E_FAIL;

		int oHasInf,oHasSup;
		double oInfR,oSupR;
		spFreeParm->GetRanges(oHasInf,oInfR,oHasSup,oSupR);

		if(!oHasInf || !oHasSup)
			return E_FAIL;

		infRangesList.Append(oInfR);
		supRangesList.Append(oSupR);
		inputsList.Append(spParm);
	}	
	//We need this trick in order to aggregate the newly created features at the
	// right place in the document i.e. Parameters in the parameter set and
	// relations in the relation set.

	CATISpecObject_var spSpecOpt = spiOptim;
	CATISpecObject_var spSpecParm = spParm;
	CATISpecObject_var spSpecTmp;

	//Just a trick to be able to aggregate the newly created features
	spSpecTmp = spSpecOpt->GetFather();
	_spRelSet = spSpecTmp;
	if (spSpecTmp != NULL_var)
		spSpecTmp->Release();
	spSpecTmp = spSpecParm->GetFather();
	_spParamSet = spSpecTmp;
	if (spSpecTmp != NULL_var)
		spSpecTmp->Release();
	//  ->  To make the same treatment for the 3 optimization types
	//		(Min, Max, Target Value), we build a relation between
	//		the parameter to minimize and the optimization goal parameter.  
	if( FAILED(BuildUserRelation()) )
		return E_FAIL;

	//  -> we add the parameter to minimize to the list of parameters
	//	   which have to be updated by the update engine. 
	CATLISTV(CATBaseUnknown_var) outputsList;
	outputsList.Append(_spParmToMinimize);

	// -> we deal with the update management engine (just call
	//    the methods of the father class in the following order.
	if( FAILED(InitUpdate(spiOptim,&inputsList,&outputsList)) )
		return E_FAIL;

	if(FAILED(BeforeFirstUpdate()))
		return E_FAIL;

	//	-> we add a parameter in the optimization log
	CATISpecObject_var spSO = this;
	if(!spSO)
		return E_FAIL;
	CATIContainer_var spCont = spSO->GetFeatContainer();
	CATICkeParmFactory_var spParmFact = spCont;
	if(!spParmFact)
		return E_FAIL;

	CATICkeParm_var spUpdateStatus = spParmFact->CreateString("UpdateStatus","KO");




	//CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,NULL_var,CATCke::True);
	if (!!_spParamSet)
    {
	  CATIParmPublisher_var spParmPublisher = _spParamSet;
	  if (!!spParmPublisher)
	  {
		spParmPublisher->Append(spUpdateStatus);
	  }
    }

	if(!spUpdateStatus)
		return E_FAIL;

	if(!!_spUserAlgoOptimLog)
		_spUserAlgoOptimLog->AddParameterInOptimLog(spUpdateStatus);


	//	-> initialize the timer and get the stop flag
	CATTime beginning = CATTime::GetCurrentLocalTime();
	CATTimeSpan elapsed;

	int* pStop = NULL;
	if( spiOptim != NULL_var )		
		pStop = spiOptim->RunHasToStop();
	int withStopFlag = (pStop != NULL);

	//  -> Get the algorithm stopping criteria
	double maxTime = 0; // in minutes
	double maxUpdateNb = 0;
	GetSetting(UserAlgoMaxTimeSetting,maxTime);
	maxTime = maxTime*60.0; // conversion to secondes for comparisons with elapsed
	GetSetting(UserAlgoNbUpdatesMaxSetting,maxUpdateNb);
	CATUnicodeString strMaxTime;
	strMaxTime.BuildFromNum(maxTime);
	CATUnicodeString strMaxUpdateNb;
	strMaxUpdateNb.BuildFromNum(maxUpdateNb);

	//** lets start the algorithm
	// At each update one parameter can take 2 values :
	// the value of the first middle (parm at level one) or the value of the 2d middle (parm at level 2) 
	// of the divided range
	// => in one iteration, there are 2^parmNb combinations of values identified by the folowing array
	CATListPV updateList;
//	int updateNb = pow(2,freeParmNb);
	int updateNb = (1 << freeParmNb);
	for(i = 1; i <= updateNb; i++)
	{
		CATListOfInt* pUpdateConfig = new CATListOfInt;
		updateList.Append(pUpdateConfig);
	}

	int parm = 1;
 for(; parm <= freeParmNb; parm++)
	{
//		int motifSize = pow(2,parm);
		int motifSize = (1 << parm);
		int countInMotif = 1;
		for(int update = 1; update <= updateNb; update++)
		{
			if(countInMotif <= motifSize / 2 )
				((CATListOfInt*)updateList[update])->Append(1);
			else
				((CATListOfInt*)updateList[update])->Append(2);

			if(countInMotif == motifSize)
				countInMotif = 1;
			else
				countInMotif++;
		}
	
	}

	int totalUpdateNb = 0;
	int currentIteration = 0;
	while(elapsed.GetTotalSeconds() < maxTime)
	{
		double bestResult = 0;	// the best result get during the current iteration, used to know which
								// part of space has to be explored during the next iteration
		int bestUpdate = 1;		// the index of the update that gives the best result in the current iteration

		currentIteration++;
		CATUnicodeString strIteration;
		strIteration.BuildFromNum(currentIteration);
		CATUnicodeString strIterationMsg = "\n## iteration ";
		strIterationMsg.Append(strIteration);
		strIterationMsg.Append(" ##");

		// launch the updates list for the current space part
		for(int update = 1; update <= updateNb; update++)
		{
			// -> valuate each parameter for the current update
			for(parm = 1; parm <= freeParmNb; parm++)
			{
				int parmLevel = (*((CATListOfInt*) updateList[update]))[parm];
				CATICkeParm_var spParm = inputsList[parm];

				if( parmLevel == 1 )
				{// we deal with the first middle of the divided range	
					spParm->Valuate(infRangesList[parm] + (supRangesList[parm] - infRangesList[parm])/4 );
				}
				else if ( parmLevel == 2 )
				{// 2d middle
					spParm->Valuate(infRangesList[parm] + 3*(supRangesList[parm] - infRangesList[parm])/4 );
				}
				else
				{// error
					for(i = 1; i <= updateNb; i++)
						delete (CATListOfInt*) (updateList[i]);

					updateList.RemoveAll();
					return E_FAIL;
				}

			}

			// -> launch update for this input parameters configuration
			if( SUCCEEDED(LaunchUpdate()) )
				spUpdateStatus->Valuate("OK");
			else
				spUpdateStatus->Valuate("KO");

			totalUpdateNb++;

      
			// -> compute elapsed time
			elapsed = (CATTime::GetCurrentLocalTime()- beginning );

			// -> send the notification (to be received by the main program in batch mode or by the stop dialog
			//	  in interactiv mode)
			if(update != 1)
				strIterationMsg = "";
			CATUnicodeString strUpdate;
			strUpdate.BuildFromNum(totalUpdateNb);
			CATUnicodeString strElapsed;
			strElapsed.BuildFromNum(elapsed.GetTotalSeconds() );
			strIterationMsg.Append("\nupdate ");
			strIterationMsg.Append(strUpdate);
			strIterationMsg.Append("/");
			strIterationMsg.Append(strMaxUpdateNb);
			strIterationMsg.Append(" - elapsed time ");
			strIterationMsg.Append(strElapsed);
			strIterationMsg.Append("s/");
			strIterationMsg.Append(strMaxTime);
			strIterationMsg.Append("s");
			CAAPeoUserAlgorithmNotif updateNotif( (int) (elapsed.GetTotalSeconds()), totalUpdateNb, strIterationMsg);
			SendEndIterationNotification(&updateNotif);			


			// -> store the update in the model (storage format chosen while initializing the optimization log) 
			//	  to keep a run historic
			if(!!_spUserAlgoOptimLog)
			{
				// for optimization purpose, we do the synchro between the file content
				// and the buffered data only when we deal with the last update of the current iteration.
				if( FAILED (_spUserAlgoOptimLog->AddRowInOptimLog( (update == updateNb ? 1 : 0) )) )
					cerr << "\nWARNING : update nb " << totalUpdateNb << " FAILED";
			}


			// -> interpret results
			CATICkeInst_var spInst = _spParmToMinimize->Value();
			if(!! spInst)
			{
				double currentValue = spInst->AsReal();

				if(update == 1)
				{
					bestResult = currentValue;
				}
				else
				{
					if(currentValue < bestResult)
					{
						bestResult = currentValue;
						bestUpdate = update;
					}
				}
			}

			// -> check the stop flag that may have been updated by the stop dialog
			if( withStopFlag && (*pStop) == 1 )
			{
				cerr << "\n\n==== Algorithm interrupted at update number " << totalUpdateNb << " ===\n\n";
				break;
			}
		
		}
		
		// -> we have tested all the updates for this iteration (or we have been interrupted) : do we have to stop ?
		if(totalUpdateNb >= maxUpdateNb || (withStopFlag && (*pStop) == 1) || elapsed.GetTotalSeconds() >= maxTime)
		{// => yes : we valuate all the parameters from the best configuration		 

			for(parm = 1; parm <= freeParmNb; parm++)
			{
				int parmLevel = (*( (CATListOfInt*) updateList[bestUpdate] ))[parm];
				CATICkeParm_var spParm = inputsList[parm];

				if( parmLevel == 1 )
				{				
					spParm->Valuate(infRangesList[parm] + (supRangesList[parm] - infRangesList[parm])/4 );
				}
				else if ( parmLevel == 2 )
					spParm->Valuate(infRangesList[parm] + 3*(supRangesList[parm] - infRangesList[parm])/4 );
			}

			// we are on the way to launch the last update.
			BeforeLastUpdate();
			LaunchUpdate();			

			break;
			
		}
		else
		{// => NO : we reduce the study domain to the current best part to explore it in the next iteration.
		
			for(parm = 1; parm <= freeParmNb; parm++)
			{
				int parmLevel = (*( (CATListOfInt*) updateList[bestUpdate] ))[parm];
				CATICkeParm_var spParm = inputsList[parm];

				// parameters valuation
				if( parmLevel == 1 )
				{// we keep the half-part containing the first middle (inf range doesn't move)
				
					supRangesList[parm] =  infRangesList[parm] + (supRangesList[parm] - infRangesList[parm])/2;
				}
				else if ( parmLevel == 2 )
				{
					infRangesList[parm] =  supRangesList[parm] - (supRangesList[parm] - infRangesList[parm])/2;
				}
			}
		}

	}

	// we have launch all updates.
	AfterLastUpdate();

	for(i = 1; i <= updateNb; i++)
		delete (CATListOfInt*) (updateList[i]);
	
	updateList.RemoveAll();

	return S_OK;
}



/**
* We test here :
* - all the optimization variables used during the run 
*   => it may send internal error(s).
* - if the optimization problem definition is compatible with the algorithm 
*   => it may send error(s) with explanations for the user.
* We could return E_FAIL without sending internal errors but if during
* the check only internal errors appears, the run will be forbidden by the
* optimizerUI without displaying any messages to the user ...
*/
HRESULT CAAPeoUserAlgorithm::CheckCompatibility(CATIOptOptimization_var &iOptim)
{
	if(!iOptim)
		return E_FAIL;

	// we clean the errors lists
	HRESULT result = S_OK;

	// We need free parameters
	CATLISTV(CATBaseUnknown_var)* pFreeParmsList =  iOptim->GetFreeParameters();
	if(!pFreeParmsList)
	{
		// the optimization free parameters list always exists (but can be empty)
		iOptim->SendOptimizationError("","Internal error");
		result = E_FAIL;
	}
	else
	{
		int inputNb = pFreeParmsList->Size();
		if( inputNb == 0)
		{
			// In interactiv mode : the user did not select any free parameter
			iOptim->SendOptimizationError("To run the optimization, you have to give at least one free parameter.\nReminder : a free parameter is a parameter that will be modify in order to get the best optimized parameter value",
										  "Missing free parameter");
			result = E_FAIL;
		}
		else
		{
			for(int i = 1; i <= inputNb; i++)
			{
				CATIOptFreeParameter_var spFreeParm = (*pFreeParmsList)[i];
				if(!spFreeParm)
				{
					iOptim->SendOptimizationError("","Internal error");
					result = E_FAIL;
				}
				else
				{
					CATICkeParm_var spParm = spFreeParm->GetParameter();
					if(!spParm)
					{
						iOptim->SendOptimizationError("","Internal error");
						result = E_FAIL;
					}
					else
					{
						// we need a range for each free parameter
						int hasInfR,hasSupR;
						double infR,supR;
						spFreeParm->GetRanges(hasInfR,infR,hasSupR,supR);

						if(!hasInfR || !hasSupR)
						{
							CATUnicodeString paramName = spParm->Name();
							CATUnicodeString arg2 = "Missing Inf. and/or Sup. bound(s) for parameter ";
							arg2.Append(paramName);

							iOptim->SendOptimizationError("To run this algorithm, each parameter must have an Inf. and a Sup. bound.", arg2);
							result = E_FAIL;						
						}

					}
				}
			}
		}
	}
	
	// we need a well-defined optimization problem :
	// since this algorithm does not support the constraints :
	// => it can't work in "Only constraints" mode
	// => it must have a parameter to optimize
	CATIOptProblem_var spPb = iOptim->GetProblemToSolve();
	if(!spPb)
	{
		iOptim->SendOptimizationError("","Internal error");
		result = E_FAIL;
	}
	else
	{

		CATLISTV(CATBaseUnknown_var)* pGoalsList = spPb->GetGoals();
		if(!pGoalsList)
		{
			// the list always exists
			iOptim->SendOptimizationError("","Internal error");
			result = E_FAIL;
		}
		else
		{
			if( pGoalsList->Size() != 1)
			{
				// the optimizerUI creates automaticaly one optimization goal
				iOptim->SendOptimizationError("","Internal error");
				result = E_FAIL;
			}
			else
			{
				CATIOptGoal_var spGoal = (*pGoalsList)[1];
				if(!spGoal)
				{
					iOptim->SendOptimizationError("","Internal error");
					result = E_FAIL;
				}
				else
				{
					// we need a parameter to optimize
					CATICkeParm_var spGoalParm = spGoal->GetGoalParameter();
					if(!spGoalParm)
					{
						// There is no parameter to optimize :
						// => if there are some constraints, the user is trying to
						//	  run the algorithm in Only Constraints mode : impossible
						CATLISTV(CATBaseUnknown_var)* pConstList = spPb->GetConstraints();
						if(!pConstList)
						{
							//the list always exist
							iOptim->SendOptimizationError("","Internal error");
							result = E_FAIL;						
						}
						else
						{
							if(pConstList->Size() != 0)
							{
								// => Trying to run the algorithm in OnlyConstraints mode
								iOptim->SendOptimizationError("This algorithm can't work in 'Only Constraints' mode.","Algorithm compatibility");
								result = E_FAIL;
							}
							else
							{
								// => The user did not select any parameter to optimize
								iOptim->SendOptimizationError("To run the optimization, you have to give the parameter to optimize.",
															  "Missing parameter to optimize");
								result = E_FAIL;							
							}
						}
					}
					else
					{// There is a parameter to optimize
					 // => we check that there is no constraint because the algorithm can't deal with them
					
						CATLISTV(CATBaseUnknown_var)* pConstList = spPb->GetConstraints();
						if(!pConstList)
						{
							//the list always exist
							iOptim->SendOptimizationError("","Internal error");
							result = E_FAIL;						
						}
						else
						{
							if(pConstList->Size() != 0)
							{
								// => Constraints given : they won't be taken in account during the run (this algorithm
								//    can't deal with constraints).
								iOptim->SendOptimizationError("This algorithm can't be used with constraints :\n=> to run it, delete all the existing constraints.","Algorithm compatibility");
								result = E_FAIL;
							}
						}					
					}

				}
			}
		}

	}

	return result;
}


/**
* Sets an algorithm setting. This setting is defined by its attribute name. 
* The value of the setting is given as a double (but can be an integer)
*/
HRESULT CAAPeoUserAlgorithm::SetSetting(const char* attrName, double content)
{
	CATISpecAttrAccess_var access = this;

	CATISpecAttrKey_var key = access->GetAttrKey(attrName);
	if (!key)
		return E_FAIL;

	key->Release();

    CATAttrKind type = key->GetType();
	if (type == tk_integer)
		access->SetInteger(key, (int)content);
	else if (type == tk_double)
		access->SetDouble(key, content);
	else
		return E_FAIL;

	return S_OK;

}

/**
* Gets an algorithm setting. The setting is defined by its attribute name.
* The value of the setting is returned in a double but can be an integer
*/
HRESULT CAAPeoUserAlgorithm::GetSetting(const char* attrName, double &content)
{
	CATISpecAttrAccess_var access = this;	

	CATISpecAttrKey_var key = access->GetAttrKey(attrName);
	if (!key)
		return E_FAIL;

	key->Release();

	CATAttrKind type = key->GetType();
	if (type == tk_integer)
		content = (double) access->GetInteger(key);
	else if (type == tk_double)
		content = access->GetDouble(key);
	else
		return E_FAIL;

	return S_OK;

}


// User implementation
HRESULT CAAPeoUserAlgorithm::GetOptimizationData(CATIOptOptimization_var & spiOptim)
{
	if(!spiOptim)
		return E_FAIL;

	//  -> we get the optimization free parameters = the ones which can be valuated by
	//												 the algorithm to reach the optimization goal.
	CATLISTV(CATBaseUnknown_var) *pFreeParmsList = spiOptim->GetFreeParameters();
	if(!pFreeParmsList)
		return E_FAIL;

	_freeParmsList = (*pFreeParmsList);
	if(!pFreeParmsList->Size())
		return E_FAIL;

	//	-> get the goal parameter (if several were given, only the first one
	//	   is taken in account because we can can optimize only one parameter at one time)
	CATIOptProblem_var spPb = spiOptim->GetProblemToSolve();
	if(!spPb)
		return E_FAIL;
	
	CATLISTV(CATBaseUnknown_var) * pGoalsList = spPb->GetGoals();
	if(!pGoalsList)
		return E_FAIL;

	if(!pGoalsList->Size())
		return E_FAIL;
	
	_spOptGoal = (*pGoalsList)[1];
	if(!_spOptGoal)
		return E_FAIL;

	// Notice that you can launch an optimization without saving historic in file
	// => _spUserAlgoOptimLog will be checked just before using it
	_spUserAlgoOptimLog = spiOptim->GetOptimizationLog();	

	return S_OK;
}


HRESULT CAAPeoUserAlgorithm::BuildUserRelation()
{

	if(!_spOptGoal)
		return E_FAIL;

	CATICkeParm_var spGoalParm = _spOptGoal->GetGoalParameter();
	if(!spGoalParm)
		return E_FAIL;

    CATISpecObject_var spSpec = _spOptGoal;
    CATICkeParmFactory_var spOptFact = spSpec->GetFeatContainer();
    if (!spOptFact)	
        return E_FAIL; 

    _spParmToMinimize = spOptFact->CreateLiteral(spGoalParm->Type(), "ParmToMinimize");



    //CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,spDocParmPublisher,CATCke::True);
	if (!!_spParamSet)
    {
	  CATIParmPublisher_var spParmPublisher = _spParamSet;
	  if (!!spParmPublisher)
	  {
		spParmPublisher->Append(_spParmToMinimize);
	  }
    }

    CATLISTV(CATBaseUnknown_var) inputsList;
    inputsList.Append(spGoalParm);

    CATUnicodeString body;
    
    CATIOptGoal::Type optType = _spOptGoal->GetGoalType();
    if (optType == CATIOptGoal::Minimum) // Minimization
        body = "a1";
    else if (optType == CATIOptGoal::Maximum) // Maximization)
        body = "-a1";
    else
    {// Target value

        CATUnicodeString value;
        CATICkeParm_var spTargetParm = _spOptGoal->GetTargetValue();
        CATICkeInst_var spInst;
        double targetValue;

        if(!spTargetParm)
			return E_FAIL;

        spInst = spTargetParm->Value();
        if(!!spInst)
            targetValue = spInst->AsReal();
        
        CATICkeMagnitude_var spMagnitude = spTargetParm->Type();
		
        // conversion to current unit
        if (!!spMagnitude)
		{
			CATICkeUnit_var spCurrentUnit = spMagnitude->CurrentUnit();
			if(!!spCurrentUnit)
				targetValue = spCurrentUnit->Value(targetValue);
		}


        value.BuildFromNum(targetValue);
        value.ReplaceSubString(",", ".");
        
        if (!!spMagnitude)
            value.Append(spMagnitude->CurrentUnit()->Symbol());
    
        body = CATUnicodeString("abs(a1-");
		body.Append(value);
		body.Append(CATUnicodeString(")"));
    }
            
    _spUserRelation = spOptFact->CreateFormula("OptimFormula", "", "", _spParmToMinimize, &inputsList, body, NULL_var, 0);
 
    //CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,spDocParmPublisher,CATCke::True);
	if (!!_spRelSet)
    {
	  CATIParmPublisher_var spParmPublisher = _spRelSet;
	  if (!!spParmPublisher)
	  {
		spParmPublisher->Append(_spUserRelation);
	  }
    }

	if(!_spUserRelation)
		return E_FAIL;

	return S_OK;
}


