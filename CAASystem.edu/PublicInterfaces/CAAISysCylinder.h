#ifndef CAAISysCylinder_H
#define CAAISysCylinder_H

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a Cylinder object.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
// Syteme Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Mathematics Framework
class CATMathPoint;       // Needed by SetOrigin & GetOrigin

// Local Framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysCylinder;


class ExportedByCAASysGeoModelInf CAAISysCylinder : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :


  // The Cylinder is defined by:
  // ------------------------
    
  // It's radius in the space
  // -------------------------
  virtual  HRESULT     SetRadius(const float iRadius) =0;
  virtual  HRESULT     GetRadius(float & oRadius) const =0;


  // The extrusion line is defined between the base and the top point
  // ----------------------------------------------------------------

  virtual  HRESULT     SetBasePoint(const CATMathPoint & iBasePoint ) = 0;
  virtual  HRESULT     GetBasePoint(CATMathPoint & oBasePoint )   const =0;
  
  virtual  HRESULT     SetTopPoint(const CATMathPoint & iTopPoint ) = 0;
  virtual  HRESULT     GetTopPoint(CATMathPoint & oTopPoint )   const =0;
};

#endif
