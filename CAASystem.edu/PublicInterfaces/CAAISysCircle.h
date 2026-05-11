#ifndef CAAISysCircle_H
#define CAAISysCircle_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a circle object.
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

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Mathematics framework
class CATMathPoint;     // Needed by GetCenter & SetCenter 
class CATMathVector ; // Needed by SetPlanar & GetPlanar

// Local framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysCircle;

class ExportedByCAASysGeoModelInf CAAISysCircle : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

    // The circle is defined by: 
    // ------------------------

    //  A point center 
    // -------------------
    virtual  HRESULT     SetCenter(const CATMathPoint & iCenter)  =0 ;
    virtual  HRESULT     GetCenter(CATMathPoint & oCenter) const  =0 ;

    //  A radius
    // -------------------
    virtual  HRESULT     SetRadius(const float iRadius)           =0 ;
    virtual  HRESULT     GetRadius(float & oRadius)        const  =0 ;


    //  A repere defined by its 2 vectors
    // ----------------------------------
    //  iNormal represents the normal of the plane
    //  iAxis   represents the beginning of the circle.
    //
    virtual  HRESULT     SetPlanar(const CATMathVector & iNormal , 
		                           const CATMathVector & iAxis)   =0 ;

    virtual  HRESULT     GetPlanar(CATMathVector & oNormal ,
		                           CATMathVector & oAxis)  const  =0 ;   

};
#endif
