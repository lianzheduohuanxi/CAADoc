// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysColorProperties.h"

// C++ stantard library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To Create the TIE Object
#include "TIE_CAAISysColorProperties.h"
TIE_CAAISysColorProperties(CAAESysColorProperties);

// To declare that the class is a data extension of CAASysCircle and ...
// 
CATBeginImplementClass(CAAESysColorProperties, DataExtension, CATBaseUnknown, CAASysCircle);
CATAddClassExtension(CAASysEllipse) ;
CATAddClassExtension(CAASysLine) ;
CATAddClassExtension(CAASysPolyline) ;
CATEndImplementClass(CAAESysColorProperties);

// 
// To declare that CAAESysColorProperties implements CAAISysColorProperties, insert 
// these following lines in the interface dictionary:
//
//    CAASysCircle  CAAISysColorProperties  libCAASysGeoModelImpl
//    ...

//------------------------------------------------------------------------------------------


CAAESysColorProperties::CAAESysColorProperties(): _Red(255),_Blue(255),_Green(255)
{
   cout << " CAAESysColorProperties::CAAEsysColorProperties"<< endl;
}

//------------------------------------------------------------------------------------------
CAAESysColorProperties::~CAAESysColorProperties()
{
   cout << " CAAESysColorProperties::~CAAEsysColorProperties"<< endl;
}

//------------------------------------------------------------------------------------------
HRESULT CAAESysColorProperties::SetColor(const int iRed, const int iGreen, const int iBlue ) 
{
    if ( (iRed < 0   ) || ( iRed > 255   ) ) return E_FAIL ;
    if ( (iGreen < 0 ) || ( iGreen > 255 ) ) return E_FAIL ;
    if ( (iBlue < 0  ) || ( iBlue > 255  ) ) return E_FAIL ;

    _Red   = iRed ;
    _Green = iGreen ;
    _Blue  = iBlue ;

    return (S_OK);
}

//------------------------------------------------------------------------------------------
HRESULT CAAESysColorProperties::GetColor(int & oRed, int & oGreen, int & oBlue) 
{
    oRed   = _Red ;
    oGreen = _Green ;
    oBlue  = _Blue ;

    return (S_OK);
}


