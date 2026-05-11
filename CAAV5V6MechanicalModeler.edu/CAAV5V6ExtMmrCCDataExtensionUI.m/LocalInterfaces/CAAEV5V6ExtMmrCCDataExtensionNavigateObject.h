#ifndef CAAEV5V6ExtMmrCCDataExtensionNavigateObject_H
#define CAAEV5V6ExtMmrCCDataExtensionNavigateObject_H

//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrCCDataExtensionNavigateObject:
// Implementation CATINavigateObject for CAAV5V6ExtMmrCCDataExtension
//
//========================================================================

// System framework
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerNavigator framework 
#include "CATINavigateObject.h"

class CAAEV5V6ExtMmrCCDataExtensionNavigateObject: public CATINavigateObject
{
public :
	CATDeclareClass;

	//-------------------------------------------------
	//____________Constructor/Destructor_______________
	//-------------------------------------------------
	CAAEV5V6ExtMmrCCDataExtensionNavigateObject();
	virtual ~CAAEV5V6ExtMmrCCDataExtensionNavigateObject();

	//-------------------------------------------------
	//_________Interfaces CATINavigateObject___________
	//-------------------------------------------------
	CATLISTV(CATBaseUnknown_var)* GetChildren ();
	CATListOfCATUnicodeString* GetIdentificators();

};
#endif
