#ifndef CAAESysCreateInstanceForComponent_H
#define CAAESysCreateInstanceForComponent_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysComponent component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows you to create a component: CAASysComponent
//
//  See the CAASysComponentCreate module which contains a sample to use
//  this fonctionalite.
// 
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForComponent : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForComponent();
    virtual ~CAAESysCreateInstanceForComponent();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForComponent(const CAAESysCreateInstanceForComponent &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForComponent & operator = (const CAAESysCreateInstanceForComponent &iObjectToCopy);

};
#endif
