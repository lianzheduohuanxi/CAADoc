// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysSurfaceProperties.h"

// C++ standard library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To Create the TIE Object
#include "TIE_CAAISysSurfaceProperties.h"
TIE_CAAISysSurfaceProperties(CAAESysSurfaceProperties);

//
// To declare that the class is a data extension of CAASysSurface and ...
// 
CATImplementClass(CAAESysSurfaceProperties, DataExtension, CATBaseUnknown, CAASysSurface);

// 
// To declare that CAAESysSurfaceProperties implements CAAISysSurfaceProperties, insert 
// these following lines in the interface dictionary:
//
//    CAASysSurface  CAAISysSurfaceProperties  libCAASysDerivationOM
//    
//------------------------------------------------------------------------------------------


CAAESysSurfaceProperties::CAAESysSurfaceProperties(): _Red(128),_Blue(0),_Green(0)
{
   cout << "Constructs Extension CAAESysSurfaceProperties for CAASysSurface"<< endl;
}

//------------------------------------------------------------------------------------------
CAAESysSurfaceProperties::~CAAESysSurfaceProperties()
{
   cout << "Deletes Extension CAAESysSurfaceProperties for CAASysSurface"<< endl;
}

//------------------------------------------------------------------------------------------
HRESULT CAAESysSurfaceProperties::SetColor(const int iRed, const int iGreen, const int iBlue ) 
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
HRESULT CAAESysSurfaceProperties::GetColor(int & oRed, int & oGreen, int & oBlue) 
{
    oRed   = _Red ;
    oGreen = _Green ;
    oBlue  = _Blue ;

    return (S_OK);
}


