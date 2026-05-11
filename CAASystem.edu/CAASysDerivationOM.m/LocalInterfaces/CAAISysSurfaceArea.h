#ifndef CAAISysSurfaceArea_h
#define CAAISysSurfaceArea_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface to compute the area of a surface.
//
//===========================================================================

// System Framework
#include <CATBaseUnknown.h>           //Needed to derive from CATBaseUnknown

// Global Unique IDentifier defined in .cpp 
extern IID IID_CAAISysSurfaceArea;

class CAAISysSurfaceArea : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

     virtual HRESULT ComputeArea(float & oArea)  = 0;
 
};


#endif
