#ifndef CAAESysSurfaceArea_H
#define CAAESysSurfaceArea_H

// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the component CAASysSurface implementing the 
//  CAAISysSurfaceArea interface. 
//
//===========================================================================

#include "CATBaseUnknown.h"   // to derive from  CATBaseUnknown


class CAAESysSurfaceArea: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysSurfaceArea();
    virtual ~CAAESysSurfaceArea();

    virtual HRESULT ComputeArea(float & oArea) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysSurfaceArea(const CAAESysSurfaceArea &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysSurfaceArea & operator = (const CAAESysSurfaceArea &iObjectToCopy);

};
#endif
