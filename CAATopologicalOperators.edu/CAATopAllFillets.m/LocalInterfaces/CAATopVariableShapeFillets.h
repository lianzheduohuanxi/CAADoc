// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAATopVariableShapeFillets_H
#define CAATopVariableShapeFillets_H

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATCompositeLaw;

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to create a shape fillet with external radius law
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
//  CAATopVariableShapeFillets
//
//===========================================================================

int CAATopVariableShapeFillets(CATGeoFactory * iFactory, CATTopData * iTopData,
                            CATBody * iRightBody, CATBody * iLeftBody,
                            CATBody * iSpineBody, CATCompositeLaw * iLaw
                            );

#endif // CAATopVariableShapeFillets_H








































































