#ifndef CAAESysCreateInstanceForEllipse_H
#define CAAESysCreateInstanceForEllipse_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysEllipse component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysEllipse
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForEllipse : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForEllipse();
    virtual ~CAAESysCreateInstanceForEllipse();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForEllipse(const CAAESysCreateInstanceForEllipse &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForEllipse & operator = (const CAAESysCreateInstanceForEllipse &iObjectToCopy);

};
#endif
