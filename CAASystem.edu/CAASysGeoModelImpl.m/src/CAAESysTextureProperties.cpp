// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysTextureProperties.h"

// C++ standard library
#include <iostream.h>

//---------------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAISysTextureProperties.h"
TIE_CAAISysTextureProperties(CAAESysTextureProperties);

// To declare that the class is a data extension of CAASysEllipse and CAASysCircle 
// 
CATBeginImplementClass(CAAESysTextureProperties, DataExtension, CATBaseUnknown, CAASysCircle);
CATAddClassExtension(CAASysEllipse) ;
CATEndImplementClass(CAAESysTextureProperties);

// 
// To declare that CAAESysTextureProperties implements CAAISysTextureProperties, insert 
// these following lines in the interface dictionary:
//
//    CAASysEllipse CAAISysTextureProperties  libCAASysGeoModelImpl
//    CAASysCircle  CAAISysTextureProperties  libCAASysGeoModelImpl
//
//------------------------------------------------------------------------------------------


CAAESysTextureProperties::CAAESysTextureProperties(): _IsMetal(1),_IsRough(0)
{
   cout << "CAAESysTextureProperties::CAAESysTextureProperties"<< endl;
}

//------------------------------------------------------------------------------------------
CAAESysTextureProperties::~CAAESysTextureProperties()
{
   cout << "CAAESysTextureProperties::~CAAESysTextureProperties"<< endl;
}

HRESULT CAAESysTextureProperties::SetMetal(const int iIsMetal) 
{
    _IsMetal = iIsMetal ;
    return (S_OK);
}

//------------------------------------------------------------------------------------------
HRESULT CAAESysTextureProperties::SetRough(const int iIsRough) 
{
    _IsRough = iIsRough ;
    return (S_OK);
}
//------------------------------------------------------------------------------------------
HRESULT CAAESysTextureProperties::GetMetal(int & oIsMetal) 
{
    oIsMetal = _IsMetal;
    return (S_OK);
}
//------------------------------------------------------------------------------------------
HRESULT CAAESysTextureProperties::GetRough(int & oIsRough) 
{
    oIsRough = _IsRough;
    return (S_OK);
}
//------------------------------------------------------------------------------------------
