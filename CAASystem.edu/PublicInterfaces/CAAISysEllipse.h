#ifndef CAAISysEllipse_H
#define CAAISysEllipse_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes an ellipse object.
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
//  SetCenter/GetCenter
//  SetRadius/GetRadius
//  SetPlanar/GetPlanar
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Mathematics Framework
class CATMathPoint;      // Needed by GetCenter & SetCenter 
class CATMathVector;    // Needed by SetPlanar & GetPlanar

// local Framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysEllipse;


class ExportedByCAASysGeoModelInf CAAISysEllipse : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  // The ellipse is represented by:
  // ------------------------------

  // A Point center
  // ---------------
  virtual  HRESULT   SetCenter(const CATMathPoint & iCenter)  =0 ;
  virtual  HRESULT   GetCenter(CATMathPoint & oCenter)        const =0 ;

  // A radius along X and Y axis
  // ---------------------------

  virtual  HRESULT   SetRadius(const float iXRadius, 
                               const float iYRadius)           =0 ;

  virtual  HRESULT   GetRadius(float & oXRadius, 
                               float & oYRadius)               const =0 ;

  // A Repere 
  // --------
  // iNormal defined the normal of the plane
  // iAxis   defined the X axis. The Y axis = iNormal ^ iAxis .
  //
  virtual  HRESULT   SetPlanar(const CATMathVector & iNormal, 
                               const CATMathVector & iAxis)   =0 ;

  virtual  HRESULT   GetPlanar(CATMathVector & oNormal ,
                               CATMathVector & oAxis)         const =0 ;   

};

#endif
