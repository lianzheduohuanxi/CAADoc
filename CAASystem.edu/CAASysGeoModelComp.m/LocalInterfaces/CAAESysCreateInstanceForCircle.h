#ifndef CAAESysCreateInstanceForCircle_H
#define CAAESysCreateInstanceForCircle_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysCircle component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysCircle
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForCircle : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForCircle();
    virtual ~CAAESysCreateInstanceForCircle();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForCircle(const CAAESysCreateInstanceForCircle &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForCircle & operator = (const CAAESysCreateInstanceForCircle &iObjectToCopy);

};
#endif
