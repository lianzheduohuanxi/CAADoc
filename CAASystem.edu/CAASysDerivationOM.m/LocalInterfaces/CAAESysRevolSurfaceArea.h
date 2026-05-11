#ifndef CAAESysRevolSurfaceArea_H
#define CAAESysRevolSurfaceArea_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAASysRevolSurface component implementing the 
//  CAAISysSurfaceArea interface. 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   // to derive from  CATBaseUnknown


class CAAESysRevolSurfaceArea: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysRevolSurfaceArea();
    virtual ~CAAESysRevolSurfaceArea();

    virtual HRESULT ComputeArea(float & oArea) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysRevolSurfaceArea(const CAAESysRevolSurfaceArea &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysRevolSurfaceArea & operator = (const CAAESysRevolSurfaceArea &iObjectToCopy);

};
#endif
