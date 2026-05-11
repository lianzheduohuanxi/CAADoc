// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAATopTriTangentFillets_H
#define CAATopTriTangentFillets_H

class CATGeoFactory;
class CATTopData;
class CATBody;

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to create a tri tangent fillet
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
//  CAATopTriTangentFillets
//
//===========================================================================

int CAATopTriTangentFillets(CATGeoFactory * iFactory, CATTopData * iTopData,
                            CATBody * iRightBody, CATBody * iLeftBody, CATBody * iRemoveBody
                            );               
#endif








































































