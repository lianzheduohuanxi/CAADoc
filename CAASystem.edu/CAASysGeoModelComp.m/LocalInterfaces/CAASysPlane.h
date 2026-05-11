#ifndef CAASysPlane_H
#define CAASysPlane_H

// COPYRIGHT DASSAULT SYSTEMES 1999
     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysPlane component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

class  CAASysPlane : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysPlane();
    virtual ~CAASysPlane();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysPlane(const CAASysPlane &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysPlane & operator = (const CAASysPlane &iObjectToCopy);


};
#endif
