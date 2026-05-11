#ifndef CAASysComponent_H
#define CAASysComponent_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysComponent component.
//
//  See the CAASysComponentCreate module which contains a sample to use
//  this component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown


class  CAASysComponent : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysComponent();
    virtual ~CAASysComponent();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysComponent(const CAASysComponent &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysComponent & operator = (const CAASysComponent &iObjectToCopy);

};
#endif
