#ifndef CAAESysCreateInstanceForRevolSurface_H
#define CAAESysCreateInstanceForRevolSurface_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysRevolSurface component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysRevolSurface
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForRevolSurface : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForRevolSurface();
    virtual ~CAAESysCreateInstanceForRevolSurface();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForRevolSurface(const CAAESysCreateInstanceForRevolSurface &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForRevolSurface & operator = (const CAAESysCreateInstanceForRevolSurface &iObjectToCopy);

};
#endif
