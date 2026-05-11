#ifndef CAALifDesignTableAccess_H
#define CAALifDesignTableAccess_H

// COPYRIGHT DASSAULT SYSTEMES  2000

class CATIContainer_var;

#include "CATCke.h"

//=============================================================================
//  
//  ABSTRACT:
//  ---------
//
//  Creates a formula using the "Hypothenuse" user function.
//  Given x and y, two input arguments,the user function returns sqrt(x*x + y*y)
//  The function signature is created in the CAALifDicoLibrary.cpp file of the
//  CAALifBasis.m module. 
//  The function evaluator is defined in the CAALifEval.cpp file of 
//  the CAALifBasis.m module.    
//
//     Checks the validity of the user function and illustrates:
//       * How to create a formula using a user function in its expression
//       * How to determine whether s formula synatx is correct
//         
//=============================================================================

CATCke::Boolean CAALifDesignTableAccess(CATIContainer_var);               
#endif








































































