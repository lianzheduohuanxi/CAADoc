#ifndef CAAESysCreateInstanceForPoint_H
#define CAAESysCreateInstanceForPoint_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysPoint component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysPoint
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForPoint : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForPoint();
    virtual ~CAAESysCreateInstanceForPoint();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForPoint(const CAAESysCreateInstanceForPoint &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForPoint & operator = (const CAAESysCreateInstanceForPoint &iObjectToCopy);

};
#endif
