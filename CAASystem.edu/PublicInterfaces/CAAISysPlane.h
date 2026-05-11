#ifndef CAAISysPlane_H
#define CAAISysPlane_H

// COPYRIGHT DASSAULT SYSTEMES 1999
    
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a plane object.
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
//  SetPlane/GetPlane
//
//===========================================================================
// Syteme Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Mathematics Framework
class CATMathPoint;   // Needed by SetOrigin & GetOrigin
class CATMathVector;      // Needed by SetPlane  & GetPlane 

// Local Framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysPlane;


class ExportedByCAASysGeoModelInf CAAISysPlane : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :


  // The plane is defined by:
  // ------------------------
    
  // It's origin  in the space
  // -------------------------
  virtual  HRESULT     SetOrigin(const CATMathPoint & iOrigin) =0;
  virtual  HRESULT     GetOrigin(CATMathPoint & oOrigin) const =0;


  // It's U and V axis
  // -------------------------

  virtual  HRESULT     SetPlane (const CATMathVector & iU,
		                 const CATMathVector & iV) =0 ;

  virtual  HRESULT     GetPlane (CATMathVector & iU,
		                 CATMathVector & iV)  const =0;
 
};

#endif
