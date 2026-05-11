// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifParametersRights_H
#define CAALifParametersRights_H

//LiteralFeatures
class CATICkeParmFactory;
// ==========================================================
//
// ABSTRACT
// --------
// 
// Illustrates how to:
//   * determine the access rights of a parameter
//   * set the access rights of a parameter
// ==========================================================
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
//  CAALifParametersRights
//
//=========================================================================== 
class CATIContainer_var;

#include "CATCke.h"
#include "CAALifServices.h"
CATCke::Boolean CAALifParametersRights(CATICkeParmFactory* ipFact,CAALifServices& iServices);               
#endif








































































