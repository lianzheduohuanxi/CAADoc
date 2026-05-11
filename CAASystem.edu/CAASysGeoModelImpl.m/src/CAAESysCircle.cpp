// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCircle.h"

//C++ standard library
#include "iostream.h"

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysCircle.h"
TIE_CAAISysCircle(CAAESysCircle);

// To declare that the class is a data extension of CAASysCircle
//
CATImplementClass(CAAESysCircle, DataExtension, CATBaseUnknown, CAASysCircle);
// 
// To declare that CAAESysCircle implements CAAISysCircle, insert 
// the following line in the interface dictionary:
//
//    CAASysCircle CAAISysCircle  libCAASysGeoModelImpl
//
//------------------------------------------------------------------------------------

CAAESysCircle::CAAESysCircle() : _Radius(0)
{
  cout << "CAAESysCircle::CAAESysCircle" << endl;
}

CAAESysCircle::~CAAESysCircle()
{
  cout << "CAAESysCircle::~CAAESysCircle" << endl;
}

HRESULT  CAAESysCircle::SetCenter(const CATMathPoint & iCenter) 
{
	_Center = iCenter ;
	return S_OK;
}

HRESULT  CAAESysCircle::SetRadius(const float iRadius) 
{
	_Radius = iRadius ;
	return S_OK;
}
	
HRESULT  CAAESysCircle::SetPlanar(const CATMathVector & iNormal , 
                                 const CATMathVector & iAxis) 
{
	_Normal= iNormal ;
	_Axis = iAxis ;	
	return S_OK;
}

    
HRESULT CAAESysCircle::GetCenter(CATMathPoint & oCenter) const 
{
	oCenter = _Center ;
	return S_OK;
}
	
HRESULT CAAESysCircle::GetRadius(float & oRadius) const
{
	oRadius = _Radius ;
	return S_OK;
}
	
HRESULT  CAAESysCircle::GetPlanar(CATMathVector & oNormal ,
                                 CATMathVector & oAxis) const
{
	oNormal = _Normal ;
	oAxis   = _Axis ;  
	return S_OK;
}







