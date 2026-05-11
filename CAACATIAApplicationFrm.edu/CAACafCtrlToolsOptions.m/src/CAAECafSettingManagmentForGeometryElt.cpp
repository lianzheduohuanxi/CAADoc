// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAECafSettingManagmentForGeometryElt.h"


//--------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIIniSettingManagment.h"
TIE_CATIIniSettingManagment(CAAECafSettingManagmentForGeometryElt);

// To declare that the class is a data extension of CAACafGeometryEltSettingCtrl
//
CATImplementClass(CAAECafSettingManagmentForGeometryElt,DataExtension,CATBaseUnknown,CAACafGeometryEltSettingCtrl);

// 
// To declare that CAAECafSettingManagmentForGeometryElt implements CATIIniSettingManagment, 
// insert these following lines in the interface dictionary:
//
//    CAACafGeometryEltSettingCtrl     CATIIniSettingManagment  libCAACafCtrlToolsOptions
//
//--------------------------------------------------------------------

CAAECafSettingManagmentForGeometryElt::CAAECafSettingManagmentForGeometryElt():CATEIniSettingManagment("CAACafGeometryElt")
{
}

//--------------------------------------------------------------------

CAAECafSettingManagmentForGeometryElt::~CAAECafSettingManagmentForGeometryElt()
{
}




