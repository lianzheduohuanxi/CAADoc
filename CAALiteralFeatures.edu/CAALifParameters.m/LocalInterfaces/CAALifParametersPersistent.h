// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifParametersPersistent_H
#define CAALifParametersPersistent_H


#include "CAALifServices.h"

//LiteralFeatures
#include "CATCke.h"
class CATICkeParmFactory;

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to manage persistent parameters.
// Persistent parameters are literals that you can save in a permanent
// binary form (a CATPart document for example) that persists after they are deleted from memory.
// Here are the parameter types examplified in this sample: 
//   1 ) Simple type parameters (integer, real, string and boolean)
//   2 ) Dimension type parameters (Length and Angle)
//   3 ) Magnitude type parameters other than Length and Angle
//   4 ) Enum type parameters
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALifParametersMain
//  
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CAALifParametersPersistent
//
//===========================================================================

CATCke::Boolean CAALifParametersPersistent(CATICkeParmFactory* ipFact, CAALifServices& iServices);               
#endif








































































