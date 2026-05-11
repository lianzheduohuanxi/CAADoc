// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework 
#include "CAAESysSurfaceArea.h"

// C++ standard library
#include <iostream.h>

//------------------------------------------------------------------------------------------
// To Create the TIE Object
#include "TIE_CAAISysSurfaceArea.h"
TIE_CAAISysSurfaceArea(CAAESysSurfaceArea);

//
// To declare that the class is a data extension of CAASysSurface 
// 
CATImplementClass(CAAESysSurfaceArea, DataExtension, CATBaseUnknown, CAASysSurface);

// 
// To declare that CAAESysSurfaceArea implements CAAISysSurfaceArea, insert 
// these following lines in the interface dictionary:
//
//    CAASysSurface  CAAISysSurfaceArea  libCAASysDerivationOM
//    
//------------------------------------------------------------------------------------------


CAAESysSurfaceArea::CAAESysSurfaceArea()
{
   cout << "Constructs Extension CAAESysSurfaceArea for CAASysSurface"<< endl;
}

//------------------------------------------------------------------------------------------

CAAESysSurfaceArea::~CAAESysSurfaceArea()
{
   cout << "Deletes Extension CAAESysSurfaceArea for CAASysSurface"<< endl;
}

//------------------------------------------------------------------------------------------

HRESULT CAAESysSurfaceArea::ComputeArea(float & oArea)
{
    cout << "Computes Area for CAASysSurface"<< endl;

    oArea = 1.f ;

    return (S_OK);
}




