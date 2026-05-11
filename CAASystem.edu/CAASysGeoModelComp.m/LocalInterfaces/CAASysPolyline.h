#ifndef CAASysPolyline_H
#define CAASysPolyline_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysPolyline component.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

class  CAASysPolyline : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAASysPolyline();
    virtual ~CAASysPolyline();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysPolyline(const CAASysPolyline &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysPolyline & operator = (const CAASysPolyline &iObjectToCopy);
 
};

#endif
