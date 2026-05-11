#ifndef CAAESysCreateInstanceForPolyline_H
#define CAAESysCreateInstanceForPolyline_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysPolyline component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysPolyline
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForPolyline : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForPolyline();
    virtual ~CAAESysCreateInstanceForPolyline();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForPolyline(const CAAESysCreateInstanceForPolyline &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForPolyline & operator = (const CAAESysCreateInstanceForPolyline &iObjectToCopy);

};
#endif
