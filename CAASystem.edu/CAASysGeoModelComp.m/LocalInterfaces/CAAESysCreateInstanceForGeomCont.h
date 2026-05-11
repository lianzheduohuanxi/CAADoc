#ifndef CAAESysCreateInstanceForGeomCont_H
#define CAAESysCreateInstanceForGeomCont_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysGeomCont component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysGeomCont
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForGeomCont: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForGeomCont();
    virtual ~CAAESysCreateInstanceForGeomCont();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForGeomCont(const CAAESysCreateInstanceForGeomCont&iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForGeomCont & operator = (const CAAESysCreateInstanceForGeomCont&iObjectToCopy);

};
#endif
