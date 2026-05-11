//COPYRIGHT DASSAULT SYSTEMES  19994 2000

#ifndef CAALifParametersMani_H
#define CAALifParametersMani_H

class CATIContainer_var;

//LiteralFeatures
class CATICkeParmFactory;

#include "CATCke.h"
#include "CAALifServices.h"
// =============================================================================
//
// ABSTRACT
// --------
//
// Illustrates how to associate a manipulator with a literal
// When you modify a parameter value, you use the use the up and down
// arrows to increment or decrement the amount to be specified. 
// This object which is made up of the up and down arrows is called a spinner.
// The object which describes how the spinner behaves is called a manipulator.
//
// =============================================================================
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
//  CAALifParametersMani
//
//===========================================================================

CATCke::Boolean CAALifParametersMani(CATICkeParmFactory* ipFact, CAALifServices& iServices);

CATCke::Boolean CAALifParametersPersistentMani(CATICkeParmFactory* ipFact,CAALifServices& iServices);               
               
#endif








































































