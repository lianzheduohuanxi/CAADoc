#ifndef CAAESysCuboid_H
#define CAAESysCuboid_H

// COPYRIGHT DASSAULT SYSTEMES 1999
     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysCuboid component and implementing the 
//  CAAISysCuboid interface.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  SetOrigin/GetOrigin
//  SetCuboid/GetCuboid
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown

// Mathematics Framework
#include "CATMathPoint.h"     //Needed by SetOrigin & GetOrigin
#include "CATMathVector.h" //Needed by SetCuboid & GetCuboid

class CAAESysCuboid : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysCuboid();
    virtual ~CAAESysCuboid();

    // The Cuboid is defined by:
    // ------------------------
    
    // It's origin  in the space
    // -------------------------
    virtual  HRESULT  SetOrigin(const CATMathPoint & iOrigin) ;
    virtual  HRESULT  GetOrigin(CATMathPoint & oOrigin) const ;

    // Width, Depth, Height
    // -------------------------
    virtual  HRESULT  SetVectors (const CATMathVector & iV1 ,
                                  const CATMathVector & iV2,
                                  const CATMathVector & iV3);

    virtual  HRESULT  GetVectors(CATMathVector & oV1 ,
                                 CATMathVector & oV2,
                                 CATMathVector & oV3) const ;    


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCuboid(const CAAESysCuboid &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysCuboid & operator = (const CAAESysCuboid &iObjectToCopy);

  private:

    CATMathPoint      _Origin ;
    CATMathVector     _V1,_V2,_V3 ;

};
#endif
