// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysEllipse.h"

//C++ standard library
#include "iostream.h"


//----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysEllipse.h"
TIE_CAAISysEllipse(CAAESysEllipse);

// To declare that the class is a data extension of CAASysEllipse
//
CATImplementClass(CAAESysEllipse, DataExtension, CATBaseUnknown, CAASysEllipse);

// 
// To declare that CAAESysEllipse implements CAAISysEllipse, insert 
// the following line in the interface dictionary:
//
//    CAASysEllipse CAAISysEllipse libCAASysGeoModelImpl
//
//----------------------------------------------------------------------------

CAAESysEllipse::CAAESysEllipse() : _XRadius(0.f),_YRadius(0.f)
{
  cout << "CAAESysEllipse::CAAESysEllipse" << endl;
}

CAAESysEllipse::~CAAESysEllipse()
{
  cout << "CAAESysEllipse::~CAAESysEllipse" << endl;
}

HRESULT  CAAESysEllipse::SetCenter(const CATMathPoint & iCenter) 
{
	_Center = iCenter ;
	return S_OK;
}

HRESULT  CAAESysEllipse::SetRadius(const float iXRadius, const float iYRadius) 
{
	_XRadius = iXRadius ;
	_YRadius = iYRadius ;
      return S_OK;
}
	
HRESULT  CAAESysEllipse::SetPlanar(const CATMathVector & iNormal , 
                                  const CATMathVector & iAxis) 
{
	_Normal = iNormal ;
	_Axis   = iAxis;
	return S_OK;
}

    
HRESULT  CAAESysEllipse::GetCenter(CATMathPoint & oCenter) const
{
	oCenter = _Center;
	return S_OK;
}
	
HRESULT  CAAESysEllipse::GetRadius(float & oXRadius,float & oYRadius) const
{
	oXRadius = _XRadius ;
	oYRadius = _YRadius ;
	return S_OK;
}
	
HRESULT  CAAESysEllipse::GetPlanar(CATMathVector & oNormal ,
                                  CATMathVector & oAxis) const
{
	oNormal = _Normal ;
	oAxis   = _Axis ;  
	return S_OK;
}







