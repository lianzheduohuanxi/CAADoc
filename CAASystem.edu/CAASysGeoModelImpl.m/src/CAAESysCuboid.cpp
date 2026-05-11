// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAESysCuboid.h"

// C++ standard library
#include <iostream.h>

//-----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysCuboid.h"
TIE_CAAISysCuboid(CAAESysCuboid);

// To declare that the class is a data extension of CAASysCuboid
//
CATImplementClass(CAAESysCuboid, DataExtension, CATBaseUnknown, CAASysCuboid);
//
// To declare that CAAESysCuboid implements CAAISysCuboid, insert 
// the following line in the interface dictionary:
//
//    CAASysCuboid CAAISysCuboid  libCAASysGeoModelImpl
//
//-----------------------------------------------------------------------------

CAAESysCuboid::CAAESysCuboid()
{
   cout << "CAAESysCuboid::CAAESysCuboid" << endl ;
}

//-----------------------------------------------------------------------------

CAAESysCuboid::~CAAESysCuboid()
{
   cout << "CAAESysCuboid::~CAAESysCuboid" << endl ;
}

//-----------------------------------------------------------------------------

HRESULT CAAESysCuboid::GetOrigin(CATMathPoint & oOrigin) const
{
   oOrigin = _Origin ;
   return S_OK;
}

//-----------------------------------------------------------------------------

HRESULT CAAESysCuboid::SetOrigin(const CATMathPoint & iOrigin) 
{
   _Origin = iOrigin  ;
   return S_OK;
}

//-----------------------------------------------------------------------------

HRESULT  CAAESysCuboid::SetVectors(const CATMathVector & iV1, 
								  const CATMathVector & iV2,
								  const CATMathVector & iV3) 
{
   _V1 = iV1 ;
   _V2 = iV2 ;
   _V3 = iV3 ;
 
   return S_OK;
}

//-----------------------------------------------------------------------------

HRESULT  CAAESysCuboid::GetVectors( CATMathVector & oV1, 
								   CATMathVector & oV2,
								   CATMathVector & oV3) const
{
   oV1 = _V1 ;
   oV2 = _V2 ;
   oV3 = _V3 ;
 
   return S_OK;
}
//-----------------------------------------------------------------------------

