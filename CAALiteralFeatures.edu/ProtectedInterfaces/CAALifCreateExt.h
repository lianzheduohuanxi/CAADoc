//  COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifCreateExt_H
#define CAALifCreateExt_H



//==================================================================================
// ABSTRACT
//
// Required to call the user function code at run-time. 
// CAALifCreateExt is a code extension of CAALifDicoLibrary whose purpose is to declare
// a user function. 
// This extension should implement CATICreateInstance to be able to create dynamically
// a CAALifDicoLibrary object.
//==================================================================================

#include "CATBaseUnknown.h"


class CAALifCreateExt : public CATBaseUnknown 
{
  public :

    //-------------------------------
    // Constructors (not used)
    //-------------------------------
    CAALifCreateExt (){};
    CAALifCreateExt (const CAALifCreateExt&){};

    //-------------------------------
    // Destructor
    //-------------------------------
    virtual ~CAALifCreateExt (){};

    //-------------------------------
    // Create a CAALifDicoLibrary object and returns its pointer.
    //-------------------------------
    virtual HRESULT __stdcall CreateInstance (void **ppv);

  CATDeclareClass;
  
} ;

#endif







































































