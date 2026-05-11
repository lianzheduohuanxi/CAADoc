#ifndef CAAESysCreateInstanceForSurface_H
#define CAAESysCreateInstanceForSurface_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysSurface component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysSurface
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForSurface : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForSurface();
    virtual ~CAAESysCreateInstanceForSurface();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForSurface(const CAAESysCreateInstanceForSurface &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForSurface & operator = (const CAAESysCreateInstanceForSurface &iObjectToCopy);

};
#endif
