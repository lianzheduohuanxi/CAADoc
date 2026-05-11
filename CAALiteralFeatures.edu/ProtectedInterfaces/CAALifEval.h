// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifEval_h
#define CAALifEval_h

//====================================================================
//  ABSTRACT
//  
//  The evaluator purpose is to specify how to compute the user function
//  described by its signature in CAALifDicoLibrary. 
//====================================================================

// LiteralFeatures
#include "CATICkeRelationForwards.h"
#include "CATCkeEvalContext.h"


void _caalifeval0 (CATCkeListOfParm iArguments,
				   const CATICkeParm_var &iReturnValue,
				   const CATCkeEvalContext *iEvaluationContext);

#endif




