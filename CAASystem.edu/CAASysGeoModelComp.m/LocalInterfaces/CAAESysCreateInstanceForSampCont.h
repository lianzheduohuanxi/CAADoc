#ifndef CAAESysCreateInstanceForSampCont_H
#define CAAESysCreateInstanceForSampCont_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysPoint component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysSampCont
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForSampCont : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForSampCont();
    virtual ~CAAESysCreateInstanceForSampCont();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForSampCont(const CAAESysCreateInstanceForSampCont &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForSampCont & operator = (const CAAESysCreateInstanceForSampCont &iObjectToCopy);

};
#endif
