// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVisModelSphere.h"

// Visualization Framework
#include "CATMathPointf.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVisModelSphere.h"
TIE_CAAIVisModelSphere(CAAEVisModelSphere);

// To declare that the class is a data extension of CAAVisModelSphere
//
CATImplementClass(CAAEVisModelSphere,DataExtension,CATBaseUnknown,CAAVisModelSphere);

// 
// To declare that CAAEVisModelSphere implements CAAIVisModelSphere, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelSphere CAAIVisModelSphere  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVisModelSphere::CAAEVisModelSphere():_Center(0.f,0.f,0.f),_Radius(0.f)
{
  cout << "CAAEVisModelSphere::CAAEVisModelSphere" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVisModelSphere::~CAAEVisModelSphere()
{
  cout << "CAAEVisModelSphere::~CAAEVisModelSphere" << endl;
}

//----------------------------------------------------------------------------
HRESULT  CAAEVisModelSphere::SetCenter(const CATMathPointf & iCenter) 
{
	_Center = iCenter ;
	return S_OK;
}

//----------------------------------------------------------------------------

HRESULT  CAAEVisModelSphere::SetRadius(const float iRadius) 
{
	_Radius = iRadius ;
	return S_OK;
}
	
//----------------------------------------------------------------------------

HRESULT CAAEVisModelSphere::GetCenter(CATMathPointf & oCenter) const 
{
	oCenter = _Center ;
	return S_OK;
}

//----------------------------------------------------------------------------
	
HRESULT CAAEVisModelSphere::GetRadius(float & oRadius) const
{
	oRadius = _Radius ;
	return S_OK;
}
