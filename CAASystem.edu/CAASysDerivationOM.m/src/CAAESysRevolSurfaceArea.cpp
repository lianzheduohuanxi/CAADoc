// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysRevolSurfaceArea.h"

// C++ Standrad Library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To Create the TIE Object
#include "TIE_CAAISysSurfaceArea.h"
TIE_CAAISysSurfaceArea(CAAESysRevolSurfaceArea);

//
// To declare that the class is a data extension of CAASysRevolSurface 
// 
CATImplementClass(CAAESysRevolSurfaceArea, DataExtension, CATBaseUnknown, CAASysRevolSurface);

// 
// To declare that CAAESysSurfaceArea implements CAAISysSurfaceArea, insert 
// these following lines in the interface dictionary:
//
//    CAASysRevolSurface  CAAISysSurfaceArea  libCAASysDerivationOM
//    
//------------------------------------------------------------------------------------------


CAAESysRevolSurfaceArea::CAAESysRevolSurfaceArea()
{
   cout << "Constructs Extension CAAESysRevolSurfaceArea for CAASysRevolSurface"<< endl;
}

//------------------------------------------------------------------------------------------

CAAESysRevolSurfaceArea::~CAAESysRevolSurfaceArea()
{
   cout << "Deletes Extension CAAESysRevolSurfaceArea for CAASysRevolSurfacea"<< endl;
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysRevolSurfaceArea::ComputeArea(float & oArea)
{
    cout << "Computes Area for CAASysRevolSurface"<< endl;

    oArea = 2.f ;

    return (S_OK);
}




