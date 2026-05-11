#ifndef CAAESysEllipse_H
#define CAAESysEllipse_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysEllipse component and implementing the 
//  CAAISysEllipse interface.
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


class CAAESysEllipse : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysEllipse();
    virtual ~CAAESysEllipse();

    // The ellipse is represented by:
    // ------------------------------

    // A Point center
    // ---------------
    virtual  HRESULT  SetCenter(const CATMathPoint  & iCenter) ;
    virtual  HRESULT  GetCenter(CATMathPoint & oCenter)             const ;


    // A radius along X and Y axis
    // ---------------------------
    virtual  HRESULT  SetRadius(const float  iXRadius, const float iYRadius) ;
    virtual  HRESULT  GetRadius(float &oXRadius, float & oYRadius) const ;


    // A Repere 
    // --------
    // iNormal defined the normal of the plane
    // iAxis   defined the X axis. The Y axis = iNormal ^ iAxis .
    //
    virtual  HRESULT  SetPlanar(const CATMathVector & iNormal ,
	                        const CATMathVector & iAxis);

    virtual  HRESULT  GetPlanar(CATMathVector & oNormal ,
                                CATMathVector & oAxis)              const;    

   
  private:
  
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysEllipse(const CAAESysEllipse &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysEllipse & operator = (const CAAESysEllipse &iObjectToCopy);

  private:

    float           _XRadius,_YRadius  ;
    CATMathPoint    _Center ;
    CATMathVector   _Normal ;
    CATMathVector   _Axis ;


};
#endif
