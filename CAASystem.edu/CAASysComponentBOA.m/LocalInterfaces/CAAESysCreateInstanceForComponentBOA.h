#ifndef CAAESysCreateInstanceForComponentBOA_H
#define CAAESysCreateInstanceForComponentBOA_H

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysComponentBOA component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows you to create a component: CAASysComponentBOA
//
//  See the CAASysUseBOA module which contains a sample to use
//  this fonctionality.
// 
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForComponentBOA : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForComponentBOA();
    virtual ~CAAESysCreateInstanceForComponentBOA();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForComponentBOA(const CAAESysCreateInstanceForComponentBOA &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForComponentBOA & operator = (const CAAESysCreateInstanceForComponentBOA &iObjectToCopy);

};
#endif
