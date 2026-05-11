// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAATopConstantFillets_H
#define CAATopConstantFillets_H

class CATGeoFactory;
class CATTopData;
class CATBody;

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to create a constant radius/chord fillet
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
//  CAATopConstantFillets
//
//===========================================================================

int CAATopConstantFillets(CATGeoFactory * iFactory, CATTopData * iTopData, CATBody * iBody, int iRadiusType = 0);               
#endif








































































