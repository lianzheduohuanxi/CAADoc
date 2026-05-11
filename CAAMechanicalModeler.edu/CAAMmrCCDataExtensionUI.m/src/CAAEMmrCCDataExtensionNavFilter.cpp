//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//=======================================================================
//
// Class  CAAEMmrCCDataExtensionNavFilter:
// Implementation CATINavigateFilter pour les MmrCCDataExtensions
//
//
//========================================================================
// Implementation de CATINavigateFilter
//========================================================================

#include "CAAEMmrCCDataExtensionNavFilter.h"

CATImplementClass(CAAEMmrCCDataExtensionNavFilter, DataExtension, CATINavigateFilter, CAAMmrCCDataExtension);
CATImplementBOA(CATINavigateFilter,CAAEMmrCCDataExtensionNavFilter); 

CAAEMmrCCDataExtensionNavFilter::CAAEMmrCCDataExtensionNavFilter()
{
}
CAAEMmrCCDataExtensionNavFilter::~CAAEMmrCCDataExtensionNavFilter()
{
}

CATBoolean CAAEMmrCCDataExtensionNavFilter::IsShown( CATINavigateObject* iFather){
    //not viisible beneath the Combined Curve
    return TRUE;
}
