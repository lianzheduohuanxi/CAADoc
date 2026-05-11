#ifndef CAAESysCreateInstanceForCylinder_H
#define CAAESysCreateInstanceForCylinder_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysCylinder component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysCylinder
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForCylinder : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForCylinder();
    virtual ~CAAESysCreateInstanceForCylinder();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForCylinder(const CAAESysCreateInstanceForCylinder &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForCylinder & operator = (const CAAESysCreateInstanceForCylinder &iObjectToCopy);

};
#endif
