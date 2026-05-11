#ifndef CAAESysCreateInstanceForPlane_H
#define CAAESysCreateInstanceForPlane_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysPlane component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysPlane
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForPlane : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForPlane();
    virtual ~CAAESysCreateInstanceForPlane();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForPlane(const CAAESysCreateInstanceForPlane &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForPlane & operator = (const CAAESysCreateInstanceForPlane &iObjectToCopy);

};
#endif
