#ifndef CAAESysCylinder_H
#define CAAESysCylinder_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysCylinder component and implementing the 
//  CAAISysCylinder interface.
//
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by SetBasePoint & GetBasePoint

class CAAESysCylinder : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCylinder();
    virtual ~CAAESysCylinder();

    // The Cylinder is defined by: 
    // ------------------------

    //  A radius
    // -------------------
    virtual  HRESULT  SetRadius(const float           iRadius) ;
    virtual  HRESULT  GetRadius(float               & oRadius) const ;


    // The extrusion line is defined between the base and the top point
    // ----------------------------------------------------------------

    virtual  HRESULT     SetBasePoint(const CATMathPoint & iBasePoint ) ;
    virtual  HRESULT     GetBasePoint(CATMathPoint & oBasePoint ) const  ;
  
    virtual  HRESULT     SetTopPoint(const CATMathPoint & iTopPoint ) ;
    virtual  HRESULT     GetTopPoint(CATMathPoint & oTopPoint )   const ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCylinder(const CAAESysCylinder &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCylinder & operator = (const CAAESysCylinder &iObjectToCopy);

  private:

    float           _Radius ;
    CATMathPoint    _BasePoint ;
    CATMathPoint    _TopPoint ;



};
#endif
