#ifndef CAASysCircle_H
#define CAASysCircle_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysCircle component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown


class  CAASysCircle : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysCircle();
    virtual ~CAASysCircle();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCircle(const CAASysCircle &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCircle & operator = (const CAASysCircle &iObjectToCopy);

};
#endif
