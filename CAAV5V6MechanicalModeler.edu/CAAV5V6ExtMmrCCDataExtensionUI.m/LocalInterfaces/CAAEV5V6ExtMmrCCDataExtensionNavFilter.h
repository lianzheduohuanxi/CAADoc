#ifndef CAAEV5V6ExtMmrCCDataExtensionNavFilter_H
#define CAAEV5V6ExtMmrCCDataExtensionNavFilter_H

//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrCCDataExtensionNavFilter:
// Implementation of CATINavigateFilter for CAAV5V6ExtMmrCCDataExtension
//
//========================================================================

#include "CATINavigateFilter.h"

class CAAEV5V6ExtMmrCCDataExtensionNavFilter: public CATINavigateFilter
{
public :
	CATDeclareClass;

	//-------------------------------------------------
	//____________Constructor/Destructor_______________
	//-------------------------------------------------
	CAAEV5V6ExtMmrCCDataExtensionNavFilter();
	virtual ~CAAEV5V6ExtMmrCCDataExtensionNavFilter();
    
    CATBoolean IsShown( CATINavigateObject* iFather);
};
#endif
