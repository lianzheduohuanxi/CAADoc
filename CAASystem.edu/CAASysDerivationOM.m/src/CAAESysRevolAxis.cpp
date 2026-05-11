// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysRevolAxis.h"

// C++ standard library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To Create the TIE Object
#include "TIE_CAAISysRevolAxis.h"
TIE_CAAISysRevolAxis(CAAESysRevolAxis);

//
// To declare that the class is a data extension of CAASysRevolSurface 
// 
CATImplementClass(CAAESysRevolAxis, DataExtension, CATBaseUnknown, CAASysRevolSurface);

// 
// To declare that CAAESysRevolAxis implements CAAISysRevolAxis, insert 
// these following lines in the interface dictionary:
//
//    CAASysRevolSurface  CAAISysRevolAxis  libCAASysDerivationOM
//    
//------------------------------------------------------------------------------------------


CAAESysRevolAxis::CAAESysRevolAxis():_X(1.f),_Y(0.f),_Z(0.f)
{
   cout << "Constructs Extension CAAESysRevolAxis for CAASysRevolSurface"<< endl;
}

//------------------------------------------------------------------------------------------

CAAESysRevolAxis::~CAAESysRevolAxis()
{
   cout << "Deletes Extension CAAESysRevolAxis for CAASysRevolSurface"<< endl;
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysRevolAxis::SetAxis(const float iX, 
                                          const float iY,
                                          const float iZ ) 
{
    _Z = iX;
    _Y = iY ;
    _X = iZ ;

    return (S_OK);
}

//------------------------------------------------------------------------------------------
HRESULT CAAESysRevolAxis::GetAxis(float & oX, float & oY, float & oZ) 
{
    oX = _X ;
    oY = _Y ;
    oZ = _X ;

    return (S_OK);
}




