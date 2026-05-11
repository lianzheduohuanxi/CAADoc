#ifndef CAAEV5V6ExtMmrMultiMeasureNavigateObject_H
#define CAAEV5V6ExtMmrMultiMeasureNavigateObject_H

//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrMultiMeasureNavigateObject:
// Implement CATINavigateObject for CAAV5V6ExtMmrMultiMeasure
//
//========================================================================

// System framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerNavigator framework 
#include "CATINavigateObject.h"

class CAAEV5V6ExtMmrMultiMeasureNavigateObject: public CATINavigateObject
{
public :
	CATDeclareClass;

	//-------------------------------------------------
	//____________Constructor/Destructor_______________
	//-------------------------------------------------
	CAAEV5V6ExtMmrMultiMeasureNavigateObject();
	virtual ~CAAEV5V6ExtMmrMultiMeasureNavigateObject();

	//-------------------------------------------------
	//_________Interfaces CATINavigateObject___________
	//-------------------------------------------------
	CATLISTV(CATBaseUnknown_var)* GetChildren ();
	CATListOfCATUnicodeString* GetIdentificators();

};
#endif
