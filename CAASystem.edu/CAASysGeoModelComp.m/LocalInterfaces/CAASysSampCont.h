#ifndef CAASysSampCont_H
#define CAASysSampCont_H

// COPYRIGHT DASSAULT SYSTEMES 1999
  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysSampCont component.
//
//  This component is the container of the document, that is to say an object
//  which creates and contains all the document's object.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class  CAASysSampCont: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysSampCont();
    virtual ~CAASysSampCont();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysSampCont(const CAASysSampCont &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysSampCont & operator = (const CAASysSampCont &iObjectToCopy);
  
};
#endif
