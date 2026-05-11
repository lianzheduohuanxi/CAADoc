// COPYRIGHT DASSAULT SYSTEMES 1999

//LocalFramework
#include "CAAESysPlane.h"

//C++ Standard library
#include "iostream.h"


//---------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysPlane.h"
TIE_CAAISysPlane(CAAESysPlane);

// To declare that the class is a data extension of CAASysPlane
//
CATImplementClass(CAAESysPlane, DataExtension, CATBaseUnknown, CAASysPlane);
// 
// To declare that CAAESysPlane implements CAAISysPlane, insert 
// the following line in the interface dictionary:
//
//    CAASysPlane CAAISysPlane  libCAASysGeoModelImpl
//

//---------------------------------------------------------------------------

CAAESysPlane::CAAESysPlane() 
{
  cout << "CAAESysPlane::CAAESysPlane" << endl;
}

CAAESysPlane::~CAAESysPlane()
{
  cout << "CAAESysPlane::~CAAESysPlane" << endl;
}

HRESULT  CAAESysPlane::SetOrigin(const CATMathPoint & iOrigin) 
{
   _Origin = iOrigin  ;
   return S_OK;
}


HRESULT  CAAESysPlane::SetPlane(const CATMathVector & iU, const CATMathVector & iV) 
{
   _U = iU ;
   _V = iV ;
   return S_OK;
}
    
HRESULT CAAESysPlane::GetOrigin(CATMathPoint & oOrigin) 
{
   oOrigin = _Origin ;
   return S_OK;
}
	
HRESULT CAAESysPlane::GetPlane(CATMathVector & oU, CATMathVector & oV) 
{
   oU = _U ;
   oV = _V ;
   return S_OK;
}





