#ifndef CAAESysPlane_H
#define CAAESysPlane_H

// COPYRIGHT DASSAULT SYSTEMES 1999
     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysPlane component and implementing the 
//  CAAISysPlane interface.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  SetOrigin/GetOrigin
//  SetPlane/GetPlane
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by SetOrigin & GetOrigin
#include "CATMathVector.h"    //Needed by SetPlane & GetPlane

class CAAESysPlane : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysPlane();
    virtual ~CAAESysPlane();

    // The plane is defined by:
    // ------------------------
    
    // It's origin  in the space
    // -------------------------
    virtual  HRESULT  SetOrigin(const CATMathPoint & iOrigin) ;
    virtual  HRESULT  GetOrigin(CATMathPoint & oOrigin)  ;

    // It's U and V axis
    // -------------------------
    virtual  HRESULT  SetPlane (const CATMathVector & iU ,
	                        const CATMathVector & iV);

    virtual  HRESULT  GetPlane (CATMathVector & oU ,
	                        CATMathVector & oV) ;    


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysPlane(const CAAESysPlane &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysPlane & operator = (const CAAESysPlane &iObjectToCopy);

  private:

    CATMathPoint      _Origin ;
    CATMathVector  _U,_V ;

};
#endif
