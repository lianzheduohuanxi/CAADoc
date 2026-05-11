// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombCrvMf3DBehavior
//    Implementation of interface CATIMf3DBehavior for V5V6ExtCombinedCurve 
//
// Note :  CAAEV5V6ExtMmrCombCrvMf3DBehavior is the same use case as  CAAEMmrCombCrvMf3DBehavior. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//====================================================================================

// Local CAAV5V6MechanicalModeler.edu framework 
#include "CAAEV5V6ExtMmrCombCrvMf3DBehavior.h"

// C++ Standard library
#include "iostream.h"

CATImplementClass(CAAEV5V6ExtMmrCombCrvMf3DBehavior, DataExtension, CATIMf3DBehavior, V5V6ExtCombinedCurve);
CATImplementBOA(CATIMf3DBehavior,CAAEV5V6ExtMmrCombCrvMf3DBehavior);

//-----------------------------------------------------------------------------
// To declare that V5V6ExtCombinedCurve implements CATIMf3DBehavior, insert 
// the following line in the interface dictionary:
//
// V5V6ExtCombinedCurve  CATIMf3DBehavior  libCAAV5V6MmrCombinedCurve


//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombCrvMf3DBehavior::CAAEV5V6ExtMmrCombCrvMf3DBehavior()
{
	cout <<" CAAEV5V6ExtMmrCombCrvMf3DBehavior::CAAEV5V6ExtMmrCombCrvMf3DBehavior" << endl;
}

//-------------------------------------------------------------------------------------
CAAEV5V6ExtMmrCombCrvMf3DBehavior::~CAAEV5V6ExtMmrCombCrvMf3DBehavior()
{
	cout <<" CAAEV5V6ExtMmrCombCrvMf3DBehavior::~CAAEV5V6ExtMmrCombCrvMf3DBehavior" << endl;
}

//-------------------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombCrvMf3DBehavior::IsAShape()  const
{
	return S_OK;
}

//-------------------------------------------------------------------------------------
