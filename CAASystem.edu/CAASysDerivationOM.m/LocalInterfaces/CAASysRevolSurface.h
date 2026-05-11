#ifndef CAASysRevolSurface_H
#define CAASysRevolSurface_H

// COPYRIGHT DASSAULT SYSTEMES 2000
 
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation class of the CAASysRevolSurface component.
//  
//  This class must C++ derives from the implementation class
//  of the component CAASysSurface (ie the CAASysSurface class ).
//  
//  This class declares too, with the macros CATDeclareClass (in the header file) 
//  and CATImplementClass (in the cpp file), that's the component named, 
//  CAASysRevolSurface, Object Modeler (OM) derives from the CAASysSurface 
//  component.
//  
// 
//  -----------------------
//  |                     |
//  | CAASysSurface       |-o CAAISysSurfaceProperties 
//  |                     |
//  | impl                |-o CAAISysSurfaceArea    
//  ---+-----------------+-
//     |                 |
//     | C++ Derivation  | OM Derivation 
//     | of the          | of the component
//     | implementation  |
//     |                 |
//     |                 |
//     |                 |
//  ---^-----------------^---
//  | impl                  |
//  |                       |-o CAAISysRevolAxis
//  |                       |
//  |  CAASysRevolSurface   |-o CAAISysSurfaceArea      
//  |                       |
//  -------------------------
//
//
//
//===========================================================================

// System Framework
#include "CAASysSurface.h"  //Needed to derive from CAASysSurface


class CAASysRevolSurface : public CAASysSurface
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAASysRevolSurface();
    virtual ~CAASysRevolSurface();
  
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysRevolSurface(const CAASysRevolSurface &iObjectToCopy );

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAASysRevolSurface & operator = (const CAASysRevolSurface &iObjectToCopy );
};
#endif
