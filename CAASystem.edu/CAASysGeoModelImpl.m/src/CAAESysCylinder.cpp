// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysCylinder.h"

//C++ standard library
#include "iostream.h"

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysCylinder.h"
TIE_CAAISysCylinder(CAAESysCylinder);

// To declare that the class is a data extension of CAASysCylinder
//
CATImplementClass(CAAESysCylinder, DataExtension, CATBaseUnknown, CAASysCylinder);
// 
// To declare that CAAESysCylinder implements CAAISysCylinder, insert 
// the following line in the interface dictionary:
//
//    CAASysCylinder CAAISysCylinder  libCAASysGeoModelImpl
//
//------------------------------------------------------------------------------------

CAAESysCylinder::CAAESysCylinder() : _Radius(0)
{
  cout << "CAAESysCylinder::CAAESysCylinder" << endl;
}

//------------------------------------------------------------------------------------

CAAESysCylinder::~CAAESysCylinder()
{
  cout << "CAAESysCylinder::~CAAESysCylinder" << endl;
}

//------------------------------------------------------------------------------------

HRESULT  CAAESysCylinder::SetRadius(const float iRadius) 
{
	_Radius = iRadius ;
	return S_OK;
}
	
//------------------------------------------------------------------------------------

HRESULT CAAESysCylinder::GetRadius(float & oRadius) const
{
	oRadius = _Radius ;
	return S_OK;
}

//------------------------------------------------------------------------------------
	
HRESULT  CAAESysCylinder::GetBasePoint(CATMathPoint & oBasePoint )const
{
	oBasePoint = _BasePoint ;
	return S_OK;
}

//------------------------------------------------------------------------------------
	
HRESULT  CAAESysCylinder::SetBasePoint(const CATMathPoint & iBasePoint )
{
   _BasePoint = iBasePoint ;
   	return S_OK;
}	

//------------------------------------------------------------------------------------

HRESULT  CAAESysCylinder::GetTopPoint(CATMathPoint & oTopPoint )const
{
	oTopPoint = _TopPoint ;
	return S_OK;
}

//------------------------------------------------------------------------------------
	
HRESULT  CAAESysCylinder::SetTopPoint(const CATMathPoint & iTopPoint )
{
   _TopPoint = iTopPoint ;
   	return S_OK;
}	


