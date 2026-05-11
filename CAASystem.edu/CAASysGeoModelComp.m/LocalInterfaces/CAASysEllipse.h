#ifndef CAASysEllipse_H
#define CAASysEllipse_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysEllipse component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown


class  CAASysEllipse : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysEllipse();
    virtual ~CAASysEllipse();
   
  private:
  
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysEllipse(const CAASysEllipse &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysEllipse & operator = (const CAASysEllipse &iObjectToCopy);

};
#endif
