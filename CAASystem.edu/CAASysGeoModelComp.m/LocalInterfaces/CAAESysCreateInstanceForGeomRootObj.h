#ifndef CAAESysCreateInstanceForGeomRootObj_H
#define CAAESysCreateInstanceForGeomRootObj_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension of the CAASysGeomRootObj component and implementing the 
//  CATICreateInstance interface.
//
//  This Interface allows to create a component: CAASysGeomRootObj
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class CAAESysCreateInstanceForGeomRootObj : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCreateInstanceForGeomRootObj();
    virtual ~CAAESysCreateInstanceForGeomRootObj();

    // CATICreateInstance 
    // -------------------

    virtual HRESULT __stdcall CreateInstance(void **oppv);

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForGeomRootObj(const CAAESysCreateInstanceForGeomRootObj &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCreateInstanceForGeomRootObj & operator = (const CAAESysCreateInstanceForGeomRootObj &iObjectToCopy);

};
#endif
