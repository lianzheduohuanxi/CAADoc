// COPYRIGHT DASSAULT SYSTEMES  2002
//-------------------------------------------------------------
//
// Implementation of the CATIOptAlgorithm interface
// for the feature CAAPeoUserAlgo.
// Notice that your implementation has to derive from
// CATOptAlgorithmAdapter (and then, it can not be a code extension
// since CATOptAlgorithmAdapter class has member variables).
//
// In the current .dic, we have added the following row:
// CAAPeoUserAlgo		CATIOptAlgorithm	LibCAAPeoCreateUserAlgorithm
//
//-------------------------------------------------------------

#ifndef CAAPeoUserAlgorithm_H
#define CAAPeoUserAlgorithm_H

// Optimization Interfaces
#include "CATOptAlgorithmAdapter.h" // adapter extension
#include "CATIOptGoal.h"
#include "CATIOptimizationLog.h"

// system
#include "CATListOfInt.h"

// LiteralFeatures
#include "CATICkeType.h" 
#include "CATICkeParm.h"
#include "CATICkeRelationExp.h"

#include "CATIParmPublisher.h"
#include "CATICkeParameterSet.h"

class CAAPeoUserAlgorithm: public CATOptAlgorithmAdapter
{
	CATDeclareClass;
	
public:
	
	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	CAAPeoUserAlgorithm ();
	virtual ~CAAPeoUserAlgorithm ();
	
    /**
	* The algorithm code is written here. It is a loop of the following type :
	* while the termination criteria are not reached, do a modification of
	* the inputs values, update the outputs and check the termination criteria.
	* To do that, you will have to call the protected methods of the mother class in the
	* following order :
	*
	* InitUpdate()
	* BeforeFirstUpdate()
	*
	* While (...)
	* {
	*		If("it is the last update")
	*			BeforeLastUpdate()
	*
	*		LaunchUpdate()		
	* }
	*
	* AfterLastUpdate()
	*
	* @param spiOptim
	* The optimization linked to this algorithm. It is used to access the update
	* engine used in the InitUpdate() and LaunchUpdate() methods. In most cases
	* the algorithm is working on its optimization free parameters and goals, so
	* that the optimization may be used to get the inputs and outputs to update.
	* @return
	* S_OK if the operation succeeded, E_FAIL else
	*/
	virtual HRESULT Run (CATIOptOptimization_var & spiOptim);

	/**
	* This method checks if the global optimization definition is 
	* compatible with the current algorithm. For example, your
	* algorithm may not be able to run if the optimization has
	* only constraints and no parameter to optimize so that the optimization
	* won't be compatible with the current algorithm.
	* The OptimizerUI will prevent the algorithm from running if at least
	* one error is sent or if this method returns E_FAIL.
	* @param iOptim
	* The optimization you want to check compatibility with.
	* @return
	* S_OK if the algorithm is compatible with the optimization, E_FAIL else.
	*/
	virtual HRESULT CheckCompatibility(CATIOptOptimization_var &iOptim);

	/**
	* Sets an algorithm setting. This setting is defined by its attribute name. 
    * The value of the setting is given as a double (but can be an integer).
	* @return
	* S_OK if the operation succeeded, E_FAIL else (non existing attribute).
	*/
	virtual HRESULT SetSetting(const char* attrName, double content);

	
	/**
	* Gets an algorithm setting. The setting is defined by its attribute name. 
    * The value of the setting is returned in a double but can be an integer.
	* @return
	* S_OK if the operation succeeded, E_FAIL else (non existing attribute).
	*/
	virtual HRESULT GetSetting(const char* attrName, double &content);


	
protected:

	HRESULT GetOptimizationData(CATIOptOptimization_var & spiOptim);
	HRESULT BuildUserRelation();

private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	CAAPeoUserAlgorithm (CAAPeoUserAlgorithm &);
	CAAPeoUserAlgorithm& operator=(CAAPeoUserAlgorithm&);

	// member variables : in this optimization, one or many free parameters,
	//					  but only one parameter to optimize.
	CATLISTV(CATBaseUnknown_var) _freeParmsList;
	CATIOptGoal_var _spOptGoal;

	CATICkeRelationExp_var _spUserRelation; // used to apply the same treatment for the three optimization types :
											// Maximization, Minimization and Target Value
	CATICkeParm_var _spParmToMinimize;

	CATIOptimizationLog_var _spUserAlgoOptimLog;
	CATICkeParameterSet_var _spParamSet;
	CATIParmPublisher_var _spRelSet;
};

//-----------------------------------------------------------------------

#endif
