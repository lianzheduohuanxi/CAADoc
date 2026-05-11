#ifndef CAASysPoint_H
#define CAASysPoint_H

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysPoint component.
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"            // to derive from  CATBaseUnknown

class CAASysPoint: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysPoint();
    virtual ~CAASysPoint();
 
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysPoint(const CAASysPoint &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysPoint & operator = (const CAASysPoint &iObjectToCopy);
	
};
#endif
