#ifndef CAAESysCircle_H
#define CAAESysCircle_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysCircle component and implementing the 
//  CAAISysCircle interface.
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
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by SetCenter & GetCenter
#include "CATMathVector.h"    //Needed by SetPlanar & GetPlanar

class CAAESysCircle : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCircle();
    virtual ~CAAESysCircle();

    // The circle is defined by: 
    // ------------------------

    //  A point center 
    // -------------------
    virtual  HRESULT  SetCenter(const CATMathPoint  & iCenter) ;
    virtual  HRESULT  GetCenter(CATMathPoint        & oCenter) const ;


    //  A radius
    // -------------------
    virtual  HRESULT  SetRadius(const float           iRadius) ;
    virtual  HRESULT  GetRadius(float               & oRadius) const ;


    //  A repere defined by its 2 vectors
    // ----------------------------------
    //  iNormal represents the normal of the plane
    //  iAxis   represents the beginning of the circle.
    //
    virtual  HRESULT  SetPlanar(const CATMathVector & iNormal ,
                                const CATMathVector & iAxis );

    virtual  HRESULT  GetPlanar(CATMathVector       & oNormal ,
                                CATMathVector       & oAxis  ) const;    

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCircle(const CAAESysCircle &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCircle & operator = (const CAAESysCircle &iObjectToCopy);

  private:

    float           _Radius ;
    CATMathPoint    _Center ;

    CATMathVector   _Normal ;
    CATMathVector   _Axis ;


};
#endif
