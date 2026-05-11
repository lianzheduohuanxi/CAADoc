#ifndef CAAEMmrCCDataExtensionNavFilter_H
#define CAAEMmrCCDataExtensionNavFilter_H

//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//=======================================================================
//
// Class  CAAEMmrCCDataExtensionNavFilter:
// Implementation CATINavigateFilter pour les MmrCCDataExtensions
//
//========================================================================

#include "CATINavigateFilter.h"

class CAAEMmrCCDataExtensionNavFilter: public CATINavigateFilter
{
public :
	CATDeclareClass;

	//-------------------------------------------------
	//____________Constructor/Destructor_______________
	//-------------------------------------------------
	CAAEMmrCCDataExtensionNavFilter();
	virtual ~CAAEMmrCCDataExtensionNavFilter();
    
    CATBoolean IsShown( CATINavigateObject* iFather);
};
#endif
