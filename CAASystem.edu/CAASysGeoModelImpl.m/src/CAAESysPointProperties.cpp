// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysPointProperties.h"

// C++ standard library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAISysPointProperties.h"
TIE_CAAISysPointProperties(CAAESysPointProperties);

// To declare that the class is a data extension of CAASysPoint
// 
//
CATImplementClass(CAAESysPointProperties, DataExtension, CATBaseUnknown, CAASysPoint);

// 
// To declare that CAAESysPointProperties implements CAAISysPointProperties, insert 
// this following line in the interface dictionary:
//
//    CAASysPoint CAAISysPointProperties  libCAASysGeoModelImpl
//------------------------------------------------------------------------------------------


CAAESysPointProperties::CAAESysPointProperties(): _MarkerType(CAAISysPointProperties::Cross)
{
   cout << " CAAESysPointProperties::CAAESysPointproperties"<< endl;
}

//------------------------------------------------------------------------------------------

CAAESysPointProperties::~CAAESysPointProperties()
{
   cout << " CAAESysPointProperties::~CAAESysPointproperties"<< endl;
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysPointProperties::GetMarkerType(CAAISysPointProperties::MarkerType & oMarkerType )
{
    oMarkerType = _MarkerType ;
    return (S_OK);
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysPointProperties::SetMarkerType(const CAAISysPointProperties::MarkerType iMarkerType)
{
    _MarkerType = iMarkerType ;
    return (S_OK);
}
