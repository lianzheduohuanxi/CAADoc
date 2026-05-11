// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAECafSettingManagmentForGeometryView.h"


//--------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIIniSettingManagment.h"
TIE_CATIIniSettingManagment(CAAECafSettingManagmentForGeometryView);

// To declare that the class is a data extension of CAACafGeometryViewSettingCtrl
//
CATImplementClass(CAAECafSettingManagmentForGeometryView,DataExtension,CATBaseUnknown,CAACafGeometryViewSettingCtrl);

// 
// To declare that CAAECafSettingManagmentForGeometryView implements CATIIniSettingManagment, 
// insert these following lines in the interface dictionary:
//
//    CAACafGeometryViewSettingCtrl     CATIIniSettingManagment  libCAACafCtrlToolsOptions
//
//--------------------------------------------------------------------

CAAECafSettingManagmentForGeometryView::CAAECafSettingManagmentForGeometryView():CATEIniSettingManagment("CAACafGeometryView")
{
}

//--------------------------------------------------------------------

CAAECafSettingManagmentForGeometryView::~CAAECafSettingManagmentForGeometryView()
{
}




