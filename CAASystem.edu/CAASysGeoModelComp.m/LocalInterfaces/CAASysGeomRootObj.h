#ifndef CAASysGeomRootObj_h
#define CAASysGeomRootObj_h

// COPYRIGHT DASSAULT SYSTEMES 1999
  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysGeomRootObj component.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"             // Needed to derive from

class  CAASysGeomRootObj : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAASysGeomRootObj();
    virtual ~CAASysGeomRootObj();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysGeomRootObj(const CAASysGeomRootObj &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysGeomRootObj & operator = (const CAASysGeomRootObj &iObjectToCopy);

};

#endif
