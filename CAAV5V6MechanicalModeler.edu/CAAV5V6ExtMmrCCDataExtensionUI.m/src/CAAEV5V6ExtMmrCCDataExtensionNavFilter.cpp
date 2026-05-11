//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrCCDataExtensionNavFilter:
// Implementation of CATINavigateFilter for CAAV5V6ExtMmrCCDataExtensions
//
//
//========================================================================
// Implementation of CATINavigateFilter
//========================================================================

#include "CAAEV5V6ExtMmrCCDataExtensionNavFilter.h"

CATImplementClass(CAAEV5V6ExtMmrCCDataExtensionNavFilter, DataExtension, CATINavigateFilter, CAAV5V6ExtMmrCCDataExtension);
CATImplementBOA(CATINavigateFilter,CAAEV5V6ExtMmrCCDataExtensionNavFilter); 

CAAEV5V6ExtMmrCCDataExtensionNavFilter::CAAEV5V6ExtMmrCCDataExtensionNavFilter()
{
}
CAAEV5V6ExtMmrCCDataExtensionNavFilter::~CAAEV5V6ExtMmrCCDataExtensionNavFilter()
{
}

CATBoolean CAAEV5V6ExtMmrCCDataExtensionNavFilter::IsShown( CATINavigateObject* iFather){
    //Not visible beneath the CombinedCurve 
    return TRUE;
}
