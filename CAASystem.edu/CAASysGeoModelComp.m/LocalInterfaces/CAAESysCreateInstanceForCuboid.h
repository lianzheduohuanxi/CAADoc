#ifndef CAAESysCreateInstanceForCuboid_H
#define CAAESysCreateInstanceForCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysCuboid component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysCuboid
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForCuboid : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForCuboid();
    virtual ~CAAESysCreateInstanceForCuboid();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForCuboid(const CAAESysCreateInstanceForCuboid &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForCuboid & operator = (const CAAESysCreateInstanceForCuboid &iObjectToCopy);

};
#endif
