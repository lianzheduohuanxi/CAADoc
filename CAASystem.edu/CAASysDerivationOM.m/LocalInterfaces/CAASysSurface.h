#ifndef CAASysSurface_H
#define CAASysSurface_H

// COPYRIGHT DASSAULT SYSTEMES 2000
 
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysSurface component.
//  
//  This class declares, with the macros CATDeclareClass (in the header file) 
//  and CATImplementClass (in the cpp file), that's CAASysSurface
//  is an Object Modeler component
//  
//
//  Interfaces implemented (by extension) by this component:
//
//  -----------------------
//  |                     |
//  | CAASysSurface       |-o CAAISysSurfaceProperties  
//  |                     | 
//  |                     |-o CAAISysSurfaceArea    
//  ----------------------
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"  //Needed to derive from CATBaseUnknown


class CAASysSurface : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysSurface();
    virtual ~CAASysSurface();
  
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysSurface(const CAASysSurface &iObjectToCopy );

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysSurface & operator = (const CAASysSurface &iObjectToCopy );
};
#endif
