#ifndef CAASysSampRootObj_h
#define CAASysSampRootObj_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysSampRootObj component.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"             // Needed to derive from

class  CAASysSampRootObj : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAASysSampRootObj();
    virtual ~CAASysSampRootObj();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysSampRootObj(const CAASysSampRootObj &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysSampRootObj & operator = (const CAASysSampRootObj &iObjectToCopy);

};

#endif
