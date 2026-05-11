// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAATopVariableFillets_H
#define CAATopVariableFillets_H


class CATGeoFactory;
class CATTopData;
class CATBody;

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to create a variable radius/chord fillet
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAATopFilletsMain
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
//  CAATopVariableFillets
//
//===========================================================================

int CAATopVariableFillets(CATGeoFactory * iFactory, CATTopData * iTopData, CATBody * iBody,int iRadiusType = 0);               
#endif








































































