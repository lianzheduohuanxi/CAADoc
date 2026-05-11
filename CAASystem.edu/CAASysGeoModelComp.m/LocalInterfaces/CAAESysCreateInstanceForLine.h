#ifndef CAAESysCreateInstanceForLine_H
#define CAAESysCreateInstanceForLine_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysLine component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysLine
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForLine : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForLine();
    virtual ~CAAESysCreateInstanceForLine();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForLine(const CAAESysCreateInstanceForLine &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForLine & operator = (const CAAESysCreateInstanceForLine &iObjectToCopy);

};
#endif
