#ifndef CAASysCuboid_H
#define CAASysCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysCuboid component.
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"            // to derive from  CATBaseUnknown

class CAASysCuboid: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysCuboid();
    virtual ~CAASysCuboid();
 
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCuboid(const CAASysCuboid &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysCuboid & operator = (const CAASysCuboid &iObjectToCopy);
	
};
#endif
