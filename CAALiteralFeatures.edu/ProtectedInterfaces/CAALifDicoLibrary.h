#ifndef CAALifDicoLibrary_H
#define CAALifDicoLibrary_H

// COPYRIGHT DASSAULT SYSTEMES  1994 2000


//=========================================================================================
// ABSTRACT
//  
// The LiteralFeatures framework allows you to create user functions.
// Example: Hypothenuse = SQRT(X*X + Y*Y)
// This user function can be used within a relation. If "Hypothenuse" has been added to
// the "Formulas" dictionary, the end-user can create a formula using this user function
// Example: Formula1: Hypothenuse(A,B)*10
// 
// To create a user function, you must:
//    1 -  Declare that you add a function with a given signature to the dictionary
//         (CAALifDicoLibrary.cpp). To do this, you have to create an implementation of 
//          CATIAddLibrary. The only method to implement is CATIAddLibrary::Add 
//          No matter you create one or more user functions, only one library is required.
//    2 -  Provide an evaluator (CAALifEval.cpp)
//    3 -  Provide an implementation of CATICreateInstance (System) in an extension of the code  
//         which describes the user function (CAALifDicoLibrary) - This implemenattaion is 
//         provided in CAALifCreateExt.cpp
// 
//==========================================================================
//  Usage:
//  ------
//		new CAALifDicoLibrary()
//		Add().
//  
//===========================================================================
//  Inheritance:
//  ------------
//         Inherits from CATBaseUnknown.
//
//===========================================================================
//  Return Codes:
//  ------------
//         None
//
//===========================================================================

#include "CATBaseUnknown.h"


class CAALifDicoLibrary : public CATBaseUnknown 
{
  public :

    //---------------------------------------------------------------------------
    // The constructors below are not used
    // To create a CAALifDictionary, we use the CATICreateInstance implementation
    //---------------------------------------------------------------------------
    CAALifDicoLibrary (){};
    CAALifDicoLibrary (const CAALifDicoLibrary&){};
    virtual ~CAALifDicoLibrary (){};

    //---------------------------------------------------------------------------
    // Describe your user function with its signature, arguments and evaluator
    //---------------------------------------------------------------------------
    virtual void Add ();

    CATDeclareClass;
} ;

#endif







































































