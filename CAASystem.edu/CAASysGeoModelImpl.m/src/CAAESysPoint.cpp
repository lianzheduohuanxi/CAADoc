// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAESysPoint.h"

// C++ standard library
#include <iostream.h>

//-----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CAAISysPoint.h"
TIE_CAAISysPoint(CAAESysPoint);

// To declare that the class is a data extension of CAASysPoint
//
CATImplementClass(CAAESysPoint, DataExtension, CATBaseUnknown, CAASysPoint);
//
// To declare that CAAESysPoint implements CAAISysPoint, insert 
// the following line in the interface dictionary:
//
//    CAASysPoint CAAISysPoint  libCAASysGeoModelImpl
//
//-----------------------------------------------------------------------------

CAAESysPoint::CAAESysPoint(): _X(0.0f),_Y(0.0f),_Z(0.0f)
{
   cout << "CAAESysPoint::CAAESysPoint" << endl ;
}


CAAESysPoint::~CAAESysPoint()
{
   cout << "CAAESysPoint::~CAAESysPoint" << endl ;
}

HRESULT CAAESysPoint::GetCoord(float & oX, float & oY, float & oZ) const
{
   oX = _X ;
   oY = _Y ;
   oZ = _Z ;
   return S_OK;
}

HRESULT CAAESysPoint::SetCoord(const float iX, const float iY, const float iZ) 
{
   _X = iX ;
   _Y = iY ;
   _Z = iZ ;
   return S_OK;
}
