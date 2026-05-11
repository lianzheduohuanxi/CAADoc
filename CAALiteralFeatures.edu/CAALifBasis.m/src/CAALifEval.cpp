// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#include "CAALifEval.h"

// C++ headers
#include "math.h"
#include "iostream.h"

// LiteraFeatures
#include "CATICkeParm.h"
#include "CATICkeInst.h"
#include "CATCkeEvalContext.h"

// =========================================================
// ABSTRACT
//
// To write your evaluator:
// 1 - retrieve your expected parameters : Inputs and Outputs (if any)
// 2 - retrieve the input values from the parameters
// 3 - compute the result     
// 4 - assign the result to the output parameters
//
// Note : the "Evaluation Context" should not be used in the present
//         version of CATIA
// =========================================================

void _caalifeval0 (
                     CATCkeListOfParm ipArguments,
						const CATICkeParm_var &ispReturnValue,
						const CATCkeEvalContext *iEvaluationContext )
{
  // Retrieve parameters (inputs and output)
  CATICkeParm_var spParameterA =  (*ipArguments)[1];
  CATICkeParm_var spParameterB =  (*ipArguments)[2];

  // As declared in the definition of the function in CAALifDicoLibrary.cpp,
  // parameterA and parameterB are input arguments

  // Retrieve the parameter input values
  double A = spParameterA->Value()->AsReal ();
  double B = spParameterB->Value()->AsReal ();

  // Perform the computation 
  // (O equals sqrt(A*A + B*B)
  double O = sqrt(A*A+B*B);
  cout << "Evaluating SQRT(A*A + B*B): " << O << endl;
  
  //Assign a value to iReturnValue
  ispReturnValue->Valuate(O);
}

