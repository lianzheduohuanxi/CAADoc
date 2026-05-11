#ifndef CAAISysCuboid_H
#define CAAISysCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a Cuboid object.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  SetOrigin/GetOrigin
//  SetCuboid/GetCuboid
//
//===========================================================================
// Syteme Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Mathematics Framework
class CATMathPoint;      // Needed by SetOrigin & GetOrigin
class CATMathVector;      // Needed by SetVectors  & SetVectors 

// Local Framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysCuboid;

class ExportedByCAASysGeoModelInf CAAISysCuboid : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :


  // The Cuboid is defined by:
  // ------------------------
    
  // It's origin  in the space
  // -------------------------
  virtual  HRESULT     SetOrigin(const CATMathPoint & iOrigin) =0;
  virtual  HRESULT     GetOrigin(CATMathPoint & oOrigin) const =0;


  // V1 = Width 
  // V2 = Depth
  // V3 = Height
  // -------------------------

  virtual  HRESULT     SetVectors (const CATMathVector & iV1,
		                 const CATMathVector & iV2,
						 const CATMathVector & iV3) =0 ;

  virtual  HRESULT     GetVectors(CATMathVector & oV1,
		                 CATMathVector & oV2,
						 CATMathVector & oV3)  const =0;
 
};

#endif
