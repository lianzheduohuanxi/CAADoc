#ifndef CAAESysCreateInstanceForSampRootObj_H
#define CAAESysCreateInstanceForSampRootObj_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysSampRootObj component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysSampRootObj
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForSampRootObj : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForSampRootObj();
    virtual ~CAAESysCreateInstanceForSampRootObj();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForSampRootObj(const CAAESysCreateInstanceForSampRootObj &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForSampRootObj & operator = (const CAAESysCreateInstanceForSampRootObj &iObjectToCopy);

};
#endif
