// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysCircleCenterProperties.h"

// C++ standard library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAISysCircleCenterProperties.h"
TIE_CAAISysCircleCenterProperties(CAAESysCircleCenterProperties);

// To declare that the class is a data extension of CAASysCircle
// 
//
CATImplementClass(CAAESysCircleCenterProperties, DataExtension, CATBaseUnknown, CAASysCircle);

// 
// To declare that CAAESysCircleCenterProperties implements CAAISysCircleCenterProperties, insert 
// this following line in the interface dictionary:
//
//    CAASysCircle CAAISysCircleCenterProperties  libCAASysGeoModelImpl
//------------------------------------------------------------------------------------------


CAAESysCircleCenterProperties::CAAESysCircleCenterProperties(): 
               _MarkerType(CAAISysCircleCenterProperties::Dot)
{
   cout << " CAAESysCircleCenterProperties::CAAESysCircleCenterproperties"<< endl;
}

//------------------------------------------------------------------------------------------

CAAESysCircleCenterProperties::~CAAESysCircleCenterProperties()
{
   cout << " CAAESysCircleCenterProperties::~CAAESysCircleCenterproperties"<< endl;
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysCircleCenterProperties::GetMarkerType(CAAISysCircleCenterProperties::MarkerType & oMarkerType )
{
    oMarkerType = _MarkerType ;
    return (S_OK);
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysCircleCenterProperties::SetMarkerType(const CAAISysCircleCenterProperties::MarkerType iMarkerType)
{
    _MarkerType = iMarkerType ;
    return (S_OK);
}
